// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from agx_arm_msgs:msg/AgxArmStatus.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "agx_arm_msgs/msg/detail/agx_arm_status__rosidl_typesupport_introspection_c.h"
#include "agx_arm_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "agx_arm_msgs/msg/detail/agx_arm_status__functions.h"
#include "agx_arm_msgs/msg/detail/agx_arm_status__struct.h"


// Include directives for member types
// Member `joint_angle_limit`
// Member `communication_status_joint`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__AgxArmStatus_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  agx_arm_msgs__msg__AgxArmStatus__init(message_memory);
}

void agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__AgxArmStatus_fini_function(void * message_memory)
{
  agx_arm_msgs__msg__AgxArmStatus__fini(message_memory);
}

size_t agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__size_function__AgxArmStatus__joint_angle_limit(
  const void * untyped_member)
{
  const rosidl_runtime_c__boolean__Sequence * member =
    (const rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  return member->size;
}

const void * agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__get_const_function__AgxArmStatus__joint_angle_limit(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__boolean__Sequence * member =
    (const rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__get_function__AgxArmStatus__joint_angle_limit(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__boolean__Sequence * member =
    (rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  return &member->data[index];
}

void agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__fetch_function__AgxArmStatus__joint_angle_limit(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const bool * item =
    ((const bool *)
    agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__get_const_function__AgxArmStatus__joint_angle_limit(untyped_member, index));
  bool * value =
    (bool *)(untyped_value);
  *value = *item;
}

void agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__assign_function__AgxArmStatus__joint_angle_limit(
  void * untyped_member, size_t index, const void * untyped_value)
{
  bool * item =
    ((bool *)
    agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__get_function__AgxArmStatus__joint_angle_limit(untyped_member, index));
  const bool * value =
    (const bool *)(untyped_value);
  *item = *value;
}

bool agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__resize_function__AgxArmStatus__joint_angle_limit(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__boolean__Sequence * member =
    (rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  rosidl_runtime_c__boolean__Sequence__fini(member);
  return rosidl_runtime_c__boolean__Sequence__init(member, size);
}

size_t agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__size_function__AgxArmStatus__communication_status_joint(
  const void * untyped_member)
{
  const rosidl_runtime_c__boolean__Sequence * member =
    (const rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  return member->size;
}

const void * agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__get_const_function__AgxArmStatus__communication_status_joint(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__boolean__Sequence * member =
    (const rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__get_function__AgxArmStatus__communication_status_joint(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__boolean__Sequence * member =
    (rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  return &member->data[index];
}

void agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__fetch_function__AgxArmStatus__communication_status_joint(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const bool * item =
    ((const bool *)
    agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__get_const_function__AgxArmStatus__communication_status_joint(untyped_member, index));
  bool * value =
    (bool *)(untyped_value);
  *value = *item;
}

void agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__assign_function__AgxArmStatus__communication_status_joint(
  void * untyped_member, size_t index, const void * untyped_value)
{
  bool * item =
    ((bool *)
    agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__get_function__AgxArmStatus__communication_status_joint(untyped_member, index));
  const bool * value =
    (const bool *)(untyped_value);
  *item = *value;
}

bool agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__resize_function__AgxArmStatus__communication_status_joint(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__boolean__Sequence * member =
    (rosidl_runtime_c__boolean__Sequence *)(untyped_member);
  rosidl_runtime_c__boolean__Sequence__fini(member);
  return rosidl_runtime_c__boolean__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__AgxArmStatus_message_member_array[9] = {
  {
    "ctrl_mode",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agx_arm_msgs__msg__AgxArmStatus, ctrl_mode),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "arm_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agx_arm_msgs__msg__AgxArmStatus, arm_status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "mode_feedback",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agx_arm_msgs__msg__AgxArmStatus, mode_feedback),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "teach_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agx_arm_msgs__msg__AgxArmStatus, teach_status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "motion_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agx_arm_msgs__msg__AgxArmStatus, motion_status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "trajectory_num",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agx_arm_msgs__msg__AgxArmStatus, trajectory_num),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "err_status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agx_arm_msgs__msg__AgxArmStatus, err_status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "joint_angle_limit",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agx_arm_msgs__msg__AgxArmStatus, joint_angle_limit),  // bytes offset in struct
    NULL,  // default value
    agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__size_function__AgxArmStatus__joint_angle_limit,  // size() function pointer
    agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__get_const_function__AgxArmStatus__joint_angle_limit,  // get_const(index) function pointer
    agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__get_function__AgxArmStatus__joint_angle_limit,  // get(index) function pointer
    agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__fetch_function__AgxArmStatus__joint_angle_limit,  // fetch(index, &value) function pointer
    agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__assign_function__AgxArmStatus__joint_angle_limit,  // assign(index, value) function pointer
    agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__resize_function__AgxArmStatus__joint_angle_limit  // resize(index) function pointer
  },
  {
    "communication_status_joint",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agx_arm_msgs__msg__AgxArmStatus, communication_status_joint),  // bytes offset in struct
    NULL,  // default value
    agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__size_function__AgxArmStatus__communication_status_joint,  // size() function pointer
    agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__get_const_function__AgxArmStatus__communication_status_joint,  // get_const(index) function pointer
    agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__get_function__AgxArmStatus__communication_status_joint,  // get(index) function pointer
    agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__fetch_function__AgxArmStatus__communication_status_joint,  // fetch(index, &value) function pointer
    agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__assign_function__AgxArmStatus__communication_status_joint,  // assign(index, value) function pointer
    agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__resize_function__AgxArmStatus__communication_status_joint  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__AgxArmStatus_message_members = {
  "agx_arm_msgs__msg",  // message namespace
  "AgxArmStatus",  // message name
  9,  // number of fields
  sizeof(agx_arm_msgs__msg__AgxArmStatus),
  agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__AgxArmStatus_message_member_array,  // message members
  agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__AgxArmStatus_init_function,  // function to initialize message memory (memory has to be allocated)
  agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__AgxArmStatus_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__AgxArmStatus_message_type_support_handle = {
  0,
  &agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__AgxArmStatus_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agx_arm_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agx_arm_msgs, msg, AgxArmStatus)() {
  if (!agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__AgxArmStatus_message_type_support_handle.typesupport_identifier) {
    agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__AgxArmStatus_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &agx_arm_msgs__msg__AgxArmStatus__rosidl_typesupport_introspection_c__AgxArmStatus_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
