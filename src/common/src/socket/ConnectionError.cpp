/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/socket/ConnectionError.hpp>

#include <sick_perception_sdk/common/socket/SocketError.hpp>

#include <string>

namespace sick {

ConnectionError::ConnectionError(int errorCode, std::string const& message)
  : SocketError(errorCode, message)
{ }

} // namespace sick
