// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agx_arm_msgs:msg/HandStatus.idl
// generated code does not contain a copyright notice

#ifndef AGX_ARM_MSGS__MSG__DETAIL__HAND_STATUS__STRUCT_H_
#define AGX_ARM_MSGS__MSG__DETAIL__HAND_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"

/// Struct defined in msg/HandStatus in the package agx_arm_msgs.
/**
  * Revo2 dexterous hand status feedback message
 */
typedef struct agx_arm_msgs__msg__HandStatus
{
  std_msgs__msg__Header header;
  /// Hand type flag: 1=left hand, 2=right hand
  uint8_t left_or_right;
  /// Finger positions [0, 100]
  /// Thumb tip position
  uint8_t thumb_tip_pos;
  /// Thumb base position
  uint8_t thumb_base_pos;
  /// Index finger position
  uint8_t index_finger_pos;
  /// Middle finger position
  uint8_t middle_finger_pos;
  /// Ring finger position
  uint8_t ring_finger_pos;
  /// Pinky finger position
  uint8_t pinky_finger_pos;
  /// Finger motor status: 0=idle, 1=running, 2=blocked
  /// Thumb tip motor status
  uint8_t thumb_tip_status;
  /// Thumb base motor status
  uint8_t thumb_base_status;
  /// Index finger motor status
  uint8_t index_finger_status;
  /// Middle finger motor status
  uint8_t middle_finger_status;
  /// Ring finger motor status
  uint8_t ring_finger_status;
  /// Pinky finger motor status
  uint8_t pinky_finger_status;
} agx_arm_msgs__msg__HandStatus;

// Struct for a sequence of agx_arm_msgs__msg__HandStatus.
typedef struct agx_arm_msgs__msg__HandStatus__Sequence
{
  agx_arm_msgs__msg__HandStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agx_arm_msgs__msg__HandStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGX_ARM_MSGS__MSG__DETAIL__HAND_STATUS__STRUCT_H_
