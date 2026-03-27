// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agx_arm_msgs:msg/HandCmd.idl
// generated code does not contain a copyright notice

#ifndef AGX_ARM_MSGS__MSG__DETAIL__HAND_CMD__BUILDER_HPP_
#define AGX_ARM_MSGS__MSG__DETAIL__HAND_CMD__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agx_arm_msgs/msg/detail/hand_cmd__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agx_arm_msgs
{

namespace msg
{

namespace builder
{

class Init_HandCmd_pinky_finger
{
public:
  explicit Init_HandCmd_pinky_finger(::agx_arm_msgs::msg::HandCmd & msg)
  : msg_(msg)
  {}
  ::agx_arm_msgs::msg::HandCmd pinky_finger(::agx_arm_msgs::msg::HandCmd::_pinky_finger_type arg)
  {
    msg_.pinky_finger = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandCmd msg_;
};

class Init_HandCmd_ring_finger
{
public:
  explicit Init_HandCmd_ring_finger(::agx_arm_msgs::msg::HandCmd & msg)
  : msg_(msg)
  {}
  Init_HandCmd_pinky_finger ring_finger(::agx_arm_msgs::msg::HandCmd::_ring_finger_type arg)
  {
    msg_.ring_finger = std::move(arg);
    return Init_HandCmd_pinky_finger(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandCmd msg_;
};

class Init_HandCmd_middle_finger
{
public:
  explicit Init_HandCmd_middle_finger(::agx_arm_msgs::msg::HandCmd & msg)
  : msg_(msg)
  {}
  Init_HandCmd_ring_finger middle_finger(::agx_arm_msgs::msg::HandCmd::_middle_finger_type arg)
  {
    msg_.middle_finger = std::move(arg);
    return Init_HandCmd_ring_finger(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandCmd msg_;
};

class Init_HandCmd_index_finger
{
public:
  explicit Init_HandCmd_index_finger(::agx_arm_msgs::msg::HandCmd & msg)
  : msg_(msg)
  {}
  Init_HandCmd_middle_finger index_finger(::agx_arm_msgs::msg::HandCmd::_index_finger_type arg)
  {
    msg_.index_finger = std::move(arg);
    return Init_HandCmd_middle_finger(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandCmd msg_;
};

class Init_HandCmd_thumb_base
{
public:
  explicit Init_HandCmd_thumb_base(::agx_arm_msgs::msg::HandCmd & msg)
  : msg_(msg)
  {}
  Init_HandCmd_index_finger thumb_base(::agx_arm_msgs::msg::HandCmd::_thumb_base_type arg)
  {
    msg_.thumb_base = std::move(arg);
    return Init_HandCmd_index_finger(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandCmd msg_;
};

class Init_HandCmd_thumb_tip
{
public:
  explicit Init_HandCmd_thumb_tip(::agx_arm_msgs::msg::HandCmd & msg)
  : msg_(msg)
  {}
  Init_HandCmd_thumb_base thumb_tip(::agx_arm_msgs::msg::HandCmd::_thumb_tip_type arg)
  {
    msg_.thumb_tip = std::move(arg);
    return Init_HandCmd_thumb_base(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandCmd msg_;
};

class Init_HandCmd_mode
{
public:
  Init_HandCmd_mode()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_HandCmd_thumb_tip mode(::agx_arm_msgs::msg::HandCmd::_mode_type arg)
  {
    msg_.mode = std::move(arg);
    return Init_HandCmd_thumb_tip(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandCmd msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::agx_arm_msgs::msg::HandCmd>()
{
  return agx_arm_msgs::msg::builder::Init_HandCmd_mode();
}

}  // namespace agx_arm_msgs

#endif  // AGX_ARM_MSGS__MSG__DETAIL__HAND_CMD__BUILDER_HPP_
