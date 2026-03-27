// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agx_arm_msgs:msg/GripperStatus.idl
// generated code does not contain a copyright notice

#ifndef AGX_ARM_MSGS__MSG__DETAIL__GRIPPER_STATUS__STRUCT_HPP_
#define AGX_ARM_MSGS__MSG__DETAIL__GRIPPER_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__agx_arm_msgs__msg__GripperStatus __attribute__((deprecated))
#else
# define DEPRECATED__agx_arm_msgs__msg__GripperStatus __declspec(deprecated)
#endif

namespace agx_arm_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct GripperStatus_
{
  using Type = GripperStatus_<ContainerAllocator>;

  explicit GripperStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->width = 0.0;
      this->force = 0.0;
      this->voltage_too_low = false;
      this->motor_overheating = false;
      this->driver_overcurrent = false;
      this->driver_overheating = false;
      this->sensor_status = false;
      this->driver_error_status = false;
      this->driver_enable_status = false;
      this->homing_status = false;
    }
  }

  explicit GripperStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->width = 0.0;
      this->force = 0.0;
      this->voltage_too_low = false;
      this->motor_overheating = false;
      this->driver_overcurrent = false;
      this->driver_overheating = false;
      this->sensor_status = false;
      this->driver_error_status = false;
      this->driver_enable_status = false;
      this->homing_status = false;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _width_type =
    double;
  _width_type width;
  using _force_type =
    double;
  _force_type force;
  using _voltage_too_low_type =
    bool;
  _voltage_too_low_type voltage_too_low;
  using _motor_overheating_type =
    bool;
  _motor_overheating_type motor_overheating;
  using _driver_overcurrent_type =
    bool;
  _driver_overcurrent_type driver_overcurrent;
  using _driver_overheating_type =
    bool;
  _driver_overheating_type driver_overheating;
  using _sensor_status_type =
    bool;
  _sensor_status_type sensor_status;
  using _driver_error_status_type =
    bool;
  _driver_error_status_type driver_error_status;
  using _driver_enable_status_type =
    bool;
  _driver_enable_status_type driver_enable_status;
  using _homing_status_type =
    bool;
  _homing_status_type homing_status;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__width(
    const double & _arg)
  {
    this->width = _arg;
    return *this;
  }
  Type & set__force(
    const double & _arg)
  {
    this->force = _arg;
    return *this;
  }
  Type & set__voltage_too_low(
    const bool & _arg)
  {
    this->voltage_too_low = _arg;
    return *this;
  }
  Type & set__motor_overheating(
    const bool & _arg)
  {
    this->motor_overheating = _arg;
    return *this;
  }
  Type & set__driver_overcurrent(
    const bool & _arg)
  {
    this->driver_overcurrent = _arg;
    return *this;
  }
  Type & set__driver_overheating(
    const bool & _arg)
  {
    this->driver_overheating = _arg;
    return *this;
  }
  Type & set__sensor_status(
    const bool & _arg)
  {
    this->sensor_status = _arg;
    return *this;
  }
  Type & set__driver_error_status(
    const bool & _arg)
  {
    this->driver_error_status = _arg;
    return *this;
  }
  Type & set__driver_enable_status(
    const bool & _arg)
  {
    this->driver_enable_status = _arg;
    return *this;
  }
  Type & set__homing_status(
    const bool & _arg)
  {
    this->homing_status = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agx_arm_msgs::msg::GripperStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const agx_arm_msgs::msg::GripperStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agx_arm_msgs::msg::GripperStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agx_arm_msgs::msg::GripperStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agx_arm_msgs::msg::GripperStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agx_arm_msgs::msg::GripperStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agx_arm_msgs::msg::GripperStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agx_arm_msgs::msg::GripperStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agx_arm_msgs::msg::GripperStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agx_arm_msgs::msg::GripperStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agx_arm_msgs__msg__GripperStatus
    std::shared_ptr<agx_arm_msgs::msg::GripperStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agx_arm_msgs__msg__GripperStatus
    std::shared_ptr<agx_arm_msgs::msg::GripperStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GripperStatus_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->width != other.width) {
      return false;
    }
    if (this->force != other.force) {
      return false;
    }
    if (this->voltage_too_low != other.voltage_too_low) {
      return false;
    }
    if (this->motor_overheating != other.motor_overheating) {
      return false;
    }
    if (this->driver_overcurrent != other.driver_overcurrent) {
      return false;
    }
    if (this->driver_overheating != other.driver_overheating) {
      return false;
    }
    if (this->sensor_status != other.sensor_status) {
      return false;
    }
    if (this->driver_error_status != other.driver_error_status) {
      return false;
    }
    if (this->driver_enable_status != other.driver_enable_status) {
      return false;
    }
    if (this->homing_status != other.homing_status) {
      return false;
    }
    return true;
  }
  bool operator!=(const GripperStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GripperStatus_

// alias to use template instance with default allocator
using GripperStatus =
  agx_arm_msgs::msg::GripperStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace agx_arm_msgs

#endif  // AGX_ARM_MSGS__MSG__DETAIL__GRIPPER_STATUS__STRUCT_HPP_
