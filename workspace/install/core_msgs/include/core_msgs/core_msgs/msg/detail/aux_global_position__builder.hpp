// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from core_msgs:msg/AuxGlobalPosition.idl
// generated code does not contain a copyright notice

#ifndef CORE_MSGS__MSG__DETAIL__AUX_GLOBAL_POSITION__BUILDER_HPP_
#define CORE_MSGS__MSG__DETAIL__AUX_GLOBAL_POSITION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "core_msgs/msg/detail/aux_global_position__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace core_msgs
{

namespace msg
{

namespace builder
{

class Init_AuxGlobalPosition_alt
{
public:
  explicit Init_AuxGlobalPosition_alt(::core_msgs::msg::AuxGlobalPosition & msg)
  : msg_(msg)
  {}
  ::core_msgs::msg::AuxGlobalPosition alt(::core_msgs::msg::AuxGlobalPosition::_alt_type arg)
  {
    msg_.alt = std::move(arg);
    return std::move(msg_);
  }

private:
  ::core_msgs::msg::AuxGlobalPosition msg_;
};

class Init_AuxGlobalPosition_lon
{
public:
  explicit Init_AuxGlobalPosition_lon(::core_msgs::msg::AuxGlobalPosition & msg)
  : msg_(msg)
  {}
  Init_AuxGlobalPosition_alt lon(::core_msgs::msg::AuxGlobalPosition::_lon_type arg)
  {
    msg_.lon = std::move(arg);
    return Init_AuxGlobalPosition_alt(msg_);
  }

private:
  ::core_msgs::msg::AuxGlobalPosition msg_;
};

class Init_AuxGlobalPosition_lat
{
public:
  explicit Init_AuxGlobalPosition_lat(::core_msgs::msg::AuxGlobalPosition & msg)
  : msg_(msg)
  {}
  Init_AuxGlobalPosition_lon lat(::core_msgs::msg::AuxGlobalPosition::_lat_type arg)
  {
    msg_.lat = std::move(arg);
    return Init_AuxGlobalPosition_lon(msg_);
  }

private:
  ::core_msgs::msg::AuxGlobalPosition msg_;
};

class Init_AuxGlobalPosition_yaw
{
public:
  explicit Init_AuxGlobalPosition_yaw(::core_msgs::msg::AuxGlobalPosition & msg)
  : msg_(msg)
  {}
  Init_AuxGlobalPosition_lat yaw(::core_msgs::msg::AuxGlobalPosition::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return Init_AuxGlobalPosition_lat(msg_);
  }

private:
  ::core_msgs::msg::AuxGlobalPosition msg_;
};

class Init_AuxGlobalPosition_radius
{
public:
  explicit Init_AuxGlobalPosition_radius(::core_msgs::msg::AuxGlobalPosition & msg)
  : msg_(msg)
  {}
  Init_AuxGlobalPosition_yaw radius(::core_msgs::msg::AuxGlobalPosition::_radius_type arg)
  {
    msg_.radius = std::move(arg);
    return Init_AuxGlobalPosition_yaw(msg_);
  }

private:
  ::core_msgs::msg::AuxGlobalPosition msg_;
};

class Init_AuxGlobalPosition_speed
{
public:
  Init_AuxGlobalPosition_speed()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_AuxGlobalPosition_radius speed(::core_msgs::msg::AuxGlobalPosition::_speed_type arg)
  {
    msg_.speed = std::move(arg);
    return Init_AuxGlobalPosition_radius(msg_);
  }

private:
  ::core_msgs::msg::AuxGlobalPosition msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::core_msgs::msg::AuxGlobalPosition>()
{
  return core_msgs::msg::builder::Init_AuxGlobalPosition_speed();
}

}  // namespace core_msgs

#endif  // CORE_MSGS__MSG__DETAIL__AUX_GLOBAL_POSITION__BUILDER_HPP_
