cmake_minimum_required(VERSION 3.22)

set(TEST_NAME "${LIB_NAME}_unit_test")
set(TEST_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/PostRequest.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/RestClient.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/SensorConfigurator.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test_utils/TestHttpClient.cpp
)

add_executable(${TEST_NAME})

target_sources(${TEST_NAME} PRIVATE ${TEST_SOURCES})

find_package(GTest REQUIRED)

target_link_libraries(${TEST_NAME}
  PRIVATE
    ${PROJECT_NAME}::${LIB_NAME}
    GTest::gtest
)

include(GoogleTest)

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
    ${PROJECT_NAME}::${LIB_NAME}
)

target_compile_options(${TEST_NAME_ASAN} PRIVATE -fsanitize=address -fno-omit-frame-pointer)
target_link_options(${TEST_NAME_ASAN} PRIVATE -fsanitize=address)
