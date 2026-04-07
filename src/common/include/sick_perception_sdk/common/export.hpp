/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#ifndef SICK_PERCEPTION_SDK_EXPORT_H
#define SICK_PERCEPTION_SDK_EXPORT_H

// =============================================================================
// Export macros for SICK Perception SDK libraries
// =============================================================================
// This header defines export/import macros for building shared libraries on
// Windows and controlling symbol visibility on Linux/Unix systems.
//
// Usage:
//   - Apply SDK_EXPORT to public classes and functions that should be exported
//   - Apply SDK_NO_EXPORT to symbols that should remain internal
//
// Build systems:
//   - CMake automatically defines <target>_EXPORTS when building each library
//   - For static builds, these macros expand to nothing
// =============================================================================

// Detect if we're building any of the SDK libraries
#if defined(common_EXPORTS) || defined(compact_format_EXPORTS) || defined(sensor_configuration_EXPORTS) || defined(drivers_EXPORTS)
#  define SICK_PERCEPTION_SDK_BUILDING
#endif

// Define export macros based on platform and build mode
#ifdef SICK_PERCEPTION_SDK_BUILDING
// We are building the SDK libraries - export symbols
#  ifdef _WIN32
#    define SDK_EXPORT __declspec(dllexport)
#    define SDK_NO_EXPORT
#  else
#    define SDK_EXPORT __attribute__((visibility("default")))
#    define SDK_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#else
// We are consuming the SDK libraries - import symbols
#  ifdef _WIN32
#    ifdef SICK_PERCEPTION_SDK_SHARED
#      define SDK_EXPORT __declspec(dllimport)
#    else
#      define SDK_EXPORT
#    endif
#    define SDK_NO_EXPORT
#  else
#    define SDK_EXPORT __attribute__((visibility("default")))
#    define SDK_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#endif /* SICK_PERCEPTION_SDK_EXPORT_H */
