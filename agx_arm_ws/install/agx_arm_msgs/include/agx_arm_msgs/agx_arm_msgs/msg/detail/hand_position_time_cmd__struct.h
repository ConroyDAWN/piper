// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agx_arm_msgs:msg/HandPositionTimeCmd.idl
// generated code does not contain a copyright notice

#ifndef AGX_ARM_MSGS__MSG__DETAIL__HAND_POSITION_TIME_CMD__STRUCT_H_
#define AGX_ARM_MSGS__MSG__DETAIL__HAND_POSITION_TIME_CMD__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/HandPositionTimeCmd in the package agx_arm_msgs.
/**
  * Revo2 dexterous hand position/time hybrid control message
  * For position_time_ctrl(), sends position and arrival time together
 */
typedef struct agx_arm_msgs__msg__HandPositionTimeCmd
{
  /// Target positions for each finger [0, 100]
  /// Thumb tip position
  int8_t thumb_tip_pos;
  /// Thumb base position
  int8_t thumb_base_pos;
  /// Index finger position
  int8_t index_finger_pos;
  /// Middle finger position
  int8_t middle_finger_pos;
  /// Ring finger position
  int8_t ring_finger_pos;
  /// Pinky finger position
  int8_t pinky_finger_pos;
  /// Arrival time for each finger (unit: 10ms, range: [0, 255], e.g. 200 = 2 seconds)
  /// Thumb tip arrival time
  uint8_t thumb_tip_time;
  /// Thumb base arrival time
  uint8_t thumb_base_time;
  /// Index finger arrival time
  uint8_t index_finger_time;
  /// Middle finger arrival time
  uint8_t middle_finger_time;
  /// Ring finger arrival time
  uint8_t ring_finger_time;
  /// Pinky finger arrival time
  uint8_t pinky_finger_time;
} agx_arm_msgs__msg__HandPositionTimeCmd;

// Struct for a sequence of agx_arm_msgs__msg__HandPositionTimeCmd.
typedef struct agx_arm_msgs__msg__HandPositionTimeCmd__Sequence
{
  agx_arm_msgs__msg__HandPositionTimeCmd * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agx_arm_msgs__msg__HandPositionTimeCmd__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGX_ARM_MSGS__MSG__DETAIL__HAND_POSITION_TIME_CMD__STRUCT_H_
