// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from agx_arm_msgs:msg/HandPositionTimeCmd.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "agx_arm_msgs/msg/detail/hand_position_time_cmd__struct.h"
#include "agx_arm_msgs/msg/detail/hand_position_time_cmd__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool agx_arm_msgs__msg__hand_position_time_cmd__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[61];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("agx_arm_msgs.msg._hand_position_time_cmd.HandPositionTimeCmd", full_classname_dest, 60) == 0);
  }
  agx_arm_msgs__msg__HandPositionTimeCmd * ros_message = _ros_message;
  {  // thumb_tip_pos
    PyObject * field = PyObject_GetAttrString(_pymsg, "thumb_tip_pos");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->thumb_tip_pos = (int8_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // thumb_base_pos
    PyObject * field = PyObject_GetAttrString(_pymsg, "thumb_base_pos");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->thumb_base_pos = (int8_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // index_finger_pos
    PyObject * field = PyObject_GetAttrString(_pymsg, "index_finger_pos");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->index_finger_pos = (int8_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // middle_finger_pos
    PyObject * field = PyObject_GetAttrString(_pymsg, "middle_finger_pos");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->middle_finger_pos = (int8_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // ring_finger_pos
    PyObject * field = PyObject_GetAttrString(_pymsg, "ring_finger_pos");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->ring_finger_pos = (int8_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // pinky_finger_pos
    PyObject * field = PyObject_GetAttrString(_pymsg, "pinky_finger_pos");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->pinky_finger_pos = (int8_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // thumb_tip_time
    PyObject * field = PyObject_GetAttrString(_pymsg, "thumb_tip_time");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->thumb_tip_time = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // thumb_base_time
    PyObject * field = PyObject_GetAttrString(_pymsg, "thumb_base_time");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->thumb_base_time = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // index_finger_time
    PyObject * field = PyObject_GetAttrString(_pymsg, "index_finger_time");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->index_finger_time = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // middle_finger_time
    PyObject * field = PyObject_GetAttrString(_pymsg, "middle_finger_time");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->middle_finger_time = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // ring_finger_time
    PyObject * field = PyObject_GetAttrString(_pymsg, "ring_finger_time");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->ring_finger_time = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // pinky_finger_time
    PyObject * field = PyObject_GetAttrString(_pymsg, "pinky_finger_time");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->pinky_finger_time = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * agx_arm_msgs__msg__hand_position_time_cmd__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of HandPositionTimeCmd */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("agx_arm_msgs.msg._hand_position_time_cmd");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "HandPositionTimeCmd");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  agx_arm_msgs__msg__HandPositionTimeCmd * ros_message = (agx_arm_msgs__msg__HandPositionTimeCmd *)raw_ros_message;
  {  // thumb_tip_pos
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->thumb_tip_pos);
    {
      int rc = PyObject_SetAttrString(_pymessage, "thumb_tip_pos", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // thumb_base_pos
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->thumb_base_pos);
    {
      int rc = PyObject_SetAttrString(_pymessage, "thumb_base_pos", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // index_finger_pos
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->index_finger_pos);
    {
      int rc = PyObject_SetAttrString(_pymessage, "index_finger_pos", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // middle_finger_pos
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->middle_finger_pos);
    {
      int rc = PyObject_SetAttrString(_pymessage, "middle_finger_pos", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // ring_finger_pos
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->ring_finger_pos);
    {
      int rc = PyObject_SetAttrString(_pymessage, "ring_finger_pos", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // pinky_finger_pos
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->pinky_finger_pos);
    {
      int rc = PyObject_SetAttrString(_pymessage, "pinky_finger_pos", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // thumb_tip_time
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->thumb_tip_time);
    {
      int rc = PyObject_SetAttrString(_pymessage, "thumb_tip_time", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // thumb_base_time
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->thumb_base_time);
    {
      int rc = PyObject_SetAttrString(_pymessage, "thumb_base_time", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // index_finger_time
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->index_finger_time);
    {
      int rc = PyObject_SetAttrString(_pymessage, "index_finger_time", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // middle_finger_time
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->middle_finger_time);
    {
      int rc = PyObject_SetAttrString(_pymessage, "middle_finger_time", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // ring_finger_time
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->ring_finger_time);
    {
      int rc = PyObject_SetAttrString(_pymessage, "ring_finger_time", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // pinky_finger_time
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->pinky_finger_time);
    {
      int rc = PyObject_SetAttrString(_pymessage, "pinky_finger_time", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
