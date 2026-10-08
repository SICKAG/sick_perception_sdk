set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
  # Set the C runtime library if not already defined.
  # The default is to use the static runtime library (MultiThreaded) 
  # for both Debug and Release builds. This must match the configuration
  # of the third-party libraries (e.g., OpenSSL or gtest) to avoid linker errors.
  if(NOT DEFINED CMAKE_MSVC_RUNTIME_LIBRARY)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  endif()

  # Prevent Windows headers from defining min/max macros
  add_compile_definitions(NOMINMAX)
endif()