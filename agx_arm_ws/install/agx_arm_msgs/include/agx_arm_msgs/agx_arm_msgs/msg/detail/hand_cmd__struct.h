// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agx_arm_msgs:msg/HandCmd.idl
// generated code does not contain a copyright notice

#ifndef AGX_ARM_MSGS__MSG__DETAIL__HAND_CMD__STRUCT_H_
#define AGX_ARM_MSGS__MSG__DETAIL__HAND_CMD__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'mode'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/HandCmd in the package agx_arm_msgs.
/**
  * Revo2 dexterous hand control command message
 */
typedef struct agx_arm_msgs__msg__HandCmd
{
  /// Control mode: position/speed/current
  rosidl_runtime_c__String mode;
  /// Target values for each finger
  /// position mode: [0, 100]
  /// speed mode: [-100, 100]
  /// current mode: [-100, 100]
  /// Thumb tip
  int8_t thumb_tip;
  /// Thumb base
  int8_t thumb_base;
  /// Index finger
  int8_t index_finger;
  /// Middle finger
  int8_t middle_finger;
  /// Ring finger
  int8_t ring_finger;
  /// Pinky finger
  int8_t pinky_finger;
} agx_arm_msgs__msg__HandCmd;

// Struct for a sequence of agx_arm_msgs__msg__HandCmd.
typedef struct agx_arm_msgs__msg__HandCmd__Sequence
{
  agx_arm_msgs__msg__HandCmd * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agx_arm_msgs__msg__HandCmd__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGX_ARM_MSGS__MSG__DETAIL__HAND_CMD__STRUCT_H_
