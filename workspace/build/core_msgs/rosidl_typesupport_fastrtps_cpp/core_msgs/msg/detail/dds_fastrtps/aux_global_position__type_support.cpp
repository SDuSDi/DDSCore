// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from core_msgs:msg/AuxGlobalPosition.idl
// generated code does not contain a copyright notice
#include "core_msgs/msg/detail/aux_global_position__rosidl_typesupport_fastrtps_cpp.hpp"
#include "core_msgs/msg/detail/aux_global_position__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace core_msgs
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_core_msgs
cdr_serialize(
  const core_msgs::msg::AuxGlobalPosition & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: lat
  cdr << ros_message.lat;
  // Member: lon
  cdr << ros_message.lon;
  // Member: alt
  cdr << ros_message.alt;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_core_msgs
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  core_msgs::msg::AuxGlobalPosition & ros_message)
{
  // Member: lat
  cdr >> ros_message.lat;

  // Member: lon
  cdr >> ros_message.lon;

  // Member: alt
  cdr >> ros_message.alt;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_core_msgs
get_serialized_size(
  const core_msgs::msg::AuxGlobalPosition & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: lat
  {
    size_t item_size = sizeof(ros_message.lat);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: lon
  {
    size_t item_size = sizeof(ros_message.lon);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: alt
  {
    size_t item_size = sizeof(ros_message.alt);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_core_msgs
max_serialized_size_AuxGlobalPosition(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;


  // Member: lat
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: lon
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Member: alt
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  return current_alignment - initial_alignment;
}

static bool _AuxGlobalPosition__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const core_msgs::msg::AuxGlobalPosition *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _AuxGlobalPosition__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<core_msgs::msg::AuxGlobalPosition *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _AuxGlobalPosition__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const core_msgs::msg::AuxGlobalPosition *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _AuxGlobalPosition__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_AuxGlobalPosition(full_bounded, 0);
}

static message_type_support_callbacks_t _AuxGlobalPosition__callbacks = {
  "core_msgs::msg",
  "AuxGlobalPosition",
  _AuxGlobalPosition__cdr_serialize,
  _AuxGlobalPosition__cdr_deserialize,
  _AuxGlobalPosition__get_serialized_size,
  _AuxGlobalPosition__max_serialized_size
};

static rosidl_message_type_support_t _AuxGlobalPosition__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_AuxGlobalPosition__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace core_msgs

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_core_msgs
const rosidl_message_type_support_t *
get_message_type_support_handle<core_msgs::msg::AuxGlobalPosition>()
{
  return &core_msgs::msg::typesupport_fastrtps_cpp::_AuxGlobalPosition__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, core_msgs, msg, AuxGlobalPosition)() {
  return &core_msgs::msg::typesupport_fastrtps_cpp::_AuxGlobalPosition__handle;
}

#ifdef __cplusplus
}
#endif
