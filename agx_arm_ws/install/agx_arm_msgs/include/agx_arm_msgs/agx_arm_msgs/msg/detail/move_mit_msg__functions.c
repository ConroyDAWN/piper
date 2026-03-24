// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from agx_arm_msgs:msg/MoveMITMsg.idl
// generated code does not contain a copyright notice
#include "agx_arm_msgs/msg/detail/move_mit_msg__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `joint_index`
// Member `p_des`
// Member `v_des`
// Member `kp`
// Member `kd`
// Member `torque`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
agx_arm_msgs__msg__MoveMITMsg__init(agx_arm_msgs__msg__MoveMITMsg * msg)
{
  if (!msg) {
    return false;
  }
  // joint_index
  if (!rosidl_runtime_c__int32__Sequence__init(&msg->joint_index, 0)) {
    agx_arm_msgs__msg__MoveMITMsg__fini(msg);
    return false;
  }
  // p_des
  if (!rosidl_runtime_c__double__Sequence__init(&msg->p_des, 0)) {
    agx_arm_msgs__msg__MoveMITMsg__fini(msg);
    return false;
  }
  // v_des
  if (!rosidl_runtime_c__double__Sequence__init(&msg->v_des, 0)) {
    agx_arm_msgs__msg__MoveMITMsg__fini(msg);
    return false;
  }
  // kp
  if (!rosidl_runtime_c__double__Sequence__init(&msg->kp, 0)) {
    agx_arm_msgs__msg__MoveMITMsg__fini(msg);
    return false;
  }
  // kd
  if (!rosidl_runtime_c__double__Sequence__init(&msg->kd, 0)) {
    agx_arm_msgs__msg__MoveMITMsg__fini(msg);
    return false;
  }
  // torque
  if (!rosidl_runtime_c__double__Sequence__init(&msg->torque, 0)) {
    agx_arm_msgs__msg__MoveMITMsg__fini(msg);
    return false;
  }
  return true;
}

void
agx_arm_msgs__msg__MoveMITMsg__fini(agx_arm_msgs__msg__MoveMITMsg * msg)
{
  if (!msg) {
    return;
  }
  // joint_index
  rosidl_runtime_c__int32__Sequence__fini(&msg->joint_index);
  // p_des
  rosidl_runtime_c__double__Sequence__fini(&msg->p_des);
  // v_des
  rosidl_runtime_c__double__Sequence__fini(&msg->v_des);
  // kp
  rosidl_runtime_c__double__Sequence__fini(&msg->kp);
  // kd
  rosidl_runtime_c__double__Sequence__fini(&msg->kd);
  // torque
  rosidl_runtime_c__double__Sequence__fini(&msg->torque);
}

bool
agx_arm_msgs__msg__MoveMITMsg__are_equal(const agx_arm_msgs__msg__MoveMITMsg * lhs, const agx_arm_msgs__msg__MoveMITMsg * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // joint_index
  if (!rosidl_runtime_c__int32__Sequence__are_equal(
      &(lhs->joint_index), &(rhs->joint_index)))
  {
    return false;
  }
  // p_des
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->p_des), &(rhs->p_des)))
  {
    return false;
  }
  // v_des
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->v_des), &(rhs->v_des)))
  {
    return false;
  }
  // kp
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->kp), &(rhs->kp)))
  {
    return false;
  }
  // kd
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->kd), &(rhs->kd)))
  {
    return false;
  }
  // torque
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->torque), &(rhs->torque)))
  {
    return false;
  }
  return true;
}

bool
agx_arm_msgs__msg__MoveMITMsg__copy(
  const agx_arm_msgs__msg__MoveMITMsg * input,
  agx_arm_msgs__msg__MoveMITMsg * output)
{
  if (!input || !output) {
    return false;
  }
  // joint_index
  if (!rosidl_runtime_c__int32__Sequence__copy(
      &(input->joint_index), &(output->joint_index)))
  {
    return false;
  }
  // p_des
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->p_des), &(output->p_des)))
  {
    return false;
  }
  // v_des
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->v_des), &(output->v_des)))
  {
    return false;
  }
  // kp
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->kp), &(output->kp)))
  {
    return false;
  }
  // kd
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->kd), &(output->kd)))
  {
    return false;
  }
  // torque
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->torque), &(output->torque)))
  {
    return false;
  }
  return true;
}

agx_arm_msgs__msg__MoveMITMsg *
agx_arm_msgs__msg__MoveMITMsg__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agx_arm_msgs__msg__MoveMITMsg * msg = (agx_arm_msgs__msg__MoveMITMsg *)allocator.allocate(sizeof(agx_arm_msgs__msg__MoveMITMsg), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agx_arm_msgs__msg__MoveMITMsg));
  bool success = agx_arm_msgs__msg__MoveMITMsg__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agx_arm_msgs__msg__MoveMITMsg__destroy(agx_arm_msgs__msg__MoveMITMsg * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agx_arm_msgs__msg__MoveMITMsg__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agx_arm_msgs__msg__MoveMITMsg__Sequence__init(agx_arm_msgs__msg__MoveMITMsg__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agx_arm_msgs__msg__MoveMITMsg * data = NULL;

  if (size) {
    data = (agx_arm_msgs__msg__MoveMITMsg *)allocator.zero_allocate(size, sizeof(agx_arm_msgs__msg__MoveMITMsg), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agx_arm_msgs__msg__MoveMITMsg__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agx_arm_msgs__msg__MoveMITMsg__fini(&data[i - 1]);
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
agx_arm_msgs__msg__MoveMITMsg__Sequence__fini(agx_arm_msgs__msg__MoveMITMsg__Sequence * array)
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
      agx_arm_msgs__msg__MoveMITMsg__fini(&array->data[i]);
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

agx_arm_msgs__msg__MoveMITMsg__Sequence *
agx_arm_msgs__msg__MoveMITMsg__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agx_arm_msgs__msg__MoveMITMsg__Sequence * array = (agx_arm_msgs__msg__MoveMITMsg__Sequence *)allocator.allocate(sizeof(agx_arm_msgs__msg__MoveMITMsg__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agx_arm_msgs__msg__MoveMITMsg__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agx_arm_msgs__msg__MoveMITMsg__Sequence__destroy(agx_arm_msgs__msg__MoveMITMsg__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agx_arm_msgs__msg__MoveMITMsg__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agx_arm_msgs__msg__MoveMITMsg__Sequence__are_equal(const agx_arm_msgs__msg__MoveMITMsg__Sequence * lhs, const agx_arm_msgs__msg__MoveMITMsg__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agx_arm_msgs__msg__MoveMITMsg__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agx_arm_msgs__msg__MoveMITMsg__Sequence__copy(
  const agx_arm_msgs__msg__MoveMITMsg__Sequence * input,
  agx_arm_msgs__msg__MoveMITMsg__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agx_arm_msgs__msg__MoveMITMsg);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agx_arm_msgs__msg__MoveMITMsg * data =
      (agx_arm_msgs__msg__MoveMITMsg *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agx_arm_msgs__msg__MoveMITMsg__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agx_arm_msgs__msg__MoveMITMsg__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agx_arm_msgs__msg__MoveMITMsg__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
