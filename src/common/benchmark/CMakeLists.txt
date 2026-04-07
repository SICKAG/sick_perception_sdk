cmake_minimum_required(VERSION 3.24)

set(BENCHMARK_NAME common_benchmark)

set(BENCHMARK_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ByteView.benchmark.cpp
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
    ${PROJECT_NAME}::common
)
