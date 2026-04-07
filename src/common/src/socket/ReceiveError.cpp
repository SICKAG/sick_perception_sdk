/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/socket/ReceiveError.hpp>

#include <sick_perception_sdk/common/socket/SocketError.hpp>

namespace sick {

ReceiveError::ReceiveError(int errorCode)
  : SocketError(errorCode, "There was an error while receiving data from the socket.")
{ }

} // namespace sick
