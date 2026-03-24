// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from agx_arm_msgs:msg/HandCmd.idl
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
#include "agx_arm_msgs/msg/detail/hand_cmd__struct.h"
#include "agx_arm_msgs/msg/detail/hand_cmd__functions.h"

#include "rosidl_runtime_c/string.h"
#include "rosidl_runtime_c/string_functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool agx_arm_msgs__msg__hand_cmd__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[35];
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
    assert(strncmp("agx_arm_msgs.msg._hand_cmd.HandCmd", full_classname_dest, 34) == 0);
  }
  agx_arm_msgs__msg__HandCmd * ros_message = _ros_message;
  {  // mode
    PyObject * field = PyObject_GetAttrString(_pymsg, "mode");
    if (!field) {
      return false;
    }
    assert(PyUnicode_Check(field));
    PyObject * encoded_field = PyUnicode_AsUTF8String(field);
    if (!encoded_field) {
      Py_DECREF(field);
      return false;
    }
    rosidl_runtime_c__String__assign(&ros_message->mode, PyBytes_AS_STRING(encoded_field));
    Py_DECREF(encoded_field);
    Py_DECREF(field);
  }
  {  // thumb_tip
    PyObject * field = PyObject_GetAttrString(_pymsg, "thumb_tip");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->thumb_tip = (int8_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // thumb_base
    PyObject * field = PyObject_GetAttrString(_pymsg, "thumb_base");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->thumb_base = (int8_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // index_finger
    PyObject * field = PyObject_GetAttrString(_pymsg, "index_finger");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->index_finger = (int8_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // middle_finger
    PyObject * field = PyObject_GetAttrString(_pymsg, "middle_finger");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->middle_finger = (int8_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // ring_finger
    PyObject * field = PyObject_GetAttrString(_pymsg, "ring_finger");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->ring_finger = (int8_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // pinky_finger
    PyObject * field = PyObject_GetAttrString(_pymsg, "pinky_finger");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->pinky_finger = (int8_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * agx_arm_msgs__msg__hand_cmd__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of HandCmd */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("agx_arm_msgs.msg._hand_cmd");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "HandCmd");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  agx_arm_msgs__msg__HandCmd * ros_message = (agx_arm_msgs__msg__HandCmd *)raw_ros_message;
  {  // mode
    PyObject * field = NULL;
    field = PyUnicode_DecodeUTF8(
      ros_message->mode.data,
      strlen(ros_message->mode.data),
      "replace");
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "mode", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // thumb_tip
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->thumb_tip);
    {
      int rc = PyObject_SetAttrString(_pymessage, "thumb_tip", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // thumb_base
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->thumb_base);
    {
      int rc = PyObject_SetAttrString(_pymessage, "thumb_base", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // index_finger
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->index_finger);
    {
      int rc = PyObject_SetAttrString(_pymessage, "index_finger", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // middle_finger
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->middle_finger);
    {
      int rc = PyObject_SetAttrString(_pymessage, "middle_finger", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // ring_finger
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->ring_finger);
    {
      int rc = PyObject_SetAttrString(_pymessage, "ring_finger", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // pinky_finger
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->pinky_finger);
    {
      int rc = PyObject_SetAttrString(_pymessage, "pinky_finger", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
