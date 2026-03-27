// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from agx_arm_msgs:msg/HandStatus.idl
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
#include "agx_arm_msgs/msg/detail/hand_status__struct.h"
#include "agx_arm_msgs/msg/detail/hand_status__functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__header__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__header__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool agx_arm_msgs__msg__hand_status__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[41];
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
    assert(strncmp("agx_arm_msgs.msg._hand_status.HandStatus", full_classname_dest, 40) == 0);
  }
  agx_arm_msgs__msg__HandStatus * ros_message = _ros_message;
  {  // header
    PyObject * field = PyObject_GetAttrString(_pymsg, "header");
    if (!field) {
      return false;
    }
    if (!std_msgs__msg__header__convert_from_py(field, &ros_message->header)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // left_or_right
    PyObject * field = PyObject_GetAttrString(_pymsg, "left_or_right");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->left_or_right = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // thumb_tip_pos
    PyObject * field = PyObject_GetAttrString(_pymsg, "thumb_tip_pos");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->thumb_tip_pos = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // thumb_base_pos
    PyObject * field = PyObject_GetAttrString(_pymsg, "thumb_base_pos");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->thumb_base_pos = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // index_finger_pos
    PyObject * field = PyObject_GetAttrString(_pymsg, "index_finger_pos");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->index_finger_pos = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // middle_finger_pos
    PyObject * field = PyObject_GetAttrString(_pymsg, "middle_finger_pos");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->middle_finger_pos = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // ring_finger_pos
    PyObject * field = PyObject_GetAttrString(_pymsg, "ring_finger_pos");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->ring_finger_pos = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // pinky_finger_pos
    PyObject * field = PyObject_GetAttrString(_pymsg, "pinky_finger_pos");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->pinky_finger_pos = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // thumb_tip_status
    PyObject * field = PyObject_GetAttrString(_pymsg, "thumb_tip_status");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->thumb_tip_status = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // thumb_base_status
    PyObject * field = PyObject_GetAttrString(_pymsg, "thumb_base_status");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->thumb_base_status = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // index_finger_status
    PyObject * field = PyObject_GetAttrString(_pymsg, "index_finger_status");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->index_finger_status = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // middle_finger_status
    PyObject * field = PyObject_GetAttrString(_pymsg, "middle_finger_status");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->middle_finger_status = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // ring_finger_status
    PyObject * field = PyObject_GetAttrString(_pymsg, "ring_finger_status");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->ring_finger_status = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // pinky_finger_status
    PyObject * field = PyObject_GetAttrString(_pymsg, "pinky_finger_status");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->pinky_finger_status = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * agx_arm_msgs__msg__hand_status__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of HandStatus */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("agx_arm_msgs.msg._hand_status");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "HandStatus");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  agx_arm_msgs__msg__HandStatus * ros_message = (agx_arm_msgs__msg__HandStatus *)raw_ros_message;
  {  // header
    PyObject * field = NULL;
    field = std_msgs__msg__header__convert_to_py(&ros_message->header);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "header", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // left_or_right
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->left_or_right);
    {
      int rc = PyObject_SetAttrString(_pymessage, "left_or_right", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // thumb_tip_pos
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->thumb_tip_pos);
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
    field = PyLong_FromUnsignedLong(ros_message->thumb_base_pos);
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
    field = PyLong_FromUnsignedLong(ros_message->index_finger_pos);
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
    field = PyLong_FromUnsignedLong(ros_message->middle_finger_pos);
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
    field = PyLong_FromUnsignedLong(ros_message->ring_finger_pos);
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
    field = PyLong_FromUnsignedLong(ros_message->pinky_finger_pos);
    {
      int rc = PyObject_SetAttrString(_pymessage, "pinky_finger_pos", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // thumb_tip_status
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->thumb_tip_status);
    {
      int rc = PyObject_SetAttrString(_pymessage, "thumb_tip_status", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // thumb_base_status
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->thumb_base_status);
    {
      int rc = PyObject_SetAttrString(_pymessage, "thumb_base_status", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // index_finger_status
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->index_finger_status);
    {
      int rc = PyObject_SetAttrString(_pymessage, "index_finger_status", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // middle_finger_status
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->middle_finger_status);
    {
      int rc = PyObject_SetAttrString(_pymessage, "middle_finger_status", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // ring_finger_status
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->ring_finger_status);
    {
      int rc = PyObject_SetAttrString(_pymessage, "ring_finger_status", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // pinky_finger_status
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->pinky_finger_status);
    {
      int rc = PyObject_SetAttrString(_pymessage, "pinky_finger_status", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
