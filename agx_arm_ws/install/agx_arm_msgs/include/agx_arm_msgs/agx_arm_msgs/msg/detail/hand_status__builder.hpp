// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agx_arm_msgs:msg/HandStatus.idl
// generated code does not contain a copyright notice

#ifndef AGX_ARM_MSGS__MSG__DETAIL__HAND_STATUS__BUILDER_HPP_
#define AGX_ARM_MSGS__MSG__DETAIL__HAND_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agx_arm_msgs/msg/detail/hand_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agx_arm_msgs
{

namespace msg
{

namespace builder
{

class Init_HandStatus_pinky_finger_status
{
public:
  explicit Init_HandStatus_pinky_finger_status(::agx_arm_msgs::msg::HandStatus & msg)
  : msg_(msg)
  {}
  ::agx_arm_msgs::msg::HandStatus pinky_finger_status(::agx_arm_msgs::msg::HandStatus::_pinky_finger_status_type arg)
  {
    msg_.pinky_finger_status = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandStatus msg_;
};

class Init_HandStatus_ring_finger_status
{
public:
  explicit Init_HandStatus_ring_finger_status(::agx_arm_msgs::msg::HandStatus & msg)
  : msg_(msg)
  {}
  Init_HandStatus_pinky_finger_status ring_finger_status(::agx_arm_msgs::msg::HandStatus::_ring_finger_status_type arg)
  {
    msg_.ring_finger_status = std::move(arg);
    return Init_HandStatus_pinky_finger_status(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandStatus msg_;
};

class Init_HandStatus_middle_finger_status
{
public:
  explicit Init_HandStatus_middle_finger_status(::agx_arm_msgs::msg::HandStatus & msg)
  : msg_(msg)
  {}
  Init_HandStatus_ring_finger_status middle_finger_status(::agx_arm_msgs::msg::HandStatus::_middle_finger_status_type arg)
  {
    msg_.middle_finger_status = std::move(arg);
    return Init_HandStatus_ring_finger_status(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandStatus msg_;
};

class Init_HandStatus_index_finger_status
{
public:
  explicit Init_HandStatus_index_finger_status(::agx_arm_msgs::msg::HandStatus & msg)
  : msg_(msg)
  {}
  Init_HandStatus_middle_finger_status index_finger_status(::agx_arm_msgs::msg::HandStatus::_index_finger_status_type arg)
  {
    msg_.index_finger_status = std::move(arg);
    return Init_HandStatus_middle_finger_status(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandStatus msg_;
};

class Init_HandStatus_thumb_base_status
{
public:
  explicit Init_HandStatus_thumb_base_status(::agx_arm_msgs::msg::HandStatus & msg)
  : msg_(msg)
  {}
  Init_HandStatus_index_finger_status thumb_base_status(::agx_arm_msgs::msg::HandStatus::_thumb_base_status_type arg)
  {
    msg_.thumb_base_status = std::move(arg);
    return Init_HandStatus_index_finger_status(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandStatus msg_;
};

class Init_HandStatus_thumb_tip_status
{
public:
  explicit Init_HandStatus_thumb_tip_status(::agx_arm_msgs::msg::HandStatus & msg)
  : msg_(msg)
  {}
  Init_HandStatus_thumb_base_status thumb_tip_status(::agx_arm_msgs::msg::HandStatus::_thumb_tip_status_type arg)
  {
    msg_.thumb_tip_status = std::move(arg);
    return Init_HandStatus_thumb_base_status(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandStatus msg_;
};

class Init_HandStatus_pinky_finger_pos
{
public:
  explicit Init_HandStatus_pinky_finger_pos(::agx_arm_msgs::msg::HandStatus & msg)
  : msg_(msg)
  {}
  Init_HandStatus_thumb_tip_status pinky_finger_pos(::agx_arm_msgs::msg::HandStatus::_pinky_finger_pos_type arg)
  {
    msg_.pinky_finger_pos = std::move(arg);
    return Init_HandStatus_thumb_tip_status(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandStatus msg_;
};

class Init_HandStatus_ring_finger_pos
{
public:
  explicit Init_HandStatus_ring_finger_pos(::agx_arm_msgs::msg::HandStatus & msg)
  : msg_(msg)
  {}
  Init_HandStatus_pinky_finger_pos ring_finger_pos(::agx_arm_msgs::msg::HandStatus::_ring_finger_pos_type arg)
  {
    msg_.ring_finger_pos = std::move(arg);
    return Init_HandStatus_pinky_finger_pos(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandStatus msg_;
};

class Init_HandStatus_middle_finger_pos
{
public:
  explicit Init_HandStatus_middle_finger_pos(::agx_arm_msgs::msg::HandStatus & msg)
  : msg_(msg)
  {}
  Init_HandStatus_ring_finger_pos middle_finger_pos(::agx_arm_msgs::msg::HandStatus::_middle_finger_pos_type arg)
  {
    msg_.middle_finger_pos = std::move(arg);
    return Init_HandStatus_ring_finger_pos(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandStatus msg_;
};

class Init_HandStatus_index_finger_pos
{
public:
  explicit Init_HandStatus_index_finger_pos(::agx_arm_msgs::msg::HandStatus & msg)
  : msg_(msg)
  {}
  Init_HandStatus_middle_finger_pos index_finger_pos(::agx_arm_msgs::msg::HandStatus::_index_finger_pos_type arg)
  {
    msg_.index_finger_pos = std::move(arg);
    return Init_HandStatus_middle_finger_pos(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandStatus msg_;
};

class Init_HandStatus_thumb_base_pos
{
public:
  explicit Init_HandStatus_thumb_base_pos(::agx_arm_msgs::msg::HandStatus & msg)
  : msg_(msg)
  {}
  Init_HandStatus_index_finger_pos thumb_base_pos(::agx_arm_msgs::msg::HandStatus::_thumb_base_pos_type arg)
  {
    msg_.thumb_base_pos = std::move(arg);
    return Init_HandStatus_index_finger_pos(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandStatus msg_;
};

class Init_HandStatus_thumb_tip_pos
{
public:
  explicit Init_HandStatus_thumb_tip_pos(::agx_arm_msgs::msg::HandStatus & msg)
  : msg_(msg)
  {}
  Init_HandStatus_thumb_base_pos thumb_tip_pos(::agx_arm_msgs::msg::HandStatus::_thumb_tip_pos_type arg)
  {
    msg_.thumb_tip_pos = std::move(arg);
    return Init_HandStatus_thumb_base_pos(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandStatus msg_;
};

class Init_HandStatus_left_or_right
{
public:
  explicit Init_HandStatus_left_or_right(::agx_arm_msgs::msg::HandStatus & msg)
  : msg_(msg)
  {}
  Init_HandStatus_thumb_tip_pos left_or_right(::agx_arm_msgs::msg::HandStatus::_left_or_right_type arg)
  {
    msg_.left_or_right = std::move(arg);
    return Init_HandStatus_thumb_tip_pos(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandStatus msg_;
};

class Init_HandStatus_header
{
public:
  Init_HandStatus_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_HandStatus_left_or_right header(::agx_arm_msgs::msg::HandStatus::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_HandStatus_left_or_right(msg_);
  }

private:
  ::agx_arm_msgs::msg::HandStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::agx_arm_msgs::msg::HandStatus>()
{
  return agx_arm_msgs::msg::builder::Init_HandStatus_header();
}

}  // namespace agx_arm_msgs

#endif  // AGX_ARM_MSGS__MSG__DETAIL__HAND_STATUS__BUILDER_HPP_
