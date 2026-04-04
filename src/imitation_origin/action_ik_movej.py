#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Replay normalized delta-actions from HDF5 on Piper via IK + move_j.

功能：
1) 读取 HDF5 中第一帧关节角（obs/q[0]）与全部 actions
2) 机械臂回零 -> move_j 到第一帧关节角
3) 每一步将 action 反归一化为 [dx,dy,dz,drotvec]
4) 与当前实时 tcp_pose 叠加得到目标末端位姿
5) URDF IK 求解关节角并通过 move_j 下发

并提供与 playTrajectory_pyagxarm_ik_movej.py 的执行逻辑对比说明。
"""

from __future__ import annotations

import argparse
import math
import sys
import time
from pathlib import Path
from typing import List, Sequence, Tuple

import h5py
import numpy as np

SRC_DIR = Path(__file__).resolve().parents[1]
if str(SRC_DIR) not in sys.path:
    sys.path.insert(0, str(SRC_DIR))

from robot_piper.piper_arm import PiperArm
from imitation_origin.playTrajectory_pyagxarm_ik_movej import (
    PiperUrdfIkSolver,
    clip_joints,
    get_joint_limits,
    wait_exit_teach_mode,
    wait_joints_near_home,
)


ACTION_POS_SCALE = np.array([0.01, 0.01, 0.01], dtype=np.float64)
ACTION_ROT_SCALE = np.array([0.8, 0.8, 0.8], dtype=np.float64)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="HDF5 action replay with IK + move_j")
    parser.add_argument(
        "--input",
        default="/home/flowing/piper/data/single_demo2/demo_001.hdf5",
        help="hdf5 path; if omitted, auto-discover latest .hdf5 under common data dirs",
    )
    parser.add_argument("--episode-name", default="demo_0")
    parser.add_argument("--channel", default="can0")
    parser.add_argument("--robot-name", default="piper")
    parser.add_argument("--tool-type", default="none")
    parser.add_argument(
        "--urdf-path",
        default=(
        "/home/flowing/piper/agx_arm_ws/install/agx_arm_description/share/agx_arm_description/"
        "agx_arm_urdf/piper_l/urdf/piper_l_description.urdf"
        ),
    )
    parser.add_argument("--speed", type=int, default=20)
    parser.add_argument("--control_dt", type=float, default=0.05)
    parser.add_argument("--max-steps", type=int, default=0, help="0=all actions")
    parser.add_argument("--home-timeout", type=float, default=25.0)
    parser.add_argument("--home-tol", type=float, default=0.03)
    parser.add_argument("--ik-pos-hard", type=float, default=0.025)
    parser.add_argument("--ik-rot-hard", type=float, default=0.30)
    parser.add_argument("--print-every", type=int, default=20)
    parser.add_argument("--dry-run", action="store_true")
    parser.add_argument("--compare", action="store_true", help="print comparison with playTrajectory script")
    return parser.parse_args()


def resolve_hdf5_input(input_path: str | None) -> Path:
    if input_path is not None:
        return Path(input_path).expanduser().resolve()

    repo_root = Path(__file__).resolve().parents[2]
    candidates = [
        repo_root / "data",
        repo_root / "data" / "test",
        Path.home() / "piper" / "data",
        Path.home() / "piper" / "data" / "test",
    ]
    found: list[Path] = []
    for base in candidates:
        if not base.exists():
            continue
        found.extend([p for p in base.glob("*.hdf5") if p.is_file()])

    if not found:
        raise SystemExit(
            "No HDF5 input provided and no .hdf5 file found in common data dirs.\n"
            "Please run with --input /path/to/demo.hdf5"
        )

    latest = max(found, key=lambda p: p.stat().st_mtime)
    print(f"[INFO] --input not set, auto selected latest hdf5: {latest}")
    return latest.resolve()


def load_first_q_and_actions(path: Path, episode_name: str) -> Tuple[List[float], np.ndarray]:
    if not path.exists():
        raise FileNotFoundError(f"hdf5 not found: {path}")

    with h5py.File(path, "r") as f:
        ep_key = f"data/{episode_name}"
        if ep_key not in f:
            raise KeyError(f"missing episode: {ep_key}")
        ep = f[ep_key]
        if "obs/q" not in ep:
            raise KeyError(f"{ep_key} missing obs/q")
        if "actions" not in ep:
            raise KeyError(f"{ep_key} missing actions")

        q0 = [float(v) for v in ep["obs/q"][0]]
        actions = np.asarray(ep["actions"], dtype=np.float64)

    if actions.ndim != 2 or actions.shape[1] != 6:
        raise ValueError(f"expected actions shape [N,6], got {actions.shape}")
    if len(q0) != 6:
        raise ValueError(f"expected q0 len=6, got {len(q0)}")
    return q0, actions


def denormalize_action(action_norm: Sequence[float]) -> np.ndarray:
    action = np.asarray(action_norm, dtype=np.float64).reshape(6).copy()
    action[:3] *= ACTION_POS_SCALE
    action[3:6] *= ACTION_ROT_SCALE
    return action


def _skew(v: np.ndarray) -> np.ndarray:
    return np.array(
        [[0.0, -v[2], v[1]], [v[2], 0.0, -v[0]], [-v[1], v[0], 0.0]],
        dtype=np.float64,
    )


def rot_x(r: float) -> np.ndarray:
    c, s = math.cos(r), math.sin(r)
    return np.array([[1.0, 0.0, 0.0], [0.0, c, -s], [0.0, s, c]], dtype=np.float64)


def rot_y(p: float) -> np.ndarray:
    c, s = math.cos(p), math.sin(p)
    return np.array([[c, 0.0, s], [0.0, 1.0, 0.0], [-s, 0.0, c]], dtype=np.float64)


def rot_z(y: float) -> np.ndarray:
    c, s = math.cos(y), math.sin(y)
    return np.array([[c, -s, 0.0], [s, c, 0.0], [0.0, 0.0, 1.0]], dtype=np.float64)


def euler_xyz_to_rotmat(r: float, p: float, y: float) -> np.ndarray:
    return rot_z(y) @ rot_y(p) @ rot_x(r)


def rotmat_to_euler_xyz(rot: np.ndarray) -> np.ndarray:
    pitch = math.asin(float(np.clip(-rot[2, 0], -1.0, 1.0)))
    cp = math.cos(pitch)
    if abs(cp) > 1e-8:
        roll = math.atan2(float(rot[2, 1]), float(rot[2, 2]))
        yaw = math.atan2(float(rot[1, 0]), float(rot[0, 0]))
    else:
        roll = 0.0
        yaw = math.atan2(float(-rot[0, 1]), float(rot[1, 1]))
    return np.array([roll, pitch, yaw], dtype=np.float64)


def so3_exp(rotvec: Sequence[float]) -> np.ndarray:
    rv = np.asarray(rotvec, dtype=np.float64).reshape(3)
    theta = float(np.linalg.norm(rv))
    if theta < 1e-12:
        return np.eye(3, dtype=np.float64)
    axis = rv / theta
    k = _skew(axis)
    eye = np.eye(3, dtype=np.float64)
    return eye + math.sin(theta) * k + (1.0 - math.cos(theta)) * (k @ k)


def compose_next_pose(curr_pose: Sequence[float], delta_action_raw: Sequence[float]) -> np.ndarray:
    pose = np.asarray(curr_pose, dtype=np.float64).reshape(6)
    delta = np.asarray(delta_action_raw, dtype=np.float64).reshape(6)

    out = pose.copy()
    out[:3] += delta[:3]
    r_curr = euler_xyz_to_rotmat(pose[3], pose[4], pose[5])
    r_delta = so3_exp(delta[3:6])
    out[3:6] = rotmat_to_euler_xyz(r_curr @ r_delta)
    return out


def print_comparison() -> None:
    print("\n===== 与 playTrajectory_pyagxarm_ik_movej.py 对比 =====")
    print("1) 本脚本读取 actions（增量）+ 第一帧 q；旧脚本读取绝对轨迹（obs/tcp_pose 或 obs/q）。")
    print("2) 本脚本每步都基于当前实时 tcp_pose 叠加 delta action；旧脚本按文件中的绝对目标逐点执行。")
    print("3) 本脚本先回零，再对齐到第一帧 q，然后进入增量闭环；旧脚本按轨迹模式决定起点对齐策略。")
    print("4) 两者都使用 URDF IK + move_j（在 pose 路径下）并做关节限幅。")
    print("=====================================================\n")


def main() -> None:
    args = parse_args()
    if args.compare:
        print_comparison()

    hdf5_path = resolve_hdf5_input(args.input)
    q0, actions = load_first_q_and_actions(hdf5_path, args.episode_name)
    if args.max_steps > 0:
        actions = actions[: args.max_steps]

    print(f"[INFO] loaded episode={args.episode_name}, first_q={q0}")
    print(f"[INFO] actions count={len(actions)}")

    arm = PiperArm(
        channel=args.channel,
        robot_name=args.robot_name,
        auto_connect=False,
        tool_type=args.tool_type,
    )

    print(f"[INFO] connect arm on {args.channel}")
    arm.connect()

    if not wait_exit_teach_mode(arm, timeout=5.0):
        print("[WARN] still in teach mode timeout, continue trying enable")

    if not arm.enable(timeout=8.0):
        raise RuntimeError("enable timeout")

    arm.set_motion_mode_j()
    arm.set_speed_percent(args.speed)

    print("[INFO] homing to zero joints")
    arm.move_j([0.0] * 6, wait=False)
    if not wait_joints_near_home(arm, timeout=args.home_timeout, tol_rad=args.home_tol):
        raise RuntimeError("failed to reach home within timeout")

    print("[INFO] move_j to first frame joints")
    
    first_ok = arm.move_j(q0, wait=True, timeout=12.0)
    if not first_ok:
        raise RuntimeError("move_j to first frame failed")

    ik_solver = PiperUrdfIkSolver(args.urdf_path)
    limits = get_joint_limits(arm)
    q_seed = q0[:]

    try:
        for i, act_norm in enumerate(actions):
            t0 = time.time()
            act_raw = denormalize_action(act_norm)
            curr_pose = arm.get_tcp_pose6()
            target_pose = compose_next_pose(curr_pose, act_raw)

            ok, joints, info = ik_solver.solve(target_pose.tolist(), q_seed)
            if (not ok) and (
                info["pos_err"] > args.ik_pos_hard or info["rot_err"] > args.ik_rot_hard
            ):
                print(
                    f"[WARN] step={i} IK hard fail, skip "
                    f"pos_err={info['pos_err']:.4f}, rot_err={info['rot_err']:.4f}"
                )
            else:
                joints, clipped = clip_joints(list(joints), limits)
                if not args.dry_run:
                    arm.move_j(joints, wait=True)
                q_seed = joints
                if i % max(1, args.print_every) == 0:
                    print(
                        f"[INFO] step={i} dry_run={args.dry_run} ik_ok={ok} clipped={clipped} "
                        f"pos_err={info['pos_err']:.4f} rot_err={info['rot_err']:.4f}"
                    )

            dt = time.time() - t0
            if dt < args.control_dt:
                time.sleep(args.control_dt - dt)
    finally:
        try:
            if not args.dry_run:
                arm.move_j([0.0] * 6, wait=False)
                time.sleep(2.0)
        except Exception:
            pass
        try:
            arm.disable(timeout=8.0)
        except Exception:
            pass


if __name__ == "__main__":
    main()
