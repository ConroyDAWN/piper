// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from agx_arm_msgs:msg/GripperStatus.idl
// generated code does not contain a copyright notice
#include "agx_arm_msgs/msg/detail/gripper_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
agx_arm_msgs__msg__GripperStatus__init(agx_arm_msgs__msg__GripperStatus * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    agx_arm_msgs__msg__GripperStatus__fini(msg);
    return false;
  }
  // width
  // force
  // voltage_too_low
  // motor_overheating
  // driver_overcurrent
  // driver_overheating
  // sensor_status
  // driver_error_status
  // driver_enable_status
  // homing_status
  return true;
}

void
agx_arm_msgs__msg__GripperStatus__fini(agx_arm_msgs__msg__GripperStatus * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // width
  // force
  // voltage_too_low
  // motor_overheating
  // driver_overcurrent
  // driver_overheating
  // sensor_status
  // driver_error_status
  // driver_enable_status
  // homing_status
}

bool
agx_arm_msgs__msg__GripperStatus__are_equal(const agx_arm_msgs__msg__GripperStatus * lhs, const agx_arm_msgs__msg__GripperStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // width
  if (lhs->width != rhs->width) {
    return false;
  }
  // force
  if (lhs->force != rhs->force) {
    return false;
  }
  // voltage_too_low
  if (lhs->voltage_too_low != rhs->voltage_too_low) {
    return false;
  }
  // motor_overheating
  if (lhs->motor_overheating != rhs->motor_overheating) {
    return false;
  }
  // driver_overcurrent
  if (lhs->driver_overcurrent != rhs->driver_overcurrent) {
    return false;
  }
  // driver_overheating
  if (lhs->driver_overheating != rhs->driver_overheating) {
    return false;
  }
  // sensor_status
  if (lhs->sensor_status != rhs->sensor_status) {
    return false;
  }
  // driver_error_status
  if (lhs->driver_error_status != rhs->driver_error_status) {
    return false;
  }
  // driver_enable_status
  if (lhs->driver_enable_status != rhs->driver_enable_status) {
    return false;
  }
  // homing_status
  if (lhs->homing_status != rhs->homing_status) {
    return false;
  }
  return true;
}

bool
agx_arm_msgs__msg__GripperStatus__copy(
  const agx_arm_msgs__msg__GripperStatus * input,
  agx_arm_msgs__msg__GripperStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // width
  output->width = input->width;
  // force
  output->force = input->force;
  // voltage_too_low
  output->voltage_too_low = input->voltage_too_low;
  // motor_overheating
  output->motor_overheating = input->motor_overheating;
  // driver_overcurrent
  output->driver_overcurrent = input->driver_overcurrent;
  // driver_overheating
  output->driver_overheating = input->driver_overheating;
  // sensor_status
  output->sensor_status = input->sensor_status;
  // driver_error_status
  output->driver_error_status = input->driver_error_status;
  // driver_enable_status
  output->driver_enable_status = input->driver_enable_status;
  // homing_status
  output->homing_status = input->homing_status;
  return true;
}

agx_arm_msgs__msg__GripperStatus *
agx_arm_msgs__msg__GripperStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agx_arm_msgs__msg__GripperStatus * msg = (agx_arm_msgs__msg__GripperStatus *)allocator.allocate(sizeof(agx_arm_msgs__msg__GripperStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agx_arm_msgs__msg__GripperStatus));
  bool success = agx_arm_msgs__msg__GripperStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agx_arm_msgs__msg__GripperStatus__destroy(agx_arm_msgs__msg__GripperStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agx_arm_msgs__msg__GripperStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agx_arm_msgs__msg__GripperStatus__Sequence__init(agx_arm_msgs__msg__GripperStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agx_arm_msgs__msg__GripperStatus * data = NULL;

  if (size) {
    data = (agx_arm_msgs__msg__GripperStatus *)allocator.zero_allocate(size, sizeof(agx_arm_msgs__msg__GripperStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agx_arm_msgs__msg__GripperStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agx_arm_msgs__msg__GripperStatus__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
agx_arm_msgs__msg__GripperStatus__Sequence__fini(agx_arm_msgs__msg__GripperStatus__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      agx_arm_msgs__msg__GripperStatus__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

agx_arm_msgs__msg__GripperStatus__Sequence *
agx_arm_msgs__msg__GripperStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agx_arm_msgs__msg__GripperStatus__Sequence * array = (agx_arm_msgs__msg__GripperStatus__Sequence *)allocator.allocate(sizeof(agx_arm_msgs__msg__GripperStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agx_arm_msgs__msg__GripperStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agx_arm_msgs__msg__GripperStatus__Sequence__destroy(agx_arm_msgs__msg__GripperStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agx_arm_msgs__msg__GripperStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agx_arm_msgs__msg__GripperStatus__Sequence__are_equal(const agx_arm_msgs__msg__GripperStatus__Sequence * lhs, const agx_arm_msgs__msg__GripperStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agx_arm_msgs__msg__GripperStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agx_arm_msgs__msg__GripperStatus__Sequence__copy(
  const agx_arm_msgs__msg__GripperStatus__Sequence * input,
  agx_arm_msgs__msg__GripperStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agx_arm_msgs__msg__GripperStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agx_arm_msgs__msg__GripperStatus * data =
      (agx_arm_msgs__msg__GripperStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agx_arm_msgs__msg__GripperStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agx_arm_msgs__msg__GripperStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agx_arm_msgs__msg__GripperStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
