// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from agx_arm_msgs:msg/HandStatus.idl
// generated code does not contain a copyright notice

#ifndef AGX_ARM_MSGS__MSG__DETAIL__HAND_STATUS__FUNCTIONS_H_
#define AGX_ARM_MSGS__MSG__DETAIL__HAND_STATUS__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "agx_arm_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "agx_arm_msgs/msg/detail/hand_status__struct.h"

/// Initialize msg/HandStatus message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * agx_arm_msgs__msg__HandStatus
 * )) before or use
 * agx_arm_msgs__msg__HandStatus__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_agx_arm_msgs
bool
agx_arm_msgs__msg__HandStatus__init(agx_arm_msgs__msg__HandStatus * msg);

/// Finalize msg/HandStatus message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agx_arm_msgs
void
agx_arm_msgs__msg__HandStatus__fini(agx_arm_msgs__msg__HandStatus * msg);

/// Create msg/HandStatus message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * agx_arm_msgs__msg__HandStatus__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agx_arm_msgs
agx_arm_msgs__msg__HandStatus *
agx_arm_msgs__msg__HandStatus__create();

/// Destroy msg/HandStatus message.
/**
 * It calls
 * agx_arm_msgs__msg__HandStatus__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agx_arm_msgs
void
agx_arm_msgs__msg__HandStatus__destroy(agx_arm_msgs__msg__HandStatus * msg);

/// Check for msg/HandStatus message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agx_arm_msgs
bool
agx_arm_msgs__msg__HandStatus__are_equal(const agx_arm_msgs__msg__HandStatus * lhs, const agx_arm_msgs__msg__HandStatus * rhs);

/// Copy a msg/HandStatus message.
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
agx_arm_msgs__msg__HandStatus__copy(
  const agx_arm_msgs__msg__HandStatus * input,
  agx_arm_msgs__msg__HandStatus * output);

/// Initialize array of msg/HandStatus messages.
/**
 * It allocates the memory for the number of elements and calls
 * agx_arm_msgs__msg__HandStatus__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_agx_arm_msgs
bool
agx_arm_msgs__msg__HandStatus__Sequence__init(agx_arm_msgs__msg__HandStatus__Sequence * array, size_t size);

/// Finalize array of msg/HandStatus messages.
/**
 * It calls
 * agx_arm_msgs__msg__HandStatus__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agx_arm_msgs
void
agx_arm_msgs__msg__HandStatus__Sequence__fini(agx_arm_msgs__msg__HandStatus__Sequence * array);

/// Create array of msg/HandStatus messages.
/**
 * It allocates the memory for the array and calls
 * agx_arm_msgs__msg__HandStatus__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_agx_arm_msgs
agx_arm_msgs__msg__HandStatus__Sequence *
agx_arm_msgs__msg__HandStatus__Sequence__create(size_t size);

/// Destroy array of msg/HandStatus messages.
/**
 * It calls
 * agx_arm_msgs__msg__HandStatus__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_agx_arm_msgs
void
agx_arm_msgs__msg__HandStatus__Sequence__destroy(agx_arm_msgs__msg__HandStatus__Sequence * array);

/// Check for msg/HandStatus message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_agx_arm_msgs
bool
agx_arm_msgs__msg__HandStatus__Sequence__are_equal(const agx_arm_msgs__msg__HandStatus__Sequence * lhs, const agx_arm_msgs__msg__HandStatus__Sequence * rhs);

/// Copy an array of msg/HandStatus messages.
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
agx_arm_msgs__msg__HandStatus__Sequence__copy(
  const agx_arm_msgs__msg__HandStatus__Sequence * input,
  agx_arm_msgs__msg__HandStatus__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // AGX_ARM_MSGS__MSG__DETAIL__HAND_STATUS__FUNCTIONS_H_
