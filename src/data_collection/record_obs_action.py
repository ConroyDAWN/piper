#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import time
from piper_arm import PiperArm


def main():
    arm = PiperArm(
        channel="can0",
        auto_connect=False,
        tool_type="none",   # 或 "custom_tool"
        tcp_offset=[0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
    )

    try:
        print("[INFO] connect")
        arm.connect()

        print("[INFO] enable")
        if not arm.enable(timeout=8.0):
            raise RuntimeError("enable failed")

        print("[INFO] start observing")

        # 至少需要 3 帧，才能构造 obs/action/last_action
        obs_t_minus_2 = arm.get_observation_dict()
        arm.print_observation(obs_t_minus_2)

        time.sleep(0.05)
        obs_t_minus_1 = arm.get_observation_dict()
        arm.print_observation(obs_t_minus_1)

        while True:
            time.sleep(0.05)
            obs_t = arm.get_observation_dict()

            sample = arm.build_sample_with_last_action(
                prev_prev_obs=obs_t_minus_2,
                prev_obs=obs_t_minus_1,
                curr_obs=obs_t,
            )

            arm.print_sample(sample)

            # 滚动窗口更新
            obs_t_minus_2 = obs_t_minus_1
            obs_t_minus_1 = obs_t

    except KeyboardInterrupt:
        print("\n[INFO] stop by user")

    finally:
        print("[INFO] disable")
        arm.disable(timeout=8.0)


if __name__ == "__main__":
    main()