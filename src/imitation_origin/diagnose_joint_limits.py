#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""诊断关节限位问题：检查HDF5数据 vs 机器人配置"""

import h5py
import json
import numpy as np

# HDF5文件和机器人配置
HDF5_PATH = "/home/flowing/piper/data/single_demo2/demo_001.hdf5"
EPISODE_NAME = "demo_0"

# 从 piper_arm.py 中查看实际的关节限位
ROBOT_CONFIG_PATH = "/home/flowing/piper/agx_arm_ws/install/agx_arm_ctrl/share/agx_arm_ctrl/config/piper_l.yaml"

print("=" * 70)
print("第一步：检查 HDF5 中的关节角范围")
print("=" * 70)

try:
    with h5py.File(HDF5_PATH, "r") as f:
        if f"data/{EPISODE_NAME}" not in f:
            print(f"❌ 未找到 episode: {EPISODE_NAME}")
            print(f"   可用的 episode: {list(f['data'].keys())}")
        else:
            ep = f[f"data/{EPISODE_NAME}"]
            obs = ep.get("obs")
            if obs is None:
                print("❌ 未找到 obs 数据")
            else:
                if "q" not in obs:
                    print("❌ 未找到关节角数据 (obs/q)")
                else:
                    q_data = obs["q"][...]  # shape: (N, 6)
                    print(f"✓ 读取关节角数据，形状: {q_data.shape}")
                    print()
                    
                    # 逐个关节分析
                    for joint_idx in range(6):
                        j_data = q_data[:, joint_idx]
                        print(f"Joint {joint_idx + 1}:")
                        print(f"  最小值: {j_data.min():.6f} rad ({np.degrees(j_data.min()):.2f}°)")
                        print(f"  最大值: {j_data.max():.6f} rad ({np.degrees(j_data.max()):.2f}°)")
                        print(f"  均值:   {j_data.mean():.6f} rad")
                        print(f"  标准差: {j_data.std():.6f} rad")
                        print()

except FileNotFoundError:
    print(f"❌ 找不到 HDF5 文件: {HDF5_PATH}")
except Exception as e:
    print(f"❌ 读取 HDF5 错误: {e}")

print("=" * 70)
print("第二步：检查机器人配置中的关节限位")
print("=" * 70)

try:
    import yaml
    with open(ROBOT_CONFIG_PATH, "r") as f:
        cfg = yaml.safe_load(f)
    
    if "joint_limits" in cfg:
        print("✓ 找到机器人配置中的关节限位:")
        print()
        for i in range(1, 7):
            key = f"joint{i}"
            if key in cfg["joint_limits"]:
                lo, hi = cfg["joint_limits"][key]
                print(f"Joint {i}: [{lo:.6f}, {hi:.6f}] rad")
                print(f"         [{np.degrees(lo):.2f}°, {np.degrees(hi):.2f}°]")
            else:
                print(f"Joint {i}: ⚠️  未定义")
        print()
    else:
        print("⚠️  配置中未找到 joint_limits")
        
except FileNotFoundError:
    print(f"⚠️  找不到配置文件: {ROBOT_CONFIG_PATH}")
except Exception as e:
    print(f"❌ 读取配置错误: {e}")

print("=" * 70)
print("第三步：对比 URDF 中的定义")
print("=" * 70)

URDF_PATH = (
    "/home/flowing/piper/agx_arm_ws/install/agx_arm_description/share/agx_arm_description/"
    "agx_arm_urdf/piper_l/urdf/piper_l_description.urdf"
)

try:
    import xml.etree.ElementTree as ET
    tree = ET.parse(URDF_PATH)
    root = tree.getroot()
    
    ns = {"": "http://www.ros.org/urdf"}
    joints = root.findall(".//joint[@type='revolute']")
    
    print(f"✓ URDF 中发现 {len(joints)} 个旋转关节:")
    print()
    
    for i, joint in enumerate(joints[:6], start=1):
        name = joint.get("name")
        limit = joint.find("limit")
        if limit is not None:
            lower = float(limit.get("lower"))
            upper = float(limit.get("upper"))
            print(f"Joint {i} ({name}):")
            print(f"  [{lower:.6f}, {upper:.6f}] rad")
            print(f"  [{np.degrees(lower):.2f}°, {np.degrees(upper):.2f}°]")
        else:
            print(f"Joint {i} ({name}): ⚠️  未定义限位")
        print()
        
except FileNotFoundError:
    print(f"⚠️  找不到 URDF 文件: {URDF_PATH}")
except Exception as e:
    print(f"❌ 读取 URDF 错误: {e}")

print("=" * 70)
print("排查总结")
print("=" * 70)
print("""
如果发现不匹配，可能的原因：

1. 【坐标系不同】机械臂的实际安装与配置不一致
   - 解决：匹配采集时和回放时的配置

2. 【数据采集问题】采集时没有约束关节在限位内
   - 解决：重新采集，或在加载时进行clipping

3. 【配置文件过期】使用了旧的限位配置
   - 解决：更新配置文件

4. 【坐标系变换】不同坐标系（如DH参数顺序不同）
   - 解决：检查 DH 参数或关节定义顺序
""")
