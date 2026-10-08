# Must be included BEFORE project(), because project() already caches CMAKE_BUILD_TYPE
# from CMAKE_BUILD_TYPE_INIT (which Windows-MSVC.cmake unconditionally sets to Debug).
# Multi-configuration generators ignore CMAKE_BUILD_TYPE, so no generator check is needed.
if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build.")
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release RelWithDebInfo MinSizeRel)
endif()
