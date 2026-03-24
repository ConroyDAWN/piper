// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agx_arm_msgs:msg/MoveMITMsg.idl
// generated code does not contain a copyright notice

#ifndef AGX_ARM_MSGS__MSG__DETAIL__MOVE_MIT_MSG__STRUCT_HPP_
#define AGX_ARM_MSGS__MSG__DETAIL__MOVE_MIT_MSG__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__agx_arm_msgs__msg__MoveMITMsg __attribute__((deprecated))
#else
# define DEPRECATED__agx_arm_msgs__msg__MoveMITMsg __declspec(deprecated)
#endif

namespace agx_arm_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MoveMITMsg_
{
  using Type = MoveMITMsg_<ContainerAllocator>;

  explicit MoveMITMsg_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit MoveMITMsg_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _joint_index_type =
    std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>>;
  _joint_index_type joint_index;
  using _p_des_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _p_des_type p_des;
  using _v_des_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _v_des_type v_des;
  using _kp_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _kp_type kp;
  using _kd_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _kd_type kd;
  using _torque_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _torque_type torque;

  // setters for named parameter idiom
  Type & set__joint_index(
    const std::vector<int32_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int32_t>> & _arg)
  {
    this->joint_index = _arg;
    return *this;
  }
  Type & set__p_des(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->p_des = _arg;
    return *this;
  }
  Type & set__v_des(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->v_des = _arg;
    return *this;
  }
  Type & set__kp(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->kp = _arg;
    return *this;
  }
  Type & set__kd(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->kd = _arg;
    return *this;
  }
  Type & set__torque(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->torque = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agx_arm_msgs::msg::MoveMITMsg_<ContainerAllocator> *;
  using ConstRawPtr =
    const agx_arm_msgs::msg::MoveMITMsg_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agx_arm_msgs::msg::MoveMITMsg_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agx_arm_msgs::msg::MoveMITMsg_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agx_arm_msgs::msg::MoveMITMsg_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agx_arm_msgs::msg::MoveMITMsg_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agx_arm_msgs::msg::MoveMITMsg_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agx_arm_msgs::msg::MoveMITMsg_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agx_arm_msgs::msg::MoveMITMsg_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agx_arm_msgs::msg::MoveMITMsg_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agx_arm_msgs__msg__MoveMITMsg
    std::shared_ptr<agx_arm_msgs::msg::MoveMITMsg_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agx_arm_msgs__msg__MoveMITMsg
    std::shared_ptr<agx_arm_msgs::msg::MoveMITMsg_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MoveMITMsg_ & other) const
  {
    if (this->joint_index != other.joint_index) {
      return false;
    }
    if (this->p_des != other.p_des) {
      return false;
    }
    if (this->v_des != other.v_des) {
      return false;
    }
    if (this->kp != other.kp) {
      return false;
    }
    if (this->kd != other.kd) {
      return false;
    }
    if (this->torque != other.torque) {
      return false;
    }
    return true;
  }
  bool operator!=(const MoveMITMsg_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MoveMITMsg_

// alias to use template instance with default allocator
using MoveMITMsg =
  agx_arm_msgs::msg::MoveMITMsg_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace agx_arm_msgs

#endif  // AGX_ARM_MSGS__MSG__DETAIL__MOVE_MIT_MSG__STRUCT_HPP_
