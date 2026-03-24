// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from agx_arm_msgs:msg/HandPositionTimeCmd.idl
// generated code does not contain a copyright notice
#include "agx_arm_msgs/msg/detail/hand_position_time_cmd__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
agx_arm_msgs__msg__HandPositionTimeCmd__init(agx_arm_msgs__msg__HandPositionTimeCmd * msg)
{
  if (!msg) {
    return false;
  }
  // thumb_tip_pos
  // thumb_base_pos
  // index_finger_pos
  // middle_finger_pos
  // ring_finger_pos
  // pinky_finger_pos
  // thumb_tip_time
  // thumb_base_time
  // index_finger_time
  // middle_finger_time
  // ring_finger_time
  // pinky_finger_time
  return true;
}

void
agx_arm_msgs__msg__HandPositionTimeCmd__fini(agx_arm_msgs__msg__HandPositionTimeCmd * msg)
{
  if (!msg) {
    return;
  }
  // thumb_tip_pos
  // thumb_base_pos
  // index_finger_pos
  // middle_finger_pos
  // ring_finger_pos
  // pinky_finger_pos
  // thumb_tip_time
  // thumb_base_time
  // index_finger_time
  // middle_finger_time
  // ring_finger_time
  // pinky_finger_time
}

bool
agx_arm_msgs__msg__HandPositionTimeCmd__are_equal(const agx_arm_msgs__msg__HandPositionTimeCmd * lhs, const agx_arm_msgs__msg__HandPositionTimeCmd * rhs)
{
  if (!lhs || !rhs) {
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
  // thumb_tip_time
  if (lhs->thumb_tip_time != rhs->thumb_tip_time) {
    return false;
  }
  // thumb_base_time
  if (lhs->thumb_base_time != rhs->thumb_base_time) {
    return false;
  }
  // index_finger_time
  if (lhs->index_finger_time != rhs->index_finger_time) {
    return false;
  }
  // middle_finger_time
  if (lhs->middle_finger_time != rhs->middle_finger_time) {
    return false;
  }
  // ring_finger_time
  if (lhs->ring_finger_time != rhs->ring_finger_time) {
    return false;
  }
  // pinky_finger_time
  if (lhs->pinky_finger_time != rhs->pinky_finger_time) {
    return false;
  }
  return true;
}

bool
agx_arm_msgs__msg__HandPositionTimeCmd__copy(
  const agx_arm_msgs__msg__HandPositionTimeCmd * input,
  agx_arm_msgs__msg__HandPositionTimeCmd * output)
{
  if (!input || !output) {
    return false;
  }
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
  // thumb_tip_time
  output->thumb_tip_time = input->thumb_tip_time;
  // thumb_base_time
  output->thumb_base_time = input->thumb_base_time;
  // index_finger_time
  output->index_finger_time = input->index_finger_time;
  // middle_finger_time
  output->middle_finger_time = input->middle_finger_time;
  // ring_finger_time
  output->ring_finger_time = input->ring_finger_time;
  // pinky_finger_time
  output->pinky_finger_time = input->pinky_finger_time;
  return true;
}

agx_arm_msgs__msg__HandPositionTimeCmd *
agx_arm_msgs__msg__HandPositionTimeCmd__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agx_arm_msgs__msg__HandPositionTimeCmd * msg = (agx_arm_msgs__msg__HandPositionTimeCmd *)allocator.allocate(sizeof(agx_arm_msgs__msg__HandPositionTimeCmd), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agx_arm_msgs__msg__HandPositionTimeCmd));
  bool success = agx_arm_msgs__msg__HandPositionTimeCmd__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agx_arm_msgs__msg__HandPositionTimeCmd__destroy(agx_arm_msgs__msg__HandPositionTimeCmd * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agx_arm_msgs__msg__HandPositionTimeCmd__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agx_arm_msgs__msg__HandPositionTimeCmd__Sequence__init(agx_arm_msgs__msg__HandPositionTimeCmd__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agx_arm_msgs__msg__HandPositionTimeCmd * data = NULL;

  if (size) {
    data = (agx_arm_msgs__msg__HandPositionTimeCmd *)allocator.zero_allocate(size, sizeof(agx_arm_msgs__msg__HandPositionTimeCmd), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agx_arm_msgs__msg__HandPositionTimeCmd__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agx_arm_msgs__msg__HandPositionTimeCmd__fini(&data[i - 1]);
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
agx_arm_msgs__msg__HandPositionTimeCmd__Sequence__fini(agx_arm_msgs__msg__HandPositionTimeCmd__Sequence * array)
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
      agx_arm_msgs__msg__HandPositionTimeCmd__fini(&array->data[i]);
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

agx_arm_msgs__msg__HandPositionTimeCmd__Sequence *
agx_arm_msgs__msg__HandPositionTimeCmd__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agx_arm_msgs__msg__HandPositionTimeCmd__Sequence * array = (agx_arm_msgs__msg__HandPositionTimeCmd__Sequence *)allocator.allocate(sizeof(agx_arm_msgs__msg__HandPositionTimeCmd__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agx_arm_msgs__msg__HandPositionTimeCmd__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agx_arm_msgs__msg__HandPositionTimeCmd__Sequence__destroy(agx_arm_msgs__msg__HandPositionTimeCmd__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agx_arm_msgs__msg__HandPositionTimeCmd__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agx_arm_msgs__msg__HandPositionTimeCmd__Sequence__are_equal(const agx_arm_msgs__msg__HandPositionTimeCmd__Sequence * lhs, const agx_arm_msgs__msg__HandPositionTimeCmd__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agx_arm_msgs__msg__HandPositionTimeCmd__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agx_arm_msgs__msg__HandPositionTimeCmd__Sequence__copy(
  const agx_arm_msgs__msg__HandPositionTimeCmd__Sequence * input,
  agx_arm_msgs__msg__HandPositionTimeCmd__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agx_arm_msgs__msg__HandPositionTimeCmd);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agx_arm_msgs__msg__HandPositionTimeCmd * data =
      (agx_arm_msgs__msg__HandPositionTimeCmd *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agx_arm_msgs__msg__HandPositionTimeCmd__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agx_arm_msgs__msg__HandPositionTimeCmd__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agx_arm_msgs__msg__HandPositionTimeCmd__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
