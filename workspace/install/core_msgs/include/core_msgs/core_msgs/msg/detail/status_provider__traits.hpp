// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from core_msgs:msg/StatusProvider.idl
// generated code does not contain a copyright notice

#ifndef CORE_MSGS__MSG__DETAIL__STATUS_PROVIDER__TRAITS_HPP_
#define CORE_MSGS__MSG__DETAIL__STATUS_PROVIDER__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "core_msgs/msg/detail/status_provider__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace core_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const StatusProvider & msg,
  std::ostream & out)
{
  out << "{";
  // member: lat
  {
    out << "lat: ";
    rosidl_generator_traits::value_to_yaml(msg.lat, out);
    out << ", ";
  }

  // member: lon
  {
    out << "lon: ";
    rosidl_generator_traits::value_to_yaml(msg.lon, out);
    out << ", ";
  }

  // member: alt
  {
    out << "alt: ";
    rosidl_generator_traits::value_to_yaml(msg.alt, out);
    out << ", ";
  }

  // member: arming_state
  {
    out << "arming_state: ";
    rosidl_generator_traits::value_to_yaml(msg.arming_state, out);
    out << ", ";
  }

  // member: nav_state
  {
    out << "nav_state: ";
    rosidl_generator_traits::value_to_yaml(msg.nav_state, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const StatusProvider & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: lat
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lat: ";
    rosidl_generator_traits::value_to_yaml(msg.lat, out);
    out << "\n";
  }

  // member: lon
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lon: ";
    rosidl_generator_traits::value_to_yaml(msg.lon, out);
    out << "\n";
  }

  // member: alt
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "alt: ";
    rosidl_generator_traits::value_to_yaml(msg.alt, out);
    out << "\n";
  }

  // member: arming_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "arming_state: ";
    rosidl_generator_traits::value_to_yaml(msg.arming_state, out);
    out << "\n";
  }

  // member: nav_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "nav_state: ";
    rosidl_generator_traits::value_to_yaml(msg.nav_state, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const StatusProvider & msg, bool use_flow_style = false)
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
  const core_msgs::msg::StatusProvider & msg,
  std::ostream & out, size_t indentation = 0)
{
  core_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use core_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const core_msgs::msg::StatusProvider & msg)
{
  return core_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<core_msgs::msg::StatusProvider>()
{
  return "core_msgs::msg::StatusProvider";
}

template<>
inline const char * name<core_msgs::msg::StatusProvider>()
{
  return "core_msgs/msg/StatusProvider";
}

template<>
struct has_fixed_size<core_msgs::msg::StatusProvider>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<core_msgs::msg::StatusProvider>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<core_msgs::msg::StatusProvider>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CORE_MSGS__MSG__DETAIL__STATUS_PROVIDER__TRAITS_HPP_
