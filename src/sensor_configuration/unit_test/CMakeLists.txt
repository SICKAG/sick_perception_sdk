cmake_minimum_required(VERSION 3.22)

# Internal (non-public) configurator headers the unit tests include directly.
set(SENSOR_CONFIGURATOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src/SensorConfigurator)

set(TEST_NAME "${LIB_NAME}_unit_test")
set(TEST_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/SopasClient.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Convert.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/HttpHelpers.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ParameterBackupRestore.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/FirmwareUpdate.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/MultiScan100ConfiguratorGlue.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/MultiScan200ConfiguratorGlue.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/PicoScan150ConfiguratorGlue.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/LRS4000ConfiguratorGlue.test.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/test_utils/TestHttpClient.cpp
  # Internal helpers under test are not SDK_EXPORT'ed, so a shared/DLL build does not expose
  # them to the test. Compile them into the test directly to keep them out of the public API.
  ${SENSOR_CONFIGURATOR_DIR}/HttpHelpers.cpp
  ${SENSOR_CONFIGURATOR_DIR}/ParameterBackupRestore.cpp
)

add_executable(${TEST_NAME})

target_sources(${TEST_NAME} PRIVATE ${TEST_SOURCES})

# Include the sensor configurator headers so that the unit tests can access internal functions and classes.
target_include_directories(${TEST_NAME} PRIVATE ${SENSOR_CONFIGURATOR_DIR})

find_package(GTest REQUIRED)
find_package(nlohmann_json REQUIRED)

target_link_libraries(${TEST_NAME}
  PRIVATE
    ${PROJECT_NAME}::${LIB_NAME}
    GTest::gtest
    nlohmann_json::nlohmann_json
)

# On Windows OpenSSL is linked as a DLL (the CI package ships no static libs). Copy the
# OpenSSL runtime DLLs next to the test executable so the loader finds them when the test
# runs on the CI, where the DLLs are neither on PATH nor next to the binary.
if(WIN32)
  find_package(OpenSSL REQUIRED)
  # FindOpenSSL exposes the import libraries; the matching DLLs live in the sibling bin/ dir.
  get_filename_component(_openssl_lib_dir "${OPENSSL_SSL_LIBRARY}" DIRECTORY)
  file(GLOB _openssl_dlls
    "${OPENSSL_ROOT_DIR}/bin/*.dll"
    "${_openssl_lib_dir}/*.dll"
    "${_openssl_lib_dir}/../bin/*.dll"
  )
  if(_openssl_dlls)
    add_custom_command(TARGET ${TEST_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different ${_openssl_dlls} $<TARGET_FILE_DIR:${TEST_NAME}>
      COMMAND_EXPAND_LISTS
      COMMENT "Copying OpenSSL DLLs next to ${TEST_NAME}"
    )
  else()
    # No DLLs is expected and fine when OpenSSL is linked statically.
    message(STATUS "sick_perception_sdk: No OpenSSL DLLs found to copy next to ${TEST_NAME} (expected for a static OpenSSL).")
  endif()
endif()

include(GoogleTest)

# Address Sanitizer variant
set(TEST_NAME_ASAN ${TEST_NAME}_asan)

add_executable(${TEST_NAME_ASAN} EXCLUDE_FROM_ALL)

target_sources(${TEST_NAME_ASAN}
  PRIVATE
    ${TEST_SOURCES}
)

# Include the sensor configurator headers so that the unit tests can access internal functions and classes.
target_include_directories(${TEST_NAME_ASAN} PRIVATE ${SENSOR_CONFIGURATOR_DIR})

target_link_libraries(${TEST_NAME_ASAN}
  PRIVATE
    GTest::gtest
    nlohmann_json::nlohmann_json
    ${PROJECT_NAME}::${LIB_NAME}
)

target_compile_options(${TEST_NAME_ASAN} PRIVATE -fsanitize=address -fno-omit-frame-pointer)
target_link_options(${TEST_NAME_ASAN} PRIVATE -fsanitize=address)
