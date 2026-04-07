cmake_minimum_required(VERSION 3.24)

set(BENCHMARK_NAME compact_format_benchmark)

set(BENCHMARK_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ScanDataParser.benchmark.cpp
)
set(BENCHMARK_RESOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/../test/data/LRS4581_scan-frame_0.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/../test/data/multiScan136_scan-frame_0.bin
  ${CMAKE_CURRENT_SOURCE_DIR}/../test/data/picoScan150_profile1_scan-frame_0.bin
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
