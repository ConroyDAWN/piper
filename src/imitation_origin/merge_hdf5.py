#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import argparse
import json
from pathlib import Path

import h5py
import numpy as np


def copy_demo(src_ep: h5py.Group, dst_ep: h5py.Group):
    # attrs
    for k, v in src_ep.attrs.items():
        dst_ep.attrs[k] = v

    # obs
    src_obs = src_ep["obs"]
    dst_obs = dst_ep.require_group("obs")
    for key in src_obs.keys():
        dst_obs.create_dataset(key, data=src_obs[key][:], dtype=src_obs[key].dtype)

    # top-level datasets
    for key in ["actions", "rewards", "dones"]:
        dst_ep.create_dataset(key, data=src_ep[key][:], dtype=src_ep[key].dtype)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--inputs", nargs="+", required=True, help="多个单轨迹 hdf5 文件")
    parser.add_argument("--output", required=True, help="输出总 hdf5 文件")
    args = parser.parse_args()

    input_paths = [Path(p).expanduser().resolve() for p in args.inputs]
    output_path = Path(args.output).expanduser().resolve()
    output_path.parent.mkdir(parents=True, exist_ok=True)

    total = 0
    env_args_ref = None
    demo_idx = 0

    with h5py.File(output_path, "w") as fout:
        data_out = fout.require_group("data")

        for in_path in input_paths:
            with h5py.File(in_path, "r") as fin:
                data_in = fin["data"]

                if env_args_ref is None:
                    env_args_ref = data_in.attrs["env_args"]
                    data_out.attrs["env_args"] = env_args_ref
                    fout.attrs["env_args"] = env_args_ref
                    fout.attrs["env"] = fin.attrs.get("env", "real_piper_no_vision")
                else:
                    if data_in.attrs["env_args"] != env_args_ref:
                        raise RuntimeError(f"env_args mismatch: {in_path}")

                for ep_name in data_in.keys():
                    src_ep = data_in[ep_name]
                    dst_name = f"demo_{demo_idx}"
                    dst_ep = data_out.require_group(dst_name)
                    copy_demo(src_ep, dst_ep)

                    n = int(src_ep.attrs["num_samples"])
                    total += n
                    demo_idx += 1

        data_out.attrs["total"] = int(total)

    print(f"[INFO] merged {len(input_paths)} files -> {output_path}")
    print(f"[INFO] total demos: {demo_idx}")
    print(f"[INFO] total samples: {total}")


if __name__ == "__main__":
    main()