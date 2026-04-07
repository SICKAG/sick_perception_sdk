set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
  add_compile_definitions(_USE_MATH_DEFINES) # For M_PI and other mathematical constants on Windows
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  add_compile_definitions(NOMINMAX) # Prevent Windows headers from defining min/max macros
endif()