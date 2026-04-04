import json
import h5py
from pathlib import Path

hdf5_path = Path("/home/flowing/piper/data/merge_demos/train_merged_3_28_1.hdf5")

with h5py.File(hdf5_path, "a") as f:
    data = f["data"]

    if "env_args" not in data.attrs:
        raise RuntimeError("data.attrs 中不存在 env_args")

    env_args = json.loads(data.attrs["env_args"])

    if "env_name" not in env_args:
        env_args["env_name"] = "real_piper_no_vision"

    if "type" not in env_args:
        env_args["type"] = "real_robot"

    if "env_kwargs" not in env_args:
        env_args["env_kwargs"] = {}

    data.attrs["env_args"] = json.dumps(env_args, ensure_ascii=False)

    # 可选：同步更新根属性，便于 inspect
    f.attrs["env_args"] = json.dumps(env_args, ensure_ascii=False)

print(f"fixed env_args in: {hdf5_path}")