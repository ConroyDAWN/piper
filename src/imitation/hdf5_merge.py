"""Merge multiple HDF5 demo files into a single robomimic dataset."""

from __future__ import annotations

from pathlib import Path

import h5py

from common import ensure_parent, load_cfg


def main() -> None:
    """Merge files listed in imitation_cfg.yaml paths.merged_inputs."""
    cfg = load_cfg()
    in_paths = [Path(p).expanduser().resolve() for p in cfg["paths"].get("merged_inputs", [])]
    out_path = Path(cfg["paths"]["merged_hdf5"]).expanduser().resolve()
    prefix = cfg["merge"]["episode_prefix"]

    if not in_paths:
        raise RuntimeError("paths.merged_inputs is empty")

    ensure_parent(out_path)
    ep_idx = 0
    env_args = None

    with h5py.File(out_path, "w") as fout:
        data_out = fout.create_group("data")
        for p in in_paths:
            with h5py.File(p, "r") as fin:
                if "data" not in fin:
                    continue
                data_in = fin["data"]
                if env_args is None and "env_args" in data_in.attrs:
                    env_args = data_in.attrs["env_args"]
                for ep_name in data_in.keys():
                    src = data_in[ep_name]
                    dst_name = f"{prefix}{ep_idx}"
                    fin.copy(src, data_out, name=dst_name)
                    ep_idx += 1
                    print(f"[INFO] merged {p.name}:{ep_name} -> {dst_name}")

        if env_args is not None:
            data_out.attrs["env_args"] = env_args
            fout.attrs["env_args"] = env_args

    print(f"[INFO] merge done, episodes={ep_idx}, output={out_path}")


if __name__ == "__main__":
    main()
