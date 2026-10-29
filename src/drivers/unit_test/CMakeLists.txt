cmake_minimum_required(VERSION 3.22)

set(TEST_NAME "${LIB_NAME}_unit_test")

set(TEST_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/LRS4000Config.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/MultiScan100Config.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/MultiScan200Config.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/PicoScan100Config.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/UdpImuReceiverConfig.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/UdpScanDataReceiverConfig.test.cpp
)

add_executable(${TEST_NAME})

target_sources(${TEST_NAME}
  PRIVATE
    ${TEST_SOURCES}
)

target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

find_package(GTest)

target_link_libraries(${TEST_NAME}
  PRIVATE
    GTest::gtest
    ${PROJECT_NAME}::${LIB_NAME}
)

include(GoogleTest)

# Address Sanitizer variant
set(TEST_NAME_ASAN ${TEST_NAME}_asan)

add_executable(${TEST_NAME_ASAN} EXCLUDE_FROM_ALL)

target_sources(${TEST_NAME_ASAN}
  PRIVATE
    ${TEST_SOURCES}
)

target_include_directories(${TEST_NAME_ASAN} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${TEST_NAME_ASAN}
  PRIVATE
    GTest::gtest
    ${PROJECT_NAME}::${LIB_NAME}
)

target_compile_options(${TEST_NAME_ASAN} PRIVATE -fsanitize=address -fno-omit-frame-pointer)
target_link_options(${TEST_NAME_ASAN} PRIVATE -fsanitize=address)
