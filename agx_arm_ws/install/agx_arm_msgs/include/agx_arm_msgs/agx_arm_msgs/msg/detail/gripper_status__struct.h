// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from agx_arm_msgs:msg/GripperStatus.idl
// generated code does not contain a copyright notice

#ifndef AGX_ARM_MSGS__MSG__DETAIL__GRIPPER_STATUS__STRUCT_H_
#define AGX_ARM_MSGS__MSG__DETAIL__GRIPPER_STATUS__STRUCT_H_

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

/// Struct defined in msg/GripperStatus in the package agx_arm_msgs.
/**
  * AgxGripper status feedback message
 */
typedef struct agx_arm_msgs__msg__GripperStatus
{
  std_msgs__msg__Header header;
  /// Gripper status
  /// Current gripper opening width, unit: m
  double width;
  /// Current gripping force, unit: N
  double force;
  /// Driver status
  /// Voltage too low
  bool voltage_too_low;
  /// Motor overheating
  bool motor_overheating;
  /// Driver overcurrent
  bool driver_overcurrent;
  /// Driver overheating
  bool driver_overheating;
  /// Sensor status
  bool sensor_status;
  /// Driver error status
  bool driver_error_status;
  /// Driver enable status
  bool driver_enable_status;
  /// Homing/zero position status
  bool homing_status;
} agx_arm_msgs__msg__GripperStatus;

// Struct for a sequence of agx_arm_msgs__msg__GripperStatus.
typedef struct agx_arm_msgs__msg__GripperStatus__Sequence
{
  agx_arm_msgs__msg__GripperStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} agx_arm_msgs__msg__GripperStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AGX_ARM_MSGS__MSG__DETAIL__GRIPPER_STATUS__STRUCT_H_
