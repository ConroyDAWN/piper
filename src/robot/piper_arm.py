#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import time
from typing import Any, Dict, Optional, Sequence, Union

from pyAgxArm import create_agx_arm_config, AgxArmFactory


Number = Union[int, float]
Pose6 = Sequence[Number]
Joint6 = Sequence[Number]


class PiperArm:
    """
    基于 pyAgxArm 的 Piper 机械臂控制封装（最终版）。

    支持的工具类型:
        - "none"         : 无末端执行器
        - "custom_tool"  : 自定义被动工具（如钻），不初始化主动末端设备对象
        - "agx_gripper"  : AgileX 夹爪
        - "revo2"        : Revo2 主动末端

    推荐使用场景:
        1. 无末端执行器:
            tool_type="none"
            tcp_offset=[0,0,0,0,0,0]

        2. 自定义钻工具:
            tool_type="custom_tool"
            tcp_offset=[x,y,z,rx,ry,rz]   # 表达钻尖相对法兰中心偏移

        3. 原生主动末端:
            tool_type="agx_gripper" 或 "revo2"
            会初始化主动末端对象，可调用 gripper_* / revo2_* 接口
    """

    def __init__(
        self,
        channel: str = "can0",
        robot_name: str = "piper",
        comm: str = "can",
        interface: str = "socketcan",
        auto_connect: bool = True,
        auto_init_effector: bool = False,
        tool_type: str = "none",
        tcp_offset: Optional[Pose6] = None,
        motion_done_timeout: float = 5.0,
        motion_poll_interval: float = 0.1,
    ) -> None:
        self.channel = channel
        self.robot_name = robot_name
        self.comm = comm
        self.interface = interface

        self.motion_done_timeout = motion_done_timeout
        self.motion_poll_interval = motion_poll_interval

        self.tool_type = tool_type.lower().strip()
        self.end_effector = None
        self._connected = False

        self.robot_cfg = create_agx_arm_config(
            robot=robot_name,
            comm=comm,
            channel=channel,
            interface=interface,
        )
        self.robot = AgxArmFactory.create_arm(self.robot_cfg)

        if auto_connect:
            self.connect()

        if auto_init_effector:
            self.init_effector(self.tool_type)

        if tcp_offset is not None:
            self.set_tcp_offset(tcp_offset)

    # ============================================================
    # 生命周期 / 连接
    # ============================================================
    def connect(self) -> None:
        """连接机械臂通信通道。"""
        if not self._connected:
            self.robot.connect()
            self._connected = True

    def disconnect(self) -> None:
        """
        断开逻辑占位。
        若底层库没有显式 disconnect，可仅更新本地状态。
        """
        self._connected = False

    def __enter__(self) -> "PiperArm":
        if not self._connected:
            self.connect()
        return self

    def __exit__(self, exc_type, exc_val, exc_tb) -> None:
        self.disconnect()

    # ============================================================
    # 工具类型 / 末端执行器
    # ============================================================
    def init_effector(self, tool_type: Optional[str] = None) -> Any:
        """
        初始化末端执行器。

        参数:
            tool_type:
                - "none"
                - "custom_tool"
                - "agx_gripper"
                - "revo2"

        说明:
            - none / custom_tool: 不初始化主动末端执行器对象
            - custom_tool 适用于自定义钻等被动工具
        """
        if tool_type is not None:
            self.tool_type = tool_type.lower().strip()

        if self.tool_type in ("none", "custom_tool"):
            self.end_effector = None
            return None

        if self.tool_type == "agx_gripper":
            self.end_effector = self.robot.init_effector(
                self.robot.OPTIONS.EFFECTOR.AGX_GRIPPER
            )
            return self.end_effector

        if self.tool_type == "revo2":
            self.end_effector = self.robot.init_effector(
                self.robot.OPTIONS.EFFECTOR.REVO2
            )
            return self.end_effector

        raise ValueError(
            f"Unsupported tool_type: {self.tool_type}. "
            f"Expected one of ['none', 'custom_tool', 'agx_gripper', 'revo2']"
        )

    def set_tool_type(self, tool_type: str, auto_init: bool = False) -> None:
        """
        修改工具类型。
        """
        self.tool_type = tool_type.lower().strip()
        if auto_init:
            self.init_effector(self.tool_type)

    # ============================================================
    # 基础控制
    # ============================================================
    def enable(self, retry_interval: float = 0.01, timeout: float = 5.0) -> bool:
        """循环使能，直到成功或超时。"""
        start_t = time.monotonic()
        while not self.robot.enable():
            if time.monotonic() - start_t > timeout:
                return False
            time.sleep(retry_interval)
        return True

    def disable(self, retry_interval: float = 0.01, timeout: float = 5.0) -> bool:
        """循环失能，直到成功或超时。"""
        start_t = time.monotonic()
        while not self.robot.disable():
            if time.monotonic() - start_t > timeout:
                return False
            time.sleep(retry_interval)
        return True

    def reset(self, sleep_after: float = 1.5) -> None:
        """复位机械臂。"""
        self.robot.reset()
        time.sleep(sleep_after)

    def set_home(
        self,
        timeout: float = 2.0,
        disable_first: bool = True,
        enable_after: bool = True,
    ) -> bool:
        """将当前 6 关节位置设置为零点。

        注意：这是零点标定操作，不是运动到零位（go_home）。
        """
        if disable_first and (not self.disable(timeout=8.0)):
            print("[WARN] disable timeout, continue calibrate")

        ok = self.robot.calibrate_joint(joint_index=255, timeout=timeout)
        if not ok:
            return False

        if enable_after:
            return self.enable(timeout=8.0)
        return True

    def e_stop(self, sleep_after: float = 1.0) -> None:
        """电子急停。"""
        self.robot.electronic_emergency_stop()
        time.sleep(sleep_after)

    def wait_motion_done(
        self,
        timeout: Optional[float] = None,
        poll_interval: Optional[float] = None,
        initial_sleep: float = 0.5,
        verbose: bool = True,
    ) -> bool:
        """
        等待机械臂运动完成。
        判据：robot.get_arm_status().msg.motion_status == 0
        """
        timeout = timeout if timeout is not None else self.motion_done_timeout
        poll_interval = (
            poll_interval if poll_interval is not None else self.motion_poll_interval
        )

        time.sleep(initial_sleep)
        start_t = time.monotonic()

        while True:
            status = self.robot.get_arm_status()
            if status is not None and getattr(status.msg, "motion_status", None) == 0:
                if verbose:
                    print("motion done")
                return True

            if time.monotonic() - start_t > timeout:
                if verbose:
                    print(f"wait motion done timeout ({timeout:.1f}s)")
                return False

            time.sleep(poll_interval)

    # ============================================================
    # 参数设置
    # ============================================================
    def set_speed_percent(self, percent: int) -> Any:
        """设置速度百分比，典型范围 0~100。"""
        return self.robot.set_speed_percent(percent)

    def set_motion_mode_j(self) -> Any:
        """设置为关节运动模式 J。"""
        return self.robot.set_motion_mode(self.robot.OPTIONS.MOTION_MODE.J)

    def set_motion_mode_p(self) -> Any:
        """设置为位姿运动模式 P。"""
        return self.robot.set_motion_mode(self.robot.OPTIONS.MOTION_MODE.P)

    def set_installation_horizontal(self) -> Any:
        """设置安装位姿为水平。"""
        return self.robot.set_installation_pos(
            self.robot.OPTIONS.INSTALLATION_POS.HORIZONTAL
        )

    def set_installation_vertical(self) -> Any:
        """设置安装位姿为垂直。"""
        return self.robot.set_installation_pos(
            self.robot.OPTIONS.INSTALLATION_POS.VERTICAL
        )

    def set_payload_empty(self) -> Any:
        """设置负载为空载。"""
        return self.robot.set_payload(self.robot.OPTIONS.PAYLOAD.EMPTY)

    def set_tcp_offset(self, tcp_offset: Pose6) -> Any:
        """
        设置 TCP 偏移: [x, y, z, rx, ry, rz]
        单位通常为 m / rad。

        使用建议:
            - 无工具: [0, 0, 0, 0, 0, 0]
            - 自定义钻: 用于表达钻尖相对法兰中心的位置
        """
        self._check_len(tcp_offset, 6, "tcp_offset")
        return self.robot.set_tcp_offset(list(tcp_offset))

    def set_flange_vel_acc_limits(
        self,
        max_flange_vel_linear: float,
        max_flange_acc_linear: float,
        max_flange_vel_angular: float,
        max_flange_acc_angular: float,
    ) -> Any:
        """设置法兰线速度/线加速度/角速度/角加速度限制。"""
        return self.robot.set_flange_vel_acc_limits(
            max_flange_vel_linear,
            max_flange_acc_linear,
            max_flange_vel_angular,
            max_flange_acc_angular,
        )

    def restore_flange_vel_acc_limits_default(self) -> Any:
        """恢复法兰速度/加速度默认值。"""
        return self.robot.set_flange_vel_acc_limits_to_default()

    def set_joint_angle_vel_limit(self, joint_index: int, max_joint_spd: float) -> Any:
        """设置单个关节角速度上限。"""
        return self.robot.set_joint_angle_vel_limits(
            joint_index=joint_index,
            max_joint_spd=max_joint_spd,
        )

    def set_joint_acc_limit(self, max_joint_acc: float) -> Any:
        """设置关节加速度上限。"""
        return self.robot.set_joint_acc_limits(max_joint_acc=max_joint_acc)

    def restore_joint_vel_acc_limits_default(self) -> Any:
        """恢复关节角速度/加速度默认限制。"""
        return self.robot.set_joint_angle_vel_acc_limits_to_default()

    def set_crash_protection_rating(self, joint_index: int, rating: int) -> Any:
        """设置碰撞保护等级。"""
        return self.robot.set_crash_protection_rating(
            joint_index=joint_index,
            rating=rating,
        )

    # ============================================================
    # 运动控制
    # ============================================================
    def move_j(
        self,
        joints: Joint6,
        wait: bool = True,
        timeout: Optional[float] = None,
    ) -> bool:
        """关节空间运动。"""
        self._check_len(joints, 6, "joints")
        self.robot.move_j(list(joints))
        return self.wait_motion_done(timeout=timeout) if wait else True

    def move_js(
        self,
        joints: Joint6,
        sleep_after: float = 2.0,
    ) -> None:
        """
        MIT/伺服式关节运动接口（原示例中的 move_js）。
        通常不使用 motion_status 判定，因此默认 sleep。
        """
        self._check_len(joints, 6, "joints")
        self.robot.move_js(list(joints))
        time.sleep(sleep_after)

    def move_p(
        self,
        pose: Pose6,
        wait: bool = True,
        timeout: Optional[float] = None,
    ) -> bool:
        """点到点位姿运动。"""
        self._check_len(pose, 6, "pose")
        self.robot.move_p(list(pose))
        return self.wait_motion_done(timeout=timeout) if wait else True

    def move_l(
        self,
        pose: Pose6,
        wait: bool = True,
        timeout: Optional[float] = None,
    ) -> bool:
        """直线位姿运动。"""
        self._check_len(pose, 6, "pose")
        self.robot.move_l(list(pose))
        return self.wait_motion_done(timeout=timeout) if wait else True

    def move_c(
        self,
        start_pose: Pose6,
        mid_pose: Pose6,
        end_pose: Pose6,
        wait: bool = True,
        timeout: Optional[float] = None,
    ) -> bool:
        """圆弧运动。"""
        self._check_len(start_pose, 6, "start_pose")
        self._check_len(mid_pose, 6, "mid_pose")
        self._check_len(end_pose, 6, "end_pose")
        self.robot.move_c(list(start_pose), list(mid_pose), list(end_pose))
        return self.wait_motion_done(timeout=timeout) if wait else True

    def move_mit(
        self,
        joint_index: int,
        q_des: float,
        v_des: float = 0.0,
        kp: float = 0.0,
        kd: float = 0.0,
        t_ff: float = 0.0,
    ) -> Any:
        """MIT 模式控制单关节。"""
        return self.robot.move_mit(
            joint_index, q_des, v_des=v_des, kp=kp, kd=kd, t_ff=t_ff
        )

    def go_home(
        self,
        wait: bool = True,
        timeout: Optional[float] = None,
    ) -> bool:
        """回零位。"""
        return self.move_j([0.0] * 6, wait=wait, timeout=timeout)

    # ============================================================
    # 夹爪控制（仅 agx_gripper 可用）
    # ============================================================
    def gripper_move(self, opening: float, sleep_after: float = 0.2) -> None:
        """夹爪移动到指定开口量。"""
        self._check_effector(expected=("agx_gripper",))
        self.end_effector.move_gripper(opening)
        time.sleep(sleep_after)

    def gripper_open(self, width: float = 0.07, sleep_after: float = 0.2) -> None:
        """打开夹爪。"""
        self.gripper_move(width, sleep_after=sleep_after)

    def gripper_close(self, sleep_after: float = 0.2) -> None:
        """闭合夹爪。"""
        self.gripper_move(0.0, sleep_after=sleep_after)

    def gripper_disable(self) -> Any:
        """失能夹爪。"""
        self._check_effector(expected=("agx_gripper",))
        return self.end_effector.disable_gripper()

    def gripper_calibrate(self) -> Any:
        """夹爪标定。"""
        self._check_effector(expected=("agx_gripper",))
        return self.end_effector.calibrate_gripper()

    def set_gripper_teaching_param(
        self,
        teaching_range_per: Optional[int] = None,
        max_range_config: Optional[float] = None,
        teaching_friction: Optional[int] = None,
    ) -> Any:
        """设置夹爪示教器参数。"""
        self._check_effector(expected=("agx_gripper",))
        kwargs = {}
        if teaching_range_per is not None:
            kwargs["teaching_range_per"] = teaching_range_per
        if max_range_config is not None:
            kwargs["max_range_config"] = max_range_config
        if teaching_friction is not None:
            kwargs["teaching_friction"] = teaching_friction
        return self.end_effector.set_gripper_teaching_pendant_param(**kwargs)

    # ============================================================
    # Revo2 控制（仅 revo2 可用）
    # ============================================================
    def revo2_position_ctrl(self) -> Any:
        self._check_effector(expected=("revo2",))
        return self.end_effector.position_ctrl()

    def revo2_speed_ctrl(self) -> Any:
        self._check_effector(expected=("revo2",))
        return self.end_effector.speed_ctrl()

    def revo2_current_ctrl(self) -> Any:
        self._check_effector(expected=("revo2",))
        return self.end_effector.current_ctrl()

    def revo2_position_time_ctrl(self, **kwargs) -> Any:
        self._check_effector(expected=("revo2",))
        return self.end_effector.position_time_ctrl(**kwargs)

    # ============================================================
    # Leader / Follower
    # ============================================================
    def set_leader_mode(self) -> Any:
        return self.robot.set_leader_mode()

    def set_follower_mode(self) -> Any:
        return self.robot.set_follower_mode()

    def move_leader_to_home(self) -> Any:
        return self.robot.move_leader_to_home()

    def restore_leader_drag_mode(self) -> Any:
        return self.robot.restore_leader_drag_mode()

    # ============================================================
    # 数据读取
    # ============================================================
    def get_arm_status(self) -> Any:
        return self.robot.get_arm_status()

    def get_firmware(self) -> Any:
        return self.robot.get_firmware()

    def get_joint_angles(self) -> Any:
        return self.robot.get_joint_angles()

    def get_flange_pose(self) -> Any:
        return self.robot.get_flange_pose()

    def get_tcp_pose(self) -> Any:
        return self.robot.get_tcp_pose()

    def get_flange2tcp_pose(self, flange_pose_msg: Any) -> Any:
        return self.robot.get_flange2tcp_pose(flange_pose_msg)

    def get_tcp2flange_pose(self, tcp_pose: Pose6) -> Any:
        self._check_len(tcp_pose, 6, "tcp_pose")
        return self.robot.get_tcp2flange_pose(list(tcp_pose))

    def get_motor_states(self, joint_index: int) -> Any:
        return self.robot.get_motor_states(joint_index)

    def get_driver_states(self, joint_index: int) -> Any:
        return self.robot.get_driver_states(joint_index)

    def get_joint_enable_status(self, joint_index: int) -> Any:
        return self.robot.get_joint_enable_status(joint_index)

    def get_joints_enable_status_list(self) -> Any:
        return self.robot.get_joints_enable_status_list()

    def get_joint_angle_vel_limits(self, joint_index: int) -> Any:
        return self.robot.get_joint_angle_vel_limits(joint_index)

    def get_joint_acc_limits(self, joint_index: int) -> Any:
        return self.robot.get_joint_acc_limits(joint_index)

    def get_flange_vel_acc_limits(self) -> Any:
        return self.robot.get_flange_vel_acc_limits()

    def get_crash_protection_rating(self) -> Any:
        return self.robot.get_crash_protection_rating()

    def get_fps(self) -> Any:
        return self.robot.get_fps()

    def is_ok(self) -> Any:
        return self.robot.is_ok()

    def get_channel(self) -> str:
        return self.robot.get_channel()

    # ============================================================
    # 汇总读取
    # ============================================================
    def get_robot_state_dict(self) -> Dict[str, Any]:
        """
        汇总读取机械臂常用状态。
        适合后续 record_once.py / 数据采集 / 调试打印。
        """
        return {
            "channel": self.get_channel(),
            "tool_type": self.tool_type,
            "is_ok": self.is_ok(),
            "fps": self.get_fps(),
            "arm_status": self.get_arm_status(),
            "firmware": self.get_firmware(),
            "joint_angles": self.get_joint_angles(),
            "flange_pose": self.get_flange_pose(),
            "tcp_pose": self.get_tcp_pose(),
            "joint_enable_status_list": self.get_joints_enable_status_list(),
            "flange_vel_acc_limits": self.get_flange_vel_acc_limits(),
            "crash_protection_rating": self.get_crash_protection_rating(),
        }

    def print_robot_state(self) -> None:
        """打印汇总状态。"""
        state = self.get_robot_state_dict()
        for k, v in state.items():
            print(f"[{k}]")
            print(v)
            print()

    # ============================================================
    # 帮助函数
    # ============================================================
    def print_api_guide(self, category: Optional[str] = None) -> None:
        """
        按功能分类打印当前类的常用接口，便于快速查阅。

        category:
            - None: 打印全部
            - "lifecycle"
            - "tool"
            - "basic"
            - "config"
            - "motion"
            - "gripper"
            - "revo2"
            - "leader_follower"
            - "state"
            - "tools"
        """
        api_map = {
            "lifecycle": {
                "desc": "生命周期/连接相关",
                "funcs": [
                    "connect()",
                    "disconnect()",
                    "__enter__() / __exit__()",
                ],
            },
            "tool": {
                "desc": "工具/末端执行器相关",
                "funcs": [
                    "set_tool_type(tool_type, auto_init=False)",
                    "init_effector(tool_type=None)",
                    "支持 tool_type: 'none' | 'custom_tool' | 'agx_gripper' | 'revo2'",
                    "说明: custom_tool 不初始化主动末端对象，通常配合 set_tcp_offset() 使用",
                ],
            },
            "basic": {
                "desc": "基础控制",
                "funcs": [
                    "enable()",
                    "disable()",
                    "reset()",
                    "e_stop()",
                    "wait_motion_done()",
                ],
            },
            "config": {
                "desc": "参数设置",
                "funcs": [
                    "set_speed_percent(percent)",
                    "set_motion_mode_j()",
                    "set_motion_mode_p()",
                    "set_installation_horizontal()",
                    "set_installation_vertical()",
                    "set_payload_empty()",
                    "set_tcp_offset(tcp_offset)",
                    "set_flange_vel_acc_limits(...)",
                    "restore_flange_vel_acc_limits_default()",
                    "set_joint_angle_vel_limit(joint_index, max_joint_spd)",
                    "set_joint_acc_limit(max_joint_acc)",
                    "restore_joint_vel_acc_limits_default()",
                    "set_crash_protection_rating(joint_index, rating)",
                ],
            },
            "motion": {
                "desc": "机械臂运动控制",
                "funcs": [
                    "move_j(joints, wait=True, timeout=None)",
                    "move_js(joints, sleep_after=2.0)",
                    "move_p(pose, wait=True, timeout=None)",
                    "move_l(pose, wait=True, timeout=None)",
                    "move_c(start_pose, mid_pose, end_pose, wait=True, timeout=None)",
                    "move_mit(joint_index, q_des, v_des=0.0, kp=0.0, kd=0.0, t_ff=0.0)",
                    "go_home(wait=True, timeout=None)",
                ],
            },
            "gripper": {
                "desc": "夹爪控制（仅 agx_gripper）",
                "funcs": [
                    "gripper_move(opening, sleep_after=0.2)",
                    "gripper_open(width=0.07, sleep_after=0.2)",
                    "gripper_close(sleep_after=0.2)",
                    "gripper_disable()",
                    "gripper_calibrate()",
                    "set_gripper_teaching_param(...)",
                ],
            },
            "revo2": {
                "desc": "Revo2 控制（仅 revo2）",
                "funcs": [
                    "revo2_position_ctrl()",
                    "revo2_speed_ctrl()",
                    "revo2_current_ctrl()",
                    "revo2_position_time_ctrl(**kwargs)",
                ],
            },
            "leader_follower": {
                "desc": "主从控制相关",
                "funcs": [
                    "set_leader_mode()",
                    "set_follower_mode()",
                    "move_leader_to_home()",
                    "restore_leader_drag_mode()",
                ],
            },
            "state": {
                "desc": "状态读取",
                "funcs": [
                    "get_arm_status()",
                    "get_firmware()",
                    "get_joint_angles()",
                    "get_flange_pose()",
                    "get_tcp_pose()",
                    "get_flange2tcp_pose(flange_pose_msg)",
                    "get_tcp2flange_pose(tcp_pose)",
                    "get_motor_states(joint_index)",
                    "get_driver_states(joint_index)",
                    "get_joint_enable_status(joint_index)",
                    "get_joints_enable_status_list()",
                    "get_joint_angle_vel_limits(joint_index)",
                    "get_joint_acc_limits(joint_index)",
                    "get_flange_vel_acc_limits()",
                    "get_crash_protection_rating()",
                    "get_fps()",
                    "is_ok()",
                    "get_channel()",
                ],
            },
            "tools": {
                "desc": "工具与汇总接口",
                "funcs": [
                    "get_robot_state_dict()",
                    "print_robot_state()",
                    "print_api_guide(category=None)",
                    "print_quick_examples()",
                    "help(category=None)",
                ],
            },
        }

        if category is not None:
            category = category.strip().lower()
            if category not in api_map:
                print(f"Unknown category: {category}")
                print("Available categories:")
                for key in api_map.keys():
                    print(f"  - {key}")
                return
            selected_keys = [category]
        else:
            selected_keys = list(api_map.keys())

        print("\n========== PiperArm API Guide ==========\n")
        for key in selected_keys:
            print(f"[{key}] {api_map[key]['desc']}")
            for func in api_map[key]["funcs"]:
                print(f"  - {func}")
            print()

    def print_quick_examples(self) -> None:
        """打印最小使用示例。"""
        print("\n========== PiperArm Quick Examples ==========\n")

        print("[1] 无末端执行器")
        print("  arm = PiperArm(channel='can0', tool_type='none')")
        print("  arm.enable()")
        print("  arm.set_tcp_offset([0, 0, 0, 0, 0, 0])")
        print("  arm.move_j([0, 0.3, 0, 0, 0, 0])")
        print()

        print("[2] 自定义钻工具")
        print("  arm = PiperArm(channel='can0', tool_type='custom_tool')")
        print("  arm.enable()")
        print("  arm.set_tcp_offset([0.0, 0.0, 0.12, 0.0, 0.0, 0.0])")
        print("  arm.move_p([0.25, 0.00, 0.18, 0.0, 1.57, 0.0])")
        print()

        print("[3] AgileX 夹爪")
        print("  arm = PiperArm(channel='can0', tool_type='agx_gripper')")
        print("  arm.init_effector()")
        print("  arm.enable()")
        print("  arm.gripper_open()")
        print("  arm.gripper_close()")
        print()

        print("[4] 状态读取")
        print("  state = arm.get_robot_state_dict()")
        print("  print(state['joint_angles'])")
        print("  print(state['tcp_pose'])")
        print()

    def help(self, category: Optional[str] = None) -> None:
        """print_api_guide 的别名。"""
        self.print_api_guide(category)

    # ============================================================
    # 私有工具函数
    # ============================================================
    @staticmethod
    def _check_len(data: Sequence[Any], expected_len: int, name: str) -> None:
        if len(data) != expected_len:
            raise ValueError(f"{name} length must be {expected_len}, got {len(data)}")

    def _check_effector(self, expected: Optional[Sequence[str]] = None) -> None:
        if self.end_effector is None:
            raise RuntimeError(
                f"No active end effector object. Current tool_type='{self.tool_type}'. "
                f"If you are using 'none' or 'custom_tool', gripper/revo2 methods are unavailable."
            )
        if expected is not None and self.tool_type not in expected:
            raise RuntimeError(
                f"Current tool_type='{self.tool_type}' does not support this method. "
                f"Expected one of {list(expected)}."
            )
        

    # ============================================================
    # Observation / Action
    # ============================================================
    def get_joint_position_rad(self) -> list:
        """
        获取当前 6 关节角度，单位 rad。
        当前环境下：get_joint_angles().msg 为 6 维 list
        """
        data = self.get_joint_angles()
        if not hasattr(data, "msg"):
            raise RuntimeError("get_joint_angles() 返回对象中不存在 msg 字段")
        q = data.msg
        if not isinstance(q, (list, tuple)) or len(q) != 6:
            raise RuntimeError(f"joint_angles.msg 不是长度为6的列表，实际为: {q}")
        return [float(v) for v in q]

    def get_joint_velocity_rad_s(self) -> list:
        """
        获取当前 6 关节角速度，单位 rad/s。
        逐个读取 get_motor_states(joint_index)。
        """
        dq = []
        speed_fields = ["motor_speed", "speed", "vel", "velocity"]

        for joint_index in range(1, 7):
            data = self.get_motor_states(joint_index)

            candidates = []
            if hasattr(data, "msg"):
                candidates.append(data.msg)
            candidates.append(data)

            found = False
            for obj in candidates:
                for field in speed_fields:
                    if hasattr(obj, field):
                        dq.append(float(getattr(obj, field)))
                        found = True
                        break
                if found:
                    break

            if not found:
                raise RuntimeError(
                    f"joint {joint_index} 未找到速度字段，"
                    f"请先打印 arm.get_motor_states({joint_index}) 查看真实结构"
                )

        return dq

    def get_tcp_pose6(self) -> list:
        """
        获取当前 TCP 位姿 [x, y, z, rx, ry, rz]。
        当前环境下：get_tcp_pose().msg 为 6 维 list
        """
        data = self.get_tcp_pose()
        if not hasattr(data, "msg"):
            raise RuntimeError("get_tcp_pose() 返回对象中不存在 msg 字段")
        tcp_pose = data.msg
        if not isinstance(tcp_pose, (list, tuple)) or len(tcp_pose) != 6:
            raise RuntimeError(f"tcp_pose.msg 不是长度为6的列表，实际为: {tcp_pose}")
        return [float(v) for v in tcp_pose]

    def get_tcp_xyz(self) -> list:
        """获取当前 TCP 位置 [x, y, z]。"""
        return self.get_tcp_pose6()[:3]

    def get_observation_dict(self, timestamp: float = None) -> dict:
        """
        获取当前 observation。

        返回格式：
            {
                "t": 时间戳,
                "q": [q1..q6],              # rad
                "dq": [dq1..dq6],           # rad/s
                "tcp_pose": [x,y,z,rx,ry,rz],
                "tcp_xyz": [x,y,z],
            }
        """
        if timestamp is None:
            timestamp = time.time()

        q = self.get_joint_position_rad()
        dq = self.get_joint_velocity_rad_s()
        tcp_pose = self.get_tcp_pose6()
        tcp_xyz = tcp_pose[:3]

        return {
            "t": float(timestamp),
            "q": q,
            "dq": dq,
            "tcp_pose": tcp_pose,
            "tcp_xyz": tcp_xyz,
        }

    @staticmethod
    def compute_action_from_obs(prev_obs: dict, curr_obs: dict) -> list:
        """
        用相邻两帧 TCP 位置差分得到 action = [Δx, Δy, Δz]
        """
        prev_xyz = prev_obs["tcp_xyz"]
        curr_xyz = curr_obs["tcp_xyz"]
        return [
            float(curr_xyz[0] - prev_xyz[0]),
            float(curr_xyz[1] - prev_xyz[1]),
            float(curr_xyz[2] - prev_xyz[2]),
        ]

    def build_sample_with_last_action(
        self,
        prev_prev_obs: dict,
        prev_obs: dict,
        curr_obs: dict,
    ) -> dict:
        """
        用三帧 observation 构造样本：

            sample = {
                "obs": obs_t,
                "action": action_t,
                "last_action": last_action_t
            }

        其中：
            last_action_t = obs_(t-1) - obs_(t-2) 的 TCP差分
            action_t      = obs_t     - obs_(t-1) 的 TCP差分
        """
        last_action = self.compute_action_from_obs(prev_prev_obs, prev_obs)
        action = self.compute_action_from_obs(prev_obs, curr_obs)

        return {
            "obs": curr_obs,
            "action": action,
            "last_action": last_action,
        }

    def print_observation(
        self,
        obs: dict,
        precision: int = 6,
    ) -> None:
        """
        打印 observation。
        """
        def fmt(vals):
            return "[" + ", ".join(f"{float(v):.{precision}f}" for v in vals) + "]"

        print("\n========== Observation ==========")
        print(f"t              : {obs['t']:.6f}")
        print(f"q (rad)        : {fmt(obs['q'])}")
        print(f"dq (rad/s)     : {fmt(obs['dq'])}")
        print(f"tcp_xyz (m)    : {fmt(obs['tcp_xyz'])}")
        print(f"tcp_pose (6D)  : {fmt(obs['tcp_pose'])}")
        print("=================================\n")

    def print_sample(
        self,
        sample: dict,
        precision: int = 6,
    ) -> None:
        """
        打印 sample = {obs, action, last_action}
        """
        def fmt(vals):
            return "[" + ", ".join(f"{float(v):.{precision}f}" for v in vals) + "]"

        print("\n========== Sample ==========")
        obs = sample["obs"]
        print(f"t              : {obs['t']:.6f}")
        print(f"q (rad)        : {fmt(obs['q'])}")
        print(f"dq (rad/s)     : {fmt(obs['dq'])}")
        print(f"tcp_xyz (m)    : {fmt(obs['tcp_xyz'])}")
        print(f"tcp_pose (6D)  : {fmt(obs['tcp_pose'])}")
        print(f"action         : {fmt(sample['action'])}")
        print(f"last_action    : {fmt(sample['last_action'])}")
        print("============================\n")

    def observe_once(self, do_print: bool = True) -> dict:
        """
        仅读取一帧 observation。
        """
        obs = self.get_observation_dict()
        if do_print:
            self.print_observation(obs)
        return obs