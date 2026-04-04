"""Deploy policy on real robot: obs -> action -> next_pose -> IK -> move_j."""

from __future__ import annotations

import time
import importlib
from pathlib import Path

import numpy as np
import torch

from common import compose_next_pose, load_cfg
from ik_movej import IkMoveJ
from robot_piper import create_arm, get_obs


class PolicyRunner:
    """Thin policy wrapper for torch checkpoint / scripted model."""

    def __init__(self, ckpt: Path):
        self.mode = "jit"
        self.model = None
        self.policy = None
        try:
            self.model = torch.jit.load(str(ckpt), map_location="cpu")
            self.model.eval()
            print("[INFO] loaded TorchScript model")
        except RuntimeError as exc:
            # Robomimic checkpoints are regular .pth dict files and are not TorchScript archives.
            if "constants.pkl" not in str(exc):
                raise
            try:
                FileUtils = importlib.import_module("robomimic.utils.file_utils")
            except ModuleNotFoundError:
                import sys

                robomimic_root = Path(__file__).resolve().parents[2] / "robomimic" / "robomimic"
                if str(robomimic_root) not in sys.path:
                    sys.path.insert(0, str(robomimic_root))
                FileUtils = importlib.import_module("robomimic.utils.file_utils")

            self.mode = "robomimic"
            self.policy, _ = FileUtils.policy_from_checkpoint(
                ckpt_path=str(ckpt),
                device=torch.device("cpu"),
                verbose=False,
            )
            self.policy.start_episode()
            print("[INFO] loaded robomimic checkpoint")

    def act(self, obs: dict) -> np.ndarray:
        """Infer normalized 6D action from observation dict."""
        if self.mode == "jit":
            with torch.no_grad():
                x = np.concatenate([np.asarray(obs["q"]), np.asarray(obs["dq"]), np.asarray(obs["tcp_pose"])], axis=0)
                x_t = torch.from_numpy(x.astype(np.float32)).unsqueeze(0)
                a = self.model(x_t).squeeze(0).cpu().numpy()
            return a.astype(np.float64)

        obs_dict = {
            "q": np.asarray(obs["q"], dtype=np.float32),
            "dq": np.asarray(obs["dq"], dtype=np.float32),
            "tcp_pose": np.asarray(obs["tcp_pose"], dtype=np.float32),
        }
        a = self.policy(obs_dict)
        return np.asarray(a, dtype=np.float64)


def main() -> None:
    """Deploy control loop based on config only (no argparse)."""
    cfg = load_cfg()
    dc = cfg["deploy"]
    ckpt = Path(cfg["paths"]["model_deploy"]).expanduser().resolve()

    policy = PolicyRunner(ckpt)
    arm = create_arm(cfg["robot"])
    ik = IkMoveJ(
        arm,
        cfg["paths"]["urdf"],
        ik_pos_hard=cfg["replay"]["ik_pos_hard"],
        ik_rot_hard=cfg["replay"]["ik_rot_hard"],
    )

    pos_scale = np.array(dc["action_pos_scale"], dtype=np.float64)
    rot_scale = np.array(dc["action_rot_scale"], dtype=np.float64)
    max_steps = int(dc["max_steps"])

    print(f"[INFO] deploy start, ckpt={ckpt}")
    print("[INFO] moving to home before deploy")
    ik.go_home(timeout=cfg["replay"]["home_timeout"], tol=cfg["replay"]["home_tol"])
    q_seed = arm.get_joint_position_rad()
    step = 0
    try:
        while True:
            t0 = time.time()
            obs = get_obs(arm)
            action = policy.act(obs)
            action[:3] *= pos_scale
            action[3:] *= rot_scale

            next_pose = compose_next_pose(obs["tcp_pose"], action)
            joints = ik.solve_and_move(next_pose, q_seed, wait=False)
            if joints is not None:
                q_seed = joints

            if step % max(1, int(dc["print_every"])) == 0:
                print(f"[INFO] step={step}, joints_ok={joints is not None}")
            step += 1
            if max_steps > 0 and step >= max_steps:
                break

            dt = time.time() - t0
            if dt < float(dc["control_dt"]):
                time.sleep(float(dc["control_dt"]) - dt)
    finally:
        arm.disable(timeout=8.0)


if __name__ == "__main__":
    main()
