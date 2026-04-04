# Piper 数据流程分析报告

## 1. 观测数据（Observation）定义

### 在 `no_vision_pipeline_simplified.py` 中的定义

```python
def build_obs(arm: PiperArm) -> Dict:
    """读取一帧 observation。"""
    ts = time.time()
    raw = arm.get_observation_dict(timestamp=ts)
    return {
        "t": float(raw["t"]),           # 时间戳
        "q": [float(v) for v in raw["q"]],           # 关节角 [6D] (rad)
        "dq": [float(v) for v in raw["dq"]],         # 关节角速度 [6D] (rad/s)
        "tcp_xyz": [float(v) for v in raw["tcp_xyz"]], # 末端位置 [3D] (m)
        "tcp_pose": [float(v) for v in raw["tcp_pose"]], # 末端位姿 [6D]: (x,y,z,rx,ry,rz)
    }
```

**观测数据格式总结：**
- `t` (1D): 时间戳
- `q` (6D): 关节角位置 [rad]
- `dq` (6D): 关节角速度 [rad/s]  
- `tcp_xyz` (3D): 末端笛卡尔位置 [m]
- `tcp_pose` (6D): 末端笛卡尔位姿 [x,y,z,roll,pitch,yaw]

---

## 2. Action 数据定义

### Action 的产生过程

在采集阶段（`no_vision_pipeline_simplified.py`）：

```python
def action_from_obs(prev_obs: Dict, curr_obs: Dict) -> List[float]:
    """
    由相邻两帧 obs 差分得到 6D action，并归一化到 [-1, 1]。
    action = [Δx, Δy, Δz, Δr_x, Δr_y, Δr_z]
    其中 Δr 为 SO(3) 相对旋转的旋转向量（rotvec），不是欧拉角直接相减。
    """
    p0 = np.asarray(prev_obs["tcp_pose"], dtype=np.float32)
    p1 = np.asarray(curr_obs["tcp_pose"], dtype=np.float32)

    # 平移增量
    delta_xyz = p1[:3] - p0[:3]  # [Δx, Δy, Δz]
    
    # 旋转增量（SO(3) 旋转向量表示）
    r0 = euler_xyz_to_rotmat(float(p0[3]), float(p0[4]), float(p0[5]))
    r1 = euler_xyz_to_rotmat(float(p1[3]), float(p1[4]), float(p1[5]))
    r_delta = r0.T @ r1  # 相对旋转矩阵
    delta_rotvec = so3_log(r_delta).astype(np.float32)  # 转换为旋转向量

    raw = np.concatenate([delta_xyz.astype(np.float32), delta_rotvec], axis=0)
    # raw shape: (6,) = [Δx, Δy, Δz, Δrx, Δry, Δrz]
    
    action = normalize_action(raw)  # 归一化到 [-1, 1]
    return action.tolist()
```

### Action 归一化和反归一化

```python
# 归一化参数
ACTION_POS_SCALE = np.array([0.01, 0.01, 0.01], dtype=np.float32)  # 米
ACTION_ROT_SCALE = np.array([0.8, 0.8, 0.8], dtype=np.float32)     # 弧度

def normalize_action(action_raw: np.ndarray) -> np.ndarray:
    """
    raw 6D action -> normalized 6D action in [-1, 1]
    action_raw = [dx, dy, dz, drx, dry, drz]
    """
    action_raw = np.asarray(action_raw, dtype=np.float32).copy()
    
    # 位置缩放：1cm -> 1.0 (normalized)
    action_raw[0:3] = action_raw[0:3] / ACTION_POS_SCALE
    # 旋转缩放：0.8rad -> 1.0 (normalized)
    action_raw[3:6] = action_raw[3:6] / ACTION_ROT_SCALE
    
    return np.clip(action_raw, -1.0, 1.0)

def denormalize_action(action_norm: np.ndarray) -> np.ndarray:
    """
    normalized 6D action -> raw 6D action
    部署时使用（deploy_policy_real.py）。
    """
    action_norm = np.asarray(action_norm, dtype=np.float32).copy()
    action_norm[0:3] = action_norm[0:3] * ACTION_POS_SCALE
    action_norm[3:6] = action_norm[3:6] * ACTION_ROT_SCALE
    return action_norm
```

**Action 格式总结：**
- **原始值**: [Δx, Δy, Δz, ΔRx, ΔRy, ΔRz] (物理单位：m, rad)
- **归一化值**: [-1, 1] 范围
- **旋转表示**: SO(3) 旋转向量（rotvec）而非欧拉角差
- **产生方式**: 从相邻两帧 tcp_pose 的差分得出

---

## 3. HDF5 数据结构

### HDF5 文件格式定义

```
/data
├── /data/<episode_name>          # 单条轨迹数据
│   ├── attributes:
│   │   └── num_samples: int      # 该 episode 的帧数
│   │
│   ├── /obs                      # 观测数据组
│   │   ├── t (shape: [num_samples, 1])        # 时间戳
│   │   ├── q (shape: [num_samples, 6])        # 关节角
│   │   ├── dq (shape: [num_samples, 6])       # 关节角速度
│   │   ├── tcp_xyz (shape: [num_samples, 3])  # 末端位置
│   │   └── tcp_pose (shape: [num_samples, 6]) # 末端位姿
│   │
│   ├── actions (shape: [num_samples, 6])      # 归一化后的 action
│   ├── rewards (shape: [num_samples,])        # 奖励（采集时为 0.0）
│   └── dones (shape: [num_samples,])          # 是否为最后一帧
│
└── /data attributes:            # 全局元数据
    ├── env_args (JSON)          # 环境配置
    └── total: int               # 总帧数
```

### 采集过程中的赋值步骤

```python
def write_sample(ep_group: h5py.Group, idx: int, obs: Dict, action: List[float], is_last: bool) -> None:
    ep_group["obs/t"][idx] = np.asarray([obs["t"]], dtype=np.float64)
    ep_group["obs/q"][idx] = np.asarray(obs["q"], dtype=np.float32)
    ep_group["obs/dq"][idx] = np.asarray(obs["dq"], dtype=np.float32)
    ep_group["obs/tcp_xyz"][idx] = np.asarray(obs["tcp_xyz"], dtype=np.float32)
    ep_group["obs/tcp_pose"][idx] = np.asarray(obs["tcp_pose"], dtype=np.float32)
    
    ep_group["actions"][idx] = np.asarray(action, dtype=np.float32)  # 这里存储的是归一化后的 action
    ep_group["rewards"][idx] = np.float32(0.0)
    ep_group["dones"][idx] = np.bool_(is_last)
```

### 采集流程的 obs-action 关系

```
Frame 0: obs_prev (无对应action)
         |
         | 采集间隔 0.01s (100Hz)
         |
Frame 1: obs_curr -> action_from_obs(obs_prev, obs_curr) -> actions[0]
         obs_prev = obs_curr
         |
         | 采集间隔 0.01s
         |
Frame 2: obs_curr -> action_from_obs(obs_prev, obs_curr) -> actions[1]
         ...
```

**关键：** `actions[i]` 是从 `obs[i]` 到 `obs[i+1]` 的动作增量。

---

## 4. Robomimic 期望的 Policy 输入格式

### 在 `deploy_policy_real.py` 中的观测格式

Policy 期望接收的是以下三种形状之一的观测：

```python
def get_obs_dict(arm, use_dq: bool = True, mode: str = "flat") -> Dict[str, np.ndarray]:
    q = np.asarray(arm.get_joint_position_rad(), dtype=np.float32)
    if use_dq:
        dq = np.asarray(arm.get_joint_velocity_rad_s(), dtype=np.float32)
    else:
        dq = np.zeros(6, dtype=np.float32)
    tcp_pose = np.asarray(arm.get_tcp_pose6(), dtype=np.float32)

    if mode == "rnn":
        # BC-RNN 期望的时间序列输入
        return {
            "q": q.reshape(1, 1, 6),           # shape: [B=1, T=1, D=6]
            "dq": dq.reshape(1, 1, 6),         # shape: [B=1, T=1, D=6]
            "tcp_pose": tcp_pose.reshape(1, 1, 6),  # shape: [B=1, T=1, D=6]
        }
    if mode == "batch":
        # Batch 输入
        return {
            "q": q.reshape(1, 6),              # shape: [B=1, D=6]
            "dq": dq.reshape(1, 6),            # shape: [B=1, D=6]
            "tcp_pose": tcp_pose.reshape(1, 6),     # shape: [B=1, D=6]
        }
    if mode == "flat":
        # 平坦输入
        return {
            "q": q.reshape(6),                 # shape: [D=6]
            "dq": dq.reshape(6),               # shape: [D=6]
            "tcp_pose": tcp_pose.reshape(6),        # shape: [D=6]
        }
```

### Policy 推理调用

```python
# 尝试推理（自动适配维度）
action_norm = None
with torch.no_grad():
    mode_candidates = ["rnn", "batch", "flat"]  # 按优先级尝试
    for obs_mode in mode_candidates:
        obs = get_obs_dict(arm, use_dq=True, mode=obs_mode)
        try:
            action_norm = policy(ob=obs)  # 调用 policy
            print(f"[INFO] policy obs shape mode = {obs_mode}")
            break
        except AssertionError as exc:
            print(f"[WARN] policy 输入维度不匹配，切换模式")
            continue
```

### Policy 期望的观测键

基于代码，Policy 期望接收的观测包含：
- **`q`**: 当前关节角 [6D]
- **`dq`**: 当前关节角速度 [6D]
- **`tcp_pose`**: 当前末端位姿 [6D]

---

## 5. "action not found" 警告原因分析

### 问题根源

在 HDF5 文件中，有两种可能的情况导致 robomimic 在某些操作中警告 "action not found"：

#### **原因1：action 数据不完整或缺失**

```python
# 在 create_episode_datasets() 中
ep_group.create_dataset("actions", shape=(num_samples, 6), dtype=np.float32)

# 但在采集流程中
for idx in range(args.samples):
    time.sleep(1.0 / collect_freq)
    obs_curr = build_obs(arm)
    action = action_from_obs(obs_prev, obs_curr)
    
    # 这里存储的是: actions[idx] = obs_prev -> obs_curr 的增量
    write_sample(ep_group, idx, obs_prev, action, is_last=(idx == args.samples - 1))
    obs_prev = obs_curr
```

**特殊情况：** 第一帧 `obs[0]` 之前没有前一帧，所以 `actions[0]` 的计算方式需要明确定义。

#### **原因2：Robomimic 的 action 键匹配问题**

Robomimic 在加载 HDF5 时，会查询 dataset 名称。某些个定的模型或配置可能期望不同的键名。

常见键名：
- `action` （单数）
- `actions` （复数）
- `action_<type>` （类型标记）

#### **原因3：Robomimic 对 obs-action 序列的理解**

在训练时，Robomimic BC-RNN 使用过去的观测序列来预测下一步的 action。关键的 obs-action 对应关系：

```
时刻 t:
  观测: obs[t]
  动作: actions[t]  <- 这是从 obs[t] 执行后得到 obs[t+1] 的动作

问题：
  - actions 数组应该有 num_samples 个元素吗？
  - 还是应该有 num_samples-1 个（因为最后一帧没有后续动作）？
```

### 可能的警告来源

Robomimic 在以下场景会发出 "action not found" 警告：

1. **配置文件中指定的 action 键与 HDF5 中不匹配**
   ```json
   // 训练配置如果期望 "action" 但 HDF5 提供 "actions"
   ```

2. **数据形状不匹配**
   ```python
   # HDF5 中 actions shape: (num_samples, 6)
   # 但某些处理期望 (num_samples-1, 6) 或其他形状
   ```

3. **Episode 元数据不完整**
   ```python
   # HDF5 可能缺少关键元数据：
   # - "num_samples" attribute
   # - "env_args" attribute (包含 action_dim 等信息)
   ```

---

## 6. 完整数据流总结

```
采集阶段 (no_vision_pipeline_simplified.py):
├─ 初始化: obs_prev = build_obs()
├─ 循环 (100Hz):
│  ├─ obs_curr = build_obs()
│  ├─ action = action_from_obs(obs_prev, obs_curr)  [归一化]
│  ├─ write_sample(obs_prev, action)  -> HDF5
│  └─ obs_prev = obs_curr
└─ 保存: HDF5 file with /data/<episode>/obs/* and actions

训练阶段 (robomimic):
├─ 读取 HDF5: 加载 obs/* 和 actions
├─ 构建 dataset: 将 obs 序列和对应的 action 配对
├─ BC-RNN 训练: 
│  ├─ 输入: obs 序列 [B, T, D]
│  └─ 目标: 对应的 action [B, D]
└─ 模型保存: checkpoint (.pth)

部署阶段 (deploy_policy_real.py):
├─ 加载 policy: policy_from_checkpoint()
├─ 循环执行:
│  ├─ obs = get_obs_dict(mode="rnn")  [获取当前观测]
│  ├─ action_norm = policy(ob=obs)    [推理得到归一化 action]
│  ├─ action_raw = denormalize_action(action_norm)  [反归一化]
│  ├─ target_pose = compose_next_pose(curr_pose, action_raw)  [叠加到当前位姿]
│  ├─ joints = ik_solver.solve(target_pose)  [逆运动学求解]
│  └─ arm.move_j(joints)  [下发关节指令]
└─ 结束: 回零并失能

回放阶段 (playTrajectory_pyagxarm_ik_movej.py):
├─ 读取 HDF5: load_track_from_hdf5()
│  └─ 提取 obs/tcp_pose (TRAJECTORY_MODE="pose")
│      或 obs/q (TRAJECTORY_MODE="joint")
├─ 对每帧执行:
│  ├─ target_pose = hdf5_pose[i]
│  ├─ joints = ik_solver.solve(target_pose)
│  └─ arm.move_j(joints)
└─ 完成回放
```

---

## 7. 关键结论

| 问题 | 答案 |
|------|------|
| **obs 的定义** | `{t, q, dq, tcp_xyz, tcp_pose}` 5 个键，总共 18D |
| **action 的定义** | `[Δx, Δy, Δz, Δrx, Δry, Δrz]` 6D，使用 SO(3) 旋转向量 |
| **action 与 obs 的对应** | `actions[i]` = obs[i] → obs[i+1] 的增量 |
| **Robomimic 输入格式** | RNN: [1,1,18] / Batch: [1,18] / Flat: [18] |
| **HDF5 中的 action 键** | `actions` (复数) |
| **Action 归一化** | 位置: /0.01m, 旋转: /0.8rad -> clip to [-1,1] |
| **"action not found" 原因** | HDF5 中 actions 键名不匹配或形状错误，或元数据缺失 |

