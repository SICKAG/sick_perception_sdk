cmake_minimum_required(VERSION 3.22)

include(${CMAKE_SOURCE_DIR}/cmake/install-library.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/compiler-defines.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/clang-tidy.cmake)

set(LIB_NAME "common")

add_library(${LIB_NAME})
add_library(${PROJECT_NAME}::${LIB_NAME} ALIAS ${LIB_NAME})

set(LIB_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/IpV4Address.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/logging/plog/CustomFormatter.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/logging/plog/logging.plog.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/quantities/Acceleration.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/quantities/Angle.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/quantities/AngularVelocity.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/quantities/Distance.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/quantities/Duration.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/quantities/Temperature.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/quantities/Speed.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/quantities/Timestamp.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/socket/ConnectionError.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/socket/ReceiveError.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/socket/SocketError.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/socket/TcpClientSocket.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/socket/UdpListeningSocket.cpp
)

target_sources(${LIB_NAME} PRIVATE ${LIB_SOURCES})

target_include_directories(${LIB_NAME} PUBLIC
  # Prefer the generated headers during an in-tree build
  $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/generated/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

find_package(plog REQUIRED CONFIG)

target_link_libraries(${LIB_NAME}
  PRIVATE
    $<$<BOOL:${ZLIB_FOUND}>:ZLIB::ZLIB>
    plog::plog
)

target_enable_clang_tidy(
  TARGET 
    ${LIB_NAME}
  SOURCES
    ${LIB_SOURCES}
  INCLUDE_DIRS 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  LIBS
    plog::plog
)

# Configure version header for build
set(COMMON_VERSION_IN ${CMAKE_SOURCE_DIR}/cmake/version.hpp.in)
set(COMMON_VERSION_OUT ${CMAKE_BINARY_DIR}/generated/include/sick_perception_sdk/common/version.hpp)

# Make sure the output directory exists before writing the file
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/generated/include/sick_perception_sdk/common)
configure_file(${COMMON_VERSION_IN} ${COMMON_VERSION_OUT} @ONLY)

# Expose the generated include root so consumers find
# <sick_perception_sdk/common/version.hpp> in the generated tree first

if(BUILD_BENCHMARKS)
  add_subdirectory(benchmark)
endif()

if(BUILD_UNIT_TESTS)
  add_subdirectory(unit_test)
endif()

#===============================================================================
# Installation
#===============================================================================
install_sdk_library(
  TARGET ${LIB_NAME}
  DEPENDENCIES plog
)

# Install the generated version header so consumers can include it after install
install(FILES ${COMMON_VERSION_OUT}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sick_perception_sdk/common
)
