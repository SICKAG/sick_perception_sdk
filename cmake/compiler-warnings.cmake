# Function to enable compiler warnings for SDK targets
# These warnings are applied with PRIVATE scope so they don't propagate to consumers
# Usage: add_sdk_compiler_warnings(TARGET <target_name>)
function(add_sdk_compiler_warnings)
  set(options "")
  set(oneValueArgs TARGET)
  set(multiValueArgs "")
  cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  if(NOT ARG_TARGET)
    message(FATAL_ERROR "sick_perception_sdk: add_sdk_compiler_warnings: TARGET argument is required")
  endif()

  set(LIB_NAME ${ARG_TARGET})

  if(MSVC)
    # MSVC compiler warnings
    # /W4 = Warning level 4 (most warnings)
    target_compile_options(${LIB_NAME} PRIVATE /W4)
    
    # /wd4251 = Disable "class 'type' needs to have dll-interface to be used by clients of class 'type2'"
    # This warning is expected for exported classes with STL members; the DLL ABI is documented and maintained.
    # /wd4275 = Disable "non dll-interface class 'base' used as base for dll-interface class 'derived'"
    # Exception classes commonly inherit from std::runtime_error; this is standard practice.
    target_compile_options(${LIB_NAME} PRIVATE /wd4251 /wd4275)
  else()
    # GCC and Clang warnings
    # -Wall = Enable most warnings
    # -Wextra = Enable extra warnings
    # -Wpedantic = Enable pedantic warnings
    target_compile_options(${LIB_NAME} PRIVATE -Wall -Wextra -Wpedantic)
  endif()
endfunction()
