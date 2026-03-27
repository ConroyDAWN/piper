// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from agx_arm_msgs:msg/AgxArmStatus.idl
// generated code does not contain a copyright notice

#ifndef AGX_ARM_MSGS__MSG__DETAIL__AGX_ARM_STATUS__STRUCT_HPP_
#define AGX_ARM_MSGS__MSG__DETAIL__AGX_ARM_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__agx_arm_msgs__msg__AgxArmStatus __attribute__((deprecated))
#else
# define DEPRECATED__agx_arm_msgs__msg__AgxArmStatus __declspec(deprecated)
#endif

namespace agx_arm_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AgxArmStatus_
{
  using Type = AgxArmStatus_<ContainerAllocator>;

  explicit AgxArmStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->ctrl_mode = 0;
      this->arm_status = 0;
      this->mode_feedback = 0;
      this->teach_status = 0;
      this->motion_status = 0;
      this->trajectory_num = 0;
      this->err_status = 0ll;
    }
  }

  explicit AgxArmStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->ctrl_mode = 0;
      this->arm_status = 0;
      this->mode_feedback = 0;
      this->teach_status = 0;
      this->motion_status = 0;
      this->trajectory_num = 0;
      this->err_status = 0ll;
    }
  }

  // field types and members
  using _ctrl_mode_type =
    uint8_t;
  _ctrl_mode_type ctrl_mode;
  using _arm_status_type =
    uint8_t;
  _arm_status_type arm_status;
  using _mode_feedback_type =
    uint8_t;
  _mode_feedback_type mode_feedback;
  using _teach_status_type =
    uint8_t;
  _teach_status_type teach_status;
  using _motion_status_type =
    uint8_t;
  _motion_status_type motion_status;
  using _trajectory_num_type =
    uint8_t;
  _trajectory_num_type trajectory_num;
  using _err_status_type =
    int64_t;
  _err_status_type err_status;
  using _joint_angle_limit_type =
    std::vector<bool, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<bool>>;
  _joint_angle_limit_type joint_angle_limit;
  using _communication_status_joint_type =
    std::vector<bool, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<bool>>;
  _communication_status_joint_type communication_status_joint;

  // setters for named parameter idiom
  Type & set__ctrl_mode(
    const uint8_t & _arg)
  {
    this->ctrl_mode = _arg;
    return *this;
  }
  Type & set__arm_status(
    const uint8_t & _arg)
  {
    this->arm_status = _arg;
    return *this;
  }
  Type & set__mode_feedback(
    const uint8_t & _arg)
  {
    this->mode_feedback = _arg;
    return *this;
  }
  Type & set__teach_status(
    const uint8_t & _arg)
  {
    this->teach_status = _arg;
    return *this;
  }
  Type & set__motion_status(
    const uint8_t & _arg)
  {
    this->motion_status = _arg;
    return *this;
  }
  Type & set__trajectory_num(
    const uint8_t & _arg)
  {
    this->trajectory_num = _arg;
    return *this;
  }
  Type & set__err_status(
    const int64_t & _arg)
  {
    this->err_status = _arg;
    return *this;
  }
  Type & set__joint_angle_limit(
    const std::vector<bool, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<bool>> & _arg)
  {
    this->joint_angle_limit = _arg;
    return *this;
  }
  Type & set__communication_status_joint(
    const std::vector<bool, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<bool>> & _arg)
  {
    this->communication_status_joint = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    agx_arm_msgs::msg::AgxArmStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const agx_arm_msgs::msg::AgxArmStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<agx_arm_msgs::msg::AgxArmStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<agx_arm_msgs::msg::AgxArmStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      agx_arm_msgs::msg::AgxArmStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<agx_arm_msgs::msg::AgxArmStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      agx_arm_msgs::msg::AgxArmStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<agx_arm_msgs::msg::AgxArmStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<agx_arm_msgs::msg::AgxArmStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<agx_arm_msgs::msg::AgxArmStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__agx_arm_msgs__msg__AgxArmStatus
    std::shared_ptr<agx_arm_msgs::msg::AgxArmStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__agx_arm_msgs__msg__AgxArmStatus
    std::shared_ptr<agx_arm_msgs::msg::AgxArmStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AgxArmStatus_ & other) const
  {
    if (this->ctrl_mode != other.ctrl_mode) {
      return false;
    }
    if (this->arm_status != other.arm_status) {
      return false;
    }
    if (this->mode_feedback != other.mode_feedback) {
      return false;
    }
    if (this->teach_status != other.teach_status) {
      return false;
    }
    if (this->motion_status != other.motion_status) {
      return false;
    }
    if (this->trajectory_num != other.trajectory_num) {
      return false;
    }
    if (this->err_status != other.err_status) {
      return false;
    }
    if (this->joint_angle_limit != other.joint_angle_limit) {
      return false;
    }
    if (this->communication_status_joint != other.communication_status_joint) {
      return false;
    }
    return true;
  }
  bool operator!=(const AgxArmStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AgxArmStatus_

// alias to use template instance with default allocator
using AgxArmStatus =
  agx_arm_msgs::msg::AgxArmStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace agx_arm_msgs

#endif  // AGX_ARM_MSGS__MSG__DETAIL__AGX_ARM_STATUS__STRUCT_HPP_
