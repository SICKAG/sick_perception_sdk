cmake_minimum_required(VERSION 3.22)

set(TEST_NAME compact_format_unit_test)
set(TEST_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/utils/ScanDataGenerator.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/utils/test_utils.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/utils/TestParams.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Crc32Utils.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/EncoderParser.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/FrameSequenceNumberLossMonitor.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ImuParser.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/OrganizedPointCloudBuilder.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/PointCloudCollector.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/PointCloudToPcdConverter.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ScanDataParser.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/SegmentIndexLossMonitor.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/SequenceNumberLossMonitor.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/StreamExtractor.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/telegram_type_1_scanData_DataLossMonitor.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/UnorganizedPointCloud.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/UnorganizedPointCloudBuilder.test.cpp
)
set(TEST_RESOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/data/LRS4581_scan-frame_0.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/LRS4581_scan-frame_1.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/LRS4581_scan-frame_2.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/multiScan136_imu-frame_0.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/multiScan136_imu-frame_1.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/multiScan136_imu-frame_2.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/multiScan136_scan-frame_0.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/multiScan136_scan-frame_1.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/multiScan136_scan-frame_2.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/picoScan150_encoder-frame_0.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/picoScan150_encoder-frame_1.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/picoScan150_encoder-frame_2.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/picoScan150_profile1_scan-frame_0.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/picoScan150_profile1_scan-frame_1.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/picoScan150_profile1_scan-frame_2.bin
)

# Add option to enable gcov-based coverage generation
option(ENABLE_GCOV "Enable gcov coverage generation and produce gcovr HTML report" OFF)

add_executable(${TEST_NAME})


target_sources(${TEST_NAME}
  PRIVATE
    ${TEST_SOURCES}
)

find_package(GTest)

target_link_libraries(${TEST_NAME}
  PRIVATE
    GTest::gtest
    ${PROJECT_NAME}::compact_format
)

include(GoogleTest)

foreach(resource ${TEST_RESOURCES})
  add_custom_command(
    TARGET ${TEST_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${TEST_NAME}>/data
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${resource}
            $<TARGET_FILE_DIR:${TEST_NAME}>/data
    COMMENT "Copying ${resource} to $<TARGET_FILE_DIR:${TEST_NAME}>/data"
  )
endforeach()

# Address Sanitizer variant
set(TEST_NAME_ASAN ${TEST_NAME}_asan)

add_executable(${TEST_NAME_ASAN} EXCLUDE_FROM_ALL)

target_sources(${TEST_NAME_ASAN}
  PRIVATE
    ${TEST_SOURCES}
)

target_link_libraries(${TEST_NAME_ASAN}
  PRIVATE
    GTest::gtest
    ${PROJECT_NAME}::compact_format
)

target_compile_options(${TEST_NAME_ASAN} PRIVATE -fsanitize=address -fno-omit-frame-pointer)
target_link_options(${TEST_NAME_ASAN} PRIVATE -fsanitize=address)
