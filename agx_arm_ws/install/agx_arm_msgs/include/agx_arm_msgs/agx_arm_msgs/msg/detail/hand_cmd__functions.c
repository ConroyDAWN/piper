// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from agx_arm_msgs:msg/HandCmd.idl
// generated code does not contain a copyright notice
#include "agx_arm_msgs/msg/detail/hand_cmd__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `mode`
#include "rosidl_runtime_c/string_functions.h"

bool
agx_arm_msgs__msg__HandCmd__init(agx_arm_msgs__msg__HandCmd * msg)
{
  if (!msg) {
    return false;
  }
  // mode
  if (!rosidl_runtime_c__String__init(&msg->mode)) {
    agx_arm_msgs__msg__HandCmd__fini(msg);
    return false;
  }
  // thumb_tip
  // thumb_base
  // index_finger
  // middle_finger
  // ring_finger
  // pinky_finger
  return true;
}

void
agx_arm_msgs__msg__HandCmd__fini(agx_arm_msgs__msg__HandCmd * msg)
{
  if (!msg) {
    return;
  }
  // mode
  rosidl_runtime_c__String__fini(&msg->mode);
  // thumb_tip
  // thumb_base
  // index_finger
  // middle_finger
  // ring_finger
  // pinky_finger
}

bool
agx_arm_msgs__msg__HandCmd__are_equal(const agx_arm_msgs__msg__HandCmd * lhs, const agx_arm_msgs__msg__HandCmd * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // mode
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->mode), &(rhs->mode)))
  {
    return false;
  }
  // thumb_tip
  if (lhs->thumb_tip != rhs->thumb_tip) {
    return false;
  }
  // thumb_base
  if (lhs->thumb_base != rhs->thumb_base) {
    return false;
  }
  // index_finger
  if (lhs->index_finger != rhs->index_finger) {
    return false;
  }
  // middle_finger
  if (lhs->middle_finger != rhs->middle_finger) {
    return false;
  }
  // ring_finger
  if (lhs->ring_finger != rhs->ring_finger) {
    return false;
  }
  // pinky_finger
  if (lhs->pinky_finger != rhs->pinky_finger) {
    return false;
  }
  return true;
}

bool
agx_arm_msgs__msg__HandCmd__copy(
  const agx_arm_msgs__msg__HandCmd * input,
  agx_arm_msgs__msg__HandCmd * output)
{
  if (!input || !output) {
    return false;
  }
  // mode
  if (!rosidl_runtime_c__String__copy(
      &(input->mode), &(output->mode)))
  {
    return false;
  }
  // thumb_tip
  output->thumb_tip = input->thumb_tip;
  // thumb_base
  output->thumb_base = input->thumb_base;
  // index_finger
  output->index_finger = input->index_finger;
  // middle_finger
  output->middle_finger = input->middle_finger;
  // ring_finger
  output->ring_finger = input->ring_finger;
  // pinky_finger
  output->pinky_finger = input->pinky_finger;
  return true;
}

agx_arm_msgs__msg__HandCmd *
agx_arm_msgs__msg__HandCmd__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agx_arm_msgs__msg__HandCmd * msg = (agx_arm_msgs__msg__HandCmd *)allocator.allocate(sizeof(agx_arm_msgs__msg__HandCmd), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(agx_arm_msgs__msg__HandCmd));
  bool success = agx_arm_msgs__msg__HandCmd__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
agx_arm_msgs__msg__HandCmd__destroy(agx_arm_msgs__msg__HandCmd * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    agx_arm_msgs__msg__HandCmd__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
agx_arm_msgs__msg__HandCmd__Sequence__init(agx_arm_msgs__msg__HandCmd__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agx_arm_msgs__msg__HandCmd * data = NULL;

  if (size) {
    data = (agx_arm_msgs__msg__HandCmd *)allocator.zero_allocate(size, sizeof(agx_arm_msgs__msg__HandCmd), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = agx_arm_msgs__msg__HandCmd__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        agx_arm_msgs__msg__HandCmd__fini(&data[i - 1]);
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
agx_arm_msgs__msg__HandCmd__Sequence__fini(agx_arm_msgs__msg__HandCmd__Sequence * array)
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
      agx_arm_msgs__msg__HandCmd__fini(&array->data[i]);
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

agx_arm_msgs__msg__HandCmd__Sequence *
agx_arm_msgs__msg__HandCmd__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  agx_arm_msgs__msg__HandCmd__Sequence * array = (agx_arm_msgs__msg__HandCmd__Sequence *)allocator.allocate(sizeof(agx_arm_msgs__msg__HandCmd__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = agx_arm_msgs__msg__HandCmd__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
agx_arm_msgs__msg__HandCmd__Sequence__destroy(agx_arm_msgs__msg__HandCmd__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    agx_arm_msgs__msg__HandCmd__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
agx_arm_msgs__msg__HandCmd__Sequence__are_equal(const agx_arm_msgs__msg__HandCmd__Sequence * lhs, const agx_arm_msgs__msg__HandCmd__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!agx_arm_msgs__msg__HandCmd__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
agx_arm_msgs__msg__HandCmd__Sequence__copy(
  const agx_arm_msgs__msg__HandCmd__Sequence * input,
  agx_arm_msgs__msg__HandCmd__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(agx_arm_msgs__msg__HandCmd);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    agx_arm_msgs__msg__HandCmd * data =
      (agx_arm_msgs__msg__HandCmd *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!agx_arm_msgs__msg__HandCmd__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          agx_arm_msgs__msg__HandCmd__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!agx_arm_msgs__msg__HandCmd__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
