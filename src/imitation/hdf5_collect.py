"""Collect q/dq/tcp_pose and delta action into robomimic-style HDF5."""

from __future__ import annotations

import time
from pathlib import Path

import h5py
import numpy as np

try:
    # Package mode: python -m src.imitation.hdf5_collect
    from .common import ensure_parent, load_cfg, so3_log, to_json_text
    from ..robot_piper import create_arm, get_obs
except ImportError:
    # Script mode: python hdf5_collect.py
    import sys

    src_dir = Path(__file__).resolve().parents[1]
    if str(src_dir) not in sys.path:
        sys.path.insert(0, str(src_dir))
    from common import ensure_parent, load_cfg, so3_log, to_json_text
    from robot_piper import create_arm, get_obs

def get_ctrl_mode(arm) -> int | None:
    """Read ctrl_mode for teach-mode checks."""
    status = arm.get_arm_status()
    if status is None:
        return None
    return getattr(status.msg, "ctrl_mode", None)


def wait_for_teach_mode(arm, timeout_s: float) -> None:
    """Wait until robot enters teach mode (ctrl_mode == 2)."""
    end_t = time.monotonic() + float(timeout_s)
    while get_ctrl_mode(arm) != 2:
        if time.monotonic() > end_t:
            raise RuntimeError("wait teach mode timeout (ctrl_mode!=2)")
        time.sleep(0.05)


def wait_exit_teach_mode(arm, timeout_s: float) -> None:
    """Wait until robot exits teach mode (ctrl_mode != 2)."""
    end_t = time.monotonic() + float(timeout_s)
    while get_ctrl_mode(arm) == 2:
        if time.monotonic() > end_t:
            raise RuntimeError("exit teach mode timeout (ctrl_mode still 2)")
        time.sleep(0.05)


def wait_joints_near_home(arm, timeout_s: float, tol_rad: float) -> bool:
    """Keep publishing home joints and check if all joints are near zero."""
    start_t = time.monotonic()
    last_pub = 0.0
    while time.monotonic() - start_t <= float(timeout_s):
        now = time.monotonic()
        if now - last_pub >= 0.25:
            arm.move_j([0.0] * 6, wait=False)
            last_pub = now
        try:
            q = arm.get_joint_position_rad()
            if q and max(abs(v) for v in q) <= float(tol_rad):
                return True
        except Exception:
            pass
        time.sleep(0.05)
    return False

def _build_action(prev_pose: np.ndarray, curr_pose: np.ndarray) -> np.ndarray:
    """Compute raw action [dxyz, drotvec] from two tcp poses."""
    dxyz = curr_pose[:3] - prev_pose[:3]
    r0 = np.array(prev_pose[3:6], dtype=np.float64)
    r1 = np.array(curr_pose[3:6], dtype=np.float64)
    from common import euler_xyz_to_rotmat  # local import keeps top cleaner

    drot = so3_log(euler_xyz_to_rotmat(*r0).T @ euler_xyz_to_rotmat(*r1))
    return np.concatenate([dxyz, drot], axis=0)


def main() -> None:
    """Run collection using imitation_cfg.yaml only (no argparse)."""

    #---------build obs and actions buffers before collection------------------------
    cfg = load_cfg()
    c = cfg["collect"]
    path = Path(cfg["paths"]["collected_hdf5"]).expanduser().resolve()
    ep_name = c["episode_name"]
    n = int(c["samples"])
    sample_freq = float(c["sample_freq"])
    teach_wait_timeout = float(c.get("teach_wait_timeout"))
    home_timeout = float(c.get("home_timeout"))
    home_tol = float(c.get("home_tol"))
    pos_scale = np.array(c["action_pos_scale"], dtype=np.float64)
    rot_scale = np.array(c["action_rot_scale"], dtype=np.float64)


    ensure_parent(path)
    arm = create_arm(cfg["robot"])
    print(f"[INFO] collecting to {path}, episode={ep_name}, samples={n}")

    obs_buf = []

    #--------------go_home, wait for teach mode, collect obs, wait for exit teach mode, go home----------------
    try:
        print("[INFO] move to home before teach mode")
        arm.move_j([0.0] * 6, wait=True)
        if not wait_joints_near_home(arm, home_timeout, home_tol):
            raise RuntimeError("timeout waiting for joints to reach home position")

        print("[INFO] waiting for teach mode")
        wait_for_teach_mode(arm, teach_wait_timeout)
        print("[INFO] teach mode entered, start collecting")
        input("Press Enter to start collection...")

        for i in range(n):
            obs_buf.append(get_obs(arm, time.time()))
            if i % 20 == 0:
                print(f"[INFO] sample={i}")
            time.sleep(1/sample_freq)

    finally:
        input("[INFO] collect done, press Enter to continue with exit teach mode and return home")
        arm.reset()
        time.sleep(1)  


# --------------------create actions and save to HDF5 in robomimic format-----------------------
    actions_raw = np.zeros((n, 6), dtype=np.float32)
    for i in range(n - 1):
        prev_pose = np.asarray(obs_buf[i]["tcp_pose"], dtype=np.float64)
        curr_pose = np.asarray(obs_buf[i + 1]["tcp_pose"], dtype=np.float64)
        actions_raw[i] = _build_action(prev_pose, curr_pose)
        # print(f"[DEBUG] i={i}, action_raw={actions_raw[i]}")

    actions = actions_raw.copy()
    actions[:, :3] /= pos_scale
    actions[:, 3:] /= rot_scale
    # print(f"[DEBUG] actions after scaling: {actions}")

    with h5py.File(path, "a") as f:
        data = f.require_group("data")

        env_args = {
            "env_name": "real_piper_no_vision",
            "type": "real_robot",
            "env_kwargs": {}, 
            "obs_keys": ["q", "dq", "tcp_pose"],
            "action_definition": "delta_tcp_pose_xyz_plus_delta_rotvec_normalized",
        }
        f.attrs["env_args"] = to_json_text(env_args)
        data.attrs["env_args"] = to_json_text(env_args)

        if ep_name in data:
            del data[ep_name]
        ep = data.create_group(ep_name)
        ep.attrs["num_samples"] = n

        obs = ep.create_group("obs")
        t = np.asarray([[o["t"]] for o in obs_buf], dtype=np.float64)
        q = np.asarray([o["q"] for o in obs_buf], dtype=np.float32)
        dq = np.asarray([o["dq"] for o in obs_buf], dtype=np.float32)
        tcp_pose = np.asarray([o["tcp_pose"] for o in obs_buf], dtype=np.float32)
        # create hdf5 datasets and attributes in robomimic format
        obs.create_dataset("t", data=t)
        obs.create_dataset("q", data=q)
        obs.create_dataset("dq", data=dq)
        obs.create_dataset("tcp_pose", data=tcp_pose)

        dones = np.zeros((n,), dtype=np.bool_)
        dones[-1] = True
        ep.create_dataset("actions", data=actions.astype(np.float32))
        ep.create_dataset("rewards", data=np.zeros((n,), dtype=np.float32))
        ep.create_dataset("dones", data=dones)

    print("[INFO] collect done")


if __name__ == "__main__":
    main()
