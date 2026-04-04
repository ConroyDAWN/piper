"""Shared utilities for simplified imitation scripts."""

from __future__ import annotations

import json
import math
from pathlib import Path
from typing import Sequence

import numpy as np
import yaml


CFG_PATH = Path(__file__).with_name("imitation_cfg.yaml")


def load_cfg() -> dict:
    """Load yaml config from imitation/imitation_cfg.yaml."""
    with CFG_PATH.open("r", encoding="utf-8") as f:
        return yaml.safe_load(f)


def ensure_parent(path: Path) -> None:
    """Create parent directory if missing."""
    path.parent.mkdir(parents=True, exist_ok=True)


def to_json_text(obj: dict) -> str:
    """Serialize dict to utf-8 safe JSON text."""
    return json.dumps(obj, ensure_ascii=False)


def _skew(v: np.ndarray) -> np.ndarray:
    return np.array([[0.0, -v[2], v[1]], [v[2], 0.0, -v[0]], [-v[1], v[0], 0.0]], dtype=np.float64)


def rot_x(r: float) -> np.ndarray:
    c, s = math.cos(r), math.sin(r)
    return np.array([[1.0, 0.0, 0.0], [0.0, c, -s], [0.0, s, c]], dtype=np.float64)


def rot_y(p: float) -> np.ndarray:
    c, s = math.cos(p), math.sin(p)
    return np.array([[c, 0.0, s], [0.0, 1.0, 0.0], [-s, 0.0, c]], dtype=np.float64)


def rot_z(y: float) -> np.ndarray:
    c, s = math.cos(y), math.sin(y)
    return np.array([[c, -s, 0.0], [s, c, 0.0], [0.0, 0.0, 1.0]], dtype=np.float64)


def euler_xyz_to_rotmat(r: float, p: float, y: float) -> np.ndarray:
    """Euler xyz -> rotation matrix under URDF Rz*Ry*Rx convention."""
    return rot_z(y) @ rot_y(p) @ rot_x(r)


def rotmat_to_euler_xyz(rot: np.ndarray) -> np.ndarray:
    """Rotation matrix -> euler xyz."""
    pitch = math.asin(float(np.clip(-rot[2, 0], -1.0, 1.0)))
    cp = math.cos(pitch)
    if abs(cp) > 1e-8:
        roll = math.atan2(float(rot[2, 1]), float(rot[2, 2]))
        yaw = math.atan2(float(rot[1, 0]), float(rot[0, 0]))
    else:
        roll = 0.0
        yaw = math.atan2(float(-rot[0, 1]), float(rot[1, 1]))
    return np.array([roll, pitch, yaw], dtype=np.float64)


def so3_log(rot: np.ndarray) -> np.ndarray:
    """SO(3) logarithm map, output rotvec."""
    cos_theta = float(np.clip((np.trace(rot) - 1.0) * 0.5, -1.0, 1.0))
    theta = math.acos(cos_theta)
    if theta < 1e-12:
        return np.zeros(3, dtype=np.float64)
    w = np.array([rot[2, 1] - rot[1, 2], rot[0, 2] - rot[2, 0], rot[1, 0] - rot[0, 1]], dtype=np.float64)
    return 0.5 * theta / math.sin(theta) * w


def so3_exp(rotvec: Sequence[float]) -> np.ndarray:
    """SO(3) exponential map, input rotvec."""
    rv = np.asarray(rotvec, dtype=np.float64).reshape(3)
    theta = float(np.linalg.norm(rv))
    if theta < 1e-12:
        return np.eye(3, dtype=np.float64)
    axis = rv / theta
    k = _skew(axis)
    eye = np.eye(3, dtype=np.float64)
    return eye + math.sin(theta) * k + (1.0 - math.cos(theta)) * (k @ k)


def compose_next_pose(curr_pose: Sequence[float], delta_action_raw: Sequence[float]) -> np.ndarray:
    """Apply [dx,dy,dz,drotvec] to current [xyz,rpy] and return next pose."""
    pose = np.asarray(curr_pose, dtype=np.float64).reshape(6)
    delta = np.asarray(delta_action_raw, dtype=np.float64).reshape(6)
    out = pose.copy()
    out[:3] += delta[:3]
    r_curr = euler_xyz_to_rotmat(*pose[3:6])
    out[3:6] = rotmat_to_euler_xyz(r_curr @ so3_exp(delta[3:6]))
    return out
