// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from core_msgs:msg/AuxGlobalPosition.idl
// generated code does not contain a copyright notice

#ifndef CORE_MSGS__MSG__DETAIL__AUX_GLOBAL_POSITION__TRAITS_HPP_
#define CORE_MSGS__MSG__DETAIL__AUX_GLOBAL_POSITION__TRAITS_HPP_

#include "core_msgs/msg/detail/aux_global_position__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<core_msgs::msg::AuxGlobalPosition>()
{
  return "core_msgs::msg::AuxGlobalPosition";
}

template<>
inline const char * name<core_msgs::msg::AuxGlobalPosition>()
{
  return "core_msgs/msg/AuxGlobalPosition";
}

template<>
struct has_fixed_size<core_msgs::msg::AuxGlobalPosition>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<core_msgs::msg::AuxGlobalPosition>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<core_msgs::msg::AuxGlobalPosition>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CORE_MSGS__MSG__DETAIL__AUX_GLOBAL_POSITION__TRAITS_HPP_
