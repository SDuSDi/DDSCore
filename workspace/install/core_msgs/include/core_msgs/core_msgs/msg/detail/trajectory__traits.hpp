// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from core_msgs:msg/Trajectory.idl
// generated code does not contain a copyright notice

#ifndef CORE_MSGS__MSG__DETAIL__TRAJECTORY__TRAITS_HPP_
#define CORE_MSGS__MSG__DETAIL__TRAJECTORY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "core_msgs/msg/detail/trajectory__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace core_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Trajectory & msg,
  std::ostream & out)
{
  out << "{";
  // member: x
  {
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << ", ";
  }

  // member: y
  {
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << ", ";
  }

  // member: z
  {
    out << "z: ";
    rosidl_generator_traits::value_to_yaml(msg.z, out);
    out << ", ";
  }

  // member: yaw
  {
    out << "yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Trajectory & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << "\n";
  }

  // member: z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "z: ";
    rosidl_generator_traits::value_to_yaml(msg.z, out);
    out << "\n";
  }

  // member: yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Trajectory & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace core_msgs

namespace rosidl_generator_traits
{

[[deprecated("use core_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const core_msgs::msg::Trajectory & msg,
  std::ostream & out, size_t indentation = 0)
{
  core_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use core_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const core_msgs::msg::Trajectory & msg)
{
  return core_msgs::msg::to_yaml(msg);
}

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
