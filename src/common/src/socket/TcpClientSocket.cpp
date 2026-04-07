/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/socket/TcpClientSocket.hpp>

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/logging/logging.hpp>
#include <sick_perception_sdk/common/socket/ConnectionError.hpp>
#include <sick_perception_sdk/common/socket/Socket.hpp>

#include <cstdint>
#include <stdexcept>
#include <string>

// NOLINTBEGIN(misc-include-cleaner): socket definitions are platform dependent

namespace sick {

TcpClientSocket::TcpClientSocket(IpV4Address serverAddress, std::uint16_t serverPort)
  : m_serverAddress(serverAddress)
  , m_port(serverPort)
  , m_addressInfo(nullptr)
{
  // No connection yet
  m_socket = INVALID_SOCKET;

  // Set up client address info
  struct addrinfo hints = {0};
  hints.ai_family       = AF_INET;
  hints.ai_socktype     = SOCK_STREAM;

  // Resolve the server address and port, throws on failure
  auto const result = getaddrinfo(m_serverAddress.toString().c_str(), std::to_string(m_port).c_str(), &hints, &m_addressInfo);
  if (result != 0 || m_addressInfo == nullptr)
  {
    cleanup();
    throw std::runtime_error("getaddrinfo() failed with error: " + std::to_string(result));
  }

  LOG_INFO("TcpClientSocket") << "Creating socket.";
  m_socket = socket(m_addressInfo->ai_family, m_addressInfo->ai_socktype, m_addressInfo->ai_protocol);
  if (m_socket == INVALID_SOCKET)
  {
    cleanup();
    throw std::runtime_error("Creating socket failed");
  }
}

TcpClientSocket::~TcpClientSocket()
{
  LOG_INFO("TcpClientSocket") << "Closing TCP client socket.";
  closeConnection();
  if (m_addressInfo != nullptr)
  {
    freeaddrinfo(m_addressInfo);
    m_addressInfo = nullptr;
  }
}

void TcpClientSocket::connect()
{
  if (m_addressInfo == nullptr)
  {
    throw std::runtime_error("Address info is not set. Cannot connect.");
  }

  if (::connect(m_socket, m_addressInfo->ai_addr, static_cast<int>(m_addressInfo->ai_addrlen)) == SOCKET_ERROR)
  {
    auto const errorCode = getErrorCode();

    std::string const errorMsg =
      "Unable to connect to server at " + m_serverAddress.toString() + ":" + std::to_string(m_port) + " connect() failed with error " +
      std::to_string(errorCode) + ". Make sure that the server is running and reachable under the IP address and port.";
    LOG_ERROR("TcpClientSocket") << errorMsg;

    closeConnection();
    m_socket = INVALID_SOCKET;
    throw sick::ConnectionError(errorCode, errorMsg);
  }
}

} // namespace sick

// NOLINTEND(misc-include-cleaner)
