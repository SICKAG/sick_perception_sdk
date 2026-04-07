cmake_minimum_required(VERSION 3.22)

set(TEST_NAME "${LIB_NAME}_unit_test")

set(TEST_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/Acceleration.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Angle.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Angularvelocity.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/BitmapEncoder.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ByteView.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Distance.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Duration.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Interval.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/IpV4Address.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Speed.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/SubByteArrayConverter.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Temperature.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Timestamp.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/version.test.cpp
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
    ${PROJECT_NAME}::common
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
