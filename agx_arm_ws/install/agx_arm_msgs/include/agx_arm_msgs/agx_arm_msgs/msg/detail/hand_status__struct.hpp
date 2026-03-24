// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agx_arm_msgs:msg/HandStatus.idl
// generated code does not contain a copyright notice

#ifndef AGX_ARM_MSGS__MSG__DETAIL__HAND_STATUS__STRUCT_HPP_
#define AGX_ARM_MSGS__MSG__DETAIL__HAND_STATUS__STRUCT_HPP_

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
# define DEPRECATED__agx_arm_msgs__msg__HandStatus __attribute__((deprecated))
#else
# define DEPRECATED__agx_arm_msgs__msg__HandStatus __declspec(deprecated)
#endif

namespace agx_arm_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct HandStatus_
{
  using Type = HandStatus_<ContainerAllocator>;

  explicit HandStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->left_or_right = 0;
      this->thumb_tip_pos = 0;
      this->thumb_base_pos = 0;
      this->index_finger_pos = 0;
      this->middle_finger_pos = 0;
      this->ring_finger_pos = 0;
      this->pinky_finger_pos = 0;
      this->thumb_tip_status = 0;
      this->thumb_base_status = 0;
      this->index_finger_status = 0;
      this->middle_finger_status = 0;
      this->ring_finger_status = 0;
      this->pinky_finger_status = 0;
    }
  }

  explicit HandStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->left_or_right = 0;
      this->thumb_tip_pos = 0;
      this->thumb_base_pos = 0;
      this->index_finger_pos = 0;
      this->middle_finger_pos = 0;
      this->ring_finger_pos = 0;
      this->pinky_finger_pos = 0;
      this->thumb_tip_status = 0;
      this->thumb_base_status = 0;
      this->index_finger_status = 0;
      this->middle_finger_status = 0;
      this->ring_finger_status = 0;
      this->pinky_finger_status = 0;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _left_or_right_type =
    uint8_t;
  _left_or_right_type left_or_right;
  using _thumb_tip_pos_type =
    uint8_t;
  _thumb_tip_pos_type thumb_tip_pos;
  using _thumb_base_pos_type =
    uint8_t;
  _thumb_base_pos_type thumb_base_pos;
  using _index_finger_pos_type =
    uint8_t;
  _index_finger_pos_type index_finger_pos;
  using _middle_finger_pos_type =
    uint8_t;
  _middle_finger_pos_type middle_finger_pos;
  using _ring_finger_pos_type =
    uint8_t;
  _ring_finger_pos_type ring_finger_pos;
  using _pinky_finger_pos_type =
    uint8_t;
  _pinky_finger_pos_type pinky_finger_pos;
  using _thumb_tip_status_type =
    uint8_t;
  _thumb_tip_status_type thumb_tip_status;
  using _thumb_base_status_type =
    uint8_t;
  _thumb_base_status_type thumb_base_status;
  using _index_finger_status_type =
    uint8_t;
  _index_finger_status_type index_finger_status;
  using _middle_finger_status_type =
    uint8_t;
  _middle_finger_status_type middle_finger_status;
  using _ring_finger_status_type =
    uint8_t;
  _ring_finger_status_type ring_finger_status;
  using _pinky_finger_status_type =
    uint8_t;
  _pinky_finger_status_type pinky_finger_status;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__left_or_right(
    const uint8_t & _arg)
  {
    this->left_or_right = _arg;
    return *this;
  }
  Type & set__thumb_tip_pos(
    const uint8_t & _arg)
  {
    this->thumb_tip_pos = _arg;
    return *this;
  }
  Type & set__thumb_base_pos(
    const uint8_t & _arg)
  {
    this->thumb_base_pos = _arg;
    return *this;
  }
  Type & set__index_finger_pos(
    const uint8_t & _arg)
  {
    this->index_finger_pos = _arg;
    return *this;
  }
  Type & set__middle_finger_pos(
    const uint8_t & _arg)
  {
    this->middle_finger_pos = _arg;
    return *this;
  }
  Type & set__ring_finger_pos(
    const uint8_t & _arg)
  {
    this->ring_finger_pos = _arg;
    return *this;
  }
  Type & set__pinky_finger_pos(
    const uint8_t & _arg)
  {
    this->pinky_finger_pos = _arg;
    return *this;
  }
  Type & set__thumb_tip_status(
    const uint8_t & _arg)
  {
    this->thumb_tip_status = _arg;
    return *this;
  }
  Type & set__thumb_base_status(
    const uint8_t & _arg)
  {
    this->thumb_base_status = _arg;
    return *this;
  }
  Type & set__index_finger_status(
    const uint8_t & _arg)
  {
    this->index_finger_status = _arg;
    return *this;
  }
  Type & set__middle_finger_status(
    const uint8_t & _arg)
  {
    this->middle_finger_status = _arg;
    return *this;
  }
  Type & set__ring_finger_status(
    const uint8_t & _arg)
  {
    this->ring_finger_status = _arg;
    return *this;
  }
  Type & set__pinky_finger_status(
    const uint8_t & _arg)
  {
    this->pinky_finger_status = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agx_arm_msgs::msg::HandStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const agx_arm_msgs::msg::HandStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agx_arm_msgs::msg::HandStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agx_arm_msgs::msg::HandStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agx_arm_msgs::msg::HandStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agx_arm_msgs::msg::HandStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agx_arm_msgs::msg::HandStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agx_arm_msgs::msg::HandStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agx_arm_msgs::msg::HandStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agx_arm_msgs::msg::HandStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agx_arm_msgs__msg__HandStatus
    std::shared_ptr<agx_arm_msgs::msg::HandStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agx_arm_msgs__msg__HandStatus
    std::shared_ptr<agx_arm_msgs::msg::HandStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const HandStatus_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->left_or_right != other.left_or_right) {
      return false;
    }
    if (this->thumb_tip_pos != other.thumb_tip_pos) {
      return false;
    }
    if (this->thumb_base_pos != other.thumb_base_pos) {
      return false;
    }
    if (this->index_finger_pos != other.index_finger_pos) {
      return false;
    }
    if (this->middle_finger_pos != other.middle_finger_pos) {
      return false;
    }
    if (this->ring_finger_pos != other.ring_finger_pos) {
      return false;
    }
    if (this->pinky_finger_pos != other.pinky_finger_pos) {
      return false;
    }
    if (this->thumb_tip_status != other.thumb_tip_status) {
      return false;
    }
    if (this->thumb_base_status != other.thumb_base_status) {
      return false;
    }
    if (this->index_finger_status != other.index_finger_status) {
      return false;
    }
    if (this->middle_finger_status != other.middle_finger_status) {
      return false;
    }
    if (this->ring_finger_status != other.ring_finger_status) {
      return false;
    }
    if (this->pinky_finger_status != other.pinky_finger_status) {
      return false;
    }
    return true;
  }
  bool operator!=(const HandStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct HandStatus_

// alias to use template instance with default allocator
using HandStatus =
  agx_arm_msgs::msg::HandStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace agx_arm_msgs

#endif  // AGX_ARM_MSGS__MSG__DETAIL__HAND_STATUS__STRUCT_HPP_
