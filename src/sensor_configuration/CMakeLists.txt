# cmake versions >= 3.5 are compatible with cmake 4, versions >= 3.10 are not deprecated.
cmake_minimum_required(VERSION 3.22)

include(${CMAKE_SOURCE_DIR}/cmake/install-library.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/compiler-defines.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/clang-tidy.cmake)

set(LIB_NAME "sensor_configuration")

add_library(${LIB_NAME})
add_library(${PROJECT_NAME}::${LIB_NAME} ALIAS ${LIB_NAME})

set(LIB_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/SensorConfigurator/SensorConfigurator.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/SensorConfigurator/LRS4000/LRS4000Configurator.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/SensorConfigurator/multiScan100/MultiScan100Configurator.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/SensorConfigurator/picoScan150/PicoScan150Configurator.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/HttpClient/httplib_client/HttpClient.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/HttpClient/httplib_client/HttpsClient.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/RestClient/PostRequest.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/RestClient/RestClient.cpp
)

target_sources(${LIB_NAME} PRIVATE ${LIB_SOURCES})

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

target_link_libraries(${LIB_NAME}
  PUBLIC
  ${PROJECT_NAME}::common
  nlohmann_json::nlohmann_json
  httplib::httplib
  OpenSSL::SSL
  OpenSSL::Crypto
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
