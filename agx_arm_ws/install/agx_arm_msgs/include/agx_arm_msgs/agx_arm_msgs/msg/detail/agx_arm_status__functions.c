// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from agx_arm_msgs:msg/AgxArmStatus.idl
// generated code does not contain a copyright notice
#include "agx_arm_msgs/msg/detail/agx_arm_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `joint_angle_limit`
// Member `communication_status_joint`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
agx_arm_msgs__msg__AgxArmStatus__init(agx_arm_msgs__msg__AgxArmStatus * msg)
{
  if (!msg) {
    return false;
  }
  // ctrl_mode
  // arm_status
  // mode_feedback
  // teach_status
  // motion_status
  // trajectory_num
  // err_status
  // joint_angle_limit
  if (!rosidl_runtime_c__boolean__Sequence__init(&msg->joint_angle_limit, 0)) {
    agx_arm_msgs__msg__AgxArmStatus__fini(msg);
    return false;
  }
  // communication_status_joint
  if (!rosidl_runtime_c__boolean__Sequence__init(&msg->communication_status_joint, 0)) {
    agx_arm_msgs__msg__AgxArmStatus__fini(msg);
    return false;
  }
  return true;
}

void
agx_arm_msgs__msg__AgxArmStatus__fini(agx_arm_msgs__msg__AgxArmStatus * msg)
{
  if (!msg) {
    return;
  }
  // ctrl_mode
  // arm_status
  // mode_feedback
  // teach_status
  // motion_status
  // trajectory_num
  // err_status
  // joint_angle_limit
  rosidl_runtime_c__boolean__Sequence__fini(&msg->joint_angle_limit);
  // communication_status_joint
  rosidl_runtime_c__boolean__Sequence__fini(&msg->communication_status_joint);
}

bool
agx_arm_msgs__msg__AgxArmStatus__are_equal(const agx_arm_msgs__msg__AgxArmStatus * lhs, const agx_arm_msgs__msg__AgxArmStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // ctrl_mode
  if (lhs->ctrl_mode != rhs->ctrl_mode) {
    return false;
  }
  // arm_status
  if (lhs->arm_status != rhs->arm_status) {
    return false;
  }
  // mode_feedback
  if (lhs->mode_feedback != rhs->mode_feedback) {
    return false;
  }
  // teach_status
  if (lhs->teach_status != rhs->teach_status) {
    return false;
  }
  // motion_status
  if (lhs->motion_status != rhs->motion_status) {
    return false;
  }
  // trajectory_num
  if (lhs->trajectory_num != rhs->trajectory_num) {
    return false;
  }
  // err_status
  if (lhs->err_status != rhs->err_status) {
    return false;
  }
  // joint_angle_limit
  if (!rosidl_runtime_c__boolean__Sequence__are_equal(
      &(lhs->joint_angle_limit), &(rhs->joint_angle_limit)))
  {
    return false;
  }
  // communication_status_joint
  if (!rosidl_runtime_c__boolean__Sequence__are_equal(
      &(lhs->communication_status_joint), &(rhs->communication_status_joint)))
  {
    return false;
  }
  return true;
}

bool
agx_arm_msgs__msg__AgxArmStatus__copy(
  const agx_arm_msgs__msg__AgxArmStatus * input,
  agx_arm_msgs__msg__AgxArmStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // ctrl_mode
  output->ctrl_mode = input->ctrl_mode;
  // arm_status
  output->arm_status = input->arm_status;
  // mode_feedback
  output->mode_feedback = input->mode_feedback;
  // teach_status
  output->teach_status = input->teach_status;
  // motion_status
  output->motion_status = input->motion_status;
  // trajectory_num
  output->trajectory_num = input->trajectory_num;
  // err_status
  output->err_status = input->err_status;
  // joint_angle_limit
  if (!rosidl_runtime_c__boolean__Sequence__copy(
      &(input->joint_angle_limit), &(output->joint_angle_limit)))
  {
    return false;
  }
  // communication_status_joint
  if (!rosidl_runtime_c__boolean__Sequence__copy(
      &(input->communication_status_joint), &(output->communication_status_joint)))
  {
    return false;
  }
  return true;
}

agx_arm_msgs__msg__AgxArmStatus *
agx_arm_msgs__msg__AgxArmStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agx_arm_msgs__msg__AgxArmStatus * msg = (agx_arm_msgs__msg__AgxArmStatus *)allocator.allocate(sizeof(agx_arm_msgs__msg__AgxArmStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agx_arm_msgs__msg__AgxArmStatus));
  bool success = agx_arm_msgs__msg__AgxArmStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agx_arm_msgs__msg__AgxArmStatus__destroy(agx_arm_msgs__msg__AgxArmStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agx_arm_msgs__msg__AgxArmStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agx_arm_msgs__msg__AgxArmStatus__Sequence__init(agx_arm_msgs__msg__AgxArmStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agx_arm_msgs__msg__AgxArmStatus * data = NULL;

  if (size) {
    data = (agx_arm_msgs__msg__AgxArmStatus *)allocator.zero_allocate(size, sizeof(agx_arm_msgs__msg__AgxArmStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agx_arm_msgs__msg__AgxArmStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agx_arm_msgs__msg__AgxArmStatus__fini(&data[i - 1]);
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
agx_arm_msgs__msg__AgxArmStatus__Sequence__fini(agx_arm_msgs__msg__AgxArmStatus__Sequence * array)
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
      agx_arm_msgs__msg__AgxArmStatus__fini(&array->data[i]);
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

agx_arm_msgs__msg__AgxArmStatus__Sequence *
agx_arm_msgs__msg__AgxArmStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agx_arm_msgs__msg__AgxArmStatus__Sequence * array = (agx_arm_msgs__msg__AgxArmStatus__Sequence *)allocator.allocate(sizeof(agx_arm_msgs__msg__AgxArmStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agx_arm_msgs__msg__AgxArmStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agx_arm_msgs__msg__AgxArmStatus__Sequence__destroy(agx_arm_msgs__msg__AgxArmStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agx_arm_msgs__msg__AgxArmStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agx_arm_msgs__msg__AgxArmStatus__Sequence__are_equal(const agx_arm_msgs__msg__AgxArmStatus__Sequence * lhs, const agx_arm_msgs__msg__AgxArmStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agx_arm_msgs__msg__AgxArmStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agx_arm_msgs__msg__AgxArmStatus__Sequence__copy(
  const agx_arm_msgs__msg__AgxArmStatus__Sequence * input,
  agx_arm_msgs__msg__AgxArmStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agx_arm_msgs__msg__AgxArmStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agx_arm_msgs__msg__AgxArmStatus * data =
      (agx_arm_msgs__msg__AgxArmStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agx_arm_msgs__msg__AgxArmStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agx_arm_msgs__msg__AgxArmStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agx_arm_msgs__msg__AgxArmStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
