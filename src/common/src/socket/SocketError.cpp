/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/socket/SocketError.hpp>

#include <stdexcept>
#include <string>

namespace sick {

SocketError::SocketError(int errorCode, std::string const& message)
  : std::runtime_error(message + " Error code: " + std::to_string(errorCode))
  , m_errorCode(errorCode)
{ }

auto SocketError::getErrorCode() const -> int
{
  return m_errorCode;
}

} // namespace sick
