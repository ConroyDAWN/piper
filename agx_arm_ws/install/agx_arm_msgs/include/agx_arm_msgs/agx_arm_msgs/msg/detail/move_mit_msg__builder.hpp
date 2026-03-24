// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agx_arm_msgs:msg/MoveMITMsg.idl
// generated code does not contain a copyright notice

#ifndef AGX_ARM_MSGS__MSG__DETAIL__MOVE_MIT_MSG__BUILDER_HPP_
#define AGX_ARM_MSGS__MSG__DETAIL__MOVE_MIT_MSG__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agx_arm_msgs/msg/detail/move_mit_msg__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agx_arm_msgs
{

namespace msg
{

namespace builder
{

class Init_MoveMITMsg_torque
{
public:
  explicit Init_MoveMITMsg_torque(::agx_arm_msgs::msg::MoveMITMsg & msg)
  : msg_(msg)
  {}
  ::agx_arm_msgs::msg::MoveMITMsg torque(::agx_arm_msgs::msg::MoveMITMsg::_torque_type arg)
  {
    msg_.torque = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agx_arm_msgs::msg::MoveMITMsg msg_;
};

class Init_MoveMITMsg_kd
{
public:
  explicit Init_MoveMITMsg_kd(::agx_arm_msgs::msg::MoveMITMsg & msg)
  : msg_(msg)
  {}
  Init_MoveMITMsg_torque kd(::agx_arm_msgs::msg::MoveMITMsg::_kd_type arg)
  {
    msg_.kd = std::move(arg);
    return Init_MoveMITMsg_torque(msg_);
  }

private:
  ::agx_arm_msgs::msg::MoveMITMsg msg_;
};

class Init_MoveMITMsg_kp
{
public:
  explicit Init_MoveMITMsg_kp(::agx_arm_msgs::msg::MoveMITMsg & msg)
  : msg_(msg)
  {}
  Init_MoveMITMsg_kd kp(::agx_arm_msgs::msg::MoveMITMsg::_kp_type arg)
  {
    msg_.kp = std::move(arg);
    return Init_MoveMITMsg_kd(msg_);
  }

private:
  ::agx_arm_msgs::msg::MoveMITMsg msg_;
};

class Init_MoveMITMsg_v_des
{
public:
  explicit Init_MoveMITMsg_v_des(::agx_arm_msgs::msg::MoveMITMsg & msg)
  : msg_(msg)
  {}
  Init_MoveMITMsg_kp v_des(::agx_arm_msgs::msg::MoveMITMsg::_v_des_type arg)
  {
    msg_.v_des = std::move(arg);
    return Init_MoveMITMsg_kp(msg_);
  }

private:
  ::agx_arm_msgs::msg::MoveMITMsg msg_;
};

class Init_MoveMITMsg_p_des
{
public:
  explicit Init_MoveMITMsg_p_des(::agx_arm_msgs::msg::MoveMITMsg & msg)
  : msg_(msg)
  {}
  Init_MoveMITMsg_v_des p_des(::agx_arm_msgs::msg::MoveMITMsg::_p_des_type arg)
  {
    msg_.p_des = std::move(arg);
    return Init_MoveMITMsg_v_des(msg_);
  }

private:
  ::agx_arm_msgs::msg::MoveMITMsg msg_;
};

class Init_MoveMITMsg_joint_index
{
public:
  Init_MoveMITMsg_joint_index()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveMITMsg_p_des joint_index(::agx_arm_msgs::msg::MoveMITMsg::_joint_index_type arg)
  {
    msg_.joint_index = std::move(arg);
    return Init_MoveMITMsg_p_des(msg_);
  }

private:
  ::agx_arm_msgs::msg::MoveMITMsg msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::agx_arm_msgs::msg::MoveMITMsg>()
{
  return agx_arm_msgs::msg::builder::Init_MoveMITMsg_joint_index();
}

}  // namespace agx_arm_msgs

#endif  // AGX_ARM_MSGS__MSG__DETAIL__MOVE_MIT_MSG__BUILDER_HPP_
