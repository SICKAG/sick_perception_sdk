# cmake versions >= 3.5 are compatible with cmake 4, versions >= 3.10 are not deprecated.
cmake_minimum_required(VERSION 3.22)

include(${CMAKE_SOURCE_DIR}/cmake/install-library.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/compiler-defines.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/compiler-warnings.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/clang-tidy.cmake)

set(LIB_NAME "sensor_configuration")

add_library(${LIB_NAME})
add_library(${PROJECT_NAME}::${LIB_NAME} ALIAS ${LIB_NAME})

add_sdk_compiler_warnings(TARGET ${LIB_NAME})

set(LIB_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/SopasClient.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/HttpClient/httplib_client/HttpClient.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/HttpClient/httplib_client/HttpsClient.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/SensorConfigurator/LRS4000/LRS4000Configurator.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/SensorConfigurator/multiScan100/MultiScan100Configurator.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/SensorConfigurator/multiScan200/MultiScan200Configurator.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/SensorConfigurator/picoScan150/PicoScan150Configurator.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/SensorConfigurator/HttpHelpers.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/SensorConfigurator/ParameterBackupRestore.cpp
)

# Pull in the auto-generated per-device Endpoints translation units.
include(${CMAKE_CURRENT_SOURCE_DIR}/generated/generated_sources.cmake)

target_sources(${LIB_NAME} PRIVATE ${LIB_SOURCES} ${SENSOR_CONFIGURATION_GENERATED_SOURCES_ALL})

target_compile_options(${LIB_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/bigobj>
)

target_include_directories(${LIB_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

find_package(OpenSSL REQUIRED)
find_package(httplib REQUIRED)
find_package(nlohmann_json REQUIRED)

# sensor_configuration requires OpenSSL itself. Therefore, we configure support in cpp-httplib as well.
target_compile_definitions(${LIB_NAME} PUBLIC CPPHTTPLIB_OPENSSL_SUPPORT=1)

# nlohmann_json is an internal implementation detail: it is only used inside the compiled
# translation units (SopasClient.cpp and the generated Endpoints.g.cpp). Public headers are
# nlohmann-free, so it is linked PRIVATE and consumers never need it.
target_link_libraries(${LIB_NAME}
  PUBLIC
  ${PROJECT_NAME}::common
  httplib::httplib
  OpenSSL::SSL
  OpenSSL::Crypto
  PRIVATE
  nlohmann_json::nlohmann_json
)

target_enable_clang_tidy(
  TARGET 
    ${LIB_NAME}
  SOURCES
    ${LIB_SOURCES}
  INCLUDE_DIRS 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  LIBS
    ${PROJECT_NAME}::common
    httplib::httplib
    nlohmann_json::nlohmann_json
    OpenSSL::SSL
    OpenSSL::Crypto
)

# The clang-tidy target is a separate object library and does not inherit the
# main library's OpenSSL support definition, which cpp-httplib requires for HTTPS.
if(TARGET ${LIB_NAME}_clang_tidy)
  target_compile_definitions(${LIB_NAME}_clang_tidy PUBLIC CPPHTTPLIB_OPENSSL_SUPPORT=1)
endif()

if(BUILD_UNIT_TESTS)
  add_subdirectory(unit_test)
endif()

#===============================================================================
# Installation
#===============================================================================
install_sdk_library(
  TARGET
    ${LIB_NAME}
  DEPENDENCIES
    httplib
    nlohmann_json
    OpenSSL
)
