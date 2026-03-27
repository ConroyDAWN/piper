// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from agx_arm_msgs:msg/HandStatus.idl
// generated code does not contain a copyright notice
#include "agx_arm_msgs/msg/detail/hand_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
agx_arm_msgs__msg__HandStatus__init(agx_arm_msgs__msg__HandStatus * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    agx_arm_msgs__msg__HandStatus__fini(msg);
    return false;
  }
  // left_or_right
  // thumb_tip_pos
  // thumb_base_pos
  // index_finger_pos
  // middle_finger_pos
  // ring_finger_pos
  // pinky_finger_pos
  // thumb_tip_status
  // thumb_base_status
  // index_finger_status
  // middle_finger_status
  // ring_finger_status
  // pinky_finger_status
  return true;
}

void
agx_arm_msgs__msg__HandStatus__fini(agx_arm_msgs__msg__HandStatus * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // left_or_right
  // thumb_tip_pos
  // thumb_base_pos
  // index_finger_pos
  // middle_finger_pos
  // ring_finger_pos
  // pinky_finger_pos
  // thumb_tip_status
  // thumb_base_status
  // index_finger_status
  // middle_finger_status
  // ring_finger_status
  // pinky_finger_status
}

bool
agx_arm_msgs__msg__HandStatus__are_equal(const agx_arm_msgs__msg__HandStatus * lhs, const agx_arm_msgs__msg__HandStatus * rhs)
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
  // left_or_right
  if (lhs->left_or_right != rhs->left_or_right) {
    return false;
  }
  // thumb_tip_pos
  if (lhs->thumb_tip_pos != rhs->thumb_tip_pos) {
    return false;
  }
  // thumb_base_pos
  if (lhs->thumb_base_pos != rhs->thumb_base_pos) {
    return false;
  }
  // index_finger_pos
  if (lhs->index_finger_pos != rhs->index_finger_pos) {
    return false;
  }
  // middle_finger_pos
  if (lhs->middle_finger_pos != rhs->middle_finger_pos) {
    return false;
  }
  // ring_finger_pos
  if (lhs->ring_finger_pos != rhs->ring_finger_pos) {
    return false;
  }
  // pinky_finger_pos
  if (lhs->pinky_finger_pos != rhs->pinky_finger_pos) {
    return false;
  }
  // thumb_tip_status
  if (lhs->thumb_tip_status != rhs->thumb_tip_status) {
    return false;
  }
  // thumb_base_status
  if (lhs->thumb_base_status != rhs->thumb_base_status) {
    return false;
  }
  // index_finger_status
  if (lhs->index_finger_status != rhs->index_finger_status) {
    return false;
  }
  // middle_finger_status
  if (lhs->middle_finger_status != rhs->middle_finger_status) {
    return false;
  }
  // ring_finger_status
  if (lhs->ring_finger_status != rhs->ring_finger_status) {
    return false;
  }
  // pinky_finger_status
  if (lhs->pinky_finger_status != rhs->pinky_finger_status) {
    return false;
  }
  return true;
}

bool
agx_arm_msgs__msg__HandStatus__copy(
  const agx_arm_msgs__msg__HandStatus * input,
  agx_arm_msgs__msg__HandStatus * output)
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
  // left_or_right
  output->left_or_right = input->left_or_right;
  // thumb_tip_pos
  output->thumb_tip_pos = input->thumb_tip_pos;
  // thumb_base_pos
  output->thumb_base_pos = input->thumb_base_pos;
  // index_finger_pos
  output->index_finger_pos = input->index_finger_pos;
  // middle_finger_pos
  output->middle_finger_pos = input->middle_finger_pos;
  // ring_finger_pos
  output->ring_finger_pos = input->ring_finger_pos;
  // pinky_finger_pos
  output->pinky_finger_pos = input->pinky_finger_pos;
  // thumb_tip_status
  output->thumb_tip_status = input->thumb_tip_status;
  // thumb_base_status
  output->thumb_base_status = input->thumb_base_status;
  // index_finger_status
  output->index_finger_status = input->index_finger_status;
  // middle_finger_status
  output->middle_finger_status = input->middle_finger_status;
  // ring_finger_status
  output->ring_finger_status = input->ring_finger_status;
  // pinky_finger_status
  output->pinky_finger_status = input->pinky_finger_status;
  return true;
}

agx_arm_msgs__msg__HandStatus *
agx_arm_msgs__msg__HandStatus__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agx_arm_msgs__msg__HandStatus * msg = (agx_arm_msgs__msg__HandStatus *)allocator.allocate(sizeof(agx_arm_msgs__msg__HandStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agx_arm_msgs__msg__HandStatus));
  bool success = agx_arm_msgs__msg__HandStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agx_arm_msgs__msg__HandStatus__destroy(agx_arm_msgs__msg__HandStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agx_arm_msgs__msg__HandStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agx_arm_msgs__msg__HandStatus__Sequence__init(agx_arm_msgs__msg__HandStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agx_arm_msgs__msg__HandStatus * data = NULL;

  if (size) {
    data = (agx_arm_msgs__msg__HandStatus *)allocator.zero_allocate(size, sizeof(agx_arm_msgs__msg__HandStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agx_arm_msgs__msg__HandStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agx_arm_msgs__msg__HandStatus__fini(&data[i - 1]);
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
agx_arm_msgs__msg__HandStatus__Sequence__fini(agx_arm_msgs__msg__HandStatus__Sequence * array)
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
      agx_arm_msgs__msg__HandStatus__fini(&array->data[i]);
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

agx_arm_msgs__msg__HandStatus__Sequence *
agx_arm_msgs__msg__HandStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agx_arm_msgs__msg__HandStatus__Sequence * array = (agx_arm_msgs__msg__HandStatus__Sequence *)allocator.allocate(sizeof(agx_arm_msgs__msg__HandStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agx_arm_msgs__msg__HandStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agx_arm_msgs__msg__HandStatus__Sequence__destroy(agx_arm_msgs__msg__HandStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agx_arm_msgs__msg__HandStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agx_arm_msgs__msg__HandStatus__Sequence__are_equal(const agx_arm_msgs__msg__HandStatus__Sequence * lhs, const agx_arm_msgs__msg__HandStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agx_arm_msgs__msg__HandStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agx_arm_msgs__msg__HandStatus__Sequence__copy(
  const agx_arm_msgs__msg__HandStatus__Sequence * input,
  agx_arm_msgs__msg__HandStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agx_arm_msgs__msg__HandStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agx_arm_msgs__msg__HandStatus * data =
      (agx_arm_msgs__msg__HandStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agx_arm_msgs__msg__HandStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agx_arm_msgs__msg__HandStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agx_arm_msgs__msg__HandStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
