#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import argparse
import ast
import shlex
from typing import Any, Dict, List, Set, Tuple

from piper_arm import PiperArm


SAFE_METHODS: Set[str] = {
    "enable",
    "disable",
    "go_home",
    "move_j",
    "move_js",
    "move_p",
    "move_l",
    "move_c",
    "set_speed_percent",
    "set_motion_mode_j",
    "set_motion_mode_p",
    "set_tcp_offset",
    "set_payload_empty",
    "set_installation_horizontal",
    "set_installation_vertical",
    "get_arm_status",
    "get_joint_angles",
    "get_flange_pose",
    "get_tcp_pose",
    "get_robot_state_dict",
    "print_robot_state",
    "is_ok",
    "get_fps",
    "get_channel",

    # 新增
    "get_joint_position_rad",
    "get_joint_velocity_rad_s",
    "get_tcp_pose6",
    "get_tcp_xyz",
    "get_observation_dict",
    "observe_once",
}


def build_arm(channel: str, init_mode: str) -> PiperArm:
    """
    初始化 PiperArm。

    init_mode:
        - custom_tool: 自定义被动工具（custom_）
        - none: 无末端工具
    """
    if init_mode == "custom_tool":
        return PiperArm(
            channel=channel,
            auto_connect=False,
            tool_type="custom_tool",
            tcp_offset=[0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
        )

    return PiperArm(
        channel=channel,
        auto_connect=False,
        tool_type="none",
        tcp_offset=[0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
    )


def parse_token(token: str) -> Any:
    """把 token 解析成 Python 字面量，失败时原样返回字符串。"""
    lower = token.lower()
    if lower == "true":
        return True
    if lower == "false":
        return False
    if lower == "none":
        return None

    try:
        return ast.literal_eval(token)
    except (ValueError, SyntaxError):
        return token


def parse_call(line: str) -> Tuple[str, List[Any], Dict[str, Any]]:
    """
    解析命令格式:
        method arg1 arg2 key=value
    """
    parts = shlex.split(line)
    if not parts:
        raise ValueError("空命令")

    method = parts[0]
    args: List[Any] = []
    kwargs: Dict[str, Any] = {}

    for p in parts[1:]:
        if "=" in p:
            key, val = p.split("=", 1)
            if not key:
                raise ValueError(f"非法参数: {p}")
            kwargs[key] = parse_token(val)
        else:
            args.append(parse_token(p))

    return method, args, kwargs


def print_repl_help() -> None:
    print("\n===== Piper 交互命令 =====")
    print("内置命令:")
    print("  help            查看帮助")
    print("  methods         查看白名单方法")
    print("  state           打印汇总状态")
    print("  exit / quit     退出")
    print("\n调用格式:")
    print("  method [arg ...] [key=value ...]")
    print("\n示例:")
    print("  go_home wait=True timeout=15")
    print("  move_j \"[0,0.3,0,0,0,0]\" wait=True timeout=10")
    print("  set_speed_percent 20")
    print("==========================\n")


def run_repl(arm: PiperArm) -> None:
    print_repl_help()
    while True:
        try:
            line = input("piper> ").strip()
        except (KeyboardInterrupt, EOFError):
            print("\n[INFO] 收到退出信号")
            break

        if not line:
            continue
        if line in {"exit", "quit"}:
            break
        if line == "help":
            print_repl_help()
            continue
        if line == "methods":
            print("\n白名单可调用方法:")
            for name in sorted(SAFE_METHODS):
                print(f"  - {name}")
            print()
            continue
        if line == "state":
            arm.print_robot_state()
            continue

        try:
            method_name, args, kwargs = parse_call(line)

            if method_name.startswith("_"):
                raise PermissionError("禁止调用私有方法")
            if method_name not in SAFE_METHODS:
                raise PermissionError(
                    f"方法不在白名单中: {method_name}. 输入 methods 查看可用方法"
                )

            method = getattr(arm, method_name, None)
            if method is None or not callable(method):
                raise AttributeError(f"方法不存在: {method_name}")

            result = method(*args, **kwargs)
            print(f"[RET] {result}")
        except Exception as exc:
            print(f"[ERROR] {exc}")


def main() -> None:
    parser = argparse.ArgumentParser(
        description="PiperArm 交互测试：输入函数与参数控制机械臂"
    )
    parser.add_argument("--channel", default="can0", help="CAN 通道，例如 can0")
    parser.add_argument(
        "--init-mode",
        default="none",
        choices=["none", "custom_tool"],
        help="初始化方式：none(无tool) 或 custom_tool(custom_)",
    )
    parser.add_argument(
        "--auto-home",
        action="store_true",
        help="进入交互前自动 go_home 一次",
    )
    args = parser.parse_args()

    arm = build_arm(channel=args.channel, init_mode=args.init_mode)

    try:
        print(f"[INFO] connect: channel={args.channel}, init_mode={args.init_mode}")
        arm.connect()

        print("[INFO] enable")
        if not arm.enable(timeout=8.0):
            raise RuntimeError("enable 失败：超时")

        if args.auto_home:
            print("[INFO] go home")
            if not arm.go_home(wait=True, timeout=15.0):
                raise RuntimeError("go_home 失败：超时")

        print("[INFO] 进入交互模式，输入 help 查看说明")
        run_repl(arm)

    finally:
        print("[INFO] disable")
        arm.disable(timeout=8.0)


if __name__ == "__main__":
    main()
