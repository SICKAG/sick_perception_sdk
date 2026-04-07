# Set boolean defines based on BUILD_EXAMPLES_DEVICE_TYPE
set(USE_PICOSCAN100 OFF)
set(USE_MULTISCAN100 OFF)
set(USE_LRS4000 OFF)
if(BUILD_EXAMPLES_DEVICE_TYPE STREQUAL "picoScan100")
  set(USE_PICOSCAN100 ON)
elseif(BUILD_EXAMPLES_DEVICE_TYPE STREQUAL "multiScan100")
  set(USE_MULTISCAN100 ON)
elseif(BUILD_EXAMPLES_DEVICE_TYPE STREQUAL "LRS4000")
  set(USE_LRS4000 ON)
else()
  message(FATAL_ERROR "Invalid BUILD_EXAMPLES_DEVICE_TYPE: ${BUILD_EXAMPLES_DEVICE_TYPE}. Valid values: picoScan100, multiScan100, LRS4000")
endif()

# Function to add an example project.
# Usage: add_example(FAMILY <device_family> TARGET <target_name> [SOURCES <file1> <file2> ...] [DEPENDENCIES <dep1> <dep2> ... ])
function(add_example)
  set(options "")
  set(oneValueArgs FAMILY TARGET)
  set(multiValueArgs SOURCES DEPENDENCIES)
  cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  if(NOT ARG_FAMILY)
    message(FATAL_ERROR "add_example: FAMILY argument is required")
  endif()
  if(NOT ARG_TARGET)
    message(FATAL_ERROR "add_example: TARGET argument is required")
  endif()

  set(TARGET_NAME "${ARG_FAMILY}_${ARG_TARGET}_example")

  add_executable(${TARGET_NAME})

  if(ARG_SOURCES)
    target_sources(${TARGET_NAME} PRIVATE ${ARG_SOURCES})
  else()
    target_sources(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${ARG_TARGET}.cpp)
  endif()

  if(ARG_DEPENDENCIES)
    target_link_libraries(${TARGET_NAME} PRIVATE ${ARG_DEPENDENCIES})
  endif()

  # Apply device type compile definitions for shared examples
  if(USE_PICOSCAN100)
    target_compile_definitions(${TARGET_NAME} PRIVATE USE_PICOSCAN100)
  endif()
  if(USE_MULTISCAN100)
    target_compile_definitions(${TARGET_NAME} PRIVATE USE_MULTISCAN100)
  endif()
  if(USE_LRS4000)
    target_compile_definitions(${TARGET_NAME} PRIVATE USE_LRS4000)
  endif()
endfunction()
