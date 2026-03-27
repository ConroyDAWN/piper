// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agx_arm_msgs:msg/HandPositionTimeCmd.idl
// generated code does not contain a copyright notice

#ifndef AGX_ARM_MSGS__MSG__DETAIL__HAND_POSITION_TIME_CMD__STRUCT_HPP_
#define AGX_ARM_MSGS__MSG__DETAIL__HAND_POSITION_TIME_CMD__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__agx_arm_msgs__msg__HandPositionTimeCmd __attribute__((deprecated))
#else
# define DEPRECATED__agx_arm_msgs__msg__HandPositionTimeCmd __declspec(deprecated)
#endif

namespace agx_arm_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct HandPositionTimeCmd_
{
  using Type = HandPositionTimeCmd_<ContainerAllocator>;

  explicit HandPositionTimeCmd_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->thumb_tip_pos = 0;
      this->thumb_base_pos = 0;
      this->index_finger_pos = 0;
      this->middle_finger_pos = 0;
      this->ring_finger_pos = 0;
      this->pinky_finger_pos = 0;
      this->thumb_tip_time = 0;
      this->thumb_base_time = 0;
      this->index_finger_time = 0;
      this->middle_finger_time = 0;
      this->ring_finger_time = 0;
      this->pinky_finger_time = 0;
    }
  }

  explicit HandPositionTimeCmd_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->thumb_tip_pos = 0;
      this->thumb_base_pos = 0;
      this->index_finger_pos = 0;
      this->middle_finger_pos = 0;
      this->ring_finger_pos = 0;
      this->pinky_finger_pos = 0;
      this->thumb_tip_time = 0;
      this->thumb_base_time = 0;
      this->index_finger_time = 0;
      this->middle_finger_time = 0;
      this->ring_finger_time = 0;
      this->pinky_finger_time = 0;
    }
  }

  // field types and members
  using _thumb_tip_pos_type =
    int8_t;
  _thumb_tip_pos_type thumb_tip_pos;
  using _thumb_base_pos_type =
    int8_t;
  _thumb_base_pos_type thumb_base_pos;
  using _index_finger_pos_type =
    int8_t;
  _index_finger_pos_type index_finger_pos;
  using _middle_finger_pos_type =
    int8_t;
  _middle_finger_pos_type middle_finger_pos;
  using _ring_finger_pos_type =
    int8_t;
  _ring_finger_pos_type ring_finger_pos;
  using _pinky_finger_pos_type =
    int8_t;
  _pinky_finger_pos_type pinky_finger_pos;
  using _thumb_tip_time_type =
    uint8_t;
  _thumb_tip_time_type thumb_tip_time;
  using _thumb_base_time_type =
    uint8_t;
  _thumb_base_time_type thumb_base_time;
  using _index_finger_time_type =
    uint8_t;
  _index_finger_time_type index_finger_time;
  using _middle_finger_time_type =
    uint8_t;
  _middle_finger_time_type middle_finger_time;
  using _ring_finger_time_type =
    uint8_t;
  _ring_finger_time_type ring_finger_time;
  using _pinky_finger_time_type =
    uint8_t;
  _pinky_finger_time_type pinky_finger_time;

  // setters for named parameter idiom
  Type & set__thumb_tip_pos(
    const int8_t & _arg)
  {
    this->thumb_tip_pos = _arg;
    return *this;
  }
  Type & set__thumb_base_pos(
    const int8_t & _arg)
  {
    this->thumb_base_pos = _arg;
    return *this;
  }
  Type & set__index_finger_pos(
    const int8_t & _arg)
  {
    this->index_finger_pos = _arg;
    return *this;
  }
  Type & set__middle_finger_pos(
    const int8_t & _arg)
  {
    this->middle_finger_pos = _arg;
    return *this;
  }
  Type & set__ring_finger_pos(
    const int8_t & _arg)
  {
    this->ring_finger_pos = _arg;
    return *this;
  }
  Type & set__pinky_finger_pos(
    const int8_t & _arg)
  {
    this->pinky_finger_pos = _arg;
    return *this;
  }
  Type & set__thumb_tip_time(
    const uint8_t & _arg)
  {
    this->thumb_tip_time = _arg;
    return *this;
  }
  Type & set__thumb_base_time(
    const uint8_t & _arg)
  {
    this->thumb_base_time = _arg;
    return *this;
  }
  Type & set__index_finger_time(
    const uint8_t & _arg)
  {
    this->index_finger_time = _arg;
    return *this;
  }
  Type & set__middle_finger_time(
    const uint8_t & _arg)
  {
    this->middle_finger_time = _arg;
    return *this;
  }
  Type & set__ring_finger_time(
    const uint8_t & _arg)
  {
    this->ring_finger_time = _arg;
    return *this;
  }
  Type & set__pinky_finger_time(
    const uint8_t & _arg)
  {
    this->pinky_finger_time = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agx_arm_msgs::msg::HandPositionTimeCmd_<ContainerAllocator> *;
  using ConstRawPtr =
    const agx_arm_msgs::msg::HandPositionTimeCmd_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agx_arm_msgs::msg::HandPositionTimeCmd_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agx_arm_msgs::msg::HandPositionTimeCmd_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agx_arm_msgs::msg::HandPositionTimeCmd_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agx_arm_msgs::msg::HandPositionTimeCmd_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agx_arm_msgs::msg::HandPositionTimeCmd_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agx_arm_msgs::msg::HandPositionTimeCmd_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agx_arm_msgs::msg::HandPositionTimeCmd_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agx_arm_msgs::msg::HandPositionTimeCmd_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agx_arm_msgs__msg__HandPositionTimeCmd
    std::shared_ptr<agx_arm_msgs::msg::HandPositionTimeCmd_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agx_arm_msgs__msg__HandPositionTimeCmd
    std::shared_ptr<agx_arm_msgs::msg::HandPositionTimeCmd_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const HandPositionTimeCmd_ & other) const
  {
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
    if (this->thumb_tip_time != other.thumb_tip_time) {
      return false;
    }
    if (this->thumb_base_time != other.thumb_base_time) {
      return false;
    }
    if (this->index_finger_time != other.index_finger_time) {
      return false;
    }
    if (this->middle_finger_time != other.middle_finger_time) {
      return false;
    }
    if (this->ring_finger_time != other.ring_finger_time) {
      return false;
    }
    if (this->pinky_finger_time != other.pinky_finger_time) {
      return false;
    }
    return true;
  }
  bool operator!=(const HandPositionTimeCmd_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct HandPositionTimeCmd_

// alias to use template instance with default allocator
using HandPositionTimeCmd =
  agx_arm_msgs::msg::HandPositionTimeCmd_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace agx_arm_msgs

#endif  // AGX_ARM_MSGS__MSG__DETAIL__HAND_POSITION_TIME_CMD__STRUCT_HPP_
