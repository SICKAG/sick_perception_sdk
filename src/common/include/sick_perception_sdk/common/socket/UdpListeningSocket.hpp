/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/
#pragma once

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/socket/Socket.hpp>

#include <chrono>
#include <memory>
#include <string>
#include <vector>

namespace sick {

//! \brief A blocking UDP socket
class SDK_EXPORT UdpListeningSocket : public Socket
{
public:
  //! \brief Create a listening socket at the given port.
  //! \param port The port on which to open the socket.
  explicit UdpListeningSocket(std::uint16_t port);
  virtual ~UdpListeningSocket();

  UdpListeningSocket(UdpListeningSocket const&)                    = delete;
  auto operator=(UdpListeningSocket const&) -> UdpListeningSocket& = delete;
  UdpListeningSocket(UdpListeningSocket&&)                         = delete;
  auto operator=(UdpListeningSocket&&) -> UdpListeningSocket&      = delete;

  void joinMulticastGroup(IpV4Address const& multicastGroupAddress, IpV4Address const& localInterfaceAddress);
};

} // namespace sick
