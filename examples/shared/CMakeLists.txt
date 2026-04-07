# cmake versions >= 3.5 are compatible with cmake 4, versions >= 3.10 are not deprecated.
cmake_minimum_required(VERSION 3.22)
project(sick_perception_sdk_shared_examples)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(IS_ROOT_PROJECT TRUE)
else()
  set(IS_ROOT_PROJECT FALSE)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/../../cmake/compiler-defines.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/../examples.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (IS_ROOT_PROJECT)
  find_package(sick_perception_sdk COMPONENTS compact_format drivers sensor_configuration REQUIRED)
endif()


add_example(
  FAMILY ${BUILD_EXAMPLES_DEVICE_TYPE}
  TARGET change_ip_address
  DEPENDENCIES sick_perception_sdk::drivers sick_perception_sdk::sensor_configuration
)

add_example(
  FAMILY ${BUILD_EXAMPLES_DEVICE_TYPE}
  TARGET configuration
  DEPENDENCIES sick_perception_sdk::drivers sick_perception_sdk::sensor_configuration
)

add_example(
  FAMILY ${BUILD_EXAMPLES_DEVICE_TYPE}
  TARGET print_version
  DEPENDENCIES sick_perception_sdk::drivers sick_perception_sdk::sensor_configuration
)

# TCP streaming examples (LRS4000 only)
if(USE_LRS4000)
  add_example(
    FAMILY ${BUILD_EXAMPLES_DEVICE_TYPE}
    TARGET data_streaming_tcp
    DEPENDENCIES sick_perception_sdk::drivers sick_perception_sdk::sensor_configuration
  )

  add_example(
    FAMILY ${BUILD_EXAMPLES_DEVICE_TYPE}
    TARGET low_level_streaming_tcp
    DEPENDENCIES sick_perception_sdk::drivers
  )
endif()

# UDP streaming examples (picoScan100 and multiScan100 only)
if(USE_PICOSCAN100 OR USE_MULTISCAN100)
  add_example(
    FAMILY ${BUILD_EXAMPLES_DEVICE_TYPE}
    TARGET data_streaming_udp
    DEPENDENCIES sick_perception_sdk::drivers sick_perception_sdk::sensor_configuration
  )

  add_example(
    FAMILY ${BUILD_EXAMPLES_DEVICE_TYPE}
    TARGET multiple_devices
    DEPENDENCIES sick_perception_sdk::drivers sick_perception_sdk::sensor_configuration
  )

  add_example(
    FAMILY ${BUILD_EXAMPLES_DEVICE_TYPE}
    TARGET segmented_data
    DEPENDENCIES sick_perception_sdk::drivers sick_perception_sdk::sensor_configuration
  )

  add_example(
    FAMILY ${BUILD_EXAMPLES_DEVICE_TYPE}
    TARGET low_level_streaming_udp
    DEPENDENCIES sick_perception_sdk::drivers
  )

  add_example(
  FAMILY ${BUILD_EXAMPLES_DEVICE_TYPE}
  TARGET write_to_pcd_files
  DEPENDENCIES sick_perception_sdk::drivers sick_perception_sdk::sensor_configuration
)
endif()

add_example(
  FAMILY ${BUILD_EXAMPLES_DEVICE_TYPE}
  TARGET data_streaming_roi
  DEPENDENCIES sick_perception_sdk::drivers sick_perception_sdk::sensor_configuration
)

# Download and import config examples (picoScan100, multiScan100)
if(USE_PICOSCAN100 OR USE_MULTISCAN100)
  add_example(
    FAMILY ${BUILD_EXAMPLES_DEVICE_TYPE}
    TARGET download_and_import_config
    DEPENDENCIES sick_perception_sdk::sensor_configuration
  )
endif()

# Object detection examples (picoScan100, multiScan100 and LRS4000)
if(USE_PICOSCAN100 OR USE_MULTISCAN100 OR USE_LRS4000)
  add_example(
    FAMILY ${BUILD_EXAMPLES_DEVICE_TYPE}
    TARGET object_detection
    DEPENDENCIES sick_perception_sdk::drivers sick_perception_sdk::sensor_configuration
  )
endif()
