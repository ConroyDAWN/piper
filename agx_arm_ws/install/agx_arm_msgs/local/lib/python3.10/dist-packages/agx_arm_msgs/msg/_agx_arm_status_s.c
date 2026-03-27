// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from agx_arm_msgs:msg/AgxArmStatus.idl
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
#include "agx_arm_msgs/msg/detail/agx_arm_status__struct.h"
#include "agx_arm_msgs/msg/detail/agx_arm_status__functions.h"

#include "rosidl_runtime_c/primitives_sequence.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool agx_arm_msgs__msg__agx_arm_status__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[46];
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
    assert(strncmp("agx_arm_msgs.msg._agx_arm_status.AgxArmStatus", full_classname_dest, 45) == 0);
  }
  agx_arm_msgs__msg__AgxArmStatus * ros_message = _ros_message;
  {  // ctrl_mode
    PyObject * field = PyObject_GetAttrString(_pymsg, "ctrl_mode");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->ctrl_mode = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // arm_status
    PyObject * field = PyObject_GetAttrString(_pymsg, "arm_status");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->arm_status = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // mode_feedback
    PyObject * field = PyObject_GetAttrString(_pymsg, "mode_feedback");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->mode_feedback = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // teach_status
    PyObject * field = PyObject_GetAttrString(_pymsg, "teach_status");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->teach_status = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // motion_status
    PyObject * field = PyObject_GetAttrString(_pymsg, "motion_status");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->motion_status = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // trajectory_num
    PyObject * field = PyObject_GetAttrString(_pymsg, "trajectory_num");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->trajectory_num = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // err_status
    PyObject * field = PyObject_GetAttrString(_pymsg, "err_status");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->err_status = PyLong_AsLongLong(field);
    Py_DECREF(field);
  }
  {  // joint_angle_limit
    PyObject * field = PyObject_GetAttrString(_pymsg, "joint_angle_limit");
    if (!field) {
      return false;
    }
    if (PyObject_CheckBuffer(field)) {
      // Optimization for converting arrays of primitives
      Py_buffer view;
      int rc = PyObject_GetBuffer(field, &view, PyBUF_SIMPLE);
      if (rc < 0) {
        Py_DECREF(field);
        return false;
      }
      Py_ssize_t size = view.len / sizeof(bool);
      if (!rosidl_runtime_c__boolean__Sequence__init(&(ros_message->joint_angle_limit), size)) {
        PyErr_SetString(PyExc_RuntimeError, "unable to create boolean__Sequence ros_message");
        PyBuffer_Release(&view);
        Py_DECREF(field);
        return false;
      }
      bool * dest = ros_message->joint_angle_limit.data;
      rc = PyBuffer_ToContiguous(dest, &view, view.len, 'C');
      if (rc < 0) {
        PyBuffer_Release(&view);
        Py_DECREF(field);
        return false;
      }
      PyBuffer_Release(&view);
    } else {
      PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'joint_angle_limit'");
      if (!seq_field) {
        Py_DECREF(field);
        return false;
      }
      Py_ssize_t size = PySequence_Size(field);
      if (-1 == size) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
      if (!rosidl_runtime_c__boolean__Sequence__init(&(ros_message->joint_angle_limit), size)) {
        PyErr_SetString(PyExc_RuntimeError, "unable to create boolean__Sequence ros_message");
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
      bool * dest = ros_message->joint_angle_limit.data;
      for (Py_ssize_t i = 0; i < size; ++i) {
        PyObject * item = PySequence_Fast_GET_ITEM(seq_field, i);
        if (!item) {
          Py_DECREF(seq_field);
          Py_DECREF(field);
          return false;
        }
        assert(PyBool_Check(item));
        bool tmp = (item == Py_True);
        memcpy(&dest[i], &tmp, sizeof(bool));
      }
      Py_DECREF(seq_field);
    }
    Py_DECREF(field);
  }
  {  // communication_status_joint
    PyObject * field = PyObject_GetAttrString(_pymsg, "communication_status_joint");
    if (!field) {
      return false;
    }
    if (PyObject_CheckBuffer(field)) {
      // Optimization for converting arrays of primitives
      Py_buffer view;
      int rc = PyObject_GetBuffer(field, &view, PyBUF_SIMPLE);
      if (rc < 0) {
        Py_DECREF(field);
        return false;
      }
      Py_ssize_t size = view.len / sizeof(bool);
      if (!rosidl_runtime_c__boolean__Sequence__init(&(ros_message->communication_status_joint), size)) {
        PyErr_SetString(PyExc_RuntimeError, "unable to create boolean__Sequence ros_message");
        PyBuffer_Release(&view);
        Py_DECREF(field);
        return false;
      }
      bool * dest = ros_message->communication_status_joint.data;
      rc = PyBuffer_ToContiguous(dest, &view, view.len, 'C');
      if (rc < 0) {
        PyBuffer_Release(&view);
        Py_DECREF(field);
        return false;
      }
      PyBuffer_Release(&view);
    } else {
      PyObject * seq_field = PySequence_Fast(field, "expected a sequence in 'communication_status_joint'");
      if (!seq_field) {
        Py_DECREF(field);
        return false;
      }
      Py_ssize_t size = PySequence_Size(field);
      if (-1 == size) {
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
      if (!rosidl_runtime_c__boolean__Sequence__init(&(ros_message->communication_status_joint), size)) {
        PyErr_SetString(PyExc_RuntimeError, "unable to create boolean__Sequence ros_message");
        Py_DECREF(seq_field);
        Py_DECREF(field);
        return false;
      }
      bool * dest = ros_message->communication_status_joint.data;
      for (Py_ssize_t i = 0; i < size; ++i) {
        PyObject * item = PySequence_Fast_GET_ITEM(seq_field, i);
        if (!item) {
          Py_DECREF(seq_field);
          Py_DECREF(field);
          return false;
        }
        assert(PyBool_Check(item));
        bool tmp = (item == Py_True);
        memcpy(&dest[i], &tmp, sizeof(bool));
      }
      Py_DECREF(seq_field);
    }
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * agx_arm_msgs__msg__agx_arm_status__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of AgxArmStatus */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("agx_arm_msgs.msg._agx_arm_status");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "AgxArmStatus");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  agx_arm_msgs__msg__AgxArmStatus * ros_message = (agx_arm_msgs__msg__AgxArmStatus *)raw_ros_message;
  {  // ctrl_mode
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->ctrl_mode);
    {
      int rc = PyObject_SetAttrString(_pymessage, "ctrl_mode", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // arm_status
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->arm_status);
    {
      int rc = PyObject_SetAttrString(_pymessage, "arm_status", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // mode_feedback
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->mode_feedback);
    {
      int rc = PyObject_SetAttrString(_pymessage, "mode_feedback", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // teach_status
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->teach_status);
    {
      int rc = PyObject_SetAttrString(_pymessage, "teach_status", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // motion_status
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->motion_status);
    {
      int rc = PyObject_SetAttrString(_pymessage, "motion_status", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // trajectory_num
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->trajectory_num);
    {
      int rc = PyObject_SetAttrString(_pymessage, "trajectory_num", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // err_status
    PyObject * field = NULL;
    field = PyLong_FromLongLong(ros_message->err_status);
    {
      int rc = PyObject_SetAttrString(_pymessage, "err_status", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // joint_angle_limit
    PyObject * field = NULL;
    size_t size = ros_message->joint_angle_limit.size;
    bool * src = ros_message->joint_angle_limit.data;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    for (size_t i = 0; i < size; ++i) {
      int rc = PyList_SetItem(field, i, PyBool_FromLong(src[i] ? 1 : 0));
      (void)rc;
      assert(rc == 0);
    }
    assert(PySequence_Check(field));
    {
      int rc = PyObject_SetAttrString(_pymessage, "joint_angle_limit", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // communication_status_joint
    PyObject * field = NULL;
    size_t size = ros_message->communication_status_joint.size;
    bool * src = ros_message->communication_status_joint.data;
    field = PyList_New(size);
    if (!field) {
      return NULL;
    }
    for (size_t i = 0; i < size; ++i) {
      int rc = PyList_SetItem(field, i, PyBool_FromLong(src[i] ? 1 : 0));
      (void)rc;
      assert(rc == 0);
    }
    assert(PySequence_Check(field));
    {
      int rc = PyObject_SetAttrString(_pymessage, "communication_status_joint", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
