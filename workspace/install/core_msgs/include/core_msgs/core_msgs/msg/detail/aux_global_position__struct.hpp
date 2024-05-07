// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from core_msgs:msg/AuxGlobalPosition.idl
// generated code does not contain a copyright notice

#ifndef CORE_MSGS__MSG__DETAIL__AUX_GLOBAL_POSITION__STRUCT_HPP_
#define CORE_MSGS__MSG__DETAIL__AUX_GLOBAL_POSITION__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__core_msgs__msg__AuxGlobalPosition __attribute__((deprecated))
#else
# define DEPRECATED__core_msgs__msg__AuxGlobalPosition __declspec(deprecated)
#endif

namespace core_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct AuxGlobalPosition_
{
  using Type = AuxGlobalPosition_<ContainerAllocator>;

  explicit AuxGlobalPosition_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->lat = 0.0;
      this->lon = 0.0;
      this->alt = 0.0f;
    }
  }

  explicit AuxGlobalPosition_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->lat = 0.0;
      this->lon = 0.0;
      this->alt = 0.0f;
    }
  }

  // field types and members
  using _lat_type =
    double;
  _lat_type lat;
  using _lon_type =
    double;
  _lon_type lon;
  using _alt_type =
    float;
  _alt_type alt;

  // setters for named parameter idiom
  Type & set__lat(
    const double & _arg)
  {
    this->lat = _arg;
    return *this;
  }
  Type & set__lon(
    const double & _arg)
  {
    this->lon = _arg;
    return *this;
  }
  Type & set__alt(
    const float & _arg)
  {
    this->alt = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    core_msgs::msg::AuxGlobalPosition_<ContainerAllocator> *;
  using ConstRawPtr =
    const core_msgs::msg::AuxGlobalPosition_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<core_msgs::msg::AuxGlobalPosition_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<core_msgs::msg::AuxGlobalPosition_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      core_msgs::msg::AuxGlobalPosition_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<core_msgs::msg::AuxGlobalPosition_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      core_msgs::msg::AuxGlobalPosition_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<core_msgs::msg::AuxGlobalPosition_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<core_msgs::msg::AuxGlobalPosition_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<core_msgs::msg::AuxGlobalPosition_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__core_msgs__msg__AuxGlobalPosition
    std::shared_ptr<core_msgs::msg::AuxGlobalPosition_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__core_msgs__msg__AuxGlobalPosition
    std::shared_ptr<core_msgs::msg::AuxGlobalPosition_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const AuxGlobalPosition_ & other) const
  {
    if (this->lat != other.lat) {
      return false;
    }
    if (this->lon != other.lon) {
      return false;
    }
    if (this->alt != other.alt) {
      return false;
    }
    return true;
  }
  bool operator!=(const AuxGlobalPosition_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct AuxGlobalPosition_

// alias to use template instance with default allocator
using AuxGlobalPosition =
  core_msgs::msg::AuxGlobalPosition_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace core_msgs

#endif  // CORE_MSGS__MSG__DETAIL__AUX_GLOBAL_POSITION__STRUCT_HPP_
