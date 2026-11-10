/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>

#include <stdexcept>
#include <string>

namespace sick {

//! \brief The peer closed the connection; the receive loop that reports this has ended and must be restarted to reconnect.
class SDK_EXPORT ConnectionClosed : public std::runtime_error
{
public:
  explicit ConnectionClosed(std::string const& message)
    : std::runtime_error(message)
  { }
};

} // namespace sick
