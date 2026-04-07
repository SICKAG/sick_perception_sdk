#
# Sets up a clang-tidy target for the specified project. The resulting target
# will be an OBJECT library. Thus, correct sources, include directories and
# libraries to link against have to be passed.
#
# All header files (*.hpp) found in the INCLUDE_DIRS and source file
# directories are automatically included
#
# Usage:
#   target_enable_clang_tidy(
#     TARGET <target>
#     SOURCES <source1> [<source2> ...]
#     INCLUDE_DIRS <include_dir1> [<include_dir2> ...]
#     LIBS <lib1> [<lib2> ...]
#   )
#
# TARGET
#   Name of the target project to enable clang-tidy for. The generated target
#   will be ${target}_clang_tidy.
#
# SOURCES
#   List of source files to include in the clang-tidy target.
#
# INCLUDE_DIRS
#   List of include directories to associate with the clang-tidy target.
#
# LIBS
#   List of libraries to link against the clang-tidy target.
#
function(target_enable_clang_tidy)

  set(options)
  set(oneValueArgs TARGET)
  set(multiValueArgs SOURCES INCLUDE_DIRS LIBS)
  cmake_parse_arguments(CLANG_TIDY_ARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  set(targetName ${CLANG_TIDY_ARGS_TARGET}_clang_tidy)
  set(clangTidyBinaryName "clang-tidy")
  find_program(CLANG_TIDY_EXE NAMES ${clangTidyBinaryName} NO_CACHE)

  # Only create the target if clang-tidy is available.
  if(CLANG_TIDY_EXE)
    # Collect all headers from include directories and source file directories.
    set(ALL_HEADERS "")
    foreach(includeDir IN LISTS CLANG_TIDY_ARGS_INCLUDE_DIRS)
      file(GLOB_RECURSE DIR_HEADERS "${includeDir}/*.hpp")
      list(APPEND ALL_HEADERS ${DIR_HEADERS})
    endforeach()
    foreach(sourceFile IN LISTS CLANG_TIDY_ARGS_SOURCES)
      get_filename_component(sourceDir "${sourceFile}" DIRECTORY)
      file(GLOB DIR_HEADERS "${sourceDir}/*.hpp")
      list(APPEND ALL_HEADERS ${DIR_HEADERS})
    endforeach()
    list(REMOVE_DUPLICATES ALL_HEADERS)

    set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE};-p;${CMAKE_BINARY_DIR};--extra-arg=-Wno-unknown-warning-option") # Uses .clang-tidy file for header filter and checks.
    add_library(${targetName} OBJECT ${CLANG_TIDY_ARGS_SOURCES} ${ALL_HEADERS})
    target_include_directories(${targetName} PUBLIC ${CLANG_TIDY_ARGS_INCLUDE_DIRS})
    target_link_libraries(${targetName} ${CLANG_TIDY_ARGS_LIBS})
    target_compile_definitions(${targetName} PUBLIC CLANG_TIDY)
    set_target_properties(${targetName} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}" EXCLUDE_FROM_ALL TRUE)
    message(STATUS "Set up target ${targetName}.")
  else()
    message(INFO "[INFO] Could not find ${clangTidyBinaryName}. Skipping target ${targetName}.")
  endif()
endfunction()
