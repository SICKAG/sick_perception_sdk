cmake_minimum_required(VERSION 3.24)

set(BENCHMARK_NAME compact_format_benchmark)

set(BENCHMARK_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/PointCloud/UnorganizedPointCloud.benchmark.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/telegram_type_1_scan_data/telegram_type_1_ScanDataParser.benchmark.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/telegram_type_6_multiScan200/telegram_type_6_MultiScan200Parser.benchmark.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/telegram_type_6_multiScan200/telegram_type_6_MultiScan200PointCloudConverter.benchmark.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)
set(BENCHMARK_RESOURCES
  # Telegram type 1
  ${CMAKE_CURRENT_SOURCE_DIR}/../test/data/telegram_type_1_LRS4581-frame_0.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/../test/data/telegram_type_1_multiScan136-frame_0.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/../test/data/telegram_type_1_picoScan150_profile_1-frame_0.bin
  # Telegram type 6
  ${CMAKE_CURRENT_SOURCE_DIR}/../test/data/telegram_type_6_multiScan270_profile_12_full-frame_0.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/../test/data/telegram_type_6_multiScan270_profile_12_minimal-frame_0.bin
)

add_executable(${BENCHMARK_NAME})

target_sources(${BENCHMARK_NAME}
  PRIVATE
    ${BENCHMARK_SOURCES}
)

find_package(benchmark REQUIRED)

target_link_libraries(${BENCHMARK_NAME}
  PRIVATE
    benchmark::benchmark
    ${PROJECT_NAME}::compact_format
)

foreach(resource ${BENCHMARK_RESOURCES})
  add_custom_command(
    TARGET ${BENCHMARK_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${BENCHMARK_NAME}>/data
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${resource}
            $<TARGET_FILE_DIR:${BENCHMARK_NAME}>/data
    COMMENT "Copying ${resource} to $<TARGET_FILE_DIR:${BENCHMARK_NAME}>/data"
  )
endforeach()
