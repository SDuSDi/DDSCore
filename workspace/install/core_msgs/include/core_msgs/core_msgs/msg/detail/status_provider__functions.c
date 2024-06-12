// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from core_msgs:msg/StatusProvider.idl
// generated code does not contain a copyright notice
#include "core_msgs/msg/detail/status_provider__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
core_msgs__msg__StatusProvider__init(core_msgs__msg__StatusProvider * msg)
{
  if (!msg) {
    return false;
  }
  // lat
  // lon
  // alt
  // arming_state
  // nav_state
  return true;
}

void
core_msgs__msg__StatusProvider__fini(core_msgs__msg__StatusProvider * msg)
{
  if (!msg) {
    return;
  }
  // lat
  // lon
  // alt
  // arming_state
  // nav_state
}

bool
core_msgs__msg__StatusProvider__are_equal(const core_msgs__msg__StatusProvider * lhs, const core_msgs__msg__StatusProvider * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // lat
  if (lhs->lat != rhs->lat) {
    return false;
  }
  // lon
  if (lhs->lon != rhs->lon) {
    return false;
  }
  // alt
  if (lhs->alt != rhs->alt) {
    return false;
  }
  // arming_state
  if (lhs->arming_state != rhs->arming_state) {
    return false;
  }
  // nav_state
  if (lhs->nav_state != rhs->nav_state) {
    return false;
  }
  return true;
}

bool
core_msgs__msg__StatusProvider__copy(
  const core_msgs__msg__StatusProvider * input,
  core_msgs__msg__StatusProvider * output)
{
  if (!input || !output) {
    return false;
  }
  // lat
  output->lat = input->lat;
  // lon
  output->lon = input->lon;
  // alt
  output->alt = input->alt;
  // arming_state
  output->arming_state = input->arming_state;
  // nav_state
  output->nav_state = input->nav_state;
  return true;
}

core_msgs__msg__StatusProvider *
core_msgs__msg__StatusProvider__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  core_msgs__msg__StatusProvider * msg = (core_msgs__msg__StatusProvider *)allocator.allocate(sizeof(core_msgs__msg__StatusProvider), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(core_msgs__msg__StatusProvider));
  bool success = core_msgs__msg__StatusProvider__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
core_msgs__msg__StatusProvider__destroy(core_msgs__msg__StatusProvider * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    core_msgs__msg__StatusProvider__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
core_msgs__msg__StatusProvider__Sequence__init(core_msgs__msg__StatusProvider__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  core_msgs__msg__StatusProvider * data = NULL;

  if (size) {
    data = (core_msgs__msg__StatusProvider *)allocator.zero_allocate(size, sizeof(core_msgs__msg__StatusProvider), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = core_msgs__msg__StatusProvider__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        core_msgs__msg__StatusProvider__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
core_msgs__msg__StatusProvider__Sequence__fini(core_msgs__msg__StatusProvider__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      core_msgs__msg__StatusProvider__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

core_msgs__msg__StatusProvider__Sequence *
core_msgs__msg__StatusProvider__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  core_msgs__msg__StatusProvider__Sequence * array = (core_msgs__msg__StatusProvider__Sequence *)allocator.allocate(sizeof(core_msgs__msg__StatusProvider__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = core_msgs__msg__StatusProvider__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
core_msgs__msg__StatusProvider__Sequence__destroy(core_msgs__msg__StatusProvider__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    core_msgs__msg__StatusProvider__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
core_msgs__msg__StatusProvider__Sequence__are_equal(const core_msgs__msg__StatusProvider__Sequence * lhs, const core_msgs__msg__StatusProvider__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!core_msgs__msg__StatusProvider__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
core_msgs__msg__StatusProvider__Sequence__copy(
  const core_msgs__msg__StatusProvider__Sequence * input,
  core_msgs__msg__StatusProvider__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(core_msgs__msg__StatusProvider);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    core_msgs__msg__StatusProvider * data =
      (core_msgs__msg__StatusProvider *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!core_msgs__msg__StatusProvider__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          core_msgs__msg__StatusProvider__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!core_msgs__msg__StatusProvider__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
