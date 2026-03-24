#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""精简版：基于 pyAgxArm 录制轨迹（无 argparse）。

直接修改下方配置区即可。
CSV 格式:
    wait_time,j1,j2,j3,j4,j5,j6[,gripper_width]
"""

import csv
import os
import time
from typing import List

from piper_arm import PiperArm


# ======================== 配置区（按需修改） ========================
CHANNEL = "can0"
ROBOT_NAME = "piper"
HAVE_GRIPPER = False

# 最大录制时间（秒），0 表示无限
RECORD_TIME = 10.0
# 等待示教模式超时（秒）
TEACH_TIMEOUT = 10.0
# 采样间隔（秒）
SAMPLE_INTERVAL = 0.01
# 最小变化阈值（rad / m）
CHANGE_EPS = 1e-4

CSV_PATH = os.path.join(os.path.dirname(__file__), "trajectory_simple0.csv")
# ==================================================================


def get_ctrl_mode(arm: PiperArm):
    status = arm.get_arm_status()
    if status is None:
        return None
    return getattr(status.msg, "ctrl_mode", None)


def get_gripper_width(arm: PiperArm):
    if arm.end_effector is None:
        return None
    gs = arm.end_effector.get_gripper_status()
    if gs is None:
        return None
    return getattr(gs.msg, "width", None)


def state_changed(prev: List[float], cur: List[float], eps: float) -> bool:
    if len(prev) != len(cur):
        return True
    return any(abs(a - b) > eps for a, b in zip(prev, cur))


def main() -> None:
    arm = PiperArm(
        channel=CHANNEL,
        robot_name=ROBOT_NAME,
        auto_connect=False,
        tool_type="agx_gripper" if HAVE_GRIPPER else "none",
    )

    print(f"[INFO] connect: channel={CHANNEL}, robot={ROBOT_NAME}")
    arm.connect()

    have_gripper = HAVE_GRIPPER
    if have_gripper:
        try:
            arm.init_effector("agx_gripper")
        except Exception as exc:  # noqa: BLE001
            print(f"[WARN] init gripper failed, continue without gripper: {exc}")
            have_gripper = False

    print("step 1: 请点击示教按钮进入示教模式")
    end_t = time.monotonic() + TEACH_TIMEOUT
    while get_ctrl_mode(arm) != 2:
        if time.monotonic() > end_t:
            raise RuntimeError("示教模式检测超时，请检查示教模式是否开启")
        time.sleep(0.01)

    input("step 2: 回车开始录制轨迹")

    os.makedirs(os.path.dirname(CSV_PATH), exist_ok=True)
    with open(CSV_PATH, "w", newline="", encoding="utf-8") as f:
        writer = csv.writer(f)

        cur = arm.get_joint_position_rad()
        if have_gripper:
            width = get_gripper_width(arm)
            if width is not None:
                cur = cur + [float(width)]

        last_pos = cur
        last_t = time.monotonic()
        stop_t = float("inf") if RECORD_TIME == 0 else last_t + RECORD_TIME

        while time.monotonic() < stop_t:
            cur = arm.get_joint_position_rad()
            if have_gripper:
                width = get_gripper_width(arm)
                if width is not None:
                    cur = cur + [float(width)]

            if state_changed(last_pos, cur, CHANGE_EPS):
                now = time.monotonic()
                wait_time = now - last_t
                writer.writerow([wait_time] + cur)
                print(f"INFO: 等待时间:{wait_time:0.4f}s，当前位置: {cur}")
                last_pos = cur
                last_t = now

            time.sleep(SAMPLE_INTERVAL)

    print(f"INFO: 录制结束，轨迹已保存到: {CSV_PATH}")
    print("INFO: 请再次点击示教按钮退出示教模式")


if __name__ == "__main__":
    main()
