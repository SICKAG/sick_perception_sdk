/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/socket/Socket.hpp>

#include <cstdint>
#include <memory>
#include <optional>

namespace sick::compact {

struct MulticastGroup
{
  IpV4Address groupAddress;
  IpV4Address localInterfaceAddress;
};

/**
 * @brief Create a bound UDP listening socket and join @p multicast if one is configured.
 */
SDK_EXPORT auto makeUdpSocket(std::uint16_t receiverPort, std::optional<MulticastGroup> const& multicast) -> std::unique_ptr<Socket>;

//! \brief Create a TCP client socket. The connection is established when the receive loop starts.
SDK_EXPORT auto makeTcpSocket(IpV4Address const& sensorAddress, std::uint16_t sensorPort) -> std::unique_ptr<Socket>;

} // namespace sick::compact
