"""Robot adapter used by simplified imitation pipeline."""

from __future__ import annotations

import sys
import time
from pathlib import Path
from typing import Any


SRC_DIR = Path(__file__).resolve().parents[1] / "src"
if str(SRC_DIR) not in sys.path:
    sys.path.insert(0, str(SRC_DIR))

from robot_piper.piper_arm import PiperArm  # noqa: E402


def create_arm(cfg: dict[str, Any]) -> PiperArm:
    """Create, connect, and enable Piper arm from config."""
    arm = PiperArm(
        channel=cfg["channel"],
        robot_name=cfg.get("robot_name", "piper"),
        auto_connect=False,
        tool_type=cfg.get("tool_type", "none"),
    )
    arm.connect()
    if not arm.enable(timeout=cfg.get("enable_timeout", 8.0)):
        raise RuntimeError("enable timeout")
    arm.set_motion_mode_j()
    arm.set_speed_percent(int(cfg.get("speed")))
    return arm


def get_obs(arm: PiperArm, t: float | None = None) -> dict[str, Any]:
    """Read observation in collect/deploy compatible format."""
    if t is None:
        t = time.time()
    return {
        "t": float(t),
        "q": arm.get_joint_position_rad(),
        "dq": arm.get_joint_velocity_rad_s(),
        "tcp_pose": arm.get_tcp_pose6(),
    }
