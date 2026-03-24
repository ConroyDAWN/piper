#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import argparse
import json
import sys
import time
from pathlib import Path
from typing import Dict, List, Optional

try:
    from robot.piper_arm import PiperArm
except ModuleNotFoundError:
    src_dir = Path(__file__).resolve().parents[1]
    if str(src_dir) not in sys.path:
        sys.path.insert(0, str(src_dir))
    from robot.piper_arm import PiperArm


def obs_to_sample(prev_prev_obs: Dict, prev_obs: Dict, curr_obs: Dict) -> Dict:
    """
    固定 sample 结构为:
        {
            "obs": 当前 observation,
            "action": 当前位移增量 [δx, δy, δz],
            "last_action": 上一帧位移增量 [δx_prev, δy_prev, δz_prev]
        }
    单位:
        q          -> rad
        dq         -> rad/s
        tcp_pose   -> [m, m, m, rad, rad, rad]
        tcp_xyz    -> [m, m, m]
        action     -> [m, m, m]
        last_action-> [m, m, m]
    """
    prev_prev_xyz = prev_prev_obs["tcp_xyz"]
    prev_xyz = prev_obs["tcp_xyz"]
    curr_xyz = curr_obs["tcp_xyz"]

    last_action = [
        float(prev_xyz[0] - prev_prev_xyz[0]),
        float(prev_xyz[1] - prev_prev_xyz[1]),
        float(prev_xyz[2] - prev_prev_xyz[2]),
    ]
    action = [
        float(curr_xyz[0] - prev_xyz[0]),
        float(curr_xyz[1] - prev_xyz[1]),
        float(curr_xyz[2] - prev_xyz[2]),
    ]

    return {
        "obs": curr_obs,
        "action": action,
        "last_action": last_action,
    }


def print_sample(sample: Dict, precision: int = 6) -> None:
    def fmt(vals: List[float]) -> str:
        return "[" + ", ".join(f"{float(v):.{precision}f}" for v in vals) + "]"

    obs = sample["obs"]
    print("\n========== Sample ==========")
    print(f"t              : {obs['t']:.6f}")
    print(f"q (rad)        : {fmt(obs['q'])}")
    print(f"dq (rad/s)     : {fmt(obs['dq'])}")
    print(f"tcp_xyz (m)    : {fmt(obs['tcp_xyz'])}")
    print(f"tcp_pose (6D)  : {fmt(obs['tcp_pose'])}")
    print(f"action (m)     : {fmt(sample['action'])}")
    print(f"last_action(m) : {fmt(sample['last_action'])}")
    print("============================\n")


def main() -> None:
    parser = argparse.ArgumentParser(description="采集并打印固定 sample 结构: {obs, action, last_action}")
    parser.add_argument("--channel", default="can0")
    parser.add_argument("--tool-type", default="none", choices=["none", "custom_tool", "agx_gripper", "revo2"])
    parser.add_argument("--tcp-offset", default="[0,0,0,0,0,0]", help="JSON list, 单位 [m,m,m,rad,rad,rad]")
    parser.add_argument("--period", type=float, default=0.05, help="采样周期，默认 0.05 s (20 Hz)")
    parser.add_argument("--count", type=int, default=0, help="采样 sample 数，0 表示直到 Ctrl+C")
    args = parser.parse_args()

    tcp_offset = json.loads(args.tcp_offset)

    arm = PiperArm(
        channel=args.channel,
        auto_connect=False,
        tool_type=args.tool_type,
        tcp_offset=tcp_offset,
    )

    try:
        print(f"[INFO] connect: channel={args.channel}, tool_type={args.tool_type}")
        arm.connect()

        print("[INFO] enable")
        if not arm.enable(timeout=8.0):
            raise RuntimeError("enable failed")

        print(f"[INFO] start observing, nominal period={args.period:.4f}s")

        obs_t_minus_2 = arm.get_observation_dict()
        time.sleep(args.period)
        obs_t_minus_1 = arm.get_observation_dict()

        n = 0
        while True:
            time.sleep(args.period)
            obs_t = arm.get_observation_dict()
            sample = obs_to_sample(obs_t_minus_2, obs_t_minus_1, obs_t)
            print_sample(sample)

            obs_t_minus_2 = obs_t_minus_1
            obs_t_minus_1 = obs_t
            n += 1
            if args.count > 0 and n >= args.count:
                break

    except KeyboardInterrupt:
        print("\n[INFO] stop by user")
    finally:
        print("[INFO] disable")
        arm.disable(timeout=8.0)


if __name__ == "__main__":
    main()
