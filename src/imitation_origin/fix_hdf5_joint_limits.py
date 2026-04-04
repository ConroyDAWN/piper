#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
修复HDF5中的越限关节角数据。

这个脚本会：
1. 读取原始 HDF5
2. 对每个关节角进行 clipping，确保在 URDF 限位内
3. 保存到新文件（backfile被备份）
"""

import h5py
import numpy as np
from pathlib import Path

# URDF 中定义的关节限位（来自诊断脚本的输出）
URDF_LIMITS = {
    1: (-2.617994, 2.617994),   # [-150°, 150°]
    2: (0.000000, 3.141593),     # [0°, 180°]  ← Joint2 最小值不能为负
    3: (-2.967060, 0.000000),    # [-170°, 0°]
    4: (-1.745329, 1.745329),    # [-100°, 100°]
    5: (-1.221730, 1.221730),    # [-70°, 70°]
    6: (-2.094395, 2.094395),    # [-120°, 120°]
}

def fix_joint_limits(hdf5_path, output_path=None):
    """修复HDF5中的越限关节角。"""
    
    hdf5_path = Path(hdf5_path).expanduser().resolve()
    if not hdf5_path.exists():
        raise FileNotFoundError(f"文件不存在: {hdf5_path}")
    
    if output_path is None:
        output_path = hdf5_path.parent / f"{hdf5_path.stem}_fixed.hdf5"
    else:
        output_path = Path(output_path).expanduser().resolve()
    
    print(f"[INFO] 输入文件: {hdf5_path}")
    print(f"[INFO] 输出文件: {output_path}")
    
    with h5py.File(hdf5_path, "r") as f_in:
        with h5py.File(output_path, "w") as f_out:
            
            # 复制所有内容，但修复关节角数据
            def copy_with_fix(name, obj):
                """递归复制，对关节角数据进行修复。"""
                
                if name.endswith("/obs/q"):
                    # 这是关节角数据，需要修复
                    q_data = obj[...]  # 读取数据，shape: (N, 6)
                    q_fixed = np.array(q_data, copy=True)
                    
                    clipped_count = 0
                    joint_stats = {}
                    
                    for joint_idx in range(6):
                        joint_num = joint_idx + 1
                        lo, hi = URDF_LIMITS[joint_num]
                        
                        original = q_fixed[:, joint_idx]
                        
                        # Clip 到限位范围
                        q_fixed[:, joint_idx] = np.clip(original, lo, hi)
                        
                        # 统计被修改的样本数
                        modified = np.sum((original < lo) | (original > hi))
                        if modified > 0:
                            clipped_count += modified
                            joint_stats[joint_num] = {
                                "original_min": original.min(),
                                "original_max": original.max(),
                                "clipped_samples": modified,
                                "limit": (lo, hi)
                            }
                    
                    # 创建数据集
                    f_out.create_dataset(name, data=q_fixed, compression="gzip")
                    
                    if clipped_count > 0:
                        print(f"\n[INFO] 关节角数据已修复: {name}")
                        for j_num, stats in sorted(joint_stats.items()):
                            print(f"  Joint {j_num}:")
                            print(f"    修改样本数: {int(stats['clipped_samples'])}")
                            print(f"    原始范围: [{stats['original_min']:.6f}, {stats['original_max']:.6f}]")
                            print(f"    限位范围: [{stats['limit'][0]:.6f}, {stats['limit'][1]:.6f}]")
                    else:
                        print(f"[OK] {name} 无需修复")
                
                elif isinstance(obj, h5py.Dataset):
                    # 其他数据集直接复制
                    f_out.create_dataset(name, data=obj, compression="gzip")
                
                elif isinstance(obj, h5py.Group):
                    # 组直接创建，递归处理内容
                    f_out.create_group(name)
            
            # 开始递归复制
            f_in.visititems(copy_with_fix)
    
    print(f"\n[SUCCESS] 修复完成！")
    print(f"[INFO] 原文件已保存为备份: {hdf5_path}.backup")
    
    # 备份原文件
    import shutil
    backup_path = str(hdf5_path) + ".backup"
    shutil.copy2(hdf5_path, backup_path)
    
    # 用修复后的文件替换原文件
    shutil.move(output_path, hdf5_path)
    print(f"[INFO] {hdf5_path} 已更新")
    
    return hdf5_path

if __name__ == "__main__":
    import sys
    
    if len(sys.argv) > 1:
        hdf5_file = sys.argv[1]
    else:
        # 默认修复 demo_010.hdf5
        hdf5_file = "/home/flowing/piper/data/single_demo2/demo_001.hdf5"
    
    try:
        fix_joint_limits(hdf5_file)
    except Exception as e:
        print(f"[ERROR] {e}")
        sys.exit(1)
