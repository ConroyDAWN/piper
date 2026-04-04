"""Replay HDF5 action sequence on Piper: curr_pose + action -> next_pose -> IK -> move_j."""

from __future__ import annotations

import time
from pathlib import Path

import h5py
import numpy as np

from common import compose_next_pose, load_cfg
from ik_movej import IkMoveJ
from robot_piper import create_arm


def main() -> None:
    """Run trajectory replay using config values only."""
    cfg = load_cfg()
    rc = cfg["replay"]
    # path = Path(cfg["paths"]["merged_hdf5"]).expanduser().resolve()
    path = Path(cfg["paths"]["collected_hdf5"]).expanduser().resolve()
    ep_name = rc["episode_name"]

    with h5py.File(path, "r") as f:
        ep = f[f"data/{ep_name}"]
        q0 = ep["obs/q"][0].astype(np.float64).tolist()
        actions = ep["actions"][:].astype(np.float64)

    if int(rc["max_steps"]) > 0:
        actions = actions[: int(rc["max_steps"])]

    pos_scale = np.array(rc["action_pos_scale"], dtype=np.float64)
    rot_scale = np.array(rc["action_rot_scale"], dtype=np.float64)

    arm = create_arm(cfg["robot"])
    ik = IkMoveJ(
        arm,
        cfg["paths"]["urdf"],
        ik_pos_hard=rc["ik_pos_hard"],
        ik_rot_hard=rc["ik_rot_hard"],
        ik_pos_tol=rc.get("ik_pos_tol", 0.001),
    )

    print(f"[INFO] replay episode={ep_name}, steps={len(actions)}")
    q_seed = q0[:]
    try:
        ik.go_home(timeout=rc["home_timeout"], tol=rc["home_tol"])
        if not arm.move_j(q0, wait=True, timeout=rc["step_timeout"]):
            raise RuntimeError("failed to move to first q")

        for i, act in enumerate(actions):
            t0 = time.time()
            raw = act.copy()
            raw[:3] *= pos_scale
            raw[3:] *= rot_scale

            # if i % 20 == 0:
            #     print(f"[INFO] step={i}, action_raw={raw}")
            curr_pose = arm.get_tcp_pose6()
            next_pose = compose_next_pose(curr_pose, raw)
            if i % max(1, int(rc["print_every"])) == 0:
                print(f"[INFO] step={i}, curr_pose={curr_pose}, next_pose={next_pose}")
            joints = ik.solve_and_move(next_pose, q_seed, wait=True, timeout=rc["step_timeout"])
            if joints is not None:
                q_seed = joints

            if i % max(1, int(rc["print_every"])) == 0:
                print(f"[INFO] step={i}, joints_ok={joints is not None}")
            dt = time.time() - t0
            if dt < float(rc["control_dt"]):
                time.sleep(float(rc["control_dt"]) - dt)
    finally:
        if bool(rc.get("return_home_on_exit", True)):
            arm.move_j([0.0] * 6, wait=False)
            time.sleep(2.0)
        arm.disable(timeout=8.0)


if __name__ == "__main__":
    main()
