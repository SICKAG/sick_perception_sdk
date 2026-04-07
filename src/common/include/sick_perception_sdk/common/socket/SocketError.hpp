/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once
#include <sick_perception_sdk/common/export.hpp>

#include <stdexcept>
#include <string>

namespace sick {

class SDK_EXPORT SocketError : public std::runtime_error
{
public:
  explicit SocketError(int errorCode, std::string const& message = "");

  auto getErrorCode() const -> int;

private:
  int m_errorCode;
};
} // namespace sick
