#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
Piper 无视觉 imitation（robomimic BC-RNN）最小闭环脚本。

提供 4 个子命令：
1) collect: 采集示教轨迹并直接写 robomimic 风格 HDF5
2) inspect: 打印 HDF5 结构和关键 shape，确认可训练
3) replay: 把 HDF5 中 action 直接部署到实机（位置增量伺服）
4) make-config: 生成 BC-RNN 训练配置 JSON（可直接给 robomimic scripts/train.py 使用）

采集字段（按你的要求）：
- 时间戳 t
- 当前关节角度 q
- 当前关节角速度 dq
- 末端位置 tcp_xyz（以及 tcp_pose 6D）
- action 指令（Δx,Δy,Δz 或 Δx,Δy,Δz,Δrx,Δry,Δrz）
- 上个 action 指令 last_action
"""

from __future__ import annotations

import argparse
import json
import sys
import time
from pathlib import Path
from typing import Dict, List

import h5py
import numpy as np

try:
    from robot.piper_arm import PiperArm
except ModuleNotFoundError:
    src_dir = Path(__file__).resolve().parents[1]
    if str(src_dir) not in sys.path:
        sys.path.insert(0, str(src_dir))
    from robot.piper_arm import PiperArm


def build_obs(arm: PiperArm, ts: float | None = None) -> Dict:
    """读取一帧 observation。"""
    if ts is None:
        ts = time.time()
    raw = arm.get_observation_dict(timestamp=ts)
    return {
        "t": float(raw["t"]),
        "q": [float(v) for v in raw["q"]],
        "dq": [float(v) for v in raw["dq"]],
        "tcp_xyz": [float(v) for v in raw["tcp_xyz"]],
        "tcp_pose": [float(v) for v in raw["tcp_pose"]],
    }


def get_ctrl_mode(arm: PiperArm):
    """读取控制模式（用于示教模式检测）。"""
    status = arm.get_arm_status()
    if status is None:
        return None
    return getattr(status.msg, "ctrl_mode", None)


def wait_for_teach_mode(arm: PiperArm, timeout_s: float) -> None:
    """
    等待进入示教模式（ctrl_mode == 2）。
    超时抛错，避免在非示教状态下“采不到动作”。
    """
    end_t = time.monotonic() + timeout_s
    while get_ctrl_mode(arm) != 2:
        if time.monotonic() > end_t:
            raise RuntimeError("示教模式检测超时，请检查示教模式是否开启（ctrl_mode==2）")
        time.sleep(0.01)


def wait_exit_teach_mode(arm: PiperArm, timeout_s: float) -> None:
    """
    等待退出示教模式（ctrl_mode != 2）。
    replay 阶段如果仍在示教模式，控制指令通常不会生效。
    """
    end_t = time.monotonic() + timeout_s
    while get_ctrl_mode(arm) == 2:
        if time.monotonic() > end_t:
            raise RuntimeError("退出示教模式超时，请手动退出示教后重试 replay")
        time.sleep(0.01)


def get_runtime_state(arm: PiperArm) -> Dict[str, object]:
    """
    获取回放诊断状态，帮助判断 connect / enable / 模式是否正常。
    注意：不同底层返回结构可能略有差异，因此做了容错读取。
    """
    state: Dict[str, object] = {}
    try:
        state["is_ok"] = arm.is_ok()
    except Exception:  # noqa: BLE001
        state["is_ok"] = "unknown"

    try:
        state["ctrl_mode"] = get_ctrl_mode(arm)
    except Exception:  # noqa: BLE001
        state["ctrl_mode"] = "unknown"

    try:
        state["joint_enable"] = arm.get_joints_enable_status_list()
    except Exception:  # noqa: BLE001
        state["joint_enable"] = "unknown"

    try:
        state["tcp_pose"] = arm.get_tcp_pose6()
    except Exception:  # noqa: BLE001
        state["tcp_pose"] = "unknown"
    return state


def print_runtime_state(arm: PiperArm, tag: str) -> None:
    s = get_runtime_state(arm)
    print(
        f"[STATE:{tag}] "
        f"is_ok={s['is_ok']}, ctrl_mode={s['ctrl_mode']}, "
        f"joint_enable={s['joint_enable']}, tcp_pose={s['tcp_pose']}"
    )


def wait_non_teaching_mode_after_enable(arm: PiperArm, timeout_s: float) -> None:
    """
    enable 后再次确认不在示教模式。
    实测中可能出现：enable 成功但 ctrl_mode 仍是 TEACHING_MODE(0x2)，
    这会导致 move_p / move_l 不执行并持续 wait_motion_done timeout。
    """
    end_t = time.monotonic() + timeout_s
    last_mode = None
    while time.monotonic() < end_t:
        mode = get_ctrl_mode(arm)
        last_mode = mode
        # mode 可能是整型或字符串形式（如 TEACHING_MODE(0x2)）
        mode_str = str(mode)
        if mode is None or (mode != 2 and "TEACHING_MODE" not in mode_str):
            return
        time.sleep(0.05)
    raise RuntimeError(
        f"enable 后仍处于示教模式: ctrl_mode={last_mode}。"
        "请手动退出示教模式（点示教按钮）后重试。"
    )


def action_from_obs(prev_obs: Dict, curr_obs: Dict, action_dim: int) -> List[float]:
    """
    由相邻两帧 obs 差分得到 action。
    action_dim=3 -> [Δx,Δy,Δz]
    action_dim=6 -> [Δx,Δy,Δz,Δrx,Δry,Δrz]
    """
    if action_dim not in (3, 6):
        raise ValueError("action_dim must be 3 or 6")

    p0 = prev_obs["tcp_pose"]
    p1 = curr_obs["tcp_pose"]

    if action_dim == 3:
        return [float(p1[i] - p0[i]) for i in range(3)]
    return [float(p1[i] - p0[i]) for i in range(6)]


def create_episode_datasets(ep_group: h5py.Group, num_samples: int, action_dim: int) -> None:
    """创建单个 episode 的数据集。"""
    obs = ep_group.require_group("obs")
    obs.create_dataset("t", shape=(num_samples, 1), dtype=np.float64)
    obs.create_dataset("q", shape=(num_samples, 6), dtype=np.float32)
    obs.create_dataset("dq", shape=(num_samples, 6), dtype=np.float32)
    obs.create_dataset("tcp_xyz", shape=(num_samples, 3), dtype=np.float32)
    obs.create_dataset("tcp_pose", shape=(num_samples, 6), dtype=np.float32)

    ep_group.create_dataset("actions", shape=(num_samples, action_dim), dtype=np.float32)
    ep_group.create_dataset("last_actions", shape=(num_samples, action_dim), dtype=np.float32)


def write_sample(ep_group: h5py.Group, idx: int, obs: Dict, action: List[float], last_action: List[float]) -> None:
    ep_group["obs/t"][idx] = np.asarray([obs["t"]], dtype=np.float64)
    ep_group["obs/q"][idx] = np.asarray(obs["q"], dtype=np.float32)
    ep_group["obs/dq"][idx] = np.asarray(obs["dq"], dtype=np.float32)
    ep_group["obs/tcp_xyz"][idx] = np.asarray(obs["tcp_xyz"], dtype=np.float32)
    ep_group["obs/tcp_pose"][idx] = np.asarray(obs["tcp_pose"], dtype=np.float32)

    ep_group["actions"][idx] = np.asarray(action, dtype=np.float32)
    ep_group["last_actions"][idx] = np.asarray(last_action, dtype=np.float32)


def add_file_metadata(f: h5py.File, args: argparse.Namespace, total_samples: int) -> None:
    env_args = {
        "type": "real_robot",
        "robot": "piper",
        "channel": args.channel,
        "tool_type": args.tool_type,
        "tcp_offset": json.loads(args.tcp_offset),
        "nominal_period_s": args.period,
        "action_dim": args.action_dim,
        "action_definition": "delta_tcp_xyz" if args.action_dim == 3 else "delta_tcp_pose6",
        "action_units": "m" if args.action_dim == 3 else ["m", "m", "m", "rad", "rad", "rad"],
        "q_units": "rad",
        "dq_units": "rad/s",
    }
    f.attrs["env"] = "real_piper_no_vision"
    f.attrs["env_args"] = json.dumps(env_args, ensure_ascii=False)
    f.require_group("data").attrs["total"] = int(total_samples)


def cmd_collect(args: argparse.Namespace) -> None:
    if args.samples <= 0:
        raise ValueError("--samples 必须 > 0")
    if args.action_dim not in (3, 6):
        raise ValueError("--action-dim 只能是 3 或 6")

    out_path = Path(args.output).expanduser().resolve()
    out_path.parent.mkdir(parents=True, exist_ok=True)

    arm = PiperArm(
        channel=args.channel,
        auto_connect=False,
        tool_type=args.tool_type,
        tcp_offset=json.loads(args.tcp_offset),
    )

    with h5py.File(out_path, "w") as f:
        data_group = f.require_group("data")
        ep_group = data_group.require_group(args.episode_name)
        create_episode_datasets(ep_group, args.samples, args.action_dim)

        try:
            print(f"[INFO] connect: channel={args.channel}, tool_type={args.tool_type}")
            arm.connect()

            if args.require_teach_mode:
                print("[INFO] step 1: 请点击示教按钮进入示教模式")
                wait_for_teach_mode(arm, timeout_s=args.teach_timeout)
                print("[INFO] 已检测到示教模式")

            if not args.auto_start:
                input("[INFO] step 2: 按回车开始采集")

            # 采集示教数据时，通常不需要 enable（保持示教拖动状态）。
            # 若你的现场流程需要先 enable，可显式打开参数。
            if args.enable_before_collect:
                print("[INFO] enable")
                if not arm.enable(timeout=8.0):
                    raise RuntimeError("enable failed")

            print(f"[INFO] start collect: action_dim={args.action_dim}, samples={args.samples}")
            # 为了构造 first sample，需要 3 帧
            obs_t2 = build_obs(arm)
            time.sleep(args.period)
            obs_t1 = build_obs(arm)

            for idx in range(args.samples):
                time.sleep(args.period)
                obs_t = build_obs(arm)

                last_action = action_from_obs(obs_t2, obs_t1, args.action_dim)
                action = action_from_obs(obs_t1, obs_t, args.action_dim)
                write_sample(ep_group, idx, obs_t, action, last_action)

                obs_t2, obs_t1 = obs_t1, obs_t

                if (idx + 1) % 20 == 0 or idx == args.samples - 1:
                    print(f"[INFO] collected {idx + 1}/{args.samples}")

            add_file_metadata(f, args, args.samples)
            print(f"[INFO] saved: {out_path}")

        finally:
            if args.enable_before_collect:
                print("[INFO] disable")
                arm.disable(timeout=8.0)


def cmd_inspect(args: argparse.Namespace) -> None:
    in_path = Path(args.input).expanduser().resolve()
    if not in_path.exists():
        raise FileNotFoundError(in_path)

    with h5py.File(in_path, "r") as f:
        print("\n===== HDF5 attrs =====")
        for k, v in f.attrs.items():
            print(f"{k}: {v}")

        data = f["data"]
        print(f"\n[data].attrs.total = {data.attrs.get('total', 'N/A')}")

        for ep_name in data.keys():
            ep = data[ep_name]
            print(f"\n--- episode: {ep_name} ---")
            print(f"obs/q shape         : {ep['obs/q'].shape}")
            print(f"obs/dq shape        : {ep['obs/dq'].shape}")
            print(f"obs/tcp_xyz shape   : {ep['obs/tcp_xyz'].shape}")
            print(f"obs/tcp_pose shape  : {ep['obs/tcp_pose'].shape}")
            print(f"actions shape       : {ep['actions'].shape}")
            print(f"last_actions shape  : {ep['last_actions'].shape}")


def _clip_action(action: np.ndarray, pos_step_max: float, rot_step_max: float) -> np.ndarray:
    """动作限幅，保护实机。"""
    out = action.copy()
    if out.shape[0] >= 3:
        out[:3] = np.clip(out[:3], -pos_step_max, pos_step_max)
    if out.shape[0] >= 6:
        out[3:6] = np.clip(out[3:6], -rot_step_max, rot_step_max)
    return out


def _apply_deadband_and_scale(
    action: np.ndarray,
    action_scale: float,
    min_pos_step: float,
    min_rot_step: float,
) -> np.ndarray:
    """
    - action_scale: 放大/缩小动作（解决采样差分过小导致不动）
    - deadband: 小于阈值的动作置零，避免抖动和无效细碎命令
    """
    out = action.copy() * float(action_scale)

    if out.shape[0] >= 3 and min_pos_step > 0:
        for i in range(3):
            if abs(out[i]) < min_pos_step:
                out[i] = 0.0

    if out.shape[0] >= 6 and min_rot_step > 0:
        for i in range(3, 6):
            if abs(out[i]) < min_rot_step:
                out[i] = 0.0
    return out


def _smooth_action(action: np.ndarray, prev_action: np.ndarray | None, alpha: float) -> np.ndarray:
    """一阶低通平滑。"""
    if prev_action is None:
        return action
    return alpha * prev_action + (1.0 - alpha) * action


def _compose_next_pose(curr_pose: np.ndarray, delta_action: np.ndarray) -> np.ndarray:
    """把 delta action 叠加到当前 tcp_pose，得到下一步目标 pose。"""
    next_pose = curr_pose.copy()
    if delta_action.shape[0] == 3:
        next_pose[:3] += delta_action[:3]
    elif delta_action.shape[0] == 6:
        next_pose[:6] += delta_action[:6]
    else:
        raise ValueError("action dim must be 3 or 6")
    return next_pose


def _send_pose_command(
    arm: PiperArm,
    pose_next: np.ndarray,
    exec_mode: str,
    wait_motion_done: bool,
    motion_timeout: float,
) -> bool:
    """
    统一发送末端位姿命令。
    - exec_mode=move_l: 线性运动
    - exec_mode=move_p: 点到点位姿运动
    """
    pose_list = pose_next.tolist()
    if exec_mode == "move_l":
        return bool(arm.move_l(pose_list, wait=wait_motion_done, timeout=motion_timeout))
    elif exec_mode == "move_p":
        return bool(arm.move_p(pose_list, wait=wait_motion_done, timeout=motion_timeout))
    else:
        raise ValueError(f"unsupported exec_mode: {exec_mode}")


def _send_joint_command(
    arm: PiperArm,
    joints: np.ndarray,
    wait_motion_done: bool,
    motion_timeout: float,
) -> bool:
    """发送关节目标（用于 tcp 回放无运动时的诊断/兜底）。"""
    return bool(arm.move_j(joints.tolist(), wait=wait_motion_done, timeout=motion_timeout))


def cmd_replay(args: argparse.Namespace) -> None:
    in_path = Path(args.input).expanduser().resolve()
    if not in_path.exists():
        raise FileNotFoundError(in_path)

    arm = PiperArm(
        channel=args.channel,
        auto_connect=False,
        tool_type=args.tool_type,
        tcp_offset=json.loads(args.tcp_offset),
    )

    with h5py.File(in_path, "r") as f:
        ep = f[f"data/{args.episode_name}"]
        actions = np.asarray(ep["actions"], dtype=np.float32)
        obs_q = np.asarray(ep["obs/q"], dtype=np.float32) if "obs/q" in ep else None

        if args.max_steps > 0:
            actions = actions[: args.max_steps]
            if obs_q is not None:
                obs_q = obs_q[: args.max_steps]

        prev_action = None
        try:
            print(f"[INFO] connect: channel={args.channel}")
            arm.connect()
            print_runtime_state(arm, "after_connect")

            if args.require_exit_teach_mode:
                print("[INFO] 请确保已退出示教模式（回放需要非示教状态）")
                wait_exit_teach_mode(arm, timeout_s=args.exit_teach_timeout)
                print("[INFO] 已确认退出示教模式")
                print_runtime_state(arm, "after_exit_teach_check")

            print("[INFO] enable")
            if not arm.enable(timeout=8.0):
                raise RuntimeError("enable failed")
            print_runtime_state(arm, "after_enable")

            if args.require_non_teaching_after_enable:
                wait_non_teaching_mode_after_enable(
                    arm=arm,
                    timeout_s=args.non_teaching_timeout,
                )
                print_runtime_state(arm, "after_non_teaching_check")

            arm.set_motion_mode_p()
            arm.set_speed_percent(args.speed_percent)
            print_runtime_state(arm, "after_set_mode_speed")

            raw_norm = np.linalg.norm(actions[:, :3], axis=1) if actions.shape[1] >= 3 else np.zeros(len(actions))
            print(
                f"[INFO] raw action stats | mean={raw_norm.mean():.6f}, "
                f"p95={np.percentile(raw_norm, 95):.6f}, max={raw_norm.max():.6f}"
            )

            print(f"[INFO] replay start, steps={len(actions)}")
            no_motion_counter = 0
            timeout_counter = 0
            dynamic_wait_motion_done = bool(args.wait_motion_done)
            for i, act in enumerate(actions):
                act = _apply_deadband_and_scale(
                    act,
                    action_scale=args.action_scale,
                    min_pos_step=args.min_pos_step,
                    min_rot_step=args.min_rot_step,
                )
                act = _clip_action(act, args.pos_step_max, args.rot_step_max)
                act = _smooth_action(act, prev_action, args.smooth_alpha)

                curr_pose = np.asarray(arm.get_tcp_pose6(), dtype=np.float64)
                next_pose = _compose_next_pose(curr_pose, act)

                move_ok = _send_pose_command(
                    arm=arm,
                    pose_next=next_pose,
                    exec_mode=args.exec_mode,
                    wait_motion_done=dynamic_wait_motion_done,
                    motion_timeout=args.motion_timeout,
                )
                if not move_ok and args.retry_nonblocking_on_timeout and dynamic_wait_motion_done:
                    timeout_counter += 1
                    print("[WARN] wait_motion_done 超时，自动重试一次 non-blocking 下发")
                    _send_pose_command(
                        arm=arm,
                        pose_next=next_pose,
                        exec_mode=args.exec_mode,
                        wait_motion_done=False,
                        motion_timeout=args.motion_timeout,
                    )
                    if timeout_counter >= args.timeout_switch_threshold:
                        dynamic_wait_motion_done = False
                        print(
                            "[WARN] 连续 wait 超时，后续自动切换为 no-wait 模式继续回放 "
                            f"(threshold={args.timeout_switch_threshold})"
                        )
                prev_action = act

                if (i + 1) % 20 == 0 or i == len(actions) - 1:
                    pose_after = np.asarray(arm.get_tcp_pose6(), dtype=np.float64)
                    move_norm = float(np.linalg.norm(pose_after[:3] - curr_pose[:3]))
                    cmd_norm = float(np.linalg.norm(act[:3])) if act.shape[0] >= 3 else 0.0
                    if move_norm < args.motion_epsilon:
                        no_motion_counter += 1
                    else:
                        no_motion_counter = 0

                    print(
                        f"[INFO] replay {i + 1}/{len(actions)} | "
                        f"cmd_norm={cmd_norm:.6f}, measured_move={move_norm:.6f}, "
                        f"no_motion_counter={no_motion_counter}"
                    )
                    print_runtime_state(arm, f"replay_step_{i+1}")

                    if no_motion_counter >= args.no_motion_warn_steps:
                        print(
                            "[WARN] 连续多次检测到“有指令但几乎无位移”。"
                            "请检查：是否仍在示教模式、是否驱动已使能、"
                            "碰撞保护是否触发、速度比例是否过低。"
                        )
                        if args.try_fallback_move_p:
                            print("[WARN] 尝试 fallback: 使用 move_p + wait=True 发送一次当前目标位姿")
                            _send_pose_command(
                                arm=arm,
                                pose_next=next_pose,
                                exec_mode="move_p",
                                wait_motion_done=True,
                                motion_timeout=max(args.motion_timeout, 2.0),
                            )
                            pose_fb = np.asarray(arm.get_tcp_pose6(), dtype=np.float64)
                            fb_move = float(np.linalg.norm(pose_fb[:3] - curr_pose[:3]))
                            print(f"[WARN] fallback measured_move={fb_move:.6f}")
                        if args.try_joint_fallback and obs_q is not None and i < len(obs_q):
                            print("[WARN] 尝试 joint fallback: 发送当前样本对应的 q 目标")
                            joint_ok = _send_joint_command(
                                arm=arm,
                                joints=np.asarray(obs_q[i], dtype=np.float64),
                                wait_motion_done=True,
                                motion_timeout=max(args.motion_timeout, 2.0),
                            )
                            print(f"[WARN] joint fallback done, ok={joint_ok}")

                time.sleep(args.period)

            print("[INFO] replay done")

        finally:
            print("[INFO] disable")
            arm.disable(timeout=8.0)


def cmd_make_config(args: argparse.Namespace) -> None:
    """
    生成 robomimic BC-RNN 配置模板。
    用法：
      python no_vision_pipeline.py make-config --dataset demo.hdf5 --output bc_rnn_no_vision.json
    """
    cfg = {
        "algo_name": "bc",
        "experiment": {
            "name": args.exp_name,
            "validate": True,
            "save": {"enabled": True, "every_n_epochs": 10},
            "logging": {"terminal_output_to_txt": True},
        },
        "train": {
            "data": args.dataset,
            "batch_size": args.batch_size,
            "num_epochs": args.num_epochs,
            "hdf5_cache_mode": "all",
            "seq_length": args.seq_length,
            "dataset_keys": ["actions", "obs/q", "obs/dq", "obs/tcp_xyz", "last_actions"],
        },
        "observation": {
            "modalities": {
                "obs": {
                    "low_dim": ["q", "dq", "tcp_xyz", "last_actions"]
                }
            }
        },
        "algo": {
            "rnn": {
                "enabled": True,
                "horizon": args.seq_length,
                "hidden_dim": args.rnn_hidden_dim,
                "num_layers": args.rnn_layers,
            }
        },
    }

    out_path = Path(args.output).expanduser().resolve()
    out_path.parent.mkdir(parents=True, exist_ok=True)
    out_path.write_text(json.dumps(cfg, indent=2, ensure_ascii=False), encoding="utf-8")
    print(f"[INFO] wrote config: {out_path}")


def build_parser() -> argparse.ArgumentParser:
    p = argparse.ArgumentParser(description="Piper 无视觉 imitation 最小闭环工具")
    sub = p.add_subparsers(dest="cmd", required=True)

    c = sub.add_parser("collect", help="采集并写入 HDF5")
    c.add_argument("--output", required=True)
    c.add_argument("--episode-name", default="demo_0")
    c.add_argument("--samples", type=int, required=True)
    c.add_argument("--period", type=float, default=0.05)
    c.add_argument("--action-dim", type=int, default=3, choices=[3, 6])
    c.add_argument("--channel", default="can0")
    c.add_argument("--tool-type", default="none", choices=["none", "custom_tool", "agx_gripper", "revo2"])
    c.add_argument("--tcp-offset", default="[0,0,0,0,0,0]")
    c.add_argument("--require-teach-mode", action="store_true", default=True, help="采集前强制检测示教模式（默认开启）")
    c.add_argument("--no-require-teach-mode", dest="require_teach_mode", action="store_false", help="关闭示教模式检测")
    c.add_argument("--teach-timeout", type=float, default=10.0, help="示教模式检测超时[s]")
    c.add_argument("--auto-start", action="store_true", help="不等待回车，直接开始采集")
    c.add_argument("--enable-before-collect", action="store_true", help="采集前先 enable（默认关闭，避免影响示教拖动）")
    c.set_defaults(func=cmd_collect)

    i = sub.add_parser("inspect", help="检查 HDF5 数据结构")
    i.add_argument("--input", required=True)
    i.set_defaults(func=cmd_inspect)

    r = sub.add_parser("replay", help="将 HDF5 中 action 回放到实机")
    r.add_argument("--input", required=True)
    r.add_argument("--episode-name", default="demo_0")
    r.add_argument("--max-steps", type=int, default=0, help="0 表示全回放")
    r.add_argument("--period", type=float, default=0.05)
    r.add_argument("--channel", default="can0")
    r.add_argument("--tool-type", default="none", choices=["none", "custom_tool", "agx_gripper", "revo2"])
    r.add_argument("--tcp-offset", default="[0,0,0,0,0,0]")
    r.add_argument("--speed-percent", type=int, default=30)
    r.add_argument("--action-scale", type=float, default=1.0, help="动作整体缩放系数；若不动可尝试 2~5")
    r.add_argument("--min-pos-step", type=float, default=0.0, help="平移 deadband[m]，小于该值置零")
    r.add_argument("--min-rot-step", type=float, default=0.0, help="旋转 deadband[rad]，小于该值置零")
    r.add_argument("--pos-step-max", type=float, default=0.005, help="单步最大平移[m]")
    r.add_argument("--rot-step-max", type=float, default=0.03, help="单步最大转角[rad]，action_dim=6 时使用")
    r.add_argument("--smooth-alpha", type=float, default=0.6, help="低通系数，越大越平滑")
    r.add_argument("--require-exit-teach-mode", action="store_true", default=True, help="回放前强制检查已退出示教（默认开启）")
    r.add_argument("--no-require-exit-teach-mode", dest="require_exit_teach_mode", action="store_false", help="关闭退出示教检查")
    r.add_argument("--exit-teach-timeout", type=float, default=10.0, help="等待退出示教超时[s]")
    r.add_argument("--require-non-teaching-after-enable", action="store_true", default=True, help="enable 后再次检查不在示教模式（默认开启）")
    r.add_argument("--no-require-non-teaching-after-enable", dest="require_non_teaching_after_enable", action="store_false", help="关闭 enable 后非示教检查")
    r.add_argument("--non-teaching-timeout", type=float, default=2.0, help="enable 后等待退出示教的超时[s]")
    r.add_argument("--motion-epsilon", type=float, default=1e-4, help="判定“几乎没动”的平移阈值[m]")
    r.add_argument("--no-motion-warn-steps", type=int, default=5, help="连续多少次没动触发警告（每20步检查一次）")
    r.add_argument("--exec-mode", default="move_p", choices=["move_l", "move_p"], help="回放执行指令类型，默认 move_p（更稳）")
    r.add_argument("--wait-motion-done", action="store_true", default=True, help="每步等待运动完成（默认开启）")
    r.add_argument("--no-wait-motion-done", dest="wait_motion_done", action="store_false", help="关闭每步等待完成")
    r.add_argument("--motion-timeout", type=float, default=1.0, help="单步等待运动完成超时[s]")
    r.add_argument("--retry-nonblocking-on-timeout", action="store_true", default=True, help="wait 超时后自动 non-blocking 重试（默认开启）")
    r.add_argument("--no-retry-nonblocking-on-timeout", dest="retry_nonblocking_on_timeout", action="store_false", help="关闭超时重试")
    r.add_argument("--timeout-switch-threshold", type=int, default=3, help="连续 wait 超时多少次后切 no-wait")
    r.add_argument("--try-fallback-move-p", action="store_true", default=True, help="连续无位移时尝试 move_p fallback（默认开启）")
    r.add_argument("--no-try-fallback-move-p", dest="try_fallback_move_p", action="store_false", help="关闭 move_p fallback")
    r.add_argument("--try-joint-fallback", action="store_true", default=True, help="连续无位移时尝试用 obs/q 做 move_j 兜底（默认开启）")
    r.add_argument("--no-try-joint-fallback", dest="try_joint_fallback", action="store_false", help="关闭 move_j 兜底")
    r.set_defaults(func=cmd_replay)

    m = sub.add_parser("make-config", help="生成 BC-RNN 配置模板")
    m.add_argument("--dataset", required=True)
    m.add_argument("--output", required=True)
    m.add_argument("--exp-name", default="piper_bc_rnn_no_vision")
    m.add_argument("--batch-size", type=int, default=64)
    m.add_argument("--num-epochs", type=int, default=200)
    m.add_argument("--seq-length", type=int, default=10)
    m.add_argument("--rnn-hidden-dim", type=int, default=400)
    m.add_argument("--rnn-layers", type=int, default=2)
    m.set_defaults(func=cmd_make_config)

    return p


def main() -> None:
    parser = build_parser()
    args = parser.parse_args()
    args.func(args)


if __name__ == "__main__":
    main()
