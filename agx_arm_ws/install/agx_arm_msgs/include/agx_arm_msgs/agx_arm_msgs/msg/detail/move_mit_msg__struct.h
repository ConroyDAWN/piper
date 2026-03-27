// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agx_arm_msgs:msg/MoveMITMsg.idl
// generated code does not contain a copyright notice

#ifndef AGX_ARM_MSGS__MSG__DETAIL__MOVE_MIT_MSG__STRUCT_H_
#define AGX_ARM_MSGS__MSG__DETAIL__MOVE_MIT_MSG__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'joint_index'
// Member 'p_des'
// Member 'v_des'
// Member 'kp'
// Member 'kd'
// Member 'torque'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/MoveMITMsg in the package agx_arm_msgs.
/**
  * This message contains the joint position, velocity, and torque control values for a single joint.
 */
typedef struct agx_arm_msgs__msg__MoveMITMsg
{
  /// Index of the joint to control
  rosidl_runtime_c__int32__Sequence joint_index;
  /// Desired joint position in radians
  rosidl_runtime_c__double__Sequence p_des;
  /// Desired joint velocity in radians/second
  rosidl_runtime_c__double__Sequence v_des;
  /// Position gain
  rosidl_runtime_c__double__Sequence kp;
  /// Velocity gain
  rosidl_runtime_c__double__Sequence kd;
  /// Desired joint torque in N/m
  rosidl_runtime_c__double__Sequence torque;
} agx_arm_msgs__msg__MoveMITMsg;

// Struct for a sequence of agx_arm_msgs__msg__MoveMITMsg.
typedef struct agx_arm_msgs__msg__MoveMITMsg__Sequence
{
  agx_arm_msgs__msg__MoveMITMsg * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agx_arm_msgs__msg__MoveMITMsg__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGX_ARM_MSGS__MSG__DETAIL__MOVE_MIT_MSG__STRUCT_H_
