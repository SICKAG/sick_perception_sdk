/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/drivers/Receiver/ReceiverSockets.hpp>

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/socket/Socket.hpp>
#include <sick_perception_sdk/common/socket/TcpClientSocket.hpp>
#include <sick_perception_sdk/common/socket/UdpListeningSocket.hpp>

#include <cstdint>
#include <memory>
#include <optional>

namespace sick::compact {

auto makeUdpSocket(std::uint16_t receiverPort, std::optional<MulticastGroup> const& multicast) -> std::unique_ptr<Socket>
{
  auto socket = std::make_unique<UdpListeningSocket>(receiverPort);
  if (multicast)
  {
    socket->joinMulticastGroup(multicast->groupAddress, multicast->localInterfaceAddress);
  }
  return socket;
}

auto makeTcpSocket(IpV4Address const& sensorAddress, std::uint16_t sensorPort) -> std::unique_ptr<Socket>
{
  return std::make_unique<TcpClientSocket>(sensorAddress, sensorPort);
}

} // namespace sick::compact
