cmake_minimum_required(VERSION 3.22)

include(${CMAKE_SOURCE_DIR}/cmake/install-library.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/compiler-defines.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/clang-tidy.cmake)

set(LIB_NAME "compact_format")
add_library(${LIB_NAME})
add_library(${PROJECT_NAME}::${LIB_NAME} ALIAS ${LIB_NAME})

#===============================================================================
# Configure zlib
#===============================================================================
if(NOT DEFINED TRY_TO_USE_ZLIB)
  set(TRY_TO_USE_ZLIB OFF)
endif()

if(TRY_TO_USE_ZLIB)
  if(BUILD_SHARED_LIBS)
    set(ZLIB_USE_STATIC_LIBS OFF)
  else()
    set(ZLIB_USE_STATIC_LIBS ON)
  endif()
  find_package(ZLIB REQUIRED)
endif()

if(ZLIB_FOUND)
  add_compile_definitions(USE_ZLIB_CRC32)
else()
  if (TRY_TO_USE_ZLIB)
    message(WARNING "${PROJECT_NAME}::${LIB_NAME}: ZLIB not found, using internal CRC32 implementation.")
  endif()
endif()

set(LIB_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/DataLoss/SegmentIndexLossMonitor.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/PointCloud/OrganizedPointCloudBuilder.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/PointCloud/PointCloudConfiguration.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/PointCloud/PointCloudToPcdConverter.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/PointCloud/UnorganizedPointCloudBuilder.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/telegram_type_1_scan_data/FrameSequenceNumberLossMonitor.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/telegram_type_1_scan_data/DataLossMonitor.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/telegram_type_1_scan_data/PointCloudCollector.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/telegram_type_1_scan_data/PointCloudConverter.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/telegram_type_1_scan_data/ScanDataParser.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/telegram_type_2_imu/ImuParser.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/telegram_type_4_encoder/EncoderParser.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/CompactParser.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Crc32Utils.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/Crc32UtilsImpl.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/StreamExtractor.cpp
)

target_sources(${LIB_NAME} PRIVATE ${LIB_SOURCES})

target_include_directories(${LIB_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

find_package(plog REQUIRED)

target_link_libraries(${LIB_NAME}
  PRIVATE
    $<$<BOOL:${ZLIB_FOUND}>:ZLIB::ZLIB>
  PUBLIC
    ${PROJECT_NAME}::common
)

target_enable_clang_tidy(
  TARGET 
    ${LIB_NAME}
  SOURCES
    ${LIB_SOURCES}
  INCLUDE_DIRS 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  LIBS
    $<$<BOOL:${ZLIB_FOUND}>:ZLIB::ZLIB>
    ${PROJECT_NAME}::common
)

if(BUILD_BENCHMARKS)
  add_subdirectory(benchmark)
endif()

if(BUILD_UNIT_TESTS)
  add_subdirectory(test)
endif()

#===============================================================================
# Installation
#===============================================================================
install_sdk_library(
  TARGET ${LIB_NAME}
  DEPENDENCIES ZLIB
)
