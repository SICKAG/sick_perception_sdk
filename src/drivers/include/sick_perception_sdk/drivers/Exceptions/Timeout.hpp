/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>

#include <stdexcept>
#include <string>

namespace sick {

class SDK_EXPORT Timeout : public std::runtime_error
{
public:
  explicit Timeout(std::string const& message)
    : std::runtime_error(message)
  { }
};

} // namespace sick
