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
"""

from __future__ import annotations

import argparse
import json
import sys
import time
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, List

import h5py
import numpy as np
import threading

try:
    from robot.piper_arm import PiperArm
except ModuleNotFoundError:
    src_dir = Path(__file__).resolve().parents[1] # 含义是：以当前脚本文件为基准，向上两层拿到 src 目录。
    if str(src_dir) not in sys.path: # 避免重复添加
        sys.path.insert(0, str(src_dir))
    from robot.piper_arm import PiperArm

# 监听


@dataclass
class _ReplayPoseState:
    step: int
    total: int
    action: np.ndarray
    pose: np.ndarray


class ReplayPoseMonitor:
    """异步打印回放位姿，减少主回放线程中的 I/O 阻塞。"""

    def __init__(self, print_interval_s: float = 0.10) -> None:
        self.print_interval_s = max(0.01, float(print_interval_s))
        self._stop_event = threading.Event()
        self._lock = threading.Lock()
        self._latest: _ReplayPoseState | None = None
        self._version = 0
        self._thread: threading.Thread | None = None

    def start(self) -> None:
        if self._thread is not None:
            return
        self._thread = threading.Thread(target=self._run, name="replay-pose-monitor", daemon=True)
        self._thread.start()

    def update(self, step: int, total: int, action: np.ndarray, pose: np.ndarray) -> None:
        with self._lock:
            self._latest = _ReplayPoseState(
                step=step,
                total=total,
                action=np.asarray(action, dtype=np.float64).copy(),
                pose=np.asarray(pose, dtype=np.float64).copy(),
            )
            self._version += 1

    def stop(self) -> None:
        self._stop_event.set()
        if self._thread is not None:
            self._thread.join(timeout=1.0)
            self._thread = None

    def _run(self) -> None:
        seen_version = -1
        while not self._stop_event.is_set():
            with self._lock:
                current_version = self._version
                latest = self._latest

            if latest is not None and current_version != seen_version:
                print(
                    f"[INFO] step {latest.step}/{latest.total}, "
                    f"action={latest.action}, next_pose={latest.pose}"
                )
                seen_version = current_version

            time.sleep(self.print_interval_s)

# Action normalization ----------------------------------

ACTION_POS_SCALE = np.array([0.01, 0.01, 0.01], dtype=np.float32) 
ACTION_ROT_SCALE = np.array([0.8, 0.8, 0.8], dtype=np.float32)  


def wrap_to_pi(x: np.ndarray) -> np.ndarray:
    """
    将角度差值包裹到 [-pi, pi]，避免 6D 姿态差分出现 ±2pi 跳变。
    """
    return (x + np.pi) % (2.0 * np.pi) - np.pi


def normalize_action(action_raw: np.ndarray) -> np.ndarray:
    """
    raw 6D action -> normalized 6D action in [-1, 1]
    action_raw = [dx, dy, dz, drx, dry, drz]
    """
    action_raw = np.asarray(action_raw, dtype=np.float32).copy()
    if action_raw.shape[0] != 6:
        raise ValueError(f"expected 6D action, got shape {action_raw.shape}")

    action_raw[3:6] = wrap_to_pi(action_raw[3:6])
    action_raw[0:3] = action_raw[0:3] / ACTION_POS_SCALE
    action_raw[3:6] = action_raw[3:6] / ACTION_ROT_SCALE

    return np.clip(action_raw, -1.0, 1.0)


def denormalize_action(action_norm: np.ndarray) -> np.ndarray:
    """
    normalized 6D action -> raw 6D action
    部署时使用。
    """
    action_norm = np.asarray(action_norm, dtype=np.float32).copy()
    if action_norm.shape[0] != 6:
        raise ValueError(f"expected 6D action, got shape {action_norm.shape}")

    action_norm[0:3] = action_norm[0:3] * ACTION_POS_SCALE
    action_norm[3:6] = action_norm[3:6] * ACTION_ROT_SCALE
    return action_norm


# building the observation --------------------------------
def build_obs(arm: PiperArm) -> Dict:
    """读取一帧 observation。"""

    ts = time.time()
    raw = arm.get_observation_dict(timestamp=ts)
    return {
        "t": float(raw["t"]),
        "q": [float(v) for v in raw["q"]],
        "dq": [float(v) for v in raw["dq"]],
        "tcp_xyz": [float(v) for v in raw["tcp_xyz"]],
        "tcp_pose": [float(v) for v in raw["tcp_pose"]],
    }
# --------------------------------------------------

def get_ctrl_mode(arm: PiperArm):
    """读取控制模式（用于示教模式检测）。"""
    status = arm.get_arm_status()
    if status is None:
        return None
    return getattr(status.msg, "ctrl_mode", None)

# check the teach mode -----------------------------
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
            # check_mode_later=get_ctrl_mode(arm)
            # print(f"[WARN] 等待退出示教模式超时，当前 ctrl_mode={check_mode_later}")
            raise RuntimeError("退出示教模式超时，请手动退出示教后重试 ")
        time.sleep(0.01)

#--------------------------------------------------
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


# check home pos---------------------------------
def is_near_home(arm: PiperArm, tol_rad: float) -> bool:
    """当前关节角是否接近零位。"""
    q = arm.get_joint_position_rad()
    return max(abs(v) for v in q) <= tol_rad


def ensure_home_then_confirm(
    arm: PiperArm,
    tol_rad: float,
    home_speed_percent: int,
    home_timeout: float,
    prompt: str,
) -> None:
    """
    若未在零位则先 go_home，确认到达零位后等待用户回车继续。
    """
    if not is_near_home(arm, tol_rad=tol_rad):
        print("[INFO] 当前不在零位，先执行 go_home")
        if not arm.enable(timeout=8.0):
            raise RuntimeError("go_home 前 enable 失败")
        arm.set_motion_mode_j()
        arm.set_speed_percent(home_speed_percent)
        ok = arm.go_home(wait=True, timeout=home_timeout)
        print(f"[INFO] go_home done, ok={ok}")
        if not ok:
            print("[WARN] go_home 超时，未能确认到达零位，再次执行 go_home")
            ok= arm.go_home(wait=True, timeout=home_timeout)
            if not ok:
                raise RuntimeError("第二次go_home 超时")

    if not is_near_home(arm, tol_rad=tol_rad):
        arm.disable(timeout=1.0)
        raise RuntimeError("go_home 后仍未接近零位，请人工检查")

    input(prompt)


# get action --------------------------
def action_from_obs(prev_obs: Dict, curr_obs: Dict) -> List[float]:
    """
    由相邻两帧 obs 差分得到 6D action，并归一化到 [-1, 1]。
    action = [Δx, Δy, Δz, Δrx, Δry, Δrz]
    """
    p0 = np.asarray(prev_obs["tcp_pose"], dtype=np.float32)
    p1 = np.asarray(curr_obs["tcp_pose"], dtype=np.float32)

    raw = p1 - p0
    raw[3:6] = wrap_to_pi(raw[3:6])

    action = normalize_action(raw)
    return action.tolist()


def create_episode_datasets(ep_group: h5py.Group, num_samples: int) -> None:
    """创建单个 episode 的数据集。"""
    ep_group.attrs["num_samples"] = int(num_samples)

    obs = ep_group.require_group("obs")
    obs.create_dataset("t", shape=(num_samples, 1), dtype=np.float64)
    obs.create_dataset("q", shape=(num_samples, 6), dtype=np.float32)
    obs.create_dataset("dq", shape=(num_samples, 6), dtype=np.float32)
    obs.create_dataset("tcp_xyz", shape=(num_samples, 3), dtype=np.float32)
    obs.create_dataset("tcp_pose", shape=(num_samples, 6), dtype=np.float32)

    ep_group.create_dataset("actions", shape=(num_samples, 6), dtype=np.float32)
    ep_group.create_dataset("rewards", shape=(num_samples,), dtype=np.float32)
    ep_group.create_dataset("dones", shape=(num_samples,), dtype=np.bool_)

def write_sample(
    ep_group: h5py.Group,
    idx: int,
    obs: Dict,
    action: List[float],
    is_last: bool,
) -> None:
    ep_group["obs/t"][idx] = np.asarray([obs["t"]], dtype=np.float64)
    ep_group["obs/q"][idx] = np.asarray(obs["q"], dtype=np.float32)
    ep_group["obs/dq"][idx] = np.asarray(obs["dq"], dtype=np.float32)
    ep_group["obs/tcp_xyz"][idx] = np.asarray(obs["tcp_xyz"], dtype=np.float32)
    ep_group["obs/tcp_pose"][idx] = np.asarray(obs["tcp_pose"], dtype=np.float32)

    ep_group["actions"][idx] = np.asarray(action, dtype=np.float32)
    ep_group["rewards"][idx] = np.float32(0.0)
    ep_group["dones"][idx] = np.bool_(is_last)


def add_file_metadata(f: h5py.File, args: argparse.Namespace, total_samples: int,freq) -> None:
    env_args = {
        "type": "real_robot",
        "env_name": "real_piper_no_vision",
        "env_kwargs": {},

        "robot": "piper",
        "channel": args.channel,
        "tool_type": args.tool_type,
        "tcp_offset": json.loads(args.tcp_offset),

        "nominal_period_s": 1.0 / float(freq),   # 如果后续改采样频率，这里改成 1.0 / collect_freq
        "action_dim": args.action_dim,
        "action_definition": "delta_tcp_pose6_normalized",
        "action_units": "normalized_-1_1",
        "action_raw_units": ["m", "m", "m", "rad", "rad", "rad"],
        "action_pos_scale": ACTION_POS_SCALE.tolist(),
        "action_rot_scale": ACTION_ROT_SCALE.tolist(),
        "q_units": "rad",
        "dq_units": "rad/s",
    }

    data_group = f.require_group("data")
    data_group.attrs["env_args"] = json.dumps(env_args, ensure_ascii=False)
    data_group.attrs["total"] = int(total_samples)

    # 根属性可保留，仅用于 inspect
    f.attrs["env"] = "real_piper_no_vision"
    f.attrs["env_args"] = json.dumps(env_args, ensure_ascii=False)

def cmd_collect(args: argparse.Namespace) -> None:
    # action-dim =3，6；
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
        create_episode_datasets(ep_group, args.samples)
        print(f"[INFO] connect: channel={args.channel}, tool_type={args.tool_type}")
        arm.connect()
        # 前置检查---------------------------------
        try:
            # make sure home pos before collect

            ensure_home_then_confirm(
                arm=arm,
                tol_rad=0.03,
                home_speed_percent=20,
                home_timeout=10,
                prompt="[INFO] 已在零位。请进入示教模式后按回车继续",
            )
            # check teach mode
            print("[INFO] step 1: 请点击示教按钮进入示教模式")
            wait_for_teach_mode(arm, timeout_s=5)
            print("[INFO] 已检测到示教模式")
        except Exception as exc:  
            print(f"[ERROR] 前置检查失败: {exc}")
            return

        # 采集---------------------------------
        try:
            input("[INFO] step 2: 按回车开始采集")
            print(f"[INFO] start collect: action_dim=6, samples={args.samples}")

            collect_freq=100  # 100Hz 采样频率，实测示教动作差分在这个频率下比较合适

            # 为了构造 first sample，需要 2 帧

            obs_prev = build_obs(arm)

            for idx in range(args.samples):
                time.sleep(1.0 / collect_freq)
                obs_curr = build_obs(arm)
                action = action_from_obs(obs_prev, obs_curr)
                # obs_prev是上一时刻的观测，action是从obs_prev到obs_curr的增量动作
                write_sample(ep_group, idx, obs_prev, action, is_last=(idx == args.samples - 1)) 

                obs_prev = obs_curr

                if (idx + 1) % 20 == 0 or idx == args.samples - 1:
                    print(f"[INFO] collected {idx + 1}/{args.samples}")

            add_file_metadata(f, args, args.samples, freq=collect_freq)
            print(f"[INFO] saved: {out_path}")

        finally: # 数据采集结束，机械臂仍处于示教模式；在点击取消示教模式之后，无法检测机械臂当前状态，无法发送指令。似乎只能直接退出。
            input("[INFO] collect done， 请手动退出示教模式，确认后按回车，\n回车结束将会失能机械臂，请注意安全")
       
            arm.reset()

            time.sleep(1)  # 等待机械臂状态更新，避免后续操作过快导致异常
            # arm.disable()     
            # time.sleep(0.5)  # 等待机械臂完全失能，确保安全

            # try:
            #     # check_mode=get_ctrl_mode(arm)
            #     # print(f"[INFO] 当前 ctrl_mode: {check_mode}")
            #     wait_exit_teach_mode(arm, timeout_s=5) # 如果异常，会爆出 RuntimeError，就会执行except块
            #     exited_teach = True
            #     print("[INFO] 已确认退出示教模式")
            # except Exception as exc:
            #     check_mode_later=get_ctrl_mode(arm)
            #     # print(f"[WARN] 等待退出示教模式超时，当前 ctrl_mode={check_mode_later}")
            #     print(f"[WARN] 未确认退出示教模式，跳过 go_home: {exc}")

            # if exited_teach:
            #     print("[INFO] 开始回零位")
            #     ok = arm.go_home(wait=True, timeout=10)
            #     print(f"[INFO] go_home done, ok={ok}")
            #     if not ok:
            #         raise RuntimeError("go_home 超时，未能确认到达零位")




def cmd_inspect(args: argparse.Namespace) -> None:
    in_path = Path(args.input).expanduser().resolve()
    if not in_path.exists():
        raise FileNotFoundError(in_path)

    with h5py.File(in_path, "r") as f:
        print("\n===== HDF5 root attrs =====")
        for k, v in f.attrs.items():
            print(f"{k}: {v}")

        data = f["data"]
        print("\n===== data attrs =====")
        for k, v in data.attrs.items():
            print(f"{k}: {v}")

        for ep_name in data.keys():
            ep = data[ep_name]
            print(f"\n--- episode: {ep_name} ---")
            print(f"num_samples        : {ep.attrs.get('num_samples', 'N/A')}")
            print(f"obs/q shape        : {ep['obs/q'].shape}")
            print(f"obs/dq shape       : {ep['obs/dq'].shape}")
            print(f"obs/tcp_xyz shape  : {ep['obs/tcp_xyz'].shape}")
            print(f"obs/tcp_pose shape : {ep['obs/tcp_pose'].shape}")
            print(f"actions shape      : {ep['actions'].shape}")
            print(f"rewards shape      : {ep['rewards'].shape}")
            print(f"dones shape        : {ep['dones'].shape}")

            act = np.asarray(ep["actions"], dtype=np.float32)

            # 全局统计
            print(f"\n[action global]")
            print(f"action min         : {act.min():.6f}")
            print(f"action max         : {act.max():.6f}")

            if act.shape[1] == 6:
                names = ["x", "y", "z", "rx", "ry", "rz"]

                print("\n[action normalized per-dim]")
                for i, name in enumerate(names):
                    col = act[:, i]
                    print(
                        f"{name:>2s} : "
                        f"min={col.min(): .6f}, "
                        f"max={col.max(): .6f}, "
                        f"mean={col.mean(): .6f}, "
                        f"std={col.std(): .6f}"
                    )

                # 反归一化后再看物理量范围
                act_raw = np.asarray([denormalize_action(a) for a in act], dtype=np.float32)

                print("\n[action raw per-dim]")
                raw_units = ["m", "m", "m", "rad", "rad", "rad"]
                for i, (name, unit) in enumerate(zip(names, raw_units)):
                    col = act_raw[:, i]
                    print(
                        f"{name:>2s} ({unit}) : "
                        f"min={col.min(): .6f}, "
                        f"max={col.max(): .6f}, "
                        f"mean={col.mean(): .6f}, "
                        f"std={col.std(): .6f}"
                    )

            else:
                print(f"[WARN] actions dim is {act.shape[1]}, expected 6 for pose action")

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
    initial_sleep: float = 0.1,
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
        return bool(arm.move_p(pose_list, wait=wait_motion_done, timeout=motion_timeout, initial_sleep=initial_sleep))
    else:
        raise ValueError(f"unsupported exec_mode: {exec_mode}")



# 加入差值 ------------------------------
def _interpolate_pose_linear(
    pose_start: np.ndarray,
    pose_end: np.ndarray,
    num_steps: int,
) -> List[np.ndarray]:
    """
    对 6D tcp pose 做线性插值。
    返回从 pose_start 到 pose_end 的中间点序列（不含起点，含终点）。

    pose = [x, y, z, rx, ry, rz]
    注意：
    这里对欧拉角也是做线性插值，仅适用于相邻步姿态变化较小的情况。
    由于你当前 action 本来就是相邻采样差分，因此通常可接受。
    """
    pose_start = np.asarray(pose_start, dtype=np.float64)
    pose_end = np.asarray(pose_end, dtype=np.float64)

    if pose_start.shape[0] != 6 or pose_end.shape[0] != 6:
        raise ValueError("pose_start and pose_end must be 6D")

    num_steps = max(1, int(num_steps))
    out = []

    delta = pose_end - pose_start
    delta[3:6] = wrap_to_pi(delta[3:6])

    for k in range(1, num_steps + 1):
        alpha = k / num_steps
        pose_k = pose_start.copy()
        pose_k[:3] = pose_start[:3] + alpha * delta[:3]
        pose_k[3:6] = pose_start[3:6] + alpha * delta[3:6]
        pose_k[3:6] = wrap_to_pi(pose_k[3:6])
        out.append(pose_k)

    return out

def _send_pose_command_with_interp(
    arm: PiperArm,
    pose_curr: np.ndarray,
    pose_next: np.ndarray,
    exec_mode: str,
    interp_steps: int,
    wait_motion_done: bool,
    motion_timeout: float,
    initial_sleep: float = 0.1,
    step_sleep: float = 0.02,
) -> bool:
    """
    将 pose_curr -> pose_next 拆成若干线性插值点，并逐点执行 move_p / move_l。
    返回最后一次命令的执行结果。
    """
    interp_poses = _interpolate_pose_linear(
        pose_start=pose_curr,
        pose_end=pose_next,
        num_steps=interp_steps,
    )

    ok = True
    for pose_mid in interp_poses:
        ok = _send_pose_command(
            arm=arm,
            pose_next=pose_mid,
            exec_mode=exec_mode,
            wait_motion_done=wait_motion_done,
            motion_timeout=motion_timeout,
            initial_sleep=initial_sleep,
        )
        time.sleep(step_sleep)

    return ok



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
        pose_monitor = ReplayPoseMonitor(print_interval_s=1.0)

        # 默认0表示全回放，不限制
        if args.max_steps > 0:
            actions = actions[: args.max_steps]
            if obs_q is not None:
                obs_q = obs_q[: args.max_steps]


        # 前置内容------------------------------------------
        try:
            print(f"[INFO] connect: channel={args.channel}")
            arm.connect()
            print("[INFO] 请确保已退出示教模式（回放需要非示教状态）")


            if not arm.enable(timeout=5.0):
                raise RuntimeError("enable failed")
            print("[INFO] enabled")

            ensure_home_then_confirm(
                arm=arm,
                tol_rad=0.03,
                home_speed_percent=20,
                home_timeout=10,
                prompt="[INFO] 已在零位。按回车开始回放",
            )
        except Exception as exc:
            print(f"[ERROR] 前置检查失败: {exc}")
            return
        
        # replay the trajectory------------------------------------------
        try:
            print_runtime_state(arm, "after_home_before_replay")
            pose_monitor.start()

            # prev_action = None
            time0= time.time()
            for i, act in enumerate(actions):
                # denormalize action
                act = denormalize_action(act)
                # 过小的动作可能无法触发运动。通过死区和缩放调整到合适范围。
                # act = _apply_deadband_and_scale(
                #     act,
                #     action_scale=1,
                #     min_pos_step=0.00001,
                #     min_rot_step=0.00001,
                # )
                # 动作限幅，保护实机安全
                # act = _clip_action(act, 0.5, 0.5)

                # # 一阶低通平滑
                # act = _smooth_action(act, prev_action, 0.9)

                curr_pose = np.asarray(arm.get_tcp_pose6(), dtype=np.float64)
                next_pose = _compose_next_pose(curr_pose, act)
                pose_monitor.update(i + 1, len(actions), act, next_pose)
                next_pose[3] =np.clip(next_pose[3], -np.pi, np.pi)
                next_pose[4] = np.clip(next_pose[4], -np.pi/2, np.pi/2)
                next_pose[5] = np.clip(next_pose[5], -np.pi, np.pi)

                arm.set_motion_mode_p()
                arm.set_speed_percent(1)
                _send_pose_command(
                    arm=arm,
                    pose_next=next_pose,
                    exec_mode="move_p",
                    wait_motion_done=True, # 等待反馈指令=0
                    motion_timeout=0.3,
                    initial_sleep=0.02,
                )
                # prev_action = act.copy()

                #time.sleep(0.1) # 0.1效果挺不错的，可以再降低点速度试试。另外，进行线性插值。
            time1 = time.time()
            print(f"[INFO] replay finished, total_time={time1-time0:.2f}s")
            print("[INFO] replay done")

            print("[INFO] go home after replay")
            arm.set_motion_mode_j()
            arm.set_speed_percent(20)
            home_ok = arm.go_home(wait=True, timeout=5)
            print(f"[INFO] go_home done, ok={home_ok}")

        finally:
            pose_monitor.stop()
            print("[INFO] replay over")
        #     arm.disable(timeout=8.0)


def cmd_make_config(args: argparse.Namespace) -> None:
    cfg = {
        "algo_name": "bc",
        "experiment": {
            "name": "piper_bc_rnn_no_vision",
            "validate": True,
            "logging": {
                "terminal_output_to_txt": True,
                "log_tb": True,
                "log_wandb": False,
                "wandb_proj_name": "debug"
            },
            "save": {
                "enabled": True,
                "every_n_seconds": None,
                "every_n_epochs": 10,
                "epochs": [],
                "on_best_validation": False,
                "on_best_rollout_return": False,
                "on_best_rollout_success_rate": False
            },
            "epoch_every_n_steps": 100,
            "validation_epoch_every_n_steps": 10,
            "env": None,
            "additional_envs": None,
            "render": False,
            "render_video": False,
            "keep_all_videos": False,
            "video_skip": 5,
            "rollout": {
                "enabled": False,
                "n": 0,
                "horizon": 0,
                "rate": 0,
                "warmstart": 0,
                "terminate_on_success": False
            },
            "env_meta_update_dict": {},
            "ckpt_path": None
        },
        "train": {
            "data": [
                {
                    "path": args.dataset
                }
            ],
            "output_dir": args.output,
            "normalize_weights_by_ds_size": False,
            "num_data_workers": 0,
            "hdf5_cache_mode": "all",
            "hdf5_use_swmr": True,
            "hdf5_load_next_obs": False,
            "hdf5_normalize_obs": False,
            "hdf5_filter_key": None,
            "hdf5_validation_filter_key": None,
            "seq_length": 50,
            "pad_seq_length": True,
            "frame_stack": 1,
            "pad_frame_stack": True,
            "dataset_keys": [
                "actions",
                "obs/q",
                "obs/dq",
                "obs/tcp_pose"
            ],
            "action_keys": [
                "actions"
            ],
            "action_config": {
                "actions": {
                    "normalization": None
                }
            },
            "goal_mode": None,
            "cuda": True,
            "batch_size": 64,
            "num_epochs": 200,
            "seed": 1,
            "max_grad_norm": None
        },
        "algo": {
            "optim_params": {
                "policy": {
                    "optimizer_type": "adam",
                    "learning_rate": {
                        "initial": 1e-4,
                        "decay_factor": 0.1,
                        "epoch_schedule": []
                    },
                    "regularization": {
                        "L2": 0.0
                    }
                }
            },
            "loss": {
                "l2_weight": 1.0,
                "l1_weight": 0.0,
                "cos_weight": 0.0
            },
            "actor_layer_dims": [300, 400],
            "gaussian": {
                "enabled": False
            },
            "gmm": {
                "enabled": False
            },
            "vae": {
                "enabled": False
            },
            "rnn": {
                "enabled": True,
                "horizon": 50,
                "hidden_dim": 400,
                "rnn_type": "LSTM",
                "num_layers": 2,
                "open_loop": False,
                "kwargs": {
                    "bidirectional": False
                }
            },
            "transformer": {
                "enabled": False
            }
        },
        "observation": {
            "modalities": {
                "obs": {
                    "low_dim": [
                        "q",
                        "dq",
                        "tcp_pose"
                    ],
                    "rgb": [],
                    "depth": [],
                    "scan": []
                },
                "goal": {
                    "low_dim": [],
                    "rgb": [],
                    "depth": [],
                    "scan": []
                }
            },
            "encoder": {
                "low_dim": {
                    "core_class": None,
                    "core_kwargs": {},
                    "obs_randomizer_class": None,
                    "obs_randomizer_kwargs": {}
                },
                "rgb": {
                    "core_class": "VisualCore",
                    "core_kwargs": {},
                    "obs_randomizer_class": None,
                    "obs_randomizer_kwargs": {}
                },
                "depth": {
                    "core_class": "VisualCore",
                    "core_kwargs": {},
                    "obs_randomizer_class": None,
                    "obs_randomizer_kwargs": {}
                },
                "scan": {
                    "core_class": "ScanCore",
                    "core_kwargs": {},
                    "obs_randomizer_class": None,
                    "obs_randomizer_kwargs": {}
                }
            }
        },
        "meta": {
            "hp_base_config_file": None,
            "hp_keys": [],
            "hp_values": []
        }
    }

    out_path = Path(args.output).expanduser().resolve()
    out_path.parent.mkdir(parents=True, exist_ok=True)
    out_path.write_text(json.dumps(cfg, indent=2, ensure_ascii=False), encoding="utf-8")
    print(f"[INFO] wrote config: {out_path}")

def build_parser() -> argparse.ArgumentParser:
    p = argparse.ArgumentParser(description="Piper 无视觉 imitation 最小闭环工具")
    sub = p.add_subparsers(dest="cmd", required=True)

    c = sub.add_parser("collect", help="采集并写入 HDF5")
    c.add_argument("--output", default="data/demo_6d_010.hdf5")
    c.add_argument("--episode-name", default="demo_0")
    c.add_argument("--samples", type=int, default=1000)
    c.add_argument("--action-dim", type=int, default=6, choices=[3, 6])
    c.add_argument("--channel", default="can0")
    c.add_argument("--tool-type", default="none", choices=["none", "custom_tool", "agx_gripper"])
    c.add_argument("--tcp-offset", default="[0,0,0,0,0,0]")
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
    r.add_argument("--no-require-exit-teach-mode", dest="require_exit_teach_mode", action="store_false", help="关闭退出示教检查")
    r.add_argument("--non-teaching-timeout", type=float, default=2.0, help="enable 后等待退出示教的超时[s]")
    r.add_argument("--no-ensure-home-before-replay", dest="ensure_home_before_replay", action="store_false", help="关闭回放前零位检查")
    r.add_argument("--exec-mode", default="move_p", choices=["move_l", "move_p"], help="回放执行指令类型，默认 move_p（更稳）")
    r.add_argument("--no-retry-nonblocking-on-timeout", dest="retry_nonblocking_on_timeout", action="store_false", help="关闭超时重试")
    r.add_argument("--try-fallback-move-p", action="store_true", default=True, help="连续无位移时尝试 move_p fallback（默认开启）")
    r.add_argument("--no-try-fallback-move-p", dest="try_fallback_move_p", action="store_false", help="关闭 move_p fallback")
    r.add_argument("--try-joint-fallback", action="store_true", default=True, help="连续无位移时尝试用 obs/q 做 move_j 兜底（默认开启）")
    r.add_argument("--no-try-joint-fallback", dest="try_joint_fallback", action="store_false", help="关闭 move_j 兜底")
    r.set_defaults(func=cmd_replay)

    m = sub.add_parser("make-config", help="生成 BC-RNN 配置模板")
    m.add_argument("--dataset", required=True, default = "data/demo_6d_010.hdf5")
    m.add_argument("--output", required=True, default= "bc_rnn_no_vision010.json")
    m.set_defaults(func=cmd_make_config)

    return p


def main() -> None:
    parser = build_parser()
    args = parser.parse_args()
    args.func(args)


if __name__ == "__main__":
    main()
