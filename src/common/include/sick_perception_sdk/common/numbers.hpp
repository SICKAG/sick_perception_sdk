/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

// Replacement for std::numbers which is only available in C++20 or newer.
namespace sick::numbers {

// NOLINTNEXTLINE(readability-identifier-length): 'pi' mirrors std::numbers::pi
constexpr float pi = 3.141592f;

} // namespace sick::numbers
