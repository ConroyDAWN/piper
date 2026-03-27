// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agx_arm_msgs:msg/GripperStatus.idl
// generated code does not contain a copyright notice

#ifndef AGX_ARM_MSGS__MSG__DETAIL__GRIPPER_STATUS__TRAITS_HPP_
#define AGX_ARM_MSGS__MSG__DETAIL__GRIPPER_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agx_arm_msgs/msg/detail/gripper_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace agx_arm_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const GripperStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: width
  {
    out << "width: ";
    rosidl_generator_traits::value_to_yaml(msg.width, out);
    out << ", ";
  }

  // member: force
  {
    out << "force: ";
    rosidl_generator_traits::value_to_yaml(msg.force, out);
    out << ", ";
  }

  // member: voltage_too_low
  {
    out << "voltage_too_low: ";
    rosidl_generator_traits::value_to_yaml(msg.voltage_too_low, out);
    out << ", ";
  }

  // member: motor_overheating
  {
    out << "motor_overheating: ";
    rosidl_generator_traits::value_to_yaml(msg.motor_overheating, out);
    out << ", ";
  }

  // member: driver_overcurrent
  {
    out << "driver_overcurrent: ";
    rosidl_generator_traits::value_to_yaml(msg.driver_overcurrent, out);
    out << ", ";
  }

  // member: driver_overheating
  {
    out << "driver_overheating: ";
    rosidl_generator_traits::value_to_yaml(msg.driver_overheating, out);
    out << ", ";
  }

  // member: sensor_status
  {
    out << "sensor_status: ";
    rosidl_generator_traits::value_to_yaml(msg.sensor_status, out);
    out << ", ";
  }

  // member: driver_error_status
  {
    out << "driver_error_status: ";
    rosidl_generator_traits::value_to_yaml(msg.driver_error_status, out);
    out << ", ";
  }

  // member: driver_enable_status
  {
    out << "driver_enable_status: ";
    rosidl_generator_traits::value_to_yaml(msg.driver_enable_status, out);
    out << ", ";
  }

  // member: homing_status
  {
    out << "homing_status: ";
    rosidl_generator_traits::value_to_yaml(msg.homing_status, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GripperStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: width
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "width: ";
    rosidl_generator_traits::value_to_yaml(msg.width, out);
    out << "\n";
  }

  // member: force
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "force: ";
    rosidl_generator_traits::value_to_yaml(msg.force, out);
    out << "\n";
  }

  // member: voltage_too_low
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "voltage_too_low: ";
    rosidl_generator_traits::value_to_yaml(msg.voltage_too_low, out);
    out << "\n";
  }

  // member: motor_overheating
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "motor_overheating: ";
    rosidl_generator_traits::value_to_yaml(msg.motor_overheating, out);
    out << "\n";
  }

  // member: driver_overcurrent
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "driver_overcurrent: ";
    rosidl_generator_traits::value_to_yaml(msg.driver_overcurrent, out);
    out << "\n";
  }

  // member: driver_overheating
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "driver_overheating: ";
    rosidl_generator_traits::value_to_yaml(msg.driver_overheating, out);
    out << "\n";
  }

  // member: sensor_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sensor_status: ";
    rosidl_generator_traits::value_to_yaml(msg.sensor_status, out);
    out << "\n";
  }

  // member: driver_error_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "driver_error_status: ";
    rosidl_generator_traits::value_to_yaml(msg.driver_error_status, out);
    out << "\n";
  }

  // member: driver_enable_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "driver_enable_status: ";
    rosidl_generator_traits::value_to_yaml(msg.driver_enable_status, out);
    out << "\n";
  }

  // member: homing_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "homing_status: ";
    rosidl_generator_traits::value_to_yaml(msg.homing_status, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GripperStatus & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace agx_arm_msgs

namespace rosidl_generator_traits
{

[[deprecated("use agx_arm_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const agx_arm_msgs::msg::GripperStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  agx_arm_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agx_arm_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const agx_arm_msgs::msg::GripperStatus & msg)
{
  return agx_arm_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<agx_arm_msgs::msg::GripperStatus>()
{
  return "agx_arm_msgs::msg::GripperStatus";
}

template<>
inline const char * name<agx_arm_msgs::msg::GripperStatus>()
{
  return "agx_arm_msgs/msg/GripperStatus";
}

template<>
struct has_fixed_size<agx_arm_msgs::msg::GripperStatus>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<agx_arm_msgs::msg::GripperStatus>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<agx_arm_msgs::msg::GripperStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AGX_ARM_MSGS__MSG__DETAIL__GRIPPER_STATUS__TRAITS_HPP_
