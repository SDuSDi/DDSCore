// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from core_msgs:msg/Trajectory.idl
// generated code does not contain a copyright notice

#ifndef CORE_MSGS__MSG__DETAIL__TRAJECTORY__STRUCT_H_
#define CORE_MSGS__MSG__DETAIL__TRAJECTORY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/Trajectory in the package core_msgs.
typedef struct core_msgs__msg__Trajectory
{
  float x;
  float y;
  float z;
  float yaw;
} core_msgs__msg__Trajectory;

// Struct for a sequence of core_msgs__msg__Trajectory.
typedef struct core_msgs__msg__Trajectory__Sequence
{
  core_msgs__msg__Trajectory * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} core_msgs__msg__Trajectory__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CORE_MSGS__MSG__DETAIL__TRAJECTORY__STRUCT_H_
