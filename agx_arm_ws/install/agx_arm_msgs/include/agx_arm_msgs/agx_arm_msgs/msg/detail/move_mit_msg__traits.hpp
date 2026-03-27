// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from agx_arm_msgs:msg/MoveMITMsg.idl
// generated code does not contain a copyright notice

#ifndef AGX_ARM_MSGS__MSG__DETAIL__MOVE_MIT_MSG__TRAITS_HPP_
#define AGX_ARM_MSGS__MSG__DETAIL__MOVE_MIT_MSG__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "agx_arm_msgs/msg/detail/move_mit_msg__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace agx_arm_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const MoveMITMsg & msg,
  std::ostream & out)
{
  out << "{";
  // member: joint_index
  {
    if (msg.joint_index.size() == 0) {
      out << "joint_index: []";
    } else {
      out << "joint_index: [";
      size_t pending_items = msg.joint_index.size();
      for (auto item : msg.joint_index) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: p_des
  {
    if (msg.p_des.size() == 0) {
      out << "p_des: []";
    } else {
      out << "p_des: [";
      size_t pending_items = msg.p_des.size();
      for (auto item : msg.p_des) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: v_des
  {
    if (msg.v_des.size() == 0) {
      out << "v_des: []";
    } else {
      out << "v_des: [";
      size_t pending_items = msg.v_des.size();
      for (auto item : msg.v_des) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: kp
  {
    if (msg.kp.size() == 0) {
      out << "kp: []";
    } else {
      out << "kp: [";
      size_t pending_items = msg.kp.size();
      for (auto item : msg.kp) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: kd
  {
    if (msg.kd.size() == 0) {
      out << "kd: []";
    } else {
      out << "kd: [";
      size_t pending_items = msg.kd.size();
      for (auto item : msg.kd) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: torque
  {
    if (msg.torque.size() == 0) {
      out << "torque: []";
    } else {
      out << "torque: [";
      size_t pending_items = msg.torque.size();
      for (auto item : msg.torque) {
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
  const MoveMITMsg & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: joint_index
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.joint_index.size() == 0) {
      out << "joint_index: []\n";
    } else {
      out << "joint_index:\n";
      for (auto item : msg.joint_index) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: p_des
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.p_des.size() == 0) {
      out << "p_des: []\n";
    } else {
      out << "p_des:\n";
      for (auto item : msg.p_des) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: v_des
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.v_des.size() == 0) {
      out << "v_des: []\n";
    } else {
      out << "v_des:\n";
      for (auto item : msg.v_des) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: kp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.kp.size() == 0) {
      out << "kp: []\n";
    } else {
      out << "kp:\n";
      for (auto item : msg.kp) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: kd
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.kd.size() == 0) {
      out << "kd: []\n";
    } else {
      out << "kd:\n";
      for (auto item : msg.kd) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: torque
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.torque.size() == 0) {
      out << "torque: []\n";
    } else {
      out << "torque:\n";
      for (auto item : msg.torque) {
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

inline std::string to_yaml(const MoveMITMsg & msg, bool use_flow_style = false)
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
  const agx_arm_msgs::msg::MoveMITMsg & msg,
  std::ostream & out, size_t indentation = 0)
{
  agx_arm_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use agx_arm_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const agx_arm_msgs::msg::MoveMITMsg & msg)
{
  return agx_arm_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<agx_arm_msgs::msg::MoveMITMsg>()
{
  return "agx_arm_msgs::msg::MoveMITMsg";
}

template<>
inline const char * name<agx_arm_msgs::msg::MoveMITMsg>()
{
  return "agx_arm_msgs/msg/MoveMITMsg";
}

template<>
struct has_fixed_size<agx_arm_msgs::msg::MoveMITMsg>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<agx_arm_msgs::msg::MoveMITMsg>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<agx_arm_msgs::msg::MoveMITMsg>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AGX_ARM_MSGS__MSG__DETAIL__MOVE_MIT_MSG__TRAITS_HPP_
