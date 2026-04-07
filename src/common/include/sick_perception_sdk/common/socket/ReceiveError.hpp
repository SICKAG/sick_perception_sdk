/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/socket/SocketError.hpp>

namespace sick {

class SDK_EXPORT ReceiveError : public SocketError
{
public:
  explicit ReceiveError(int errorCode);
};

} // namespace sick
