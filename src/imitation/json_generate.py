"""Generate robomimic BC-RNN training json from imitation_cfg.yaml."""

from __future__ import annotations

import json
from pathlib import Path

from common import ensure_parent, load_cfg


def main() -> None:
    """Create minimal robomimic config json file."""
    cfg = load_cfg()
    dataset = str(Path(cfg["paths"]["collected_hdf5"]).expanduser().resolve())
    out_json = Path(cfg["paths"]["robomimic_json"]).expanduser().resolve()

    jc = cfg["json"]
    model_cfg = {
        "algo_name": "bc",
        "experiment": {"name": "piper_bc_rnn", "validate": True},
        "train": {
            "data": [{"path": dataset}],
            "output_dir": jc["output_dir"],
            "seq_length": int(jc["seq_length"]),
            "batch_size": int(jc["batch_size"]),
            "num_epochs": int(jc["num_epochs"]),
            "dataset_keys": ["actions", "obs/q", "obs/dq", "obs/tcp_pose"],
            "hdf5_cache_mode": "all",
            "hdf5_normalize_obs": False,
            "cuda": True,
        },
        "algo": {"rnn": {"enabled": True, "horizon": int(jc["seq_length"]), "hidden_dim": 400, "rnn_type": "LSTM", "num_layers": 2}},
        "observation": {"modalities": {"obs": {"low_dim": ["q", "dq", "tcp_pose"]}}},
    }

    ensure_parent(out_json)
    out_json.write_text(json.dumps(model_cfg, indent=2, ensure_ascii=False), encoding="utf-8")
    print(f"[INFO] json generated: {out_json}")


if __name__ == "__main__":
    main()
