/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once
#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/socket/SocketError.hpp>

#include <string>

namespace sick {

class SDK_EXPORT ConnectionError : public SocketError
{
public:
  explicit ConnectionError(int errorCode, std::string const& message = "");
};
} // namespace sick
