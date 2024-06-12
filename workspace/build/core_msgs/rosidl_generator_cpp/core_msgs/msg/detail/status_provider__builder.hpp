// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from core_msgs:msg/StatusProvider.idl
// generated code does not contain a copyright notice

#ifndef CORE_MSGS__MSG__DETAIL__STATUS_PROVIDER__BUILDER_HPP_
#define CORE_MSGS__MSG__DETAIL__STATUS_PROVIDER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "core_msgs/msg/detail/status_provider__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace core_msgs
{

namespace msg
{

namespace builder
{

class Init_StatusProvider_nav_state
{
public:
  explicit Init_StatusProvider_nav_state(::core_msgs::msg::StatusProvider & msg)
  : msg_(msg)
  {}
  ::core_msgs::msg::StatusProvider nav_state(::core_msgs::msg::StatusProvider::_nav_state_type arg)
  {
    msg_.nav_state = std::move(arg);
    return std::move(msg_);
  }

private:
  ::core_msgs::msg::StatusProvider msg_;
};

class Init_StatusProvider_arming_state
{
public:
  explicit Init_StatusProvider_arming_state(::core_msgs::msg::StatusProvider & msg)
  : msg_(msg)
  {}
  Init_StatusProvider_nav_state arming_state(::core_msgs::msg::StatusProvider::_arming_state_type arg)
  {
    msg_.arming_state = std::move(arg);
    return Init_StatusProvider_nav_state(msg_);
  }

private:
  ::core_msgs::msg::StatusProvider msg_;
};

class Init_StatusProvider_alt
{
public:
  explicit Init_StatusProvider_alt(::core_msgs::msg::StatusProvider & msg)
  : msg_(msg)
  {}
  Init_StatusProvider_arming_state alt(::core_msgs::msg::StatusProvider::_alt_type arg)
  {
    msg_.alt = std::move(arg);
    return Init_StatusProvider_arming_state(msg_);
  }

private:
  ::core_msgs::msg::StatusProvider msg_;
};

class Init_StatusProvider_lon
{
public:
  explicit Init_StatusProvider_lon(::core_msgs::msg::StatusProvider & msg)
  : msg_(msg)
  {}
  Init_StatusProvider_alt lon(::core_msgs::msg::StatusProvider::_lon_type arg)
  {
    msg_.lon = std::move(arg);
    return Init_StatusProvider_alt(msg_);
  }

private:
  ::core_msgs::msg::StatusProvider msg_;
};

class Init_StatusProvider_lat
{
public:
  Init_StatusProvider_lat()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_StatusProvider_lon lat(::core_msgs::msg::StatusProvider::_lat_type arg)
  {
    msg_.lat = std::move(arg);
    return Init_StatusProvider_lon(msg_);
  }

private:
  ::core_msgs::msg::StatusProvider msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::core_msgs::msg::StatusProvider>()
{
  return core_msgs::msg::builder::Init_StatusProvider_lat();
}

}  // namespace core_msgs

#endif  // CORE_MSGS__MSG__DETAIL__STATUS_PROVIDER__BUILDER_HPP_
