#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""基于 URDF 数值逆运动学 + move_j 的轨迹回放脚本。

目的：
- 采集阶段记录末端位姿轨迹（而不是依赖 move_p 直接复现）。
- 回放阶段对每个目标位姿做 IK，得到关节角后调用 move_j，使轨迹更平滑、可控。

输入 CSV（支持两种格式）：
1) 推荐：wait_time,x,y,z,roll,pitch,yaw[,gripper]
2) 兼容：wait_time,j1,j2,j3,j4,j5,j6[,gripper]  # 直接透传关节，不做 IK

运行方式：
    cd /workspace/piper/src/robot
    python playTrajectory_pyagxarm_ik_movej.py

与 no_vision_pipeline_simplified.py 联用：
    1) 先用其 collect 子命令生成 hdf5（如 data/demo_6d_010.hdf5）
    2) 本文件设置 DATA_SOURCE="hdf5"、HDF5_PATH、HDF5_EPISODE_NAME
    3) TRAJECTORY_MODE 设为 "pose"（读取 obs/tcp_pose 走 IK）或 "joint"（读取 obs/q）
"""

import csv
import math
import os
import signal
import sys
import time
import xml.etree.ElementTree as ET
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, List, Optional, Sequence, Tuple

src_dir = Path(__file__).resolve().parents[1]
if str(src_dir) not in sys.path:
    sys.path.insert(0, str(src_dir))

try:
    from robot_piper.piper_arm import PiperArm
except ModuleNotFoundError:
    from robot_piper.piper_arm import PiperArm


# ======================== 配置区（按需修改） ========================
CHANNEL = "can0"
ROBOT_NAME = "piper"
# 按评审意见：默认不启用夹爪（即 gripper=None 场景）。
HAVE_GRIPPER = None

PLAY_TIMES = 1
PLAY_INTERVAL = 1.0
MOVE_SPEED = 15
PLAY_SPEED = 1.0

MODE_TIMEOUT = 5.0
ENABLE_TIMEOUT = 5.0
CLIP_TO_LIMITS = True
ENSURE_HOME_BEFORE_REPLAY = True
START_FROM_SECOND_FRAME_IF_PREPOSITIONED = True

# IK 相关配置
URDF_PATH = (
    "/home/flowing/piper/agx_arm_ws/install/agx_arm_description/share/agx_arm_description/"
    "agx_arm_urdf/piper_l/urdf/piper_l_description.urdf"
)
IK_MAX_ITERS = 280
IK_POS_TOL = 0.2          # m
IK_ROT_TOL = 0.5          # rad
IK_STEP_LIMIT = 0.08       # rad / iteration
IK_DAMPING = 0.2
IK_POSITION_WEIGHT = 1.0
IK_ROTATION_WEIGHT = 1.0

CSV_PATH = os.path.join(os.path.dirname(__file__), "trajectory_pose0.csv")
HDF5_PATH = "/home/flowing/piper/data/single_demo/demo_010.hdf5"
HDF5_EPISODE_NAME = "demo_0"

# 数据来源:
#   - "csv"  : 从 CSV 加载
#   - "hdf5" : 直接读取 no_vision_pipeline_simplified.py 产出的 hdf5
DATA_SOURCE = "hdf5"

# 轨迹解释方式:
#   - "pose"  : row[1:7] 当作 [x,y,z,r,p,y]，走 IK
#   - "joint" : row[1:7] 当作 [j1..j6]，直接 move_j
TRAJECTORY_MODE = "pose"
# ==================================================================


def clamp(v: float, lo: float, hi: float) -> float:
    return min(max(v, lo), hi)


def mat33_mul(a: List[List[float]], b: List[List[float]]) -> List[List[float]]:
    out = [[0.0, 0.0, 0.0] for _ in range(3)]
    for i in range(3):
        for j in range(3):
            out[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j] + a[i][2] * b[2][j]
    return out


def mat33_vec_mul(a: List[List[float]], v: Sequence[float]) -> List[float]:
    return [
        a[0][0] * v[0] + a[0][1] * v[1] + a[0][2] * v[2],
        a[1][0] * v[0] + a[1][1] * v[1] + a[1][2] * v[2],
        a[2][0] * v[0] + a[2][1] * v[1] + a[2][2] * v[2],
    ]


def mat33_transpose(a: List[List[float]]) -> List[List[float]]:
    return [
        [a[0][0], a[1][0], a[2][0]],
        [a[0][1], a[1][1], a[2][1]],
        [a[0][2], a[1][2], a[2][2]],
    ]


def rot_x(r: float) -> List[List[float]]:
    c, s = math.cos(r), math.sin(r)
    return [[1.0, 0.0, 0.0], [0.0, c, -s], [0.0, s, c]]


def rot_y(p: float) -> List[List[float]]:
    c, s = math.cos(p), math.sin(p)
    return [[c, 0.0, s], [0.0, 1.0, 0.0], [-s, 0.0, c]]


def rot_z(y: float) -> List[List[float]]:
    c, s = math.cos(y), math.sin(y)
    return [[c, -s, 0.0], [s, c, 0.0], [0.0, 0.0, 1.0]]


def rpy_to_rot(r: float, p: float, y: float) -> List[List[float]]:
    """"
    euler -> rotation matrix, URDF rpy convention: R = Rz(yaw) * Ry(pitch) * Rx(roll)
    """
    # URDF rpy convention: R = Rz(yaw) * Ry(pitch) * Rx(roll)
    return mat33_mul(mat33_mul(rot_z(y), rot_y(p)), rot_x(r))


def rot_to_rpy(rm: List[List[float]]) -> List[float]:
    """
    rotation matrix -> euler angles, URDF rpy convention: R = Rz(yaw) * Ry(pitch) * Rx(roll)
    """
    pitch = math.asin(clamp(-rm[2][0], -1.0, 1.0))
    cp = math.cos(pitch)
    if abs(cp) > 1e-8:
        roll = math.atan2(rm[2][1], rm[2][2])
        yaw = math.atan2(rm[1][0], rm[0][0])
    else:
        roll = 0.0
        yaw = math.atan2(-rm[0][1], rm[1][1])
    return [roll, pitch, yaw]


def compose_transform(rm: List[List[float]], t: Sequence[float]) -> List[List[float]]:
    """
    旋转矩阵 + 平移向量 -> 4x4 齐次变换矩阵
    """
    return [
        [rm[0][0], rm[0][1], rm[0][2], t[0]],
        [rm[1][0], rm[1][1], rm[1][2], t[1]],
        [rm[2][0], rm[2][1], rm[2][2], t[2]],
        [0.0, 0.0, 0.0, 1.0],
    ]


def transform_mul(a: List[List[float]], b: List[List[float]]) -> List[List[float]]:
    out = [[0.0] * 4 for _ in range(4)]
    for i in range(4):
        for j in range(4):
            out[i][j] = (
                a[i][0] * b[0][j]
                + a[i][1] * b[1][j]
                + a[i][2] * b[2][j]
                + a[i][3] * b[3][j]
            )
    return out


def axis_angle_rot(axis: Sequence[float], angle: float) -> List[List[float]]:
    x, y, z = axis
    n = math.sqrt(x * x + y * y + z * z)
    if n < 1e-12:
        return [[1.0, 0.0, 0.0], [0.0, 1.0, 0.0], [0.0, 0.0, 1.0]]
    x, y, z = x / n, y / n, z / n
    c, s = math.cos(angle), math.sin(angle)
    C = 1.0 - c
    return [
        [c + x * x * C, x * y * C - z * s, x * z * C + y * s],
        [y * x * C + z * s, c + y * y * C, y * z * C - x * s],
        [z * x * C - y * s, z * y * C + x * s, c + z * z * C],
    ]


def pose_error(curr_pos, curr_rot, tgt_pos, tgt_rot) -> Tuple[List[float], float, float]:
    """计算当前位姿与目标位姿的误差，返回 6D 误差向量（位置误差 + 旋转误差）以及位置误差和旋转误差的范数。"""

    ep = [tgt_pos[i] - curr_pos[i] for i in range(3)] # position error vector in base frame

    # orientation error vector in base frame
    ec = [0.0, 0.0, 0.0]
    c0 = [curr_rot[0][0], curr_rot[1][0], curr_rot[2][0]]
    c1 = [curr_rot[0][1], curr_rot[1][1], curr_rot[2][1]]
    c2 = [curr_rot[0][2], curr_rot[1][2], curr_rot[2][2]]
    t0 = [tgt_rot[0][0], tgt_rot[1][0], tgt_rot[2][0]]
    t1 = [tgt_rot[0][1], tgt_rot[1][1], tgt_rot[2][1]]
    t2 = [tgt_rot[0][2], tgt_rot[1][2], tgt_rot[2][2]]

    def cross(a, b):
        return [
            a[1] * b[2] - a[2] * b[1],
            a[2] * b[0] - a[0] * b[2],
            a[0] * b[1] - a[1] * b[0],
        ]
    # 旋转误差向量的计算方法参考了现代机器人学教材，基于当前旋转矩阵的列向量与目标旋转矩阵的列向量的叉积之和来构造误差向量。
    c = cross(c0, t0)
    ec[0] += c[0]
    ec[1] += c[1]
    ec[2] += c[2]
    c = cross(c1, t1)
    ec[0] += c[0]
    ec[1] += c[1]
    ec[2] += c[2]
    c = cross(c2, t2)
    ec[0] += c[0]
    ec[1] += c[1]
    ec[2] += c[2]
    ec = [0.5 * v for v in ec]

    pos_norm = math.sqrt(sum(v * v for v in ep))
    rot_norm = math.sqrt(sum(v * v for v in ec))
    return ep + ec, pos_norm, rot_norm


def solve_linear(a: List[List[float]], b: List[float]) -> Optional[List[float]]:
    n = len(b)
    aug = [row[:] + [b[i]] for i, row in enumerate(a)]

    for col in range(n):
        pivot = max(range(col, n), key=lambda r: abs(aug[r][col]))
        if abs(aug[pivot][col]) < 1e-12:
            return None
        aug[col], aug[pivot] = aug[pivot], aug[col]

        div = aug[col][col]
        for j in range(col, n + 1):
            aug[col][j] /= div

        for r in range(n):
            if r == col:
                continue
            factor = aug[r][col]
            if factor == 0:
                continue
            for j in range(col, n + 1):
                aug[r][j] -= factor * aug[col][j]

    return [aug[i][n] for i in range(n)]


@dataclass
class JointDesc:
    name: str
    xyz: List[float]
    rpy: List[float]
    axis: List[float]
    lower: float
    upper: float


class PiperUrdfIkSolver:
    def __init__(self, urdf_path: str):
        self.urdf_path = urdf_path
        self.joints = self._load_joints(urdf_path)
        if len(self.joints) != 6:
            raise RuntimeError(f"期望 6 个关节，实际 {len(self.joints)}")

    @staticmethod
    def _load_joints(urdf_path: str) -> List[JointDesc]:
        if not os.path.exists(urdf_path):
            raise FileNotFoundError(f"URDF 不存在: {urdf_path}")
        root = ET.parse(urdf_path).getroot()
        out: List[JointDesc] = []
        for jname in [f"joint{i}" for i in range(1, 7)]:
            elem = root.find(f"joint[@name='{jname}']")
            if elem is None:
                raise RuntimeError(f"URDF 缺少关节: {jname}")
            origin = elem.find("origin")
            axis = elem.find("axis")
            limit = elem.find("limit")
            if origin is None or axis is None or limit is None:
                raise RuntimeError(f"关节 {jname} 缺少 origin/axis/limit")
            xyz = [float(x) for x in origin.attrib.get("xyz", "0 0 0").split()]
            rpy = [float(x) for x in origin.attrib.get("rpy", "0 0 0").split()]
            axis_v = [float(x) for x in axis.attrib.get("xyz", "0 0 1").split()]
            lo = float(limit.attrib["lower"])
            hi = float(limit.attrib["upper"])
            out.append(JointDesc(jname, xyz, rpy, axis_v, lo, hi))
        return out

    def forward(self, q: Sequence[float]) -> Tuple[List[float], List[List[float]]]:
        """getting the end-effector pose transformation matrix (position + rotation matrix) given joint angles q"""
        if len(q) != 6:
            raise ValueError("q length must be 6")
        # initialize the transformation matrix
        t = [[1.0, 0.0, 0.0, 0.0], [0.0, 1.0, 0.0, 0.0], [0.0, 0.0, 1.0, 0.0], [0.0, 0.0, 0.0, 1.0]]
        for i, joint in enumerate(self.joints):
            # rpy roll , pich, yaw
            # t0表示从上一关节坐标系到当前关节坐标系的变换（由URDF中的origin定义），tq表示当前关节的旋转变换（由axis和q定义）。通过连续乘积更新末端位姿。
            t0 = compose_transform(rpy_to_rot(joint.rpy[0], joint.rpy[1], joint.rpy[2]), joint.xyz)
            tq = compose_transform(axis_angle_rot(joint.axis, q[i]), [0.0, 0.0, 0.0])
            t = transform_mul(t, transform_mul(t0, tq))
        pos = [t[0][3], t[1][3], t[2][3]]
        rot = [
            [t[0][0], t[0][1], t[0][2]],
            [t[1][0], t[1][1], t[1][2]],
            [t[2][0], t[2][1], t[2][2]],
        ]
        return pos, rot

    def solve(
        self,
        target_pose: Sequence[float],
        seed_q: Sequence[float],
        max_iters: int = IK_MAX_ITERS,
        pos_tol: float = IK_POS_TOL,
        rot_tol: float = IK_ROT_TOL,
    ) -> Tuple[bool, List[float], Dict[str, float]]:
        if len(target_pose) != 6:
            raise ValueError("target_pose must be [x,y,z,r,p,y]")
        q = [float(v) for v in seed_q] # copy seed_q to q, which will be updated iteratively
        tgt_pos = [target_pose[0], target_pose[1], target_pose[2]]
        tgt_rot = rpy_to_rot(target_pose[3], target_pose[4], target_pose[5])

        for _ in range(max_iters):
            curr_pos, curr_rot = self.forward(q)
            err6, pos_err, rot_err = pose_error(curr_pos, curr_rot, tgt_pos, tgt_rot)
            if pos_err < pos_tol and rot_err < rot_tol:
                return True, q, {"pos_err": pos_err, "rot_err": rot_err}

            # numerical Jacobian J(6x6)

            eps = 1e-4 # finite difference step 微小扰动

            # 计算微扰后末端位姿与当前末端位姿的误差，
            # 作为关节 j 的数值雅可比矩阵列（6D 误差对关节增量的敏感度），
            # 通过除以 eps 得到雅可比矩阵的近似值。
            j_mat = [[0.0] * 6 for _ in range(6)]
            for j in range(6):
                q2 = q[:]
                q2[j] += eps
                p2, r2 = self.forward(q2)
                e2, _, _ = pose_error(curr_pos, curr_rot, p2, r2) 
                for k in range(6):
                    j_mat[k][j] = e2[k] / eps

            w_err = [
                IK_POSITION_WEIGHT * err6[0],
                IK_POSITION_WEIGHT * err6[1],
                IK_POSITION_WEIGHT * err6[2],
                IK_ROTATION_WEIGHT * err6[3],
                IK_ROTATION_WEIGHT * err6[4],
                IK_ROTATION_WEIGHT * err6[5],
            ]

            # Damped Least Squares (DLS) method to compute joint updates dq
            # DLS: dq = J^T * (J J^T + λ^2 I)^-1 * e
            jj_t = [[0.0] * 6 for _ in range(6)]
            for r in range(6):
                for c in range(6):
                    s = 0.0
                    for k in range(6):
                        s += j_mat[r][k] * j_mat[c][k]
                    jj_t[r][c] = s
                jj_t[r][r] += IK_DAMPING * IK_DAMPING

            y = solve_linear(jj_t, w_err)
            if y is None:
                break

            dq = [0.0] * 6
            for i in range(6):
                s = 0.0
                for k in range(6):
                    s += j_mat[k][i] * y[k]
                dq[i] = clamp(s, -IK_STEP_LIMIT, IK_STEP_LIMIT)

            for i, joint in enumerate(self.joints):
                q[i] = clamp(q[i] + dq[i], joint.lower, joint.upper)

        curr_pos, curr_rot = self.forward(q)
        _, pos_err, rot_err = pose_error(curr_pos, curr_rot, tgt_pos, tgt_rot)
        return False, q, {"pos_err": pos_err, "rot_err": rot_err}


def load_track(csv_path: str) -> List[List[float]]:
    with open(csv_path, "r", encoding="utf-8") as f:
        rows = [row for row in csv.reader(f) if row]
    if not rows:
        raise RuntimeError("轨迹文件为空")

    parsed: List[List[float]] = []
    for row in rows:
        try:
            parsed.append([float(v) for v in row])
        except ValueError:
            # 支持有 header 的文件：非数值行跳过
            continue

    if not parsed:
        raise RuntimeError("轨迹文件中没有可解析数值行")
    return parsed


def load_track_from_hdf5(hdf5_path: str, episode_name: str) -> List[List[float]]:
    try:
        import h5py  # type: ignore
    except Exception as exc:
        raise RuntimeError("使用 DATA_SOURCE='hdf5' 需要先安装 h5py") from exc

    if not os.path.exists(hdf5_path):
        raise FileNotFoundError(f"hdf5 不存在: {hdf5_path}")

    with h5py.File(hdf5_path, "r") as f:
        if "data" not in f:
            raise RuntimeError("hdf5 缺少 /data group")
        data = f["data"]
        if episode_name not in data:
            raise RuntimeError(f"hdf5 缺少 episode: {episode_name}")
        ep = data[episode_name]

        obs = ep.get("obs")
        if obs is None:
            raise RuntimeError("hdf5 缺少 /data/<episode>/obs")

        times = None
        if "t" in obs:
            t_arr = obs["t"][...]
            if len(t_arr.shape) == 2 and t_arr.shape[1] == 1:
                times = [float(v[0]) for v in t_arr]
            else:
                times = [float(v) for v in t_arr]

        if TRAJECTORY_MODE == "pose":
            if "tcp_pose" not in obs:
                raise RuntimeError("TRAJECTORY_MODE=pose 但 hdf5 中缺少 obs/tcp_pose")
            values = [[float(x) for x in row] for row in obs["tcp_pose"][...]]
        elif TRAJECTORY_MODE == "joint":
            if "q" not in obs:
                raise RuntimeError("TRAJECTORY_MODE=joint 但 hdf5 中缺少 obs/q")
            values = [[float(x) for x in row] for row in obs["q"][...]]
        else:
            raise ValueError(f"未知 TRAJECTORY_MODE: {TRAJECTORY_MODE}")

        rows: List[List[float]] = []
        for i, v in enumerate(values):
            wait_t = 0.0
            if times is not None and i > 0:
                wait_t = max(0.0, times[i] - times[i - 1])
            rows.append([wait_t] + v[:6])
        return rows


def get_joint_limits(arm) -> Dict[int, Tuple[float, float]]:
    limits = {}
    cfg_limits = arm.robot_cfg.get("joint_limits", {})
    for i in range(1, 7):
        key = f"joint{i}"
        if key in cfg_limits and len(cfg_limits[key]) == 2:
            lo, hi = cfg_limits[key]
            limits[i] = (float(lo), float(hi))
    return limits


def clip_joints(joints: List[float], limits: Dict[int, Tuple[float, float]]) -> Tuple[List[float], bool]:
    out = list(joints)
    changed = False
    for i, q in enumerate(out, start=1):
        if i not in limits:
            continue
        lo, hi = limits[i]
        q_new = min(max(q, lo), hi)
        if q_new != q:
            out[i - 1] = q_new
            changed = True
    return out, changed


def get_ctrl_mode(arm):
    status = arm.get_arm_status()
    if status is None:
        return None
    return getattr(status.msg, "ctrl_mode", None)


def wait_exit_teach_mode(arm, timeout: float) -> bool:
    start_t = time.monotonic()
    got_feedback = False
    while True:
        mode = get_ctrl_mode(arm)
        if mode is not None:
            got_feedback = True
            if mode != 2:
                return True

        if time.monotonic() - start_t > timeout:
            if not got_feedback:
                print("[WARN] 未收到 ctrl_mode 反馈，继续尝试使能")
                return True
            return False
        time.sleep(0.05)


def enable_gripper_with_retry(arm, timeout: float = 3.0) -> bool:
    start_t = time.monotonic()
    while True:
        try:
            if arm.end_effector is not None and arm.end_effector.enable_gripper():
                return True
        except Exception:
            pass
        if time.monotonic() - start_t > timeout:
            return False
        time.sleep(0.05)


def wait_joints_near_home(arm, timeout: float = 25.0, tol_rad: float = 0.03) -> bool:
    start_t = time.monotonic()
    last_pub = 0.0
    while time.monotonic() - start_t <= timeout:
        now = time.monotonic()
        if now - last_pub >= 0.25:
            arm.move_j([0.0] * 6, wait=False)
            last_pub = now

        try:
            q = arm.get_joint_position_rad()
            if q and max(abs(v) for v in q) <= tol_rad:
                return True
        except Exception:
            pass

        time.sleep(0.05)
    return False


def safe_shutdown(arm, try_home: bool) -> None:
    old_sigint = signal.getsignal(signal.SIGINT)
    try:
        signal.signal(signal.SIGINT, signal.SIG_IGN)
    except Exception:
        old_sigint = None

    try:
        if try_home:
            try:
                print("[INFO] go home before disable")
                if arm.enable(timeout=3.0):
                    arm.set_speed_percent(20)
                    arm.set_motion_mode_j()
                    ok = wait_joints_near_home(arm, timeout=25.0, tol_rad=0.03)
                    if not ok:
                        print("[WARN] go home timeout")
                else:
                    print("[WARN] enable before go home failed")
            except Exception as exc:
                print(f"[WARN] go home failed: {exc}")

        try:
            print("[INFO] disable")
            if not arm.disable(timeout=8.0):
                print("[WARN] disable timeout")
        except Exception as exc:
            print(f"[WARN] disable failed: {exc}")
    finally:
        if old_sigint is not None:
            try:
                signal.signal(signal.SIGINT, old_sigint)
            except Exception:
                pass


def main() -> None:
    if PLAY_SPEED <= 0:
        raise ValueError("PLAY_SPEED 必须大于 0")
    if DATA_SOURCE == "csv":
        if not os.path.exists(CSV_PATH):
            raise FileNotFoundError(f"轨迹文件不存在: {CSV_PATH}")
        track = load_track(CSV_PATH)
    elif DATA_SOURCE == "hdf5":
        track = load_track_from_hdf5(HDF5_PATH, HDF5_EPISODE_NAME)
    else:
        raise ValueError(f"未知 DATA_SOURCE: {DATA_SOURCE}")

    if not track:
        raise RuntimeError("空轨迹")

    ik_solver = PiperUrdfIkSolver(URDF_PATH)

    have_gripper = bool(HAVE_GRIPPER)

    arm = PiperArm(
        channel=CHANNEL,
        robot_name=ROBOT_NAME,
        auto_connect=False,
        tool_type="agx_gripper" if have_gripper else "none",
    )

    connected = False
    enabled = False
    clip_warned = False
    try:
        print(f"[INFO] connect: channel={CHANNEL}, robot={ROBOT_NAME}")
        arm.connect()
        connected = True

        if have_gripper:
            try:
                arm.init_effector("agx_gripper")
                if not enable_gripper_with_retry(arm, timeout=3.0):
                    print("[WARN] gripper enable timeout, continue without gripper")
                    have_gripper = False
            except Exception as exc:
                print(f"[WARN] init gripper failed, continue without gripper: {exc}")
                have_gripper = False

        print("step 1: 播放前请确保机械臂已退出示教模式")
        if not wait_exit_teach_mode(arm, timeout=MODE_TIMEOUT):
            print("[WARN] 仍处于示教模式，将继续尝试使能")

        print("[INFO] enable")
        if not arm.enable(timeout=ENABLE_TIMEOUT):
            raise RuntimeError("enable 失败：超时")
        enabled = True

        arm.set_speed_percent(MOVE_SPEED)
        arm.set_motion_mode_j()

        limits = get_joint_limits(arm)

        q_seed = arm.get_joint_position_rad()
        if not q_seed or len(q_seed) != 6:
            q_seed = [0.0] * 6

        # 1) 先归零（与 pipeline 的预对齐思路一致）
        if ENSURE_HOME_BEFORE_REPLAY:
            print("[INFO] go home before pre-positioning to first frame")
            if not wait_joints_near_home(arm, timeout=25.0, tol_rad=0.03):
                print("[WARN] go home timeout, continue")
            q_seed = arm.get_joint_position_rad() or q_seed

        # 2) 再到第一帧，等待人工确认后再连续播放
        prepositioned = False
        first_row = track[0]
        if len(first_row) >= 7:
            first_use_pose = (TRAJECTORY_MODE == "pose")
            if first_use_pose:
                first_pose = first_row[1:7]
                ok, first_joints, info = ik_solver.solve(first_pose, q_seed)
                if not ok:
                    print(
                        "[WARN] first frame IK not fully converged: "
                        f"pos_err={info['pos_err']:.4f}m, rot_err={info['rot_err']:.4f}rad"
                    )
            else:
                first_joints = first_row[1:7]

            if CLIP_TO_LIMITS:
                first_joints, _ = clip_joints(first_joints, limits)

            print(f"[INFO] move_j to first frame: {first_joints}")
            prepositioned = bool(arm.move_j(first_joints, wait=True, timeout=12.0))
            q_seed = first_joints[:]
            if not prepositioned:
                print("[WARN] move to first frame failed or timeout, continue anyway")

        input("step 2: 已到第一帧，回车开始连续播放轨迹")

        count = 0
        while PLAY_TIMES == 0 or count < abs(PLAY_TIMES):
            start_idx = 1 if (prepositioned and START_FROM_SECOND_FRAME_IF_PREPOSITIONED and len(track) > 1) else 0
            for i in range(start_idx, len(track)):
                row = track[i]
                if len(row) < 7:
                    raise RuntimeError("轨迹列数错误，至少需要 wait_time + 6 values")

                wait_time = row[0] / PLAY_SPEED
                use_pose = (TRAJECTORY_MODE == "pose")

                if use_pose:
                    target_pose = row[1:7]
                    ok, joints, info = ik_solver.solve(target_pose, q_seed)
                    if not ok:
                        print(
                            "[WARN] IK 未在阈值内收敛: "
                            f"idx={i}, pos_err={info['pos_err']:.4f}m, rot_err={info['rot_err']:.4f}rad"
                        )
                else:
                    joints = row[1:7]

                if CLIP_TO_LIMITS:
                    joints, changed = clip_joints(joints, limits)
                    if changed and not clip_warned:
                        print("[WARN] 轨迹存在越限关节，已自动裁剪到关节限位")
                        clip_warned = True
                # print(f"[DEBUG] target joints: {joints}")
                arm.move_j(joints, wait=False)
                q_seed = joints[:]

                if have_gripper and len(row) >= 8:
                    arm.gripper_move(row[7], sleep_after=0.0)

                count += 1
                mode_txt = "pose->IK->move_j" if use_pose else "joint->move_j"
                print(
                    f"INFO: 第{count + 1}次播放[{mode_txt}]，等待:{wait_time:.4f}s，目标:{row[1:7]}"
                )

                if i == len(track) - 1:
                    time.sleep(PLAY_INTERVAL)
                else:
                    time.sleep(max(0.0, wait_time))



    except KeyboardInterrupt:
        print("\n[WARN] interrupted by user, running safe shutdown...")
    finally:
        if connected:
            safe_shutdown(arm, try_home=enabled)


if __name__ == "__main__":
    main()
