/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/socket/ReceiveError.hpp>
#include <sick_perception_sdk/common/socket/Socket.hpp>

#include <string>

namespace sick {

//! \brief A blocking TCP socket
class SDK_EXPORT TcpClientSocket : public Socket
{
public:
  //! \brief Creates a TCP client socket.
  //! \param serverAddress The IP address of the server to connect to.
  //! \param serverPort The port on the server to which to open the socket.
  TcpClientSocket(IpV4Address serverAddress, std::uint16_t serverPort);
  virtual ~TcpClientSocket();

  TcpClientSocket(TcpClientSocket const&)                    = delete;
  auto operator=(TcpClientSocket const&) -> TcpClientSocket& = delete;
  TcpClientSocket(TcpClientSocket&&)                         = delete;
  auto operator=(TcpClientSocket&&) -> TcpClientSocket&      = delete;

  void connect() override;

private:
  IpV4Address m_serverAddress;
  std::uint16_t m_port;

  struct addrinfo* m_addressInfo;
};

} // namespace sick
