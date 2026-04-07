# Function to install a library with CMake package configuration
# Usage: install_sdk_library(TARGET <target_name> [DEPENDENCIES <dep1> <dep2> ...])
function(install_sdk_library)
  set(options "")
  set(oneValueArgs TARGET)
  set(multiValueArgs DEPENDENCIES)
  cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  if(NOT ARG_TARGET)
    message(FATAL_ERROR "install_sdk_library: TARGET argument is required")
  endif()

  set(LIB_NAME ${ARG_TARGET})

  # Add compile definition for shared library builds
  # This will be exported to consumers so they know to use dllimport on Windows
  if(BUILD_SHARED_LIBS)
    target_compile_definitions(${LIB_NAME} PUBLIC SICK_PERCEPTION_SDK_SHARED)
  endif()

  install(
    TARGETS ${LIB_NAME}
    EXPORT ${PROJECT_NAME}-config
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )

  install(
    DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  )

  # Generate Config.cmake content
  set(CONFIG_CONTENT "@PACKAGE_INIT@\n\n")
  
  message(STATUS "Installing SDK library '${LIB_NAME}' with dependencies: '${ARG_DEPENDENCIES}'")
  if(ARG_DEPENDENCIES)
    string(APPEND CONFIG_CONTENT "include(CMakeFindDependencyMacro)\n\n")
    # Propagate static library preference for ZLIB based on how SDK was built
    if(NOT BUILD_SHARED_LIBS)
      string(APPEND CONFIG_CONTENT "set(ZLIB_USE_STATIC_LIBS ON)\n\n")
    endif()
    foreach(dep ${ARG_DEPENDENCIES})
      string(APPEND CONFIG_CONTENT "find_dependency(${dep} REQUIRED)\n")
    endforeach()
    string(APPEND CONFIG_CONTENT "\n")
  endif()

  # Write the dependencies.cmake.in file
  file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}-dependencies.cmake.in" "${CONFIG_CONTENT}")

  configure_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}-dependencies.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}-dependencies.cmake"
    @ONLY
  )

  install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/${LIB_NAME}-dependencies.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
  )

  # Install third-party headers for dependencies that are required by public headers
  # This copies headers from the dependencies to the SDK installation directory
  if(ARG_DEPENDENCIES)
    foreach(dep ${ARG_DEPENDENCIES})
      # Try to get the include directories for the dependency target
      if(TARGET ${dep}::${dep})
        get_target_property(DEP_INCLUDE_DIRS ${dep}::${dep} INTERFACE_INCLUDE_DIRECTORIES)
        if(DEP_INCLUDE_DIRS)
          foreach(include_dir ${DEP_INCLUDE_DIRS})
            if(EXISTS ${include_dir})
              # Get all files in the include directory
              file(GLOB_RECURSE dep_headers RELATIVE ${include_dir} ${include_dir}/*)
              foreach(header ${dep_headers})
                get_filename_component(header_dir ${header} DIRECTORY)
                # Install the header file maintaining directory structure
                install(
                  FILES ${include_dir}/${header}
                  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${header_dir}
                )
              endforeach()
            endif()
          endforeach()
        endif()
      endif()
    endforeach()
  endif()
endfunction()
