// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from agx_arm_msgs:msg/HandCmd.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "agx_arm_msgs/msg/detail/hand_cmd__rosidl_typesupport_introspection_c.h"
#include "agx_arm_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "agx_arm_msgs/msg/detail/hand_cmd__functions.h"
#include "agx_arm_msgs/msg/detail/hand_cmd__struct.h"


// Include directives for member types
// Member `mode`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void agx_arm_msgs__msg__HandCmd__rosidl_typesupport_introspection_c__HandCmd_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  agx_arm_msgs__msg__HandCmd__init(message_memory);
}

void agx_arm_msgs__msg__HandCmd__rosidl_typesupport_introspection_c__HandCmd_fini_function(void * message_memory)
{
  agx_arm_msgs__msg__HandCmd__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember agx_arm_msgs__msg__HandCmd__rosidl_typesupport_introspection_c__HandCmd_message_member_array[7] = {
  {
    "mode",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agx_arm_msgs__msg__HandCmd, mode),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "thumb_tip",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agx_arm_msgs__msg__HandCmd, thumb_tip),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "thumb_base",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agx_arm_msgs__msg__HandCmd, thumb_base),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "index_finger",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agx_arm_msgs__msg__HandCmd, index_finger),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "middle_finger",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agx_arm_msgs__msg__HandCmd, middle_finger),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "ring_finger",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agx_arm_msgs__msg__HandCmd, ring_finger),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "pinky_finger",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(agx_arm_msgs__msg__HandCmd, pinky_finger),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers agx_arm_msgs__msg__HandCmd__rosidl_typesupport_introspection_c__HandCmd_message_members = {
  "agx_arm_msgs__msg",  // message namespace
  "HandCmd",  // message name
  7,  // number of fields
  sizeof(agx_arm_msgs__msg__HandCmd),
  agx_arm_msgs__msg__HandCmd__rosidl_typesupport_introspection_c__HandCmd_message_member_array,  // message members
  agx_arm_msgs__msg__HandCmd__rosidl_typesupport_introspection_c__HandCmd_init_function,  // function to initialize message memory (memory has to be allocated)
  agx_arm_msgs__msg__HandCmd__rosidl_typesupport_introspection_c__HandCmd_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t agx_arm_msgs__msg__HandCmd__rosidl_typesupport_introspection_c__HandCmd_message_type_support_handle = {
  0,
  &agx_arm_msgs__msg__HandCmd__rosidl_typesupport_introspection_c__HandCmd_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_agx_arm_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, agx_arm_msgs, msg, HandCmd)() {
  if (!agx_arm_msgs__msg__HandCmd__rosidl_typesupport_introspection_c__HandCmd_message_type_support_handle.typesupport_identifier) {
    agx_arm_msgs__msg__HandCmd__rosidl_typesupport_introspection_c__HandCmd_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &agx_arm_msgs__msg__HandCmd__rosidl_typesupport_introspection_c__HandCmd_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
