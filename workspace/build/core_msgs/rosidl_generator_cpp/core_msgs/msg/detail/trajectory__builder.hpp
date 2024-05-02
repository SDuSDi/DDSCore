// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from core_msgs:msg/Trajectory.idl
// generated code does not contain a copyright notice

#ifndef CORE_MSGS__MSG__DETAIL__TRAJECTORY__BUILDER_HPP_
#define CORE_MSGS__MSG__DETAIL__TRAJECTORY__BUILDER_HPP_

#include "core_msgs/msg/detail/trajectory__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace core_msgs
{

namespace msg
{

namespace builder
{

class Init_Trajectory_yaw
{
public:
  explicit Init_Trajectory_yaw(::core_msgs::msg::Trajectory & msg)
  : msg_(msg)
  {}
  ::core_msgs::msg::Trajectory yaw(::core_msgs::msg::Trajectory::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return std::move(msg_);
  }

private:
  ::core_msgs::msg::Trajectory msg_;
};

class Init_Trajectory_z
{
public:
  explicit Init_Trajectory_z(::core_msgs::msg::Trajectory & msg)
  : msg_(msg)
  {}
  Init_Trajectory_yaw z(::core_msgs::msg::Trajectory::_z_type arg)
  {
    msg_.z = std::move(arg);
    return Init_Trajectory_yaw(msg_);
  }

private:
  ::core_msgs::msg::Trajectory msg_;
};

class Init_Trajectory_y
{
public:
  explicit Init_Trajectory_y(::core_msgs::msg::Trajectory & msg)
  : msg_(msg)
  {}
  Init_Trajectory_z y(::core_msgs::msg::Trajectory::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_Trajectory_z(msg_);
  }

private:
  ::core_msgs::msg::Trajectory msg_;
};

class Init_Trajectory_x
{
public:
  Init_Trajectory_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Trajectory_y x(::core_msgs::msg::Trajectory::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_Trajectory_y(msg_);
  }

private:
  ::core_msgs::msg::Trajectory msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::core_msgs::msg::Trajectory>()
{
  return core_msgs::msg::builder::Init_Trajectory_x();
}

}  // namespace core_msgs

#endif  // CORE_MSGS__MSG__DETAIL__TRAJECTORY__BUILDER_HPP_
