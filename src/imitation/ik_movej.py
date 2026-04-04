"""IK helper class: pose -> joints -> move_j execution."""

from __future__ import annotations

import sys
from pathlib import Path
from typing import Sequence

SRC_DIR = Path(__file__).resolve().parents[1] / "src"
if str(SRC_DIR) not in sys.path:
    sys.path.insert(0, str(SRC_DIR))

from playTrajectory_pyagxarm_ik_movej import (  # noqa: E402
    PiperUrdfIkSolver,
    clip_joints,
    get_joint_limits,
    wait_joints_near_home,
)


class IkMoveJ:
    """Minimal IK + move_j runner shared by replay and deploy."""

    def __init__(
        self,
        arm,
        urdf_path: str,
        ik_pos_hard: float,
        ik_rot_hard: float,
        ik_pos_tol: float = 0.001,
    ):
        self.arm = arm
        self.solver = PiperUrdfIkSolver(urdf_path)
        self.limits = get_joint_limits(arm)
        self.ik_pos_hard = float(ik_pos_hard)
        self.ik_rot_hard = float(ik_rot_hard)
        self.ik_pos_tol = float(ik_pos_tol)

    def go_home(self, timeout: float, tol: float) -> None:
        """Move to all-zero home joint and wait."""
        self.arm.move_j([0.0] * 6, wait=True)
        if not wait_joints_near_home(self.arm, timeout=timeout, tol_rad=tol):
            raise RuntimeError("failed to reach home")

    def solve_and_move(self, target_pose: Sequence[float], q_seed: Sequence[float], wait: bool = False, timeout: float = 12.0) -> list[float] | None:
        """Solve IK for target pose and send move_j if error is acceptable."""
        ok, joints, info = self.solver.solve(
            list(target_pose),
            list(q_seed),
            pos_tol=self.ik_pos_tol,
        )
        if (not ok) and (info["pos_err"] > self.ik_pos_hard or info["rot_err"] > self.ik_rot_hard):
            print(f"[WARN] IK hard fail, pos_err={info['pos_err']:.4f}, rot_err={info['rot_err']:.4f}")
            return None

        joints, clipped = clip_joints(list(joints), self.limits)
        done = self.arm.move_j(joints, wait=wait, timeout=timeout)
        if not done:
            print("[WARN] move_j command failed or timed out")
            return None
        if clipped:
            print("[INFO] joint clip applied")
        return joints
