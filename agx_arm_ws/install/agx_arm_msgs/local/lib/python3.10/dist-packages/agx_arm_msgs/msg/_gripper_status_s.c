// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from agx_arm_msgs:msg/GripperStatus.idl
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
#include "agx_arm_msgs/msg/detail/gripper_status__struct.h"
#include "agx_arm_msgs/msg/detail/gripper_status__functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__header__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__header__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool agx_arm_msgs__msg__gripper_status__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[47];
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
    assert(strncmp("agx_arm_msgs.msg._gripper_status.GripperStatus", full_classname_dest, 46) == 0);
  }
  agx_arm_msgs__msg__GripperStatus * ros_message = _ros_message;
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
  {  // width
    PyObject * field = PyObject_GetAttrString(_pymsg, "width");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->width = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // force
    PyObject * field = PyObject_GetAttrString(_pymsg, "force");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->force = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // voltage_too_low
    PyObject * field = PyObject_GetAttrString(_pymsg, "voltage_too_low");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->voltage_too_low = (Py_True == field);
    Py_DECREF(field);
  }
  {  // motor_overheating
    PyObject * field = PyObject_GetAttrString(_pymsg, "motor_overheating");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->motor_overheating = (Py_True == field);
    Py_DECREF(field);
  }
  {  // driver_overcurrent
    PyObject * field = PyObject_GetAttrString(_pymsg, "driver_overcurrent");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->driver_overcurrent = (Py_True == field);
    Py_DECREF(field);
  }
  {  // driver_overheating
    PyObject * field = PyObject_GetAttrString(_pymsg, "driver_overheating");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->driver_overheating = (Py_True == field);
    Py_DECREF(field);
  }
  {  // sensor_status
    PyObject * field = PyObject_GetAttrString(_pymsg, "sensor_status");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->sensor_status = (Py_True == field);
    Py_DECREF(field);
  }
  {  // driver_error_status
    PyObject * field = PyObject_GetAttrString(_pymsg, "driver_error_status");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->driver_error_status = (Py_True == field);
    Py_DECREF(field);
  }
  {  // driver_enable_status
    PyObject * field = PyObject_GetAttrString(_pymsg, "driver_enable_status");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->driver_enable_status = (Py_True == field);
    Py_DECREF(field);
  }
  {  // homing_status
    PyObject * field = PyObject_GetAttrString(_pymsg, "homing_status");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->homing_status = (Py_True == field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * agx_arm_msgs__msg__gripper_status__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of GripperStatus */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("agx_arm_msgs.msg._gripper_status");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "GripperStatus");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  agx_arm_msgs__msg__GripperStatus * ros_message = (agx_arm_msgs__msg__GripperStatus *)raw_ros_message;
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
  {  // width
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->width);
    {
      int rc = PyObject_SetAttrString(_pymessage, "width", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // force
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->force);
    {
      int rc = PyObject_SetAttrString(_pymessage, "force", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // voltage_too_low
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->voltage_too_low ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "voltage_too_low", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // motor_overheating
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->motor_overheating ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "motor_overheating", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // driver_overcurrent
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->driver_overcurrent ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "driver_overcurrent", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // driver_overheating
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->driver_overheating ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "driver_overheating", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // sensor_status
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->sensor_status ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "sensor_status", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // driver_error_status
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->driver_error_status ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "driver_error_status", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // driver_enable_status
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->driver_enable_status ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "driver_enable_status", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // homing_status
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->homing_status ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "homing_status", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
