// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agx_arm_msgs:msg/HandPositionTimeCmd.idl
// generated code does not contain a copyright notice

#ifndef AGX_ARM_MSGS__MSG__DETAIL__HAND_POSITION_TIME_CMD__BUILDER_HPP_
#define AGX_ARM_MSGS__MSG__DETAIL__HAND_POSITION_TIME_CMD__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agx_arm_msgs/msg/detail/hand_position_time_cmd__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agx_arm_msgs
{

namespace msg
{

namespace builder
{

class Init_HandPositionTimeCmd_pinky_finger_time
{
public:
  explicit Init_HandPositionTimeCmd_pinky_finger_time(::agx_arm_msgs::msg::HandPositionTimeCmd & msg)
  : msg_(msg)
  {}
  ::agx_arm_msgs::msg::HandPositionTimeCmd pinky_finger_time(::agx_arm_msgs::msg::HandPositionTimeCmd::_pinky_finger_time_type arg)
  {
    msg_.pinky_finger_time = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandPositionTimeCmd msg_;
};

class Init_HandPositionTimeCmd_ring_finger_time
{
public:
  explicit Init_HandPositionTimeCmd_ring_finger_time(::agx_arm_msgs::msg::HandPositionTimeCmd & msg)
  : msg_(msg)
  {}
  Init_HandPositionTimeCmd_pinky_finger_time ring_finger_time(::agx_arm_msgs::msg::HandPositionTimeCmd::_ring_finger_time_type arg)
  {
    msg_.ring_finger_time = std::move(arg);
    return Init_HandPositionTimeCmd_pinky_finger_time(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandPositionTimeCmd msg_;
};

class Init_HandPositionTimeCmd_middle_finger_time
{
public:
  explicit Init_HandPositionTimeCmd_middle_finger_time(::agx_arm_msgs::msg::HandPositionTimeCmd & msg)
  : msg_(msg)
  {}
  Init_HandPositionTimeCmd_ring_finger_time middle_finger_time(::agx_arm_msgs::msg::HandPositionTimeCmd::_middle_finger_time_type arg)
  {
    msg_.middle_finger_time = std::move(arg);
    return Init_HandPositionTimeCmd_ring_finger_time(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandPositionTimeCmd msg_;
};

class Init_HandPositionTimeCmd_index_finger_time
{
public:
  explicit Init_HandPositionTimeCmd_index_finger_time(::agx_arm_msgs::msg::HandPositionTimeCmd & msg)
  : msg_(msg)
  {}
  Init_HandPositionTimeCmd_middle_finger_time index_finger_time(::agx_arm_msgs::msg::HandPositionTimeCmd::_index_finger_time_type arg)
  {
    msg_.index_finger_time = std::move(arg);
    return Init_HandPositionTimeCmd_middle_finger_time(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandPositionTimeCmd msg_;
};

class Init_HandPositionTimeCmd_thumb_base_time
{
public:
  explicit Init_HandPositionTimeCmd_thumb_base_time(::agx_arm_msgs::msg::HandPositionTimeCmd & msg)
  : msg_(msg)
  {}
  Init_HandPositionTimeCmd_index_finger_time thumb_base_time(::agx_arm_msgs::msg::HandPositionTimeCmd::_thumb_base_time_type arg)
  {
    msg_.thumb_base_time = std::move(arg);
    return Init_HandPositionTimeCmd_index_finger_time(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandPositionTimeCmd msg_;
};

class Init_HandPositionTimeCmd_thumb_tip_time
{
public:
  explicit Init_HandPositionTimeCmd_thumb_tip_time(::agx_arm_msgs::msg::HandPositionTimeCmd & msg)
  : msg_(msg)
  {}
  Init_HandPositionTimeCmd_thumb_base_time thumb_tip_time(::agx_arm_msgs::msg::HandPositionTimeCmd::_thumb_tip_time_type arg)
  {
    msg_.thumb_tip_time = std::move(arg);
    return Init_HandPositionTimeCmd_thumb_base_time(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandPositionTimeCmd msg_;
};

class Init_HandPositionTimeCmd_pinky_finger_pos
{
public:
  explicit Init_HandPositionTimeCmd_pinky_finger_pos(::agx_arm_msgs::msg::HandPositionTimeCmd & msg)
  : msg_(msg)
  {}
  Init_HandPositionTimeCmd_thumb_tip_time pinky_finger_pos(::agx_arm_msgs::msg::HandPositionTimeCmd::_pinky_finger_pos_type arg)
  {
    msg_.pinky_finger_pos = std::move(arg);
    return Init_HandPositionTimeCmd_thumb_tip_time(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandPositionTimeCmd msg_;
};

class Init_HandPositionTimeCmd_ring_finger_pos
{
public:
  explicit Init_HandPositionTimeCmd_ring_finger_pos(::agx_arm_msgs::msg::HandPositionTimeCmd & msg)
  : msg_(msg)
  {}
  Init_HandPositionTimeCmd_pinky_finger_pos ring_finger_pos(::agx_arm_msgs::msg::HandPositionTimeCmd::_ring_finger_pos_type arg)
  {
    msg_.ring_finger_pos = std::move(arg);
    return Init_HandPositionTimeCmd_pinky_finger_pos(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandPositionTimeCmd msg_;
};

class Init_HandPositionTimeCmd_middle_finger_pos
{
public:
  explicit Init_HandPositionTimeCmd_middle_finger_pos(::agx_arm_msgs::msg::HandPositionTimeCmd & msg)
  : msg_(msg)
  {}
  Init_HandPositionTimeCmd_ring_finger_pos middle_finger_pos(::agx_arm_msgs::msg::HandPositionTimeCmd::_middle_finger_pos_type arg)
  {
    msg_.middle_finger_pos = std::move(arg);
    return Init_HandPositionTimeCmd_ring_finger_pos(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandPositionTimeCmd msg_;
};

class Init_HandPositionTimeCmd_index_finger_pos
{
public:
  explicit Init_HandPositionTimeCmd_index_finger_pos(::agx_arm_msgs::msg::HandPositionTimeCmd & msg)
  : msg_(msg)
  {}
  Init_HandPositionTimeCmd_middle_finger_pos index_finger_pos(::agx_arm_msgs::msg::HandPositionTimeCmd::_index_finger_pos_type arg)
  {
    msg_.index_finger_pos = std::move(arg);
    return Init_HandPositionTimeCmd_middle_finger_pos(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandPositionTimeCmd msg_;
};

class Init_HandPositionTimeCmd_thumb_base_pos
{
public:
  explicit Init_HandPositionTimeCmd_thumb_base_pos(::agx_arm_msgs::msg::HandPositionTimeCmd & msg)
  : msg_(msg)
  {}
  Init_HandPositionTimeCmd_index_finger_pos thumb_base_pos(::agx_arm_msgs::msg::HandPositionTimeCmd::_thumb_base_pos_type arg)
  {
    msg_.thumb_base_pos = std::move(arg);
    return Init_HandPositionTimeCmd_index_finger_pos(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandPositionTimeCmd msg_;
};

class Init_HandPositionTimeCmd_thumb_tip_pos
{
public:
  Init_HandPositionTimeCmd_thumb_tip_pos()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_HandPositionTimeCmd_thumb_base_pos thumb_tip_pos(::agx_arm_msgs::msg::HandPositionTimeCmd::_thumb_tip_pos_type arg)
  {
    msg_.thumb_tip_pos = std::move(arg);
    return Init_HandPositionTimeCmd_thumb_base_pos(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandPositionTimeCmd msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::agx_arm_msgs::msg::HandPositionTimeCmd>()
{
  return agx_arm_msgs::msg::builder::Init_HandPositionTimeCmd_thumb_tip_pos();
}

}  // namespace agx_arm_msgs

#endif  // AGX_ARM_MSGS__MSG__DETAIL__HAND_POSITION_TIME_CMD__BUILDER_HPP_
