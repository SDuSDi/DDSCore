// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from core_msgs:msg/AuxGlobalPosition.idl
// generated code does not contain a copyright notice
#include "core_msgs/msg/detail/aux_global_position__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "core_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "core_msgs/msg/detail/aux_global_position__struct.h"
#include "core_msgs/msg/detail/aux_global_position__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif


// forward declare type support functions


using _AuxGlobalPosition__ros_msg_type = core_msgs__msg__AuxGlobalPosition;

static bool _AuxGlobalPosition__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _AuxGlobalPosition__ros_msg_type * ros_message = static_cast<const _AuxGlobalPosition__ros_msg_type *>(untyped_ros_message);
  // Field name: speed
  {
    cdr << ros_message->speed;
  }

  // Field name: radius
  {
    cdr << ros_message->radius;
  }

  // Field name: yaw
  {
    cdr << ros_message->yaw;
  }

  // Field name: lat
  {
    cdr << ros_message->lat;
  }

  // Field name: lon
  {
    cdr << ros_message->lon;
  }

  // Field name: alt
  {
    cdr << ros_message->alt;
  }

  return true;
}

static bool _AuxGlobalPosition__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _AuxGlobalPosition__ros_msg_type * ros_message = static_cast<_AuxGlobalPosition__ros_msg_type *>(untyped_ros_message);
  // Field name: speed
  {
    cdr >> ros_message->speed;
  }

  // Field name: radius
  {
    cdr >> ros_message->radius;
  }

  // Field name: yaw
  {
    cdr >> ros_message->yaw;
  }

  // Field name: lat
  {
    cdr >> ros_message->lat;
  }

  // Field name: lon
  {
    cdr >> ros_message->lon;
  }

  // Field name: alt
  {
    cdr >> ros_message->alt;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_core_msgs
size_t get_serialized_size_core_msgs__msg__AuxGlobalPosition(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _AuxGlobalPosition__ros_msg_type * ros_message = static_cast<const _AuxGlobalPosition__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name speed
  {
    size_t item_size = sizeof(ros_message->speed);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name radius
  {
    size_t item_size = sizeof(ros_message->radius);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name yaw
  {
    size_t item_size = sizeof(ros_message->yaw);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name lat
  {
    size_t item_size = sizeof(ros_message->lat);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name lon
  {
    size_t item_size = sizeof(ros_message->lon);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name alt
  {
    size_t item_size = sizeof(ros_message->alt);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _AuxGlobalPosition__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_core_msgs__msg__AuxGlobalPosition(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_core_msgs
size_t max_serialized_size_core_msgs__msg__AuxGlobalPosition(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: speed
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: radius
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: yaw
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: lat
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: lon
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: alt
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = core_msgs__msg__AuxGlobalPosition;
    is_plain =
      (
      offsetof(DataType, alt) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _AuxGlobalPosition__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_core_msgs__msg__AuxGlobalPosition(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_AuxGlobalPosition = {
  "core_msgs::msg",
  "AuxGlobalPosition",
  _AuxGlobalPosition__cdr_serialize,
  _AuxGlobalPosition__cdr_deserialize,
  _AuxGlobalPosition__get_serialized_size,
  _AuxGlobalPosition__max_serialized_size
};

static rosidl_message_type_support_t _AuxGlobalPosition__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_AuxGlobalPosition,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, core_msgs, msg, AuxGlobalPosition)() {
  return &_AuxGlobalPosition__type_support;
}

#if defined(__cplusplus)
}
#endif
