# generated from ament/cmake/core/template/nameConfig.cmake.in

# prevent multiple inclusion
if(_aoa_ros_CONFIG_INCLUDED)
  return()
endif()
set(_aoa_ros_CONFIG_INCLUDED TRUE)

# output package information
if(NOT aoa_ros_FIND_QUIETLY)
  message(STATUS "Found aoa_ros: 0.0.0 (${aoa_ros_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'aoa_ros' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  message(WARNING "${_msg}")
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(aoa_ros_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${aoa_ros_DIR}/${_extra}")
endforeach()
