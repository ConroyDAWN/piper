// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agx_arm_msgs:msg/HandStatus.idl
// generated code does not contain a copyright notice

#ifndef AGX_ARM_MSGS__MSG__DETAIL__HAND_STATUS__TRAITS_HPP_
#define AGX_ARM_MSGS__MSG__DETAIL__HAND_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agx_arm_msgs/msg/detail/hand_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace agx_arm_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const HandStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: left_or_right
  {
    out << "left_or_right: ";
    rosidl_generator_traits::value_to_yaml(msg.left_or_right, out);
    out << ", ";
  }

  // member: thumb_tip_pos
  {
    out << "thumb_tip_pos: ";
    rosidl_generator_traits::value_to_yaml(msg.thumb_tip_pos, out);
    out << ", ";
  }

  // member: thumb_base_pos
  {
    out << "thumb_base_pos: ";
    rosidl_generator_traits::value_to_yaml(msg.thumb_base_pos, out);
    out << ", ";
  }

  // member: index_finger_pos
  {
    out << "index_finger_pos: ";
    rosidl_generator_traits::value_to_yaml(msg.index_finger_pos, out);
    out << ", ";
  }

  // member: middle_finger_pos
  {
    out << "middle_finger_pos: ";
    rosidl_generator_traits::value_to_yaml(msg.middle_finger_pos, out);
    out << ", ";
  }

  // member: ring_finger_pos
  {
    out << "ring_finger_pos: ";
    rosidl_generator_traits::value_to_yaml(msg.ring_finger_pos, out);
    out << ", ";
  }

  // member: pinky_finger_pos
  {
    out << "pinky_finger_pos: ";
    rosidl_generator_traits::value_to_yaml(msg.pinky_finger_pos, out);
    out << ", ";
  }

  // member: thumb_tip_status
  {
    out << "thumb_tip_status: ";
    rosidl_generator_traits::value_to_yaml(msg.thumb_tip_status, out);
    out << ", ";
  }

  // member: thumb_base_status
  {
    out << "thumb_base_status: ";
    rosidl_generator_traits::value_to_yaml(msg.thumb_base_status, out);
    out << ", ";
  }

  // member: index_finger_status
  {
    out << "index_finger_status: ";
    rosidl_generator_traits::value_to_yaml(msg.index_finger_status, out);
    out << ", ";
  }

  // member: middle_finger_status
  {
    out << "middle_finger_status: ";
    rosidl_generator_traits::value_to_yaml(msg.middle_finger_status, out);
    out << ", ";
  }

  // member: ring_finger_status
  {
    out << "ring_finger_status: ";
    rosidl_generator_traits::value_to_yaml(msg.ring_finger_status, out);
    out << ", ";
  }

  // member: pinky_finger_status
  {
    out << "pinky_finger_status: ";
    rosidl_generator_traits::value_to_yaml(msg.pinky_finger_status, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const HandStatus & msg,
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

  // member: left_or_right
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "left_or_right: ";
    rosidl_generator_traits::value_to_yaml(msg.left_or_right, out);
    out << "\n";
  }

  // member: thumb_tip_pos
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "thumb_tip_pos: ";
    rosidl_generator_traits::value_to_yaml(msg.thumb_tip_pos, out);
    out << "\n";
  }

  // member: thumb_base_pos
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "thumb_base_pos: ";
    rosidl_generator_traits::value_to_yaml(msg.thumb_base_pos, out);
    out << "\n";
  }

  // member: index_finger_pos
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "index_finger_pos: ";
    rosidl_generator_traits::value_to_yaml(msg.index_finger_pos, out);
    out << "\n";
  }

  // member: middle_finger_pos
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "middle_finger_pos: ";
    rosidl_generator_traits::value_to_yaml(msg.middle_finger_pos, out);
    out << "\n";
  }

  // member: ring_finger_pos
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ring_finger_pos: ";
    rosidl_generator_traits::value_to_yaml(msg.ring_finger_pos, out);
    out << "\n";
  }

  // member: pinky_finger_pos
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pinky_finger_pos: ";
    rosidl_generator_traits::value_to_yaml(msg.pinky_finger_pos, out);
    out << "\n";
  }

  // member: thumb_tip_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "thumb_tip_status: ";
    rosidl_generator_traits::value_to_yaml(msg.thumb_tip_status, out);
    out << "\n";
  }

  // member: thumb_base_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "thumb_base_status: ";
    rosidl_generator_traits::value_to_yaml(msg.thumb_base_status, out);
    out << "\n";
  }

  // member: index_finger_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "index_finger_status: ";
    rosidl_generator_traits::value_to_yaml(msg.index_finger_status, out);
    out << "\n";
  }

  // member: middle_finger_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "middle_finger_status: ";
    rosidl_generator_traits::value_to_yaml(msg.middle_finger_status, out);
    out << "\n";
  }

  // member: ring_finger_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ring_finger_status: ";
    rosidl_generator_traits::value_to_yaml(msg.ring_finger_status, out);
    out << "\n";
  }

  // member: pinky_finger_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pinky_finger_status: ";
    rosidl_generator_traits::value_to_yaml(msg.pinky_finger_status, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const HandStatus & msg, bool use_flow_style = false)
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
  const agx_arm_msgs::msg::HandStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  agx_arm_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agx_arm_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const agx_arm_msgs::msg::HandStatus & msg)
{
  return agx_arm_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<agx_arm_msgs::msg::HandStatus>()
{
  return "agx_arm_msgs::msg::HandStatus";
}

template<>
inline const char * name<agx_arm_msgs::msg::HandStatus>()
{
  return "agx_arm_msgs/msg/HandStatus";
}

template<>
struct has_fixed_size<agx_arm_msgs::msg::HandStatus>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<agx_arm_msgs::msg::HandStatus>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<agx_arm_msgs::msg::HandStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AGX_ARM_MSGS__MSG__DETAIL__HAND_STATUS__TRAITS_HPP_
