// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agx_arm_msgs:msg/HandCmd.idl
// generated code does not contain a copyright notice

#ifndef AGX_ARM_MSGS__MSG__DETAIL__HAND_CMD__STRUCT_HPP_
#define AGX_ARM_MSGS__MSG__DETAIL__HAND_CMD__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__agx_arm_msgs__msg__HandCmd __attribute__((deprecated))
#else
# define DEPRECATED__agx_arm_msgs__msg__HandCmd __declspec(deprecated)
#endif

namespace agx_arm_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct HandCmd_
{
  using Type = HandCmd_<ContainerAllocator>;

  explicit HandCmd_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mode = "";
      this->thumb_tip = 0;
      this->thumb_base = 0;
      this->index_finger = 0;
      this->middle_finger = 0;
      this->ring_finger = 0;
      this->pinky_finger = 0;
    }
  }

  explicit HandCmd_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : mode(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mode = "";
      this->thumb_tip = 0;
      this->thumb_base = 0;
      this->index_finger = 0;
      this->middle_finger = 0;
      this->ring_finger = 0;
      this->pinky_finger = 0;
    }
  }

  // field types and members
  using _mode_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _mode_type mode;
  using _thumb_tip_type =
    int8_t;
  _thumb_tip_type thumb_tip;
  using _thumb_base_type =
    int8_t;
  _thumb_base_type thumb_base;
  using _index_finger_type =
    int8_t;
  _index_finger_type index_finger;
  using _middle_finger_type =
    int8_t;
  _middle_finger_type middle_finger;
  using _ring_finger_type =
    int8_t;
  _ring_finger_type ring_finger;
  using _pinky_finger_type =
    int8_t;
  _pinky_finger_type pinky_finger;

  // setters for named parameter idiom
  Type & set__mode(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->mode = _arg;
    return *this;
  }
  Type & set__thumb_tip(
    const int8_t & _arg)
  {
    this->thumb_tip = _arg;
    return *this;
  }
  Type & set__thumb_base(
    const int8_t & _arg)
  {
    this->thumb_base = _arg;
    return *this;
  }
  Type & set__index_finger(
    const int8_t & _arg)
  {
    this->index_finger = _arg;
    return *this;
  }
  Type & set__middle_finger(
    const int8_t & _arg)
  {
    this->middle_finger = _arg;
    return *this;
  }
  Type & set__ring_finger(
    const int8_t & _arg)
  {
    this->ring_finger = _arg;
    return *this;
  }
  Type & set__pinky_finger(
    const int8_t & _arg)
  {
    this->pinky_finger = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agx_arm_msgs::msg::HandCmd_<ContainerAllocator> *;
  using ConstRawPtr =
    const agx_arm_msgs::msg::HandCmd_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agx_arm_msgs::msg::HandCmd_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agx_arm_msgs::msg::HandCmd_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agx_arm_msgs::msg::HandCmd_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agx_arm_msgs::msg::HandCmd_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agx_arm_msgs::msg::HandCmd_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agx_arm_msgs::msg::HandCmd_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agx_arm_msgs::msg::HandCmd_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agx_arm_msgs::msg::HandCmd_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agx_arm_msgs__msg__HandCmd
    std::shared_ptr<agx_arm_msgs::msg::HandCmd_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agx_arm_msgs__msg__HandCmd
    std::shared_ptr<agx_arm_msgs::msg::HandCmd_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const HandCmd_ & other) const
  {
    if (this->mode != other.mode) {
      return false;
    }
    if (this->thumb_tip != other.thumb_tip) {
      return false;
    }
    if (this->thumb_base != other.thumb_base) {
      return false;
    }
    if (this->index_finger != other.index_finger) {
      return false;
    }
    if (this->middle_finger != other.middle_finger) {
      return false;
    }
    if (this->ring_finger != other.ring_finger) {
      return false;
    }
    if (this->pinky_finger != other.pinky_finger) {
      return false;
    }
    return true;
  }
  bool operator!=(const HandCmd_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct HandCmd_

// alias to use template instance with default allocator
using HandCmd =
  agx_arm_msgs::msg::HandCmd_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace agx_arm_msgs

#endif  // AGX_ARM_MSGS__MSG__DETAIL__HAND_CMD__STRUCT_HPP_
