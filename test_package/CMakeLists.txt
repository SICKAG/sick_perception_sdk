cmake_minimum_required(VERSION 3.15)
project(PackageTest CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/compiler-defines.cmake)

find_package(sick_perception_sdk COMPONENTS compact_format drivers sensor_configuration REQUIRED)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    sick_perception_sdk::compact_format
    sick_perception_sdk::drivers
    sick_perception_sdk::sensor_configuration
)
