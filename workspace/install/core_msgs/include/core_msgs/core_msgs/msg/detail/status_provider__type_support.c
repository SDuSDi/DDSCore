// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from core_msgs:msg/StatusProvider.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "core_msgs/msg/detail/status_provider__rosidl_typesupport_introspection_c.h"
#include "core_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "core_msgs/msg/detail/status_provider__functions.h"
#include "core_msgs/msg/detail/status_provider__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void core_msgs__msg__StatusProvider__rosidl_typesupport_introspection_c__StatusProvider_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  core_msgs__msg__StatusProvider__init(message_memory);
}

void core_msgs__msg__StatusProvider__rosidl_typesupport_introspection_c__StatusProvider_fini_function(void * message_memory)
{
  core_msgs__msg__StatusProvider__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember core_msgs__msg__StatusProvider__rosidl_typesupport_introspection_c__StatusProvider_message_member_array[5] = {
  {
    "lat",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(core_msgs__msg__StatusProvider, lat),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "lon",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(core_msgs__msg__StatusProvider, lon),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "alt",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(core_msgs__msg__StatusProvider, alt),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "arming_state",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(core_msgs__msg__StatusProvider, arming_state),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "nav_state",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(core_msgs__msg__StatusProvider, nav_state),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers core_msgs__msg__StatusProvider__rosidl_typesupport_introspection_c__StatusProvider_message_members = {
  "core_msgs__msg",  // message namespace
  "StatusProvider",  // message name
  5,  // number of fields
  sizeof(core_msgs__msg__StatusProvider),
  core_msgs__msg__StatusProvider__rosidl_typesupport_introspection_c__StatusProvider_message_member_array,  // message members
  core_msgs__msg__StatusProvider__rosidl_typesupport_introspection_c__StatusProvider_init_function,  // function to initialize message memory (memory has to be allocated)
  core_msgs__msg__StatusProvider__rosidl_typesupport_introspection_c__StatusProvider_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t core_msgs__msg__StatusProvider__rosidl_typesupport_introspection_c__StatusProvider_message_type_support_handle = {
  0,
  &core_msgs__msg__StatusProvider__rosidl_typesupport_introspection_c__StatusProvider_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_core_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, core_msgs, msg, StatusProvider)() {
  if (!core_msgs__msg__StatusProvider__rosidl_typesupport_introspection_c__StatusProvider_message_type_support_handle.typesupport_identifier) {
    core_msgs__msg__StatusProvider__rosidl_typesupport_introspection_c__StatusProvider_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &core_msgs__msg__StatusProvider__rosidl_typesupport_introspection_c__StatusProvider_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
