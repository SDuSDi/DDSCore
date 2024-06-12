// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from core_msgs:msg/StatusProvider.idl
// generated code does not contain a copyright notice

#ifndef CORE_MSGS__MSG__DETAIL__STATUS_PROVIDER__STRUCT_H_
#define CORE_MSGS__MSG__DETAIL__STATUS_PROVIDER__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/StatusProvider in the package core_msgs.
typedef struct core_msgs__msg__StatusProvider
{
  double lat;
  double lon;
  float alt;
  uint8_t arming_state;
  uint8_t nav_state;
} core_msgs__msg__StatusProvider;

// Struct for a sequence of core_msgs__msg__StatusProvider.
typedef struct core_msgs__msg__StatusProvider__Sequence
{
  core_msgs__msg__StatusProvider * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} core_msgs__msg__StatusProvider__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CORE_MSGS__MSG__DETAIL__STATUS_PROVIDER__STRUCT_H_
