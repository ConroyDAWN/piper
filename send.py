import math
from dataclasses import MISSING

import torch

from isaaclab.assets import Articulation, RigidObject
from isaaclab.envs import ManagerBasedEnv, ManagerBasedRLEnv
from isaaclab.managers import CurriculumTermCfg as CurrTerm
from isaaclab.managers import ObservationGroupCfg as ObsGroup
from isaaclab.managers import ObservationTermCfg as ObsTerm
from isaaclab.managers import RewardTermCfg as RewTerm
from isaaclab.managers import SceneEntityCfg
from isaaclab.sensors import ContactSensor
from isaaclab.utils import configclass
from isaaclab.utils.noise import AdditiveUniformNoiseCfg as Unoise

import isaaclab_tasks.manager_based.locomotion.velocity.mdp as mdp
from isaaclab_assets.robots.quadruped_v8 import QUADRUPED_V8_CFG
from isaaclab_tasks.manager_based.locomotion.velocity.velocity_env_cfg import LocomotionVelocityRoughEnvCfg


FEET_BODIES = ["L_arm_ankle_y", "R_arm_ankle_y", "L_ankle_y", "R_ankle_y"]

UNDESIRED_CONTACT_BODIES = [
    "base_link",
    "L_s_.*",
    "R_s_.*",
    "L_arm_p",
    "R_arm_p",
    "L_arm_ankle_p",
    "R_arm_ankle_p",
    "L_h_.*",
    "R_h_.*",
    "L_k_p",
    "R_k_p",
    "L_ankle_p",
    "R_ankle_p",
]

JOINT_NAMES = [
    "L_s_p",
    "L_s_y",
    "L_s_r",
    "L_arm_p",
    "L_arm_ankle_p",
    "L_arm_ankle_y",
    "R_s_p",
    "R_s_y",
    "R_s_r",
    "R_arm_p",
    "R_arm_ankle_p",
    "R_arm_ankle_y",
    "L_h_p",
    "L_h_y",
    "L_h_r",
    "L_k_p",
    "L_ankle_p",
    "L_ankle_y",
    "R_h_p",
    "R_h_y",
    "R_h_r",
    "R_k_p",
    "R_ankle_p",
    "R_ankle_y",
]


@configclass
class UniformLevelVelocityCommandCfg(mdp.UniformVelocityCommandCfg):
    """Compatibility wrapper for velocity curriculum."""
    limit_ranges: mdp.UniformVelocityCommandCfg.Ranges = MISSING


def quadruped_v8_base_lin_vel(
    env: ManagerBasedEnv, asset_cfg: SceneEntityCfg = SceneEntityCfg("robot")
) -> torch.Tensor:
    """Return base linear velocity as [forward, lateral, vertical].

    Quadruped V8 true forward aligns with local +Y.
    """
    asset: RigidObject = env.scene[asset_cfg.name]
    vel = asset.data.root_lin_vel_b
    return torch.stack([vel[:, 1], vel[:, 0], vel[:, 2]], dim=-1)


def quadruped_v8_track_lin_vel_xy_exp(
    env: ManagerBasedRLEnv,
    std: float,
    command_name: str,
    asset_cfg: SceneEntityCfg = SceneEntityCfg("robot"),
) -> torch.Tensor:
    """Track commanded [forward, lateral] speed using Quadruped V8's real forward axis."""
    asset: RigidObject = env.scene[asset_cfg.name]
    cmd = env.command_manager.get_command(command_name)
    vel = asset.data.root_lin_vel_b
    actual_forward = vel[:, 1]
    actual_lateral = vel[:, 0]
    error = torch.square(cmd[:, 0] - actual_forward) + torch.square(cmd[:, 1] - actual_lateral)
    return torch.exp(-error / std**2)


def quadruped_v8_joint_position_penalty(
    env: ManagerBasedRLEnv,
    asset_cfg: SceneEntityCfg,
    stand_still_scale: float,
    velocity_threshold: float,
) -> torch.Tensor:
    """Posture penalty stronger at stand-still."""
    asset: Articulation = env.scene[asset_cfg.name]
    cmd = torch.linalg.norm(env.command_manager.get_command("base_velocity")[:, :2], dim=1)
    body_vel = torch.linalg.norm(asset.data.root_lin_vel_b[:, :2], dim=1)
    deviation = torch.linalg.norm((asset.data.joint_pos - asset.data.default_joint_pos), dim=1)
    return torch.where(
        torch.logical_or(cmd > 0.0, body_vel > velocity_threshold),
        deviation,
        stand_still_scale * deviation,
    )


def quadruped_v8_energy(
    env: ManagerBasedRLEnv, asset_cfg: SceneEntityCfg = SceneEntityCfg("robot")
) -> torch.Tensor:
    """Mechanical power penalty."""
    asset: Articulation = env.scene[asset_cfg.name]
    qvel = asset.data.joint_vel[:, asset_cfg.joint_ids]
    qfrc = asset.data.applied_torque[:, asset_cfg.joint_ids]
    return torch.sum(torch.abs(qvel) * torch.abs(qfrc), dim=-1)


def quadruped_v8_air_time_variance_penalty(
    env: ManagerBasedRLEnv, sensor_cfg: SceneEntityCfg
) -> torch.Tensor:
    """Penalty on gait asymmetry across four feet."""
    contact_sensor: ContactSensor = env.scene.sensors[sensor_cfg.name]
    if contact_sensor.cfg.track_air_time is False:
        raise RuntimeError("Activate ContactSensor's track_air_time!")

    last_air_time = contact_sensor.data.last_air_time[:, sensor_cfg.body_ids]
    last_contact_time = contact_sensor.data.last_contact_time[:, sensor_cfg.body_ids]
    return torch.var(torch.clip(last_air_time, max=0.5), dim=1) + torch.var(
        torch.clip(last_contact_time, max=0.5), dim=1
    )


def lin_vel_cmd_levels(
    env: ManagerBasedRLEnv,
    env_ids,
    reward_term_name: str = "track_lin_vel_xy",
) -> torch.Tensor:
    """Optional curriculum for command range expansion."""
    command_term = env.command_manager.get_term("base_velocity")
    ranges = command_term.cfg.ranges
    limit_ranges = command_term.cfg.limit_ranges

    reward_term = env.reward_manager.get_term_cfg(reward_term_name)
    reward = torch.mean(env.reward_manager._episode_sums[reward_term_name][env_ids]) / env.max_episode_length_s

    if env.common_step_counter % env.max_episode_length == 0:
        if reward > reward_term.weight * 0.8:
            delta_command = torch.tensor([-0.05, 0.05], device=env.device)
            ranges.lin_vel_x = torch.clamp(
                torch.tensor(ranges.lin_vel_x, device=env.device) + delta_command,
                limit_ranges.lin_vel_x[0],
                limit_ranges.lin_vel_x[1],
            ).tolist()
            ranges.lin_vel_y = torch.clamp(
                torch.tensor(ranges.lin_vel_y, device=env.device) + delta_command,
                limit_ranges.lin_vel_y[0],
                limit_ranges.lin_vel_y[1],
            ).tolist()

    return torch.tensor(ranges.lin_vel_x[1], device=env.device)


@configclass
class QuadrupedV8CommandsCfg:
    base_velocity = UniformLevelVelocityCommandCfg(
        asset_name="robot",
        resampling_time_range=(10.0, 10.0),
        rel_standing_envs=0.0,
        rel_heading_envs=0.0,
        heading_command=False,
        debug_vis=False,
        ranges=UniformLevelVelocityCommandCfg.Ranges(
            lin_vel_x=(0.0, 0.0),
            lin_vel_y=(0.3, 0.6),
            ang_vel_z=(0.0, 0.0),
            heading=None,
        ),
        limit_ranges=UniformLevelVelocityCommandCfg.Ranges(
            lin_vel_x=(0.0, 0.0),
            lin_vel_y=(0.3, 0.6),
            ang_vel_z=(0.0, 0.0),
            heading=None,
        ),
    )


@configclass
class QuadrupedV8ObservationsCfg:
    @configclass
    class PolicyCfg(ObsGroup):
        # 不加入 base_lin_vel，按你的要求保持当前思路
        base_ang_vel = ObsTerm(
            func=mdp.base_ang_vel,
            scale=0.2,
            clip=(-100, 100),
            noise=Unoise(n_min=-0.2, n_max=0.2),
        )
        projected_gravity = ObsTerm(
            func=mdp.projected_gravity,
            clip=(-100, 100),
            noise=Unoise(n_min=-0.05, n_max=0.05),
        )
        velocity_commands = ObsTerm(
            func=mdp.generated_commands,
            clip=(-100, 100),
            params={"command_name": "base_velocity"},
        )
        joint_pos = ObsTerm(
            func=mdp.joint_pos_rel,
            clip=(-100, 100),
            noise=Unoise(n_min=-0.01, n_max=0.01),
        )
        joint_vel = ObsTerm(
            func=mdp.joint_vel_rel,
            scale=0.05,
            clip=(-100, 100),
            noise=Unoise(n_min=-1.0, n_max=1.0),
        )
        actions = ObsTerm(func=mdp.last_action, clip=(-100, 100))

        def __post_init__(self):
            self.enable_corruption = True
            self.concatenate_terms = True

    @configclass
    class CriticCfg(ObsGroup):
        base_lin_vel = ObsTerm(func=quadruped_v8_base_lin_vel, clip=(-100, 100))
        base_ang_vel = ObsTerm(func=mdp.base_ang_vel, scale=0.2, clip=(-100, 100))
        projected_gravity = ObsTerm(func=mdp.projected_gravity, clip=(-100, 100))
        velocity_commands = ObsTerm(
            func=mdp.generated_commands,
            clip=(-100, 100),
            params={"command_name": "base_velocity"},
        )
        joint_pos = ObsTerm(func=mdp.joint_pos_rel, clip=(-100, 100))
        joint_vel = ObsTerm(func=mdp.joint_vel_rel, scale=0.05, clip=(-100, 100))
        joint_effort = ObsTerm(func=mdp.joint_effort, scale=0.01, clip=(-100, 100))
        actions = ObsTerm(func=mdp.last_action, clip=(-100, 100))

        def __post_init__(self):
            self.enable_corruption = False
            self.concatenate_terms = True

    policy: PolicyCfg = PolicyCfg()
    critic: CriticCfg = CriticCfg()


@configclass
class QuadrupedV8RewardsCfg:
    # 主任务：略降，避免速度项压过对称性
    track_lin_vel_xy = RewTerm(
        func=quadruped_v8_track_lin_vel_xy_exp,
        weight=2.2,
        params={"command_name": "base_velocity", "std": math.sqrt(0.25)},
    )
    track_ang_vel_z = RewTerm(
        func=mdp.track_ang_vel_z_exp,
        weight=0.0,
        params={"command_name": "base_velocity", "std": math.sqrt(0.25)},
    )

    # 机身稳定
    base_linear_velocity = RewTerm(func=mdp.lin_vel_z_l2, weight=-0.25)
    base_angular_velocity = RewTerm(func=mdp.ang_vel_xy_l2, weight=-0.08)
    flat_orientation_l2 = RewTerm(func=mdp.flat_orientation_l2, weight=-0.45)

    # 平顺 / 动力学
    joint_vel = RewTerm(func=mdp.joint_vel_l2, weight=-0.0015)
    joint_acc = RewTerm(func=mdp.joint_acc_l2, weight=-3.0e-7)
    joint_torques = RewTerm(func=mdp.joint_torques_l2, weight=-3.0e-4)
    action_rate = RewTerm(func=mdp.action_rate_l2, weight=-0.015)
    dof_pos_limits = RewTerm(func=mdp.joint_pos_limits, weight=-0.5)
    energy = RewTerm(func=quadruped_v8_energy, weight=-1.0e-5)

    joint_pos = RewTerm(
        func=quadruped_v8_joint_position_penalty,
        weight=-0.10,
        params={
            "asset_cfg": SceneEntityCfg("robot", joint_names=".*"),
            "stand_still_scale": 5.0,
            "velocity_threshold": 0.3,
        },
    )

    # 足端：抑制单腿长期抬起
    feet_air_time = RewTerm(
        func=mdp.feet_air_time,
        weight=0.05,
        params={
            "sensor_cfg": SceneEntityCfg("contact_forces", body_names=FEET_BODIES),
            "command_name": "base_velocity",
            "threshold": 0.4,
        },
    )

    air_time_variance = RewTerm(
        func=quadruped_v8_air_time_variance_penalty,
        weight=-0.8,
        params={"sensor_cfg": SceneEntityCfg("contact_forces", body_names=FEET_BODIES)},
    )

    feet_slide = RewTerm(
        func=mdp.feet_slide,
        weight=-0.25,
        params={
            "asset_cfg": SceneEntityCfg("robot", body_names=FEET_BODIES),
            "sensor_cfg": SceneEntityCfg("contact_forces", body_names=FEET_BODIES),
        },
    )

    feet_contact_force = RewTerm(
        func=mdp.feet_contact_force,
        weight=0.20,
        params={
            "sensor_cfg": SceneEntityCfg("contact_forces", body_names=FEET_BODIES),
            "min_force": 5.0,
            "max_force": 200.0,
        },
    )

    undesired_contacts = RewTerm(
        func=mdp.undesired_contacts,
        weight=-0.30,
        params={
            "threshold": 1.0,
            "sensor_cfg": SceneEntityCfg("contact_forces", body_names=UNDESIRED_CONTACT_BODIES),
        },
    )


@configclass
class QuadrupedV8CurriculumCfg:
    # 当前先不启用速度 curriculum，避免把偏腿 gait 推得更严重
    pass


@configclass
class QuadrupedV8FlatEnvCfg2(LocomotionVelocityRoughEnvCfg):
    observations: QuadrupedV8ObservationsCfg = QuadrupedV8ObservationsCfg()
    commands: QuadrupedV8CommandsCfg = QuadrupedV8CommandsCfg()
    rewards: QuadrupedV8RewardsCfg = QuadrupedV8RewardsCfg()
    curriculum: QuadrupedV8CurriculumCfg = QuadrupedV8CurriculumCfg()

    def __post_init__(self):
        super().__post_init__()

        self.scene.robot = QUADRUPED_V8_CFG.replace(prim_path="{ENV_REGEX_NS}/Robot")

        self.actions.joint_pos.joint_names = JOINT_NAMES
        self.actions.joint_pos.scale = 0.22

        # plane
        self.scene.terrain.terrain_type = "plane"
        self.scene.terrain.terrain_generator = None
        self.scene.height_scanner = None

        # commands
        self.commands.base_velocity.rel_standing_envs = 0.0
        self.commands.base_velocity.ranges.lin_vel_x = (0.0, 0.0)
        self.commands.base_velocity.ranges.lin_vel_y = (0.3, 0.6)
        self.commands.base_velocity.ranges.ang_vel_z = (0.0, 0.0)
        self.commands.base_velocity.heading_command = False
        self.commands.base_velocity.rel_heading_envs = 0.0

        # events：降低不对称 gait 固化风险
        self.events.physics_material.params["static_friction_range"] = (0.6, 1.0)
        self.events.physics_material.params["dynamic_friction_range"] = (0.6, 1.0)
        self.events.physics_material.params["restitution_range"] = (0.0, 0.03)

        # 先关掉 base 质量随机化
        self.events.add_base_mass = None

        self.events.base_external_force_torque = None

        # 恢复 joints reset，避免每回合起始姿态偏掉
        self.events.reset_robot_joints.func = mdp.reset_joints_by_scale
        self.events.reset_robot_joints.params["position_range"] = (0.95, 1.05)
        self.events.reset_robot_joints.params["velocity_range"] = (0.0, 0.0)

        # 收窄 reset 姿态范围
        self.events.reset_base.params = {
            "pose_range": {"x": (0.0, 0.0), "y": (0.0, 0.0), "yaw": (-0.3, 0.3)},
            "velocity_range": {
                "x": (0.0, 0.0),
                "y": (0.0, 0.0),
                "z": (0.0, 0.0),
                "roll": (0.0, 0.0),
                "pitch": (0.0, 0.0),
                "yaw": (0.0, 0.0),
            },
        }

        self.events.push_robot = None

        # termination
        self.terminations.base_contact.params["sensor_cfg"].body_names = "base_link"


@configclass
class QuadrupedV8FlatEnvCfg_PLAY2(QuadrupedV8FlatEnvCfg2):
    def __post_init__(self):
        super().__post_init__()

        self.scene.num_envs = 50
        self.scene.env_spacing = 2.5
        self.observations.policy.enable_corruption = False
        self.events.base_external_force_torque = None
        self.events.push_robot = None