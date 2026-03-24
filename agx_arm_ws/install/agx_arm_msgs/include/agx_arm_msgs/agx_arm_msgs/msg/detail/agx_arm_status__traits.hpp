// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agx_arm_msgs:msg/AgxArmStatus.idl
// generated code does not contain a copyright notice

#ifndef AGX_ARM_MSGS__MSG__DETAIL__AGX_ARM_STATUS__TRAITS_HPP_
#define AGX_ARM_MSGS__MSG__DETAIL__AGX_ARM_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agx_arm_msgs/msg/detail/agx_arm_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace agx_arm_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const AgxArmStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: ctrl_mode
  {
    out << "ctrl_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.ctrl_mode, out);
    out << ", ";
  }

  // member: arm_status
  {
    out << "arm_status: ";
    rosidl_generator_traits::value_to_yaml(msg.arm_status, out);
    out << ", ";
  }

  // member: mode_feedback
  {
    out << "mode_feedback: ";
    rosidl_generator_traits::value_to_yaml(msg.mode_feedback, out);
    out << ", ";
  }

  // member: teach_status
  {
    out << "teach_status: ";
    rosidl_generator_traits::value_to_yaml(msg.teach_status, out);
    out << ", ";
  }

  // member: motion_status
  {
    out << "motion_status: ";
    rosidl_generator_traits::value_to_yaml(msg.motion_status, out);
    out << ", ";
  }

  // member: trajectory_num
  {
    out << "trajectory_num: ";
    rosidl_generator_traits::value_to_yaml(msg.trajectory_num, out);
    out << ", ";
  }

  // member: err_status
  {
    out << "err_status: ";
    rosidl_generator_traits::value_to_yaml(msg.err_status, out);
    out << ", ";
  }

  // member: joint_angle_limit
  {
    if (msg.joint_angle_limit.size() == 0) {
      out << "joint_angle_limit: []";
    } else {
      out << "joint_angle_limit: [";
      size_t pending_items = msg.joint_angle_limit.size();
      for (auto item : msg.joint_angle_limit) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: communication_status_joint
  {
    if (msg.communication_status_joint.size() == 0) {
      out << "communication_status_joint: []";
    } else {
      out << "communication_status_joint: [";
      size_t pending_items = msg.communication_status_joint.size();
      for (auto item : msg.communication_status_joint) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const AgxArmStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: ctrl_mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ctrl_mode: ";
    rosidl_generator_traits::value_to_yaml(msg.ctrl_mode, out);
    out << "\n";
  }

  // member: arm_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "arm_status: ";
    rosidl_generator_traits::value_to_yaml(msg.arm_status, out);
    out << "\n";
  }

  // member: mode_feedback
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mode_feedback: ";
    rosidl_generator_traits::value_to_yaml(msg.mode_feedback, out);
    out << "\n";
  }

  // member: teach_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "teach_status: ";
    rosidl_generator_traits::value_to_yaml(msg.teach_status, out);
    out << "\n";
  }

  // member: motion_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "motion_status: ";
    rosidl_generator_traits::value_to_yaml(msg.motion_status, out);
    out << "\n";
  }

  // member: trajectory_num
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "trajectory_num: ";
    rosidl_generator_traits::value_to_yaml(msg.trajectory_num, out);
    out << "\n";
  }

  // member: err_status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "err_status: ";
    rosidl_generator_traits::value_to_yaml(msg.err_status, out);
    out << "\n";
  }

  // member: joint_angle_limit
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.joint_angle_limit.size() == 0) {
      out << "joint_angle_limit: []\n";
    } else {
      out << "joint_angle_limit:\n";
      for (auto item : msg.joint_angle_limit) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: communication_status_joint
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.communication_status_joint.size() == 0) {
      out << "communication_status_joint: []\n";
    } else {
      out << "communication_status_joint:\n";
      for (auto item : msg.communication_status_joint) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const AgxArmStatus & msg, bool use_flow_style = false)
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
  const agx_arm_msgs::msg::AgxArmStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  agx_arm_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agx_arm_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const agx_arm_msgs::msg::AgxArmStatus & msg)
{
  return agx_arm_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<agx_arm_msgs::msg::AgxArmStatus>()
{
  return "agx_arm_msgs::msg::AgxArmStatus";
}

template<>
inline const char * name<agx_arm_msgs::msg::AgxArmStatus>()
{
  return "agx_arm_msgs/msg/AgxArmStatus";
}

template<>
struct has_fixed_size<agx_arm_msgs::msg::AgxArmStatus>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agx_arm_msgs::msg::AgxArmStatus>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agx_arm_msgs::msg::AgxArmStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AGX_ARM_MSGS__MSG__DETAIL__AGX_ARM_STATUS__TRAITS_HPP_
