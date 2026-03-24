// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agx_arm_msgs:msg/HandCmd.idl
// generated code does not contain a copyright notice

#ifndef AGX_ARM_MSGS__MSG__DETAIL__HAND_CMD__TRAITS_HPP_
#define AGX_ARM_MSGS__MSG__DETAIL__HAND_CMD__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agx_arm_msgs/msg/detail/hand_cmd__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace agx_arm_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const HandCmd & msg,
  std::ostream & out)
{
  out << "{";
  // member: mode
  {
    out << "mode: ";
    rosidl_generator_traits::value_to_yaml(msg.mode, out);
    out << ", ";
  }

  // member: thumb_tip
  {
    out << "thumb_tip: ";
    rosidl_generator_traits::value_to_yaml(msg.thumb_tip, out);
    out << ", ";
  }

  // member: thumb_base
  {
    out << "thumb_base: ";
    rosidl_generator_traits::value_to_yaml(msg.thumb_base, out);
    out << ", ";
  }

  // member: index_finger
  {
    out << "index_finger: ";
    rosidl_generator_traits::value_to_yaml(msg.index_finger, out);
    out << ", ";
  }

  // member: middle_finger
  {
    out << "middle_finger: ";
    rosidl_generator_traits::value_to_yaml(msg.middle_finger, out);
    out << ", ";
  }

  // member: ring_finger
  {
    out << "ring_finger: ";
    rosidl_generator_traits::value_to_yaml(msg.ring_finger, out);
    out << ", ";
  }

  // member: pinky_finger
  {
    out << "pinky_finger: ";
    rosidl_generator_traits::value_to_yaml(msg.pinky_finger, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const HandCmd & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mode: ";
    rosidl_generator_traits::value_to_yaml(msg.mode, out);
    out << "\n";
  }

  // member: thumb_tip
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "thumb_tip: ";
    rosidl_generator_traits::value_to_yaml(msg.thumb_tip, out);
    out << "\n";
  }

  // member: thumb_base
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "thumb_base: ";
    rosidl_generator_traits::value_to_yaml(msg.thumb_base, out);
    out << "\n";
  }

  // member: index_finger
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "index_finger: ";
    rosidl_generator_traits::value_to_yaml(msg.index_finger, out);
    out << "\n";
  }

  // member: middle_finger
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "middle_finger: ";
    rosidl_generator_traits::value_to_yaml(msg.middle_finger, out);
    out << "\n";
  }

  // member: ring_finger
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ring_finger: ";
    rosidl_generator_traits::value_to_yaml(msg.ring_finger, out);
    out << "\n";
  }

  // member: pinky_finger
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pinky_finger: ";
    rosidl_generator_traits::value_to_yaml(msg.pinky_finger, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const HandCmd & msg, bool use_flow_style = false)
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
  const agx_arm_msgs::msg::HandCmd & msg,
  std::ostream & out, size_t indentation = 0)
{
  agx_arm_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agx_arm_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const agx_arm_msgs::msg::HandCmd & msg)
{
  return agx_arm_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<agx_arm_msgs::msg::HandCmd>()
{
  return "agx_arm_msgs::msg::HandCmd";
}

template<>
inline const char * name<agx_arm_msgs::msg::HandCmd>()
{
  return "agx_arm_msgs/msg/HandCmd";
}

template<>
struct has_fixed_size<agx_arm_msgs::msg::HandCmd>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agx_arm_msgs::msg::HandCmd>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agx_arm_msgs::msg::HandCmd>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AGX_ARM_MSGS__MSG__DETAIL__HAND_CMD__TRAITS_HPP_
