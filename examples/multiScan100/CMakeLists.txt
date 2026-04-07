# cmake versions >= 3.5 are compatible with cmake 4, versions >= 3.10 are not deprecated.
cmake_minimum_required(VERSION 3.22)
project(sick_perception_sdk_multiScan100_examples)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(IS_ROOT_PROJECT TRUE)
else()
  set(IS_ROOT_PROJECT FALSE)
endif()

set(BUILD_EXAMPLES_DEVICE_TYPE "multiScan100")

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/compiler-defines.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/../examples.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (IS_ROOT_PROJECT)
  find_package(sick_perception_sdk COMPONENTS compact_format drivers sensor_configuration REQUIRED)
endif()

add_example(
  FAMILY multiScan100
  TARGET diagnosis
  DEPENDENCIES sick_perception_sdk::drivers sick_perception_sdk::sensor_configuration
)

add_subdirectory(../shared ${CMAKE_CURRENT_BINARY_DIR}/shared)
