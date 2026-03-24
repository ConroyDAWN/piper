// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from agx_arm_msgs:msg/MoveMITMsg.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "agx_arm_msgs/msg/detail/move_mit_msg__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace agx_arm_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void MoveMITMsg_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) agx_arm_msgs::msg::MoveMITMsg(_init);
}

void MoveMITMsg_fini_function(void * message_memory)
{
  auto typed_message = static_cast<agx_arm_msgs::msg::MoveMITMsg *>(message_memory);
  typed_message->~MoveMITMsg();
}

size_t size_function__MoveMITMsg__joint_index(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<int32_t> *>(untyped_member);
  return member->size();
}

const void * get_const_function__MoveMITMsg__joint_index(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<int32_t> *>(untyped_member);
  return &member[index];
}

void * get_function__MoveMITMsg__joint_index(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<int32_t> *>(untyped_member);
  return &member[index];
}

void fetch_function__MoveMITMsg__joint_index(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const int32_t *>(
    get_const_function__MoveMITMsg__joint_index(untyped_member, index));
  auto & value = *reinterpret_cast<int32_t *>(untyped_value);
  value = item;
}

void assign_function__MoveMITMsg__joint_index(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<int32_t *>(
    get_function__MoveMITMsg__joint_index(untyped_member, index));
  const auto & value = *reinterpret_cast<const int32_t *>(untyped_value);
  item = value;
}

void resize_function__MoveMITMsg__joint_index(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<int32_t> *>(untyped_member);
  member->resize(size);
}

size_t size_function__MoveMITMsg__p_des(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<double> *>(untyped_member);
  return member->size();
}

const void * get_const_function__MoveMITMsg__p_des(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<double> *>(untyped_member);
  return &member[index];
}

void * get_function__MoveMITMsg__p_des(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<double> *>(untyped_member);
  return &member[index];
}

void fetch_function__MoveMITMsg__p_des(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__MoveMITMsg__p_des(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__MoveMITMsg__p_des(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__MoveMITMsg__p_des(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

void resize_function__MoveMITMsg__p_des(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<double> *>(untyped_member);
  member->resize(size);
}

size_t size_function__MoveMITMsg__v_des(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<double> *>(untyped_member);
  return member->size();
}

const void * get_const_function__MoveMITMsg__v_des(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<double> *>(untyped_member);
  return &member[index];
}

void * get_function__MoveMITMsg__v_des(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<double> *>(untyped_member);
  return &member[index];
}

void fetch_function__MoveMITMsg__v_des(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__MoveMITMsg__v_des(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__MoveMITMsg__v_des(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__MoveMITMsg__v_des(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

void resize_function__MoveMITMsg__v_des(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<double> *>(untyped_member);
  member->resize(size);
}

size_t size_function__MoveMITMsg__kp(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<double> *>(untyped_member);
  return member->size();
}

const void * get_const_function__MoveMITMsg__kp(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<double> *>(untyped_member);
  return &member[index];
}

void * get_function__MoveMITMsg__kp(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<double> *>(untyped_member);
  return &member[index];
}

void fetch_function__MoveMITMsg__kp(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__MoveMITMsg__kp(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__MoveMITMsg__kp(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__MoveMITMsg__kp(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

void resize_function__MoveMITMsg__kp(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<double> *>(untyped_member);
  member->resize(size);
}

size_t size_function__MoveMITMsg__kd(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<double> *>(untyped_member);
  return member->size();
}

const void * get_const_function__MoveMITMsg__kd(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<double> *>(untyped_member);
  return &member[index];
}

void * get_function__MoveMITMsg__kd(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<double> *>(untyped_member);
  return &member[index];
}

void fetch_function__MoveMITMsg__kd(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__MoveMITMsg__kd(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__MoveMITMsg__kd(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__MoveMITMsg__kd(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

void resize_function__MoveMITMsg__kd(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<double> *>(untyped_member);
  member->resize(size);
}

size_t size_function__MoveMITMsg__torque(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<double> *>(untyped_member);
  return member->size();
}

const void * get_const_function__MoveMITMsg__torque(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<double> *>(untyped_member);
  return &member[index];
}

void * get_function__MoveMITMsg__torque(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<double> *>(untyped_member);
  return &member[index];
}

void fetch_function__MoveMITMsg__torque(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const double *>(
    get_const_function__MoveMITMsg__torque(untyped_member, index));
  auto & value = *reinterpret_cast<double *>(untyped_value);
  value = item;
}

void assign_function__MoveMITMsg__torque(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<double *>(
    get_function__MoveMITMsg__torque(untyped_member, index));
  const auto & value = *reinterpret_cast<const double *>(untyped_value);
  item = value;
}

void resize_function__MoveMITMsg__torque(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<double> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember MoveMITMsg_message_member_array[6] = {
  {
    "joint_index",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agx_arm_msgs::msg::MoveMITMsg, joint_index),  // bytes offset in struct
    nullptr,  // default value
    size_function__MoveMITMsg__joint_index,  // size() function pointer
    get_const_function__MoveMITMsg__joint_index,  // get_const(index) function pointer
    get_function__MoveMITMsg__joint_index,  // get(index) function pointer
    fetch_function__MoveMITMsg__joint_index,  // fetch(index, &value) function pointer
    assign_function__MoveMITMsg__joint_index,  // assign(index, value) function pointer
    resize_function__MoveMITMsg__joint_index  // resize(index) function pointer
  },
  {
    "p_des",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agx_arm_msgs::msg::MoveMITMsg, p_des),  // bytes offset in struct
    nullptr,  // default value
    size_function__MoveMITMsg__p_des,  // size() function pointer
    get_const_function__MoveMITMsg__p_des,  // get_const(index) function pointer
    get_function__MoveMITMsg__p_des,  // get(index) function pointer
    fetch_function__MoveMITMsg__p_des,  // fetch(index, &value) function pointer
    assign_function__MoveMITMsg__p_des,  // assign(index, value) function pointer
    resize_function__MoveMITMsg__p_des  // resize(index) function pointer
  },
  {
    "v_des",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agx_arm_msgs::msg::MoveMITMsg, v_des),  // bytes offset in struct
    nullptr,  // default value
    size_function__MoveMITMsg__v_des,  // size() function pointer
    get_const_function__MoveMITMsg__v_des,  // get_const(index) function pointer
    get_function__MoveMITMsg__v_des,  // get(index) function pointer
    fetch_function__MoveMITMsg__v_des,  // fetch(index, &value) function pointer
    assign_function__MoveMITMsg__v_des,  // assign(index, value) function pointer
    resize_function__MoveMITMsg__v_des  // resize(index) function pointer
  },
  {
    "kp",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agx_arm_msgs::msg::MoveMITMsg, kp),  // bytes offset in struct
    nullptr,  // default value
    size_function__MoveMITMsg__kp,  // size() function pointer
    get_const_function__MoveMITMsg__kp,  // get_const(index) function pointer
    get_function__MoveMITMsg__kp,  // get(index) function pointer
    fetch_function__MoveMITMsg__kp,  // fetch(index, &value) function pointer
    assign_function__MoveMITMsg__kp,  // assign(index, value) function pointer
    resize_function__MoveMITMsg__kp  // resize(index) function pointer
  },
  {
    "kd",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agx_arm_msgs::msg::MoveMITMsg, kd),  // bytes offset in struct
    nullptr,  // default value
    size_function__MoveMITMsg__kd,  // size() function pointer
    get_const_function__MoveMITMsg__kd,  // get_const(index) function pointer
    get_function__MoveMITMsg__kd,  // get(index) function pointer
    fetch_function__MoveMITMsg__kd,  // fetch(index, &value) function pointer
    assign_function__MoveMITMsg__kd,  // assign(index, value) function pointer
    resize_function__MoveMITMsg__kd  // resize(index) function pointer
  },
  {
    "torque",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agx_arm_msgs::msg::MoveMITMsg, torque),  // bytes offset in struct
    nullptr,  // default value
    size_function__MoveMITMsg__torque,  // size() function pointer
    get_const_function__MoveMITMsg__torque,  // get_const(index) function pointer
    get_function__MoveMITMsg__torque,  // get(index) function pointer
    fetch_function__MoveMITMsg__torque,  // fetch(index, &value) function pointer
    assign_function__MoveMITMsg__torque,  // assign(index, value) function pointer
    resize_function__MoveMITMsg__torque  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers MoveMITMsg_message_members = {
  "agx_arm_msgs::msg",  // message namespace
  "MoveMITMsg",  // message name
  6,  // number of fields
  sizeof(agx_arm_msgs::msg::MoveMITMsg),
  MoveMITMsg_message_member_array,  // message members
  MoveMITMsg_init_function,  // function to initialize message memory (memory has to be allocated)
  MoveMITMsg_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t MoveMITMsg_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &MoveMITMsg_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace agx_arm_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<agx_arm_msgs::msg::MoveMITMsg>()
{
  return &::agx_arm_msgs::msg::rosidl_typesupport_introspection_cpp::MoveMITMsg_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, agx_arm_msgs, msg, MoveMITMsg)() {
  return &::agx_arm_msgs::msg::rosidl_typesupport_introspection_cpp::MoveMITMsg_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
