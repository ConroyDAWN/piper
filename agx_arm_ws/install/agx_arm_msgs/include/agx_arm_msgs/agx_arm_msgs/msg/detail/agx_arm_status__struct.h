// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agx_arm_msgs:msg/AgxArmStatus.idl
// generated code does not contain a copyright notice

#ifndef AGX_ARM_MSGS__MSG__DETAIL__AGX_ARM_STATUS__STRUCT_H_
#define AGX_ARM_MSGS__MSG__DETAIL__AGX_ARM_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'joint_angle_limit'
// Member 'communication_status_joint'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/AgxArmStatus in the package agx_arm_msgs.
/**
  * Arm status feedback message
 */
typedef struct agx_arm_msgs__msg__AgxArmStatus
{
  /// Control mode
  uint8_t ctrl_mode;
  /// Arm status
  uint8_t arm_status;
  /// Mode feedback
  uint8_t mode_feedback;
  /// Teach mode status
  uint8_t teach_status;
  /// Motion status: 0=reached, 1=not reached
  uint8_t motion_status;
  /// Current trajectory point number
  uint8_t trajectory_num;
  /// Error status
  int64_t err_status;
  /// Joint angle limit flags
  rosidl_runtime_c__boolean__Sequence joint_angle_limit;
  /// Joint communication status
  rosidl_runtime_c__boolean__Sequence communication_status_joint;
} agx_arm_msgs__msg__AgxArmStatus;

// Struct for a sequence of agx_arm_msgs__msg__AgxArmStatus.
typedef struct agx_arm_msgs__msg__AgxArmStatus__Sequence
{
  agx_arm_msgs__msg__AgxArmStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agx_arm_msgs__msg__AgxArmStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGX_ARM_MSGS__MSG__DETAIL__AGX_ARM_STATUS__STRUCT_H_
