#!/usr/bin/env python3
# -*- coding: utf-8 -*-

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


DATASET_SPEC = {
    "obs/q": (6, np.float32),
    "obs/dq": (6, np.float32),
    "obs/tcp_pose": (6, np.float32),
    "obs/tcp_xyz": (3, np.float32),
    "obs/t": (1, np.float64),
    "action": (3, np.float32),
    "last_action": (3, np.float32),
}


def obs_to_sample(prev_prev_obs: Dict, prev_obs: Dict, curr_obs: Dict) -> Dict:
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


def make_datasets(ep_group: h5py.Group, num_samples: int) -> None:
    obs_group = ep_group.require_group("obs")
    obs_group.create_dataset("q", shape=(num_samples, 6), dtype=np.float32)
    obs_group.create_dataset("dq", shape=(num_samples, 6), dtype=np.float32)
    obs_group.create_dataset("tcp_pose", shape=(num_samples, 6), dtype=np.float32)
    obs_group.create_dataset("tcp_xyz", shape=(num_samples, 3), dtype=np.float32)
    obs_group.create_dataset("t", shape=(num_samples, 1), dtype=np.float64)
    ep_group.create_dataset("actions", shape=(num_samples, 3), dtype=np.float32)
    ep_group.create_dataset("last_actions", shape=(num_samples, 3), dtype=np.float32)


def write_sample(ep_group: h5py.Group, idx: int, sample: Dict) -> None:
    obs = sample["obs"]
    ep_group["obs/q"][idx] = np.asarray(obs["q"], dtype=np.float32)
    ep_group["obs/dq"][idx] = np.asarray(obs["dq"], dtype=np.float32)
    ep_group["obs/tcp_pose"][idx] = np.asarray(obs["tcp_pose"], dtype=np.float32)
    ep_group["obs/tcp_xyz"][idx] = np.asarray(obs["tcp_xyz"], dtype=np.float32)
    ep_group["obs/t"][idx] = np.asarray([obs["t"]], dtype=np.float64)
    ep_group["actions"][idx] = np.asarray(sample["action"], dtype=np.float32)
    ep_group["last_actions"][idx] = np.asarray(sample["last_action"], dtype=np.float32)


def add_metadata(f: h5py.File, args: argparse.Namespace, num_samples: int) -> None:
    f.attrs["env"] = "real_piper"
    f.attrs["env_args"] = json.dumps({
        "type": "real_robot",
        "robot": "piper",
        "channel": args.channel,
        "tool_type": args.tool_type,
        "tcp_offset": json.loads(args.tcp_offset),
        "action_definition": "delta_tcp_xyz",
        "action_units": "m",
        "q_units": "rad",
        "dq_units": "rad/s",
        "tcp_pose_units": ["m", "m", "m", "rad", "rad", "rad"],
        "tcp_xyz_units": "m",
        "nominal_period_s": args.period,
    }, ensure_ascii=False)
    data_group = f["data"]
    data_group.attrs["total"] = int(num_samples)


def main() -> None:
    parser = argparse.ArgumentParser(description="采集 Piper 数据并写入 robomimic 风格 HDF5")
    parser.add_argument("--output", required=True, help="输出 HDF5 路径，例如 demo_000.hdf5")
    parser.add_argument("--channel", default="can0")
    parser.add_argument("--tool-type", default="none", choices=["none", "custom_tool", "agx_gripper", "revo2"])
    parser.add_argument("--tcp-offset", default="[0,0,0,0,0,0]", help="JSON list, 单位 [m,m,m,rad,rad,rad]")
    parser.add_argument("--period", type=float, default=0.05, help="采样周期，默认 0.05 s")
    parser.add_argument("--samples", type=int, required=True, help="要写入的 sample 数")
    parser.add_argument("--episode-name", default="demo_0", help="HDF5 内 episode 名")
    args = parser.parse_args()

    if args.samples <= 0:
        raise ValueError("--samples 必须 > 0")

    tcp_offset = json.loads(args.tcp_offset)
    out_path = Path(args.output).expanduser().resolve()
    out_path.parent.mkdir(parents=True, exist_ok=True)

    arm = PiperArm(
        channel=args.channel,
        auto_connect=False,
        tool_type=args.tool_type,
        tcp_offset=tcp_offset,
    )

    with h5py.File(out_path, "w") as f:
        data_group = f.require_group("data")
        ep_group = data_group.require_group(args.episode_name)
        make_datasets(ep_group, args.samples)

        try:
            print(f"[INFO] connect: channel={args.channel}, tool_type={args.tool_type}")
            arm.connect()

            print("[INFO] enable")
            if not arm.enable(timeout=8.0):
                raise RuntimeError("enable failed")

            print(f"[INFO] start recording to {out_path}")
            print(f"[INFO] nominal period={args.period:.4f}s, samples={args.samples}")

            # 三帧预热，才能构造第一条 sample
            obs_t_minus_2 = arm.get_observation_dict()
            time.sleep(args.period)
            obs_t_minus_1 = arm.get_observation_dict()

            for idx in range(args.samples):
                time.sleep(args.period)
                obs_t = arm.get_observation_dict()
                sample = obs_to_sample(obs_t_minus_2, obs_t_minus_1, obs_t)
                write_sample(ep_group, idx, sample)

                obs_t_minus_2 = obs_t_minus_1
                obs_t_minus_1 = obs_t

                if (idx + 1) % 20 == 0 or idx == args.samples - 1:
                    print(f"[INFO] recorded {idx + 1}/{args.samples}")

            add_metadata(f, args, args.samples)
            print(f"[INFO] saved HDF5: {out_path}")

        except KeyboardInterrupt:
            # 中断时裁剪已写入部分；这里只提示，避免复杂重写。更稳妥是使用固定 samples 完整录制。
            print("\n[INFO] interrupted by user; file contains data written before interruption")
            add_metadata(f, args, args.samples)
        finally:
            print("[INFO] disable")
            arm.disable(timeout=8.0)


if __name__ == "__main__":
    main()
