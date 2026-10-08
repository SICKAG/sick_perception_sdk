cmake_minimum_required(VERSION 3.22)

set(TEST_NAME compact_format_unit_test)
set(TEST_SOURCES
  # DataLoss
  ${CMAKE_CURRENT_SOURCE_DIR}/DataLoss/FrameSequenceNumberLossMonitor.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/DataLoss/SegmentIndexLossMonitor.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/DataLoss/SequenceNumberLossMonitor.test.cpp
  # PointCloud
  ${CMAKE_CURRENT_SOURCE_DIR}/PointCloud/OrganizedPointCloudBuilder.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/PointCloud/PointCloudToPcdConverter.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/PointCloud/UnorganizedPointCloud.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/PointCloud/UnorganizedPointCloudBuilder.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/PointCloud/UnorganizedPointCloudCollector.test.cpp
  # Telegram type 1
  ${CMAKE_CURRENT_SOURCE_DIR}/telegram_type_1_scan_data/ScanDataGenerator.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/telegram_type_1_scan_data/telegram_type_1_DataLossMonitor.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/telegram_type_1_scan_data/telegram_type_1_PointCloudCollector.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/telegram_type_1_scan_data/telegram_type_1_ScanData.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/telegram_type_1_scan_data/telegram_type_1_ScanDataParser.test.cpp
  # Telegram type 2
  ${CMAKE_CURRENT_SOURCE_DIR}/telegram_type_2_imu_legacy/telegram_type_2_ImuLegacyParser.test.cpp
  # Telegram type 3
  ${CMAKE_CURRENT_SOURCE_DIR}/telegram_type_3_ambient_light/telegram_type_3_AmbientLightParser.test.cpp
  # Telegram type 4
  ${CMAKE_CURRENT_SOURCE_DIR}/telegram_type_4_encoder/telegram_type_4_EncoderParser.test.cpp
  # Telegram type 6
  ${CMAKE_CURRENT_SOURCE_DIR}/telegram_type_6_multiScan200/MultiScan200DataGenerator.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/telegram_type_6_multiScan200/telegram_type_6_DataLossMonitor.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/telegram_type_6_multiScan200/telegram_type_6_MultiScan200Parser.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/telegram_type_6_multiScan200/telegram_type_6_PointCloudConverter.convertToOrganized.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/telegram_type_6_multiScan200/telegram_type_6_PointCloudConverter.convertToUnorganized.test.cpp
  # Telegram type 7
  ${CMAKE_CURRENT_SOURCE_DIR}/telegram_type_7_imu/telegram_type_7_ImuParser.test.cpp
  # Utils
  ${CMAKE_CURRENT_SOURCE_DIR}/utils/test_utils.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/utils/TestParams.cpp
  # Various
  ${CMAKE_CURRENT_SOURCE_DIR}/Crc32Utils.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/StreamExtractor.test.cpp
)
set(TEST_RESOURCES
  # Telegram type 1
  ${CMAKE_CURRENT_SOURCE_DIR}/data/telegram_type_1_LRS4581-frame_0.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/telegram_type_1_LRS4581-frame_1.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/telegram_type_1_LRS4581-frame_2.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/telegram_type_1_multiScan136-frame_0.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/telegram_type_1_multiScan136-frame_1.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/telegram_type_1_multiScan136-frame_2.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/telegram_type_1_picoScan150_profile_1-frame_0.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/telegram_type_1_picoScan150_profile_1-frame_1.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/telegram_type_1_picoScan150_profile_1-frame_2.bin
  # Telegram type 2
  ${CMAKE_CURRENT_SOURCE_DIR}/data/telegram_type_2_multiScan136-frame_0.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/telegram_type_2_multiScan136-frame_1.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/telegram_type_2_multiScan136-frame_2.bin
  # Telegram type 3
  ${CMAKE_CURRENT_SOURCE_DIR}/data/telegram_type_3_multiScan270_profile_12-frame_0.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/telegram_type_3_multiScan270_profile_12-frame_1.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/telegram_type_3_multiScan270_profile_12-frame_2.bin
  # Telegram type 4
  ${CMAKE_CURRENT_SOURCE_DIR}/data/telegram_type_4_v1_picoScan150-frame_0.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/telegram_type_4_v1_picoScan150-frame_1.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/telegram_type_4_v1_picoScan150-frame_2.bin
  # Telegram type 6
  ${CMAKE_CURRENT_SOURCE_DIR}/data/telegram_type_6_multiScan270_profile_12_full-frame_0.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/telegram_type_6_multiScan270_profile_12_full-frame_1.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/telegram_type_6_multiScan270_profile_12_full-frame_2.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/telegram_type_6_multiScan270_profile_12_minimal-frame_0.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/telegram_type_6_multiScan270_profile_12_minimal-frame_1.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/telegram_type_6_multiScan270_profile_12_minimal-frame_2.bin
  # Telegram type 7
  ${CMAKE_CURRENT_SOURCE_DIR}/data/telegram_type_7_multiScan270-frame_0.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/telegram_type_7_multiScan270-frame_1.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/data/telegram_type_7_multiScan270-frame_2.bin
)

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
