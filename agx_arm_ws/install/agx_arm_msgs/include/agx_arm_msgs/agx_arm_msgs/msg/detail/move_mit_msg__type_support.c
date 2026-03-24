// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from agx_arm_msgs:msg/MoveMITMsg.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "agx_arm_msgs/msg/detail/move_mit_msg__rosidl_typesupport_introspection_c.h"
#include "agx_arm_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "agx_arm_msgs/msg/detail/move_mit_msg__functions.h"
#include "agx_arm_msgs/msg/detail/move_mit_msg__struct.h"


// Include directives for member types
// Member `joint_index`
// Member `p_des`
// Member `v_des`
// Member `kp`
// Member `kd`
// Member `torque`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__MoveMITMsg_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  agx_arm_msgs__msg__MoveMITMsg__init(message_memory);
}

void agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__MoveMITMsg_fini_function(void * message_memory)
{
  agx_arm_msgs__msg__MoveMITMsg__fini(message_memory);
}

size_t agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__size_function__MoveMITMsg__joint_index(
  const void * untyped_member)
{
  const rosidl_runtime_c__int32__Sequence * member =
    (const rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return member->size;
}

const void * agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_const_function__MoveMITMsg__joint_index(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__int32__Sequence * member =
    (const rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_function__MoveMITMsg__joint_index(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__int32__Sequence * member =
    (rosidl_runtime_c__int32__Sequence *)(untyped_member);
  return &member->data[index];
}

void agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__fetch_function__MoveMITMsg__joint_index(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const int32_t * item =
    ((const int32_t *)
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_const_function__MoveMITMsg__joint_index(untyped_member, index));
  int32_t * value =
    (int32_t *)(untyped_value);
  *value = *item;
}

void agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__assign_function__MoveMITMsg__joint_index(
  void * untyped_member, size_t index, const void * untyped_value)
{
  int32_t * item =
    ((int32_t *)
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_function__MoveMITMsg__joint_index(untyped_member, index));
  const int32_t * value =
    (const int32_t *)(untyped_value);
  *item = *value;
}

bool agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__resize_function__MoveMITMsg__joint_index(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__int32__Sequence * member =
    (rosidl_runtime_c__int32__Sequence *)(untyped_member);
  rosidl_runtime_c__int32__Sequence__fini(member);
  return rosidl_runtime_c__int32__Sequence__init(member, size);
}

size_t agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__size_function__MoveMITMsg__p_des(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_const_function__MoveMITMsg__p_des(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_function__MoveMITMsg__p_des(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__fetch_function__MoveMITMsg__p_des(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_const_function__MoveMITMsg__p_des(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__assign_function__MoveMITMsg__p_des(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_function__MoveMITMsg__p_des(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__resize_function__MoveMITMsg__p_des(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

size_t agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__size_function__MoveMITMsg__v_des(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_const_function__MoveMITMsg__v_des(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_function__MoveMITMsg__v_des(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__fetch_function__MoveMITMsg__v_des(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_const_function__MoveMITMsg__v_des(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__assign_function__MoveMITMsg__v_des(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_function__MoveMITMsg__v_des(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__resize_function__MoveMITMsg__v_des(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

size_t agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__size_function__MoveMITMsg__kp(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_const_function__MoveMITMsg__kp(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_function__MoveMITMsg__kp(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__fetch_function__MoveMITMsg__kp(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_const_function__MoveMITMsg__kp(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__assign_function__MoveMITMsg__kp(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_function__MoveMITMsg__kp(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__resize_function__MoveMITMsg__kp(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

size_t agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__size_function__MoveMITMsg__kd(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_const_function__MoveMITMsg__kd(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_function__MoveMITMsg__kd(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__fetch_function__MoveMITMsg__kd(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_const_function__MoveMITMsg__kd(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__assign_function__MoveMITMsg__kd(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_function__MoveMITMsg__kd(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__resize_function__MoveMITMsg__kd(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

size_t agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__size_function__MoveMITMsg__torque(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_const_function__MoveMITMsg__torque(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_function__MoveMITMsg__torque(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__fetch_function__MoveMITMsg__torque(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_const_function__MoveMITMsg__torque(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__assign_function__MoveMITMsg__torque(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_function__MoveMITMsg__torque(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__resize_function__MoveMITMsg__torque(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__MoveMITMsg_message_member_array[6] = {
  {
    "joint_index",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agx_arm_msgs__msg__MoveMITMsg, joint_index),  // bytes offset in struct
    NULL,  // default value
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__size_function__MoveMITMsg__joint_index,  // size() function pointer
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_const_function__MoveMITMsg__joint_index,  // get_const(index) function pointer
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_function__MoveMITMsg__joint_index,  // get(index) function pointer
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__fetch_function__MoveMITMsg__joint_index,  // fetch(index, &value) function pointer
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__assign_function__MoveMITMsg__joint_index,  // assign(index, value) function pointer
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__resize_function__MoveMITMsg__joint_index  // resize(index) function pointer
  },
  {
    "p_des",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agx_arm_msgs__msg__MoveMITMsg, p_des),  // bytes offset in struct
    NULL,  // default value
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__size_function__MoveMITMsg__p_des,  // size() function pointer
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_const_function__MoveMITMsg__p_des,  // get_const(index) function pointer
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_function__MoveMITMsg__p_des,  // get(index) function pointer
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__fetch_function__MoveMITMsg__p_des,  // fetch(index, &value) function pointer
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__assign_function__MoveMITMsg__p_des,  // assign(index, value) function pointer
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__resize_function__MoveMITMsg__p_des  // resize(index) function pointer
  },
  {
    "v_des",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agx_arm_msgs__msg__MoveMITMsg, v_des),  // bytes offset in struct
    NULL,  // default value
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__size_function__MoveMITMsg__v_des,  // size() function pointer
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_const_function__MoveMITMsg__v_des,  // get_const(index) function pointer
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_function__MoveMITMsg__v_des,  // get(index) function pointer
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__fetch_function__MoveMITMsg__v_des,  // fetch(index, &value) function pointer
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__assign_function__MoveMITMsg__v_des,  // assign(index, value) function pointer
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__resize_function__MoveMITMsg__v_des  // resize(index) function pointer
  },
  {
    "kp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agx_arm_msgs__msg__MoveMITMsg, kp),  // bytes offset in struct
    NULL,  // default value
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__size_function__MoveMITMsg__kp,  // size() function pointer
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_const_function__MoveMITMsg__kp,  // get_const(index) function pointer
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_function__MoveMITMsg__kp,  // get(index) function pointer
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__fetch_function__MoveMITMsg__kp,  // fetch(index, &value) function pointer
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__assign_function__MoveMITMsg__kp,  // assign(index, value) function pointer
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__resize_function__MoveMITMsg__kp  // resize(index) function pointer
  },
  {
    "kd",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agx_arm_msgs__msg__MoveMITMsg, kd),  // bytes offset in struct
    NULL,  // default value
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__size_function__MoveMITMsg__kd,  // size() function pointer
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_const_function__MoveMITMsg__kd,  // get_const(index) function pointer
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_function__MoveMITMsg__kd,  // get(index) function pointer
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__fetch_function__MoveMITMsg__kd,  // fetch(index, &value) function pointer
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__assign_function__MoveMITMsg__kd,  // assign(index, value) function pointer
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__resize_function__MoveMITMsg__kd  // resize(index) function pointer
  },
  {
    "torque",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agx_arm_msgs__msg__MoveMITMsg, torque),  // bytes offset in struct
    NULL,  // default value
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__size_function__MoveMITMsg__torque,  // size() function pointer
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_const_function__MoveMITMsg__torque,  // get_const(index) function pointer
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__get_function__MoveMITMsg__torque,  // get(index) function pointer
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__fetch_function__MoveMITMsg__torque,  // fetch(index, &value) function pointer
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__assign_function__MoveMITMsg__torque,  // assign(index, value) function pointer
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__resize_function__MoveMITMsg__torque  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__MoveMITMsg_message_members = {
  "agx_arm_msgs__msg",  // message namespace
  "MoveMITMsg",  // message name
  6,  // number of fields
  sizeof(agx_arm_msgs__msg__MoveMITMsg),
  agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__MoveMITMsg_message_member_array,  // message members
  agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__MoveMITMsg_init_function,  // function to initialize message memory (memory has to be allocated)
  agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__MoveMITMsg_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__MoveMITMsg_message_type_support_handle = {
  0,
  &agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__MoveMITMsg_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agx_arm_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agx_arm_msgs, msg, MoveMITMsg)() {
  if (!agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__MoveMITMsg_message_type_support_handle.typesupport_identifier) {
    agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__MoveMITMsg_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &agx_arm_msgs__msg__MoveMITMsg__rosidl_typesupport_introspection_c__MoveMITMsg_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
