#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""精简版：基于 pyAgxArm 播放轨迹（无 argparse）。

直接修改下方配置区即可。
固定使用 move_j。
CSV 格式:
    wait_time,j1,j2,j3,j4,j5,j6[,gripper_width]
"""

import csv
import os
import signal
import time
from typing import Dict, List, Tuple

from piper_arm import PiperArm


# ======================== 配置区（按需修改） ========================
CHANNEL = "can0"
ROBOT_NAME = "piper"
HAVE_GRIPPER = False

# 播放次数，0 表示无限
PLAY_TIMES = 1
# 每轮播放结束后等待（秒）
PLAY_INTERVAL = 1.0
# 速度百分比（0~100）
MOVE_SPEED = 100
# 播放倍率（>0）
PLAY_SPEED = 1.0

# 示教模式检查超时（秒）
MODE_TIMEOUT = 5.0
# 使能超时（秒）
ENABLE_TIMEOUT = 8.0

# 是否按关节限位裁剪目标值
CLIP_TO_LIMITS = True

CSV_PATH = os.path.join(os.path.dirname(__file__), "trajectory_simple0.csv")
# ==================================================================


def load_track(csv_path: str) -> List[List[float]]:
    with open(csv_path, "r", encoding="utf-8") as f:
        rows = list(csv.reader(f))
    if not rows:
        raise RuntimeError("轨迹文件为空")
    return [[float(v) for v in row] for row in rows]


def get_joint_limits(arm: PiperArm) -> Dict[int, Tuple[float, float]]:
    limits = {}
    cfg_limits = arm.robot_cfg.get("joint_limits", {})
    for i in range(1, 7):
        key = f"joint{i}"
        if key in cfg_limits and len(cfg_limits[key]) == 2:
            lo, hi = cfg_limits[key]
            limits[i] = (float(lo), float(hi))
    return limits


def clip_joints(joints: List[float], limits: Dict[int, Tuple[float, float]]) -> Tuple[List[float], bool]:
    out = list(joints)
    changed = False
    for i, q in enumerate(out, start=1):
        if i not in limits:
            continue
        lo, hi = limits[i]
        q_new = min(max(q, lo), hi)
        if q_new != q:
            out[i - 1] = q_new
            changed = True
    return out, changed


def get_ctrl_mode(arm: PiperArm):
    status = arm.get_arm_status()
    if status is None:
        return None
    return getattr(status.msg, "ctrl_mode", None)


def wait_exit_teach_mode(arm: PiperArm, timeout: float) -> bool:
    start_t = time.monotonic()
    got_feedback = False
    while True:
        mode = get_ctrl_mode(arm)
        if mode is not None:
            got_feedback = True
            if mode != 2:
                return True

        if time.monotonic() - start_t > timeout:
            if not got_feedback:
                print("[WARN] 未收到 ctrl_mode 反馈，继续尝试使能")
                return True
            return False
        time.sleep(0.05)


def enable_gripper_with_retry(arm: PiperArm, timeout: float = 3.0) -> bool:
    start_t = time.monotonic()
    while True:
        try:
            if arm.end_effector is not None and arm.end_effector.enable_gripper():
                return True
        except Exception:  # noqa: BLE001
            pass
        if time.monotonic() - start_t > timeout:
            return False
        time.sleep(0.05)


def wait_joints_near_home(arm: PiperArm, timeout: float = 25.0, tol_rad: float = 0.03) -> bool:
    start_t = time.monotonic()
    last_pub = 0.0
    while time.monotonic() - start_t <= timeout:
        now = time.monotonic()
        if now - last_pub >= 0.25:
            arm.move_j([0.0] * 6, wait=False)
            last_pub = now

        try:
            q = arm.get_joint_position_rad()
            if q and max(abs(v) for v in q) <= tol_rad:
                return True
        except Exception:
            pass

        time.sleep(0.05)
    return False


def safe_shutdown(arm: PiperArm, try_home: bool) -> None:
    old_sigint = signal.getsignal(signal.SIGINT)
    try:
        signal.signal(signal.SIGINT, signal.SIG_IGN)
    except Exception:
        old_sigint = None

    try:
        if try_home:
            try:
                print("[INFO] go home before disable")
                if arm.enable(timeout=3.0):
                    arm.set_speed_percent(20)
                    arm.set_motion_mode_j()
                    ok = wait_joints_near_home(arm, timeout=25.0, tol_rad=0.03)
                    if not ok:
                        print("[WARN] go home timeout")
                else:
                    print("[WARN] enable before go home failed")
            except Exception as exc:  # noqa: BLE001
                print(f"[WARN] go home failed: {exc}")

        try:
            print("[INFO] disable")
            if not arm.disable(timeout=8.0):
                print("[WARN] disable timeout")
        except Exception as exc:  # noqa: BLE001
            print(f"[WARN] disable failed: {exc}")
    finally:
        if old_sigint is not None:
            try:
                signal.signal(signal.SIGINT, old_sigint)
            except Exception:
                pass


def main() -> None:
    if PLAY_SPEED <= 0:
        raise ValueError("PLAY_SPEED 必须大于 0")
    if not os.path.exists(CSV_PATH):
        raise FileNotFoundError(f"轨迹文件不存在: {CSV_PATH}")

    track = load_track(CSV_PATH)

    arm = PiperArm(
        channel=CHANNEL,
        robot_name=ROBOT_NAME,
        auto_connect=False,
        tool_type="agx_gripper" if HAVE_GRIPPER else "none",
    )

    connected = False
    enabled = False
    clip_warned = False
    have_gripper = HAVE_GRIPPER

    try:
        print(f"[INFO] connect: channel={CHANNEL}, robot={ROBOT_NAME}")
        arm.connect()
        connected = True

        if have_gripper:
            try:
                arm.init_effector("agx_gripper")
                if not enable_gripper_with_retry(arm, timeout=3.0):
                    print("[WARN] gripper enable timeout, continue without gripper")
                    have_gripper = False
            except Exception as exc:  # noqa: BLE001
                print(f"[WARN] init gripper failed, continue without gripper: {exc}")
                have_gripper = False

        print("step 1: 播放前请确保机械臂已退出示教模式")
        if not wait_exit_teach_mode(arm, timeout=MODE_TIMEOUT):
            print("[WARN] 仍处于示教模式，将继续尝试使能")

        print("[INFO] enable")
        if not arm.enable(timeout=ENABLE_TIMEOUT):
            raise RuntimeError("enable 失败：超时")
        enabled = True

        arm.set_speed_percent(MOVE_SPEED)
        arm.set_motion_mode_j()

        limits = get_joint_limits(arm)

        input("step 2: 回车开始播放轨迹")

        count = 0
        while PLAY_TIMES == 0 or count < abs(PLAY_TIMES):
            for i, row in enumerate(track):
                if len(row) < 7:
                    raise RuntimeError("轨迹列数错误，至少需要 wait_time + 6 joint")

                wait_time = row[0] / PLAY_SPEED
                joints = row[1:7]

                if CLIP_TO_LIMITS:
                    joints, changed = clip_joints(joints, limits)
                    if changed and not clip_warned:
                        print("[WARN] 轨迹存在越限关节，已自动裁剪到关节限位")
                        clip_warned = True

                # 固定使用 move_j
                arm.move_j(joints, wait=False)

                if have_gripper and len(row) >= 8:
                    arm.gripper_move(row[7], sleep_after=0.0)

                print(
                    f"INFO: 第{count + 1}次播放[j]，等待时间:{wait_time:0.4f}s，目标位置: {row[1:]}"
                )

                if i == len(track) - 1:
                    time.sleep(PLAY_INTERVAL)
                else:
                    time.sleep(max(0.0, wait_time))

            count += 1

    except KeyboardInterrupt:
        print("\n[WARN] interrupted by user, running safe shutdown...")
    finally:
        if connected:
            safe_shutdown(arm, try_home=enabled)


if __name__ == "__main__":
    main()
