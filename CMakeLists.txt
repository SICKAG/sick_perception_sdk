cmake_minimum_required(VERSION 3.22)
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/Version.txt" VERSION_FILE_CONTENT)
string(REGEX MATCH "version=\"([^\"]+)\"" _ "${VERSION_FILE_CONTENT}")
set(PROJECT_VERSION "${CMAKE_MATCH_1}")
string(REGEX MATCH "preRelease=\"([^\"]+)\"" _ "${VERSION_FILE_CONTENT}")
set(PRE_RELEASE_VERSION "${CMAKE_MATCH_1}")
project(sick_perception_sdk VERSION ${PROJECT_VERSION} LANGUAGES CXX)

#===============================================================================
# User configuration for the SDK package.
#===============================================================================
option(BUILD_DRIVERS "Add the library `drivers` to the cmake build." ON)
option(BUILD_COMPACT_FORMAT "Add the library `compact_format` to the cmake build." ON)
option(BUILD_SENSOR_CONFIGURATION "Add the library `sensor_configuration` to the cmake build." ON)
option(BUILD_BENCHMARKS "Build benchmarks for the libraries" OFF)
option(BUILD_UNIT_TESTS "Build unit tests for the libraries" OFF)
set(BUILD_EXAMPLES_DEVICE_TYPE "" CACHE STRING "Set the device type for examples")
set_property(CACHE BUILD_EXAMPLES_DEVICE_TYPE PROPERTY STRINGS "" "all" "LRS4000" "multiScan100" "picoScan100")
set(valid_device_types "" "all" "LRS4000" "multiScan100" "picoScan100")
list(FIND valid_device_types "${BUILD_EXAMPLES_DEVICE_TYPE}" idx)
if(idx EQUAL -1)
    message(FATAL_ERROR "Invalid BUILD_EXAMPLES_DEVICE_TYPE: ${BUILD_EXAMPLES_DEVICE_TYPE}")
endif()
option(BUILD_SHARED_LIBS "Build shared libraries (dll on Windows, so on Linux)" OFF)

# ------------------------------------------------------------------------------
# Configuration options for third-party dependencies.
# ------------------------------------------------------------------------------
option(TRY_TO_USE_ZLIB "Try to use zlib for CRC32, otherwise use internal (slower) implementation" ON)

# For Windows set the OpenSSL root directory to the installation path of OpenSSL.
# Adjust the path if OpenSSL is installed in a different location. The default path shown is for the
# installation from Shining Light Productions.
if (WIN32)
  if (NOT EXISTS "${CMAKE_BINARY_DIR}/generators/conan_toolchain.cmake")
    set(OPENSSL_ROOT_DIR "C:/Program Files/OpenSSL-Win64" CACHE STRING "Path to OpenSSL root directory")
  else()
    # Unset the cache variable when using Conan to let Conan's FindOpenSSL.cmake handle it
    unset(OPENSSL_ROOT_DIR CACHE)
  endif()
endif()

#===============================================================================
# Internal dependency logic
#===============================================================================
if(NOT BUILD_EXAMPLES_DEVICE_TYPE STREQUAL "")
  set(BUILD_DRIVERS ON)
  set(BUILD_SENSOR_CONFIGURATION ON)
  set(BUILD_COMPACT_FORMAT ON)
endif()

if (BUILD_UNIT_TESTS)
  set(BUILD_COMPACT_FORMAT ON)
  set(BUILD_SENSOR_CONFIGURATION ON)
endif()

if (BUILD_DRIVERS)
  set(BUILD_COMMON ON)
  set(BUILD_SENSOR_CONFIGURATION ON)
  set(BUILD_COMPACT_FORMAT ON)
endif()

if (BUILD_SENSOR_CONFIGURATION OR BUILD_COMPACT_FORMAT)
  set(BUILD_COMMON ON)
endif()

#===============================================================================
# Configure cmake
#===============================================================================
include(GNUInstallDirs)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#===============================================================================
# SDK Libraries
#===============================================================================
if (BUILD_COMMON)
  add_subdirectory(src/common)
endif()

if (BUILD_COMPACT_FORMAT)
  add_subdirectory(src/compact_format)
endif()

if (BUILD_SENSOR_CONFIGURATION)
  add_subdirectory(src/sensor_configuration)
endif()

if (BUILD_DRIVERS)
  add_subdirectory(src/drivers)
endif()

if (NOT BUILD_EXAMPLES_DEVICE_TYPE STREQUAL "")
  add_subdirectory(examples)
endif()

#===============================================================================
# Project export
#===============================================================================
include(CMakePackageConfigHelpers)

configure_package_config_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/${PROJECT_NAME}-config.cmake.in
  ${PROJECT_NAME}-config.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

write_basic_package_version_file(
  "${CMAKE_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

install(
  FILES
    "${CMAKE_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
    "${CMAKE_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
  DESTINATION 
    ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

install(
  EXPORT ${PROJECT_NAME}-config
  FILE ${PROJECT_NAME}-config-targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
