/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/*
* @file
*
* @brief Default version header.
*
* This file is kept in the source tree so the header is always visible during development.
* CMake will generate a build-time replacement with the actual project version 
* and the build include directories prefer the generated copy.
*/
#pragma once

namespace sick {

constexpr auto version() noexcept
{
  return "0.0.0-invalid";
}

} // namespace sick
