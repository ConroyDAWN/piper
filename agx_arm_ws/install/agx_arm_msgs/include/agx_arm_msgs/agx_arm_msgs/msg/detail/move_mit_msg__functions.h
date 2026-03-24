// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from agx_arm_msgs:msg/MoveMITMsg.idl
// generated code does not contain a copyright notice

#ifndef AGX_ARM_MSGS__MSG__DETAIL__MOVE_MIT_MSG__FUNCTIONS_H_
#define AGX_ARM_MSGS__MSG__DETAIL__MOVE_MIT_MSG__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "agx_arm_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "agx_arm_msgs/msg/detail/move_mit_msg__struct.h"

/// Initialize msg/MoveMITMsg message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * agx_arm_msgs__msg__MoveMITMsg
 * )) before or use
 * agx_arm_msgs__msg__MoveMITMsg__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_agx_arm_msgs
bool
agx_arm_msgs__msg__MoveMITMsg__init(agx_arm_msgs__msg__MoveMITMsg * msg);

/// Finalize msg/MoveMITMsg message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agx_arm_msgs
void
agx_arm_msgs__msg__MoveMITMsg__fini(agx_arm_msgs__msg__MoveMITMsg * msg);

/// Create msg/MoveMITMsg message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * agx_arm_msgs__msg__MoveMITMsg__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agx_arm_msgs
agx_arm_msgs__msg__MoveMITMsg *
agx_arm_msgs__msg__MoveMITMsg__create();

/// Destroy msg/MoveMITMsg message.
/**
 * It calls
 * agx_arm_msgs__msg__MoveMITMsg__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agx_arm_msgs
void
agx_arm_msgs__msg__MoveMITMsg__destroy(agx_arm_msgs__msg__MoveMITMsg * msg);

/// Check for msg/MoveMITMsg message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agx_arm_msgs
bool
agx_arm_msgs__msg__MoveMITMsg__are_equal(const agx_arm_msgs__msg__MoveMITMsg * lhs, const agx_arm_msgs__msg__MoveMITMsg * rhs);

/// Copy a msg/MoveMITMsg message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_agx_arm_msgs
bool
agx_arm_msgs__msg__MoveMITMsg__copy(
  const agx_arm_msgs__msg__MoveMITMsg * input,
  agx_arm_msgs__msg__MoveMITMsg * output);

/// Initialize array of msg/MoveMITMsg messages.
/**
 * It allocates the memory for the number of elements and calls
 * agx_arm_msgs__msg__MoveMITMsg__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_agx_arm_msgs
bool
agx_arm_msgs__msg__MoveMITMsg__Sequence__init(agx_arm_msgs__msg__MoveMITMsg__Sequence * array, size_t size);

/// Finalize array of msg/MoveMITMsg messages.
/**
 * It calls
 * agx_arm_msgs__msg__MoveMITMsg__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agx_arm_msgs
void
agx_arm_msgs__msg__MoveMITMsg__Sequence__fini(agx_arm_msgs__msg__MoveMITMsg__Sequence * array);

/// Create array of msg/MoveMITMsg messages.
/**
 * It allocates the memory for the array and calls
 * agx_arm_msgs__msg__MoveMITMsg__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agx_arm_msgs
agx_arm_msgs__msg__MoveMITMsg__Sequence *
agx_arm_msgs__msg__MoveMITMsg__Sequence__create(size_t size);

/// Destroy array of msg/MoveMITMsg messages.
/**
 * It calls
 * agx_arm_msgs__msg__MoveMITMsg__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agx_arm_msgs
void
agx_arm_msgs__msg__MoveMITMsg__Sequence__destroy(agx_arm_msgs__msg__MoveMITMsg__Sequence * array);

/// Check for msg/MoveMITMsg message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agx_arm_msgs
bool
agx_arm_msgs__msg__MoveMITMsg__Sequence__are_equal(const agx_arm_msgs__msg__MoveMITMsg__Sequence * lhs, const agx_arm_msgs__msg__MoveMITMsg__Sequence * rhs);

/// Copy an array of msg/MoveMITMsg messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_agx_arm_msgs
bool
agx_arm_msgs__msg__MoveMITMsg__Sequence__copy(
  const agx_arm_msgs__msg__MoveMITMsg__Sequence * input,
  agx_arm_msgs__msg__MoveMITMsg__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // AGX_ARM_MSGS__MSG__DETAIL__MOVE_MIT_MSG__FUNCTIONS_H_
