// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agx_arm_msgs:msg/AgxArmStatus.idl
// generated code does not contain a copyright notice

#ifndef AGX_ARM_MSGS__MSG__DETAIL__AGX_ARM_STATUS__BUILDER_HPP_
#define AGX_ARM_MSGS__MSG__DETAIL__AGX_ARM_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agx_arm_msgs/msg/detail/agx_arm_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agx_arm_msgs
{

namespace msg
{

namespace builder
{

class Init_AgxArmStatus_communication_status_joint
{
public:
  explicit Init_AgxArmStatus_communication_status_joint(::agx_arm_msgs::msg::AgxArmStatus & msg)
  : msg_(msg)
  {}
  ::agx_arm_msgs::msg::AgxArmStatus communication_status_joint(::agx_arm_msgs::msg::AgxArmStatus::_communication_status_joint_type arg)
  {
    msg_.communication_status_joint = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agx_arm_msgs::msg::AgxArmStatus msg_;
};

class Init_AgxArmStatus_joint_angle_limit
{
public:
  explicit Init_AgxArmStatus_joint_angle_limit(::agx_arm_msgs::msg::AgxArmStatus & msg)
  : msg_(msg)
  {}
  Init_AgxArmStatus_communication_status_joint joint_angle_limit(::agx_arm_msgs::msg::AgxArmStatus::_joint_angle_limit_type arg)
  {
    msg_.joint_angle_limit = std::move(arg);
    return Init_AgxArmStatus_communication_status_joint(msg_);
  }

private:
  ::agx_arm_msgs::msg::AgxArmStatus msg_;
};

class Init_AgxArmStatus_err_status
{
public:
  explicit Init_AgxArmStatus_err_status(::agx_arm_msgs::msg::AgxArmStatus & msg)
  : msg_(msg)
  {}
  Init_AgxArmStatus_joint_angle_limit err_status(::agx_arm_msgs::msg::AgxArmStatus::_err_status_type arg)
  {
    msg_.err_status = std::move(arg);
    return Init_AgxArmStatus_joint_angle_limit(msg_);
  }

private:
  ::agx_arm_msgs::msg::AgxArmStatus msg_;
};

class Init_AgxArmStatus_trajectory_num
{
public:
  explicit Init_AgxArmStatus_trajectory_num(::agx_arm_msgs::msg::AgxArmStatus & msg)
  : msg_(msg)
  {}
  Init_AgxArmStatus_err_status trajectory_num(::agx_arm_msgs::msg::AgxArmStatus::_trajectory_num_type arg)
  {
    msg_.trajectory_num = std::move(arg);
    return Init_AgxArmStatus_err_status(msg_);
  }

private:
  ::agx_arm_msgs::msg::AgxArmStatus msg_;
};

class Init_AgxArmStatus_motion_status
{
public:
  explicit Init_AgxArmStatus_motion_status(::agx_arm_msgs::msg::AgxArmStatus & msg)
  : msg_(msg)
  {}
  Init_AgxArmStatus_trajectory_num motion_status(::agx_arm_msgs::msg::AgxArmStatus::_motion_status_type arg)
  {
    msg_.motion_status = std::move(arg);
    return Init_AgxArmStatus_trajectory_num(msg_);
  }

private:
  ::agx_arm_msgs::msg::AgxArmStatus msg_;
};

class Init_AgxArmStatus_teach_status
{
public:
  explicit Init_AgxArmStatus_teach_status(::agx_arm_msgs::msg::AgxArmStatus & msg)
  : msg_(msg)
  {}
  Init_AgxArmStatus_motion_status teach_status(::agx_arm_msgs::msg::AgxArmStatus::_teach_status_type arg)
  {
    msg_.teach_status = std::move(arg);
    return Init_AgxArmStatus_motion_status(msg_);
  }

private:
  ::agx_arm_msgs::msg::AgxArmStatus msg_;
};

class Init_AgxArmStatus_mode_feedback
{
public:
  explicit Init_AgxArmStatus_mode_feedback(::agx_arm_msgs::msg::AgxArmStatus & msg)
  : msg_(msg)
  {}
  Init_AgxArmStatus_teach_status mode_feedback(::agx_arm_msgs::msg::AgxArmStatus::_mode_feedback_type arg)
  {
    msg_.mode_feedback = std::move(arg);
    return Init_AgxArmStatus_teach_status(msg_);
  }

private:
  ::agx_arm_msgs::msg::AgxArmStatus msg_;
};

class Init_AgxArmStatus_arm_status
{
public:
  explicit Init_AgxArmStatus_arm_status(::agx_arm_msgs::msg::AgxArmStatus & msg)
  : msg_(msg)
  {}
  Init_AgxArmStatus_mode_feedback arm_status(::agx_arm_msgs::msg::AgxArmStatus::_arm_status_type arg)
  {
    msg_.arm_status = std::move(arg);
    return Init_AgxArmStatus_mode_feedback(msg_);
  }

private:
  ::agx_arm_msgs::msg::AgxArmStatus msg_;
};

class Init_AgxArmStatus_ctrl_mode
{
public:
  Init_AgxArmStatus_ctrl_mode()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AgxArmStatus_arm_status ctrl_mode(::agx_arm_msgs::msg::AgxArmStatus::_ctrl_mode_type arg)
  {
    msg_.ctrl_mode = std::move(arg);
    return Init_AgxArmStatus_arm_status(msg_);
  }

private:
  ::agx_arm_msgs::msg::AgxArmStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::agx_arm_msgs::msg::AgxArmStatus>()
{
  return agx_arm_msgs::msg::builder::Init_AgxArmStatus_ctrl_mode();
}

}  // namespace agx_arm_msgs

#endif  // AGX_ARM_MSGS__MSG__DETAIL__AGX_ARM_STATUS__BUILDER_HPP_
