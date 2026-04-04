"""Inspect whether one HDF5 file matches expected robomimic data format."""

from __future__ import annotations

from pathlib import Path

import h5py

from common import load_cfg


REQUIRED_OBS = ["t", "q", "dq", "tcp_pose"]


def main() -> None:
    """Validate key groups and basic shapes for one episode."""
    cfg = load_cfg()
    path = Path(cfg["paths"]["collected_hdf5"]).expanduser().resolve()
    ep_name = cfg["inspect"]["episode_name"]

    with h5py.File(path, "r") as f:
        assert "data" in f, "missing /data"
        ep = f[f"data/{ep_name}"]
        obs = ep["obs"]

        for k in REQUIRED_OBS:
            assert k in obs, f"missing obs/{k}"
        assert "actions" in ep and "rewards" in ep and "dones" in ep

        n = obs["q"].shape[0]
        print(f"[INFO] file={path}")
        print(f"[INFO] episode={ep_name}, samples={n}")
        print(f"[INFO] obs/t={obs['t'].shape}")
        print(f"[INFO] obs/q={obs['q'].shape}")
        print(f"[INFO] obs/dq={obs['dq'].shape}")
        print(f"[INFO] obs/tcp_pose={obs['tcp_pose'].shape}")
        print(f"[INFO] actions={ep['actions'].shape}")
        print(f"[INFO] rewards={ep['rewards'].shape}")
        print(f"[INFO] dones={ep['dones'].shape}")

        num_rows = min(100, n)
        print(f"[INFO] actions first {num_rows} rows:")
        print(ep["actions"][:num_rows, :])

        assert obs["q"].shape[1] == 6
        assert obs["dq"].shape[1] == 6
        assert obs["tcp_pose"].shape[1] == 6
        assert ep["actions"].shape[1] == 6
        assert ep["actions"].shape[0] == n

    print("[INFO] inspect pass")


if __name__ == "__main__":
    main()
