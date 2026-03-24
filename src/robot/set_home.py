#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""Set current pose as zero point for all piper joints.

This script uses pyAgxArm calibrate_joint(255) to set current joint positions
as the zero reference.
"""

import argparse
import time

from piper_arm import PiperArm


def main() -> None:
	parser = argparse.ArgumentParser(
		description="Set current pose as zero point for all joints"
	)
	parser.add_argument("--channel", default="can0", help="CAN channel")
	parser.add_argument("--robot-name", default="piper", help="robot name")
	parser.add_argument(
		"--timeout",
		type=float,
		default=2.0,
		help="calibration timeout for each joint",
	)
	parser.add_argument(
		"--yes",
		action="store_true",
		help="skip interactive confirmation",
	)
	parser.add_argument(
		"--enable-after",
		action="store_true",
		help="enable robot after calibration",
	)
	args = parser.parse_args()

	arm = PiperArm(
		channel=args.channel,
		robot_name=args.robot_name,
		auto_connect=False,
		tool_type="none",
	)

	print(f"[INFO] connect: channel={args.channel}, robot={args.robot_name}")
	arm.connect()

	# Let status frames update before reading.
	time.sleep(0.2)
	try:
		joints = arm.get_joint_position_rad()
		print(f"[INFO] current joints(rad): {joints}")
	except Exception as exc:  # noqa: BLE001
		print(f"[WARN] failed to read joints before calibration: {exc}")

	print("[WARN] This will set CURRENT pose as zero for ALL joints.")
	if not args.yes:
		ans = input("Type 'YES' to continue: ").strip()
		if ans != "YES":
			print("[INFO] canceled")
			return

	print("[INFO] disable all joints before calibration")
	if not arm.disable(timeout=8.0):
		print("[WARN] disable timeout, continue trying calibration")

	print("[INFO] calibrate all joints (joint_index=255)")
	ok = arm.robot.calibrate_joint(joint_index=255, timeout=args.timeout)
	if not ok:
		raise RuntimeError("calibrate_joint(255) failed")

	print("[INFO] calibration success: current pose is now zero")

	if args.enable_after:
		print("[INFO] enable after calibration")
		if not arm.enable(timeout=8.0):
			raise RuntimeError("enable after calibration failed")
		print("[INFO] enable success")


if __name__ == "__main__":
	main()
