#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Deploy a robomimic BC-RNN policy checkpoint to real Piper robot.

流程：
1) 读取真机 obs: q / dq / tcp_pose
2) 调用 robomimic policy 推理得到 normalized 6D action
3) 反归一化为物理动作增量 [dx,dy,dz,drx,dry,drz]
4) 叠加到当前 tcp_pose 得到下一帧目标位姿
5) URDF IK 求解 -> move_j 下发

建议先 `--dry-run` 验证，再开启真实下发。
"""

from __future__ import annotations

import argparse
import math
import sys
import time
from pathlib import Path
from typing import Dict, Iterable, Tuple

import numpy as np


# Ensure /workspace/piper/src is importable regardless of run cwd.
_THIS_FILE = Path(__file__).resolve()
_SRC_DIR = _THIS_FILE.parents[1]
_REPO_ROOT = _THIS_FILE.parents[2]
if str(_SRC_DIR) not in sys.path:
    sys.path.insert(0, str(_SRC_DIR))



from imitation.playTrajectory_pyagxarm_ik_movej import (  # noqa: E402
    PiperUrdfIkSolver,
    clip_joints,
    get_joint_limits,
)



ACTION_POS_SCALE = np.array([0.01, 0.01, 0.01], dtype=np.float32)
ACTION_ROT_SCALE = np.array([0.8, 0.8, 0.8], dtype=np.float32)


def _import_or_raise():
    """Import runtime dependencies with clear errors."""
    try:
        import torch  # type: ignore
    except Exception as exc:  # pragma: no cover
        raise RuntimeError("缺少 torch，请先安装 PyTorch") from exc

    try:
        from robomimic.utils import file_utils as file_utils  # type: ignore
        from robomimic.utils import torch_utils as torch_utils  # type: ignore
    except Exception as exc:  # pragma: no cover
        raise RuntimeError("缺少 robomimic，请先安装并配置 PYTHONPATH") from exc

    try:
        from robot.piper_arm import PiperArm  # type: ignore
    except Exception as exc:  # pragma: no cover
        raise RuntimeError("缺少 pyAgxArm / robot.piper_arm 依赖，无法连接真机") from exc

    return torch, file_utils, torch_utils, PiperArm


def check_imports_only() -> int:
    """Check all key imports; return exit code."""
    checks: Iterable[Tuple[str, str]] = [
        ("numpy", "import numpy"),
        ("torch", "import torch"),
        ("robomimic", "import robomimic"),
        ("pyAgxArm", "import pyAgxArm"),
        ("robot.piper_arm", "from robot.piper_arm import PiperArm"),
    ]

    failed = False
    for name, stmt in checks:
        try:
            exec(stmt, {})
            print(f"[OK] import {name}")
        except Exception as exc:
            failed = True
            print(f"[FAIL] import {name}: {exc}")

    if failed:
        print("[ERROR] 依赖导入检查失败，请先补齐依赖后再部署。")
        return 2
    print("[OK] 所有关键依赖导入成功。")
    return 0


def denormalize_action(action_norm: np.ndarray) -> np.ndarray:
    """normalized 6D -> raw 6D."""
    action_norm = np.asarray(action_norm, dtype=np.float32).reshape(-1)
    if action_norm.shape[0] != 6:
        raise ValueError(f"expected action dim=6, got {action_norm.shape}")

    action_raw = action_norm.copy()
    action_raw[0:3] *= ACTION_POS_SCALE
    action_raw[3:6] *= ACTION_ROT_SCALE
    return action_raw


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


def _skew(v: np.ndarray) -> np.ndarray:
    return np.array(
        [
            [0.0, -v[2], v[1]],
            [v[2], 0.0, -v[0]],
            [-v[1], v[0], 0.0],
        ],
        dtype=np.float64,
    )


def so3_exp(rotvec: np.ndarray) -> np.ndarray:
    """SO(3) exponential map from rotation vector to rotation matrix."""
    theta = float(np.linalg.norm(rotvec))
    if theta < 1e-12:
        return np.eye(3, dtype=np.float64)
    axis = rotvec / theta
    k = _skew(axis)
    I = np.eye(3, dtype=np.float64)
    return I + math.sin(theta) * k + (1.0 - math.cos(theta)) * (k @ k)


def compose_next_pose(curr_pose: np.ndarray, delta_action: np.ndarray) -> np.ndarray:
    """Apply delta action on current tcp pose using SO(3) composition."""
    if curr_pose.shape[0] != 6 or delta_action.shape[0] != 6:
        raise ValueError("curr_pose and delta_action must be 6D")

    next_pose = curr_pose.astype(np.float64).copy()
    next_pose[:3] += delta_action[:3]
    r_curr = euler_xyz_to_rotmat(curr_pose[3], curr_pose[4], curr_pose[5])
    r_delta = so3_exp(delta_action[3:6].astype(np.float64))
    next_pose[3:6] = rotmat_to_euler_xyz(r_curr @ r_delta)
    return next_pose


def get_obs_dict(arm, use_dq: bool = True, mode: str = "flat") -> Dict[str, np.ndarray]:
    q = np.asarray(arm.get_joint_position_rad(), dtype=np.float32)
    if use_dq:
        try:
            dq = np.asarray(arm.get_joint_velocity_rad_s(), dtype=np.float32)
        except Exception:
            dq = np.zeros(6, dtype=np.float32)
    else:
        dq = np.zeros(6, dtype=np.float32)
    tcp_pose = np.asarray(arm.get_tcp_pose6(), dtype=np.float32)

    if mode == "rnn":
        return {
            "q": q.reshape(1, 1, 6),
            "dq": dq.reshape(1, 1, 6),
            "tcp_pose": tcp_pose.reshape(1, 1, 6),
        }
    if mode == "batch":
        return {
            "q": q.reshape(1, 6),
            "dq": dq.reshape(1, 6),
            "tcp_pose": tcp_pose.reshape(1, 6),
        }
    if mode == "flat":
        return {
            "q": q.reshape(6),
            "dq": dq.reshape(6),
            "tcp_pose": tcp_pose.reshape(6),
        }
    raise ValueError(f"unsupported obs mode: {mode}")


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Deploy BC-RNN policy on Piper (IK + move_j)")
    parser.add_argument(
        "--ckpt",
        default="/home/flowing/piper/data/trained_models/piper_bc_rnn_no_vision_3_28_1/piper_bc_rnn_no_vision_3_28_1/20260328234951/models/model_epoch_50.pth",
        help="robomimic .pth checkpoint path",
    )
    parser.add_argument("--channel", default="can0")
    parser.add_argument("--robot-name", default="piper")
    parser.add_argument("--tool-type", default="none")
    parser.add_argument(
        "--urdf-path",
        default=(
            "agx_arm_ws/install/agx_arm_description/share/agx_arm_description/"
            "agx_arm_urdf/piper/urdf/piper_description.urdf"
        ),
    )
    parser.add_argument("--control-dt", type=float, default=0.05)
    parser.add_argument("--max-steps", type=int, default=2000)
    parser.add_argument("--speed", type=int, default=20)
    parser.add_argument("--home-timeout", type=float, default=25.0, help="回零等待超时（秒）")
    parser.add_argument("--home-tol", type=float, default=0.03, help="回零判定阈值（rad）")
    parser.add_argument("--ik-pos-hard", type=float, default=0.02)
    parser.add_argument("--ik-rot-hard", type=float, default=0.25)
    parser.add_argument("--max-delta-pos", type=float, default=0.003)
    parser.add_argument("--max-delta-rot", type=float, default=0.05)
    parser.add_argument("--print-every", type=int, default=20)
    parser.add_argument(
        "--no-time-dim",
        action="store_true",
        help="禁用观测时间维（默认给 BC-RNN 输入 [B,T,D]，即 [1,1,D]）",
    )
    parser.add_argument(
        "--obs-shape",
        choices=["flat", "batch", "rnn"],
        default="flat",
        help="policy 观测输入形状: flat=[D], batch=[B,D], rnn=[B,T,D]",
    )
    parser.add_argument("--dry-run", action="store_true", help="只做推理与日志，不下发 move_j")
    parser.add_argument("--check-imports", action="store_true", help="仅检查关键依赖导入")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    if args.check_imports:
        return check_imports_only()

    torch, file_utils, torch_utils, PiperArm = _import_or_raise()

    if not args.ckpt:
        raise ValueError("请提供 --ckpt 路径，或使用 --check-imports 仅检查依赖")

    ckpt = Path(args.ckpt)
    if not ckpt.exists():
        raise FileNotFoundError(f"checkpoint not found: {ckpt}")

    arm = PiperArm(
        channel=args.channel,
        robot_name=args.robot_name,
        auto_connect=False,
        tool_type=args.tool_type,
    )

    print("[INFO] connecting arm ...")
    arm.connect()
    if not arm.enable(timeout=8.0):
        raise RuntimeError("arm enable timeout")

    arm.set_speed_percent(args.speed)
    arm.set_motion_mode_j()

    print("[INFO] move to home joints [0,0,0,0,0,0] before loading policy ...")
    arm.move_j([0.0] * 6, wait=False)
    home_start = time.monotonic()
    while True:
        q_now = arm.get_joint_position_rad()
        q_max = max(abs(v) for v in q_now) if q_now else float("inf")
        if q_now and q_max <= args.home_tol:
            print("[INFO] homing finished, arm stays enabled.")
            break
        if time.monotonic() - home_start > args.home_timeout:
            raise RuntimeError(
                f"home timeout: {args.home_timeout}s, "
                f"current max|q|={q_max:.4f} rad"
            )
        arm.move_j([0.0] * 6, wait=False)
        time.sleep(0.05)

    print("[INFO] loading policy after homing ...")
    device = torch_utils.get_torch_device(try_to_use_cuda=True)
    policy, _ = file_utils.policy_from_checkpoint(
        ckpt_path=str(ckpt),
        device=device,
        verbose=True,
    )

    if hasattr(policy, "start_episode"):
        policy.start_episode()

    ik_solver = PiperUrdfIkSolver(args.urdf_path)

    limits = get_joint_limits(arm)
    q_seed = arm.get_joint_position_rad()

    try:
        for step in range(args.max_steps):
            t0 = time.time()

            if args.no_time_dim:
                first_mode = "batch"
            else:
                first_mode = args.obs_shape
            mode_candidates = [first_mode]
            for m in ("flat", "batch", "rnn"):
                if m not in mode_candidates:
                    mode_candidates.append(m)

            action_norm = None
            with torch.no_grad():
                last_exc: Exception | None = None
                for obs_mode in mode_candidates:
                    obs = get_obs_dict(arm, use_dq=True, mode=obs_mode)
                    try:
                        action_norm = policy(ob=obs)
                        if step == 0:
                            print(f"[INFO] policy obs shape mode = {obs_mode}")
                        break
                    except AssertionError as exc:
                        last_exc = exc
                        print(f"[WARN] policy 输入维度不匹配，切换 obs_mode={obs_mode} -> next")
                        continue
                if action_norm is None:
                    raise RuntimeError(
                        f"policy 推理失败：flat/batch/rnn 三种 obs 形状均不匹配，最后错误: {last_exc}"
                    )

            action_norm = np.asarray(action_norm, dtype=np.float32).reshape(-1)
            action_raw = denormalize_action(action_norm)

            action_raw[:3] = np.clip(action_raw[:3], -args.max_delta_pos, args.max_delta_pos)
            action_raw[3:6] = np.clip(action_raw[3:6], -args.max_delta_rot, args.max_delta_rot)

            curr_pose = np.asarray(arm.get_tcp_pose6(), dtype=np.float64)
            target_pose = compose_next_pose(curr_pose, action_raw.astype(np.float64))

            ok, joints, info = ik_solver.solve(target_pose.tolist(), q_seed)
            if (not ok) and (
                info["pos_err"] > args.ik_pos_hard or info["rot_err"] > args.ik_rot_hard
            ):
                print(
                    f"[WARN] step={step} IK hard fail, skip. "
                    f"pos_err={info['pos_err']:.4f}, rot_err={info['rot_err']:.4f}"
                )
            else:
                joints, clipped = clip_joints(list(joints), limits)
                if not args.dry_run:
                    arm.move_j(joints, wait=False)
                q_seed = joints
                if step % max(1, args.print_every) == 0:
                    print(
                        f"[INFO] step={step} dry_run={args.dry_run} "
                        f"ik_ok={ok} clipped={clipped} "
                        f"pos_err={info['pos_err']:.4f} rot_err={info['rot_err']:.4f}"
                    )

            dt = time.time() - t0
            if dt < args.control_dt:
                time.sleep(args.control_dt - dt)
    except KeyboardInterrupt:
        print("[WARN] interrupted by user")
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

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
