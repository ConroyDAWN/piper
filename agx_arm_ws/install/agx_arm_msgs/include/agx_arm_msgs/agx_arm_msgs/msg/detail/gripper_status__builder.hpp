// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from agx_arm_msgs:msg/GripperStatus.idl
// generated code does not contain a copyright notice

#ifndef AGX_ARM_MSGS__MSG__DETAIL__GRIPPER_STATUS__BUILDER_HPP_
#define AGX_ARM_MSGS__MSG__DETAIL__GRIPPER_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "agx_arm_msgs/msg/detail/gripper_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace agx_arm_msgs
{

namespace msg
{

namespace builder
{

class Init_GripperStatus_homing_status
{
public:
  explicit Init_GripperStatus_homing_status(::agx_arm_msgs::msg::GripperStatus & msg)
  : msg_(msg)
  {}
  ::agx_arm_msgs::msg::GripperStatus homing_status(::agx_arm_msgs::msg::GripperStatus::_homing_status_type arg)
  {
    msg_.homing_status = std::move(arg);
    return std::move(msg_);
  }

private:
  ::agx_arm_msgs::msg::GripperStatus msg_;
};

class Init_GripperStatus_driver_enable_status
{
public:
  explicit Init_GripperStatus_driver_enable_status(::agx_arm_msgs::msg::GripperStatus & msg)
  : msg_(msg)
  {}
  Init_GripperStatus_homing_status driver_enable_status(::agx_arm_msgs::msg::GripperStatus::_driver_enable_status_type arg)
  {
    msg_.driver_enable_status = std::move(arg);
    return Init_GripperStatus_homing_status(msg_);
  }

private:
  ::agx_arm_msgs::msg::GripperStatus msg_;
};

class Init_GripperStatus_driver_error_status
{
public:
  explicit Init_GripperStatus_driver_error_status(::agx_arm_msgs::msg::GripperStatus & msg)
  : msg_(msg)
  {}
  Init_GripperStatus_driver_enable_status driver_error_status(::agx_arm_msgs::msg::GripperStatus::_driver_error_status_type arg)
  {
    msg_.driver_error_status = std::move(arg);
    return Init_GripperStatus_driver_enable_status(msg_);
  }

private:
  ::agx_arm_msgs::msg::GripperStatus msg_;
};

class Init_GripperStatus_sensor_status
{
public:
  explicit Init_GripperStatus_sensor_status(::agx_arm_msgs::msg::GripperStatus & msg)
  : msg_(msg)
  {}
  Init_GripperStatus_driver_error_status sensor_status(::agx_arm_msgs::msg::GripperStatus::_sensor_status_type arg)
  {
    msg_.sensor_status = std::move(arg);
    return Init_GripperStatus_driver_error_status(msg_);
  }

private:
  ::agx_arm_msgs::msg::GripperStatus msg_;
};

class Init_GripperStatus_driver_overheating
{
public:
  explicit Init_GripperStatus_driver_overheating(::agx_arm_msgs::msg::GripperStatus & msg)
  : msg_(msg)
  {}
  Init_GripperStatus_sensor_status driver_overheating(::agx_arm_msgs::msg::GripperStatus::_driver_overheating_type arg)
  {
    msg_.driver_overheating = std::move(arg);
    return Init_GripperStatus_sensor_status(msg_);
  }

private:
  ::agx_arm_msgs::msg::GripperStatus msg_;
};

class Init_GripperStatus_driver_overcurrent
{
public:
  explicit Init_GripperStatus_driver_overcurrent(::agx_arm_msgs::msg::GripperStatus & msg)
  : msg_(msg)
  {}
  Init_GripperStatus_driver_overheating driver_overcurrent(::agx_arm_msgs::msg::GripperStatus::_driver_overcurrent_type arg)
  {
    msg_.driver_overcurrent = std::move(arg);
    return Init_GripperStatus_driver_overheating(msg_);
  }

private:
  ::agx_arm_msgs::msg::GripperStatus msg_;
};

class Init_GripperStatus_motor_overheating
{
public:
  explicit Init_GripperStatus_motor_overheating(::agx_arm_msgs::msg::GripperStatus & msg)
  : msg_(msg)
  {}
  Init_GripperStatus_driver_overcurrent motor_overheating(::agx_arm_msgs::msg::GripperStatus::_motor_overheating_type arg)
  {
    msg_.motor_overheating = std::move(arg);
    return Init_GripperStatus_driver_overcurrent(msg_);
  }

private:
  ::agx_arm_msgs::msg::GripperStatus msg_;
};

class Init_GripperStatus_voltage_too_low
{
public:
  explicit Init_GripperStatus_voltage_too_low(::agx_arm_msgs::msg::GripperStatus & msg)
  : msg_(msg)
  {}
  Init_GripperStatus_motor_overheating voltage_too_low(::agx_arm_msgs::msg::GripperStatus::_voltage_too_low_type arg)
  {
    msg_.voltage_too_low = std::move(arg);
    return Init_GripperStatus_motor_overheating(msg_);
  }

private:
  ::agx_arm_msgs::msg::GripperStatus msg_;
};

class Init_GripperStatus_force
{
public:
  explicit Init_GripperStatus_force(::agx_arm_msgs::msg::GripperStatus & msg)
  : msg_(msg)
  {}
  Init_GripperStatus_voltage_too_low force(::agx_arm_msgs::msg::GripperStatus::_force_type arg)
  {
    msg_.force = std::move(arg);
    return Init_GripperStatus_voltage_too_low(msg_);
  }

private:
  ::agx_arm_msgs::msg::GripperStatus msg_;
};

class Init_GripperStatus_width
{
public:
  explicit Init_GripperStatus_width(::agx_arm_msgs::msg::GripperStatus & msg)
  : msg_(msg)
  {}
  Init_GripperStatus_force width(::agx_arm_msgs::msg::GripperStatus::_width_type arg)
  {
    msg_.width = std::move(arg);
    return Init_GripperStatus_force(msg_);
  }

private:
  ::agx_arm_msgs::msg::GripperStatus msg_;
};

class Init_GripperStatus_header
{
public:
  Init_GripperStatus_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GripperStatus_width header(::agx_arm_msgs::msg::GripperStatus::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_GripperStatus_width(msg_);
  }

private:
  ::agx_arm_msgs::msg::GripperStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::agx_arm_msgs::msg::GripperStatus>()
{
  return agx_arm_msgs::msg::builder::Init_GripperStatus_header();
}

}  // namespace agx_arm_msgs

#endif  // AGX_ARM_MSGS__MSG__DETAIL__GRIPPER_STATUS__BUILDER_HPP_
