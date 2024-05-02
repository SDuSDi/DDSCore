// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from core_msgs:msg/Trajectory.idl
// generated code does not contain a copyright notice

#ifndef CORE_MSGS__MSG__DETAIL__TRAJECTORY__TRAITS_HPP_
#define CORE_MSGS__MSG__DETAIL__TRAJECTORY__TRAITS_HPP_

#include "core_msgs/msg/detail/trajectory__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<core_msgs::msg::Trajectory>()
{
  return "core_msgs::msg::Trajectory";
}

template<>
inline const char * name<core_msgs::msg::Trajectory>()
{
  return "core_msgs/msg/Trajectory";
}

template<>
struct has_fixed_size<core_msgs::msg::Trajectory>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<core_msgs::msg::Trajectory>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<core_msgs::msg::Trajectory>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CORE_MSGS__MSG__DETAIL__TRAJECTORY__TRAITS_HPP_
