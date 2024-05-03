// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from core_msgs:msg/AuxGlobalPosition.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "core_msgs/msg/detail/aux_global_position__rosidl_typesupport_introspection_c.h"
#include "core_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "core_msgs/msg/detail/aux_global_position__functions.h"
#include "core_msgs/msg/detail/aux_global_position__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void AuxGlobalPosition__rosidl_typesupport_introspection_c__AuxGlobalPosition_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  core_msgs__msg__AuxGlobalPosition__init(message_memory);
}

void AuxGlobalPosition__rosidl_typesupport_introspection_c__AuxGlobalPosition_fini_function(void * message_memory)
{
  core_msgs__msg__AuxGlobalPosition__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember AuxGlobalPosition__rosidl_typesupport_introspection_c__AuxGlobalPosition_message_member_array[3] = {
  {
    "lat",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(core_msgs__msg__AuxGlobalPosition, lat),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
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
    offsetof(core_msgs__msg__AuxGlobalPosition, lon),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
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
    offsetof(core_msgs__msg__AuxGlobalPosition, alt),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers AuxGlobalPosition__rosidl_typesupport_introspection_c__AuxGlobalPosition_message_members = {
  "core_msgs__msg",  // message namespace
  "AuxGlobalPosition",  // message name
  3,  // number of fields
  sizeof(core_msgs__msg__AuxGlobalPosition),
  AuxGlobalPosition__rosidl_typesupport_introspection_c__AuxGlobalPosition_message_member_array,  // message members
  AuxGlobalPosition__rosidl_typesupport_introspection_c__AuxGlobalPosition_init_function,  // function to initialize message memory (memory has to be allocated)
  AuxGlobalPosition__rosidl_typesupport_introspection_c__AuxGlobalPosition_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t AuxGlobalPosition__rosidl_typesupport_introspection_c__AuxGlobalPosition_message_type_support_handle = {
  0,
  &AuxGlobalPosition__rosidl_typesupport_introspection_c__AuxGlobalPosition_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_core_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, core_msgs, msg, AuxGlobalPosition)() {
  if (!AuxGlobalPosition__rosidl_typesupport_introspection_c__AuxGlobalPosition_message_type_support_handle.typesupport_identifier) {
    AuxGlobalPosition__rosidl_typesupport_introspection_c__AuxGlobalPosition_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &AuxGlobalPosition__rosidl_typesupport_introspection_c__AuxGlobalPosition_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
