# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_link_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED link_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(link_FOUND FALSE)
  elseif(NOT link_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(link_FOUND FALSE)
  endif()
  return()
endif()
set(_link_CONFIG_INCLUDED TRUE)

# output package information
if(NOT link_FIND_QUIETLY)
  message(STATUS "Found link: 0.0.0 (${link_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'link' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${link_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(link_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${link_DIR}/${_extra}")
endforeach()
