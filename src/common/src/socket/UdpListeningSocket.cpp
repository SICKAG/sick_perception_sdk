/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/logging/logging.hpp>
#include <sick_perception_sdk/common/socket/ConnectionError.hpp>
#include <sick_perception_sdk/common/socket/UdpListeningSocket.hpp>

#include <stdexcept>
#include <string>

// NOLINTBEGIN(misc-include-cleaner): socket definitions are platform dependent

namespace sick {

UdpListeningSocket::UdpListeningSocket(std::uint16_t port)
  : Socket {"UdpListeningSocket::" + std::to_string(port)}
{
  LOG_INFO(m_idString) << "Creating socket.";
  m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (m_socket == INVALID_SOCKET)
  {
    LOG_ERROR(m_idString) << "Creating socket failed";
    cleanup();
    throw std::runtime_error("socket() failed");
  }

  // Prepare the sockaddr_in structure
  struct sockaddr_in server {};

  server.sin_family      = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port        = htons(port);

  LOG_INFO(m_idString) << "Binding listening socket to port " << port << ".";
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  if (bind(m_socket, reinterpret_cast<struct sockaddr*>(&server), sizeof(server)) == SOCKET_ERROR)
  {
    int const errorCode        = getErrorCode();
    std::string const errorMsg = "Unable to bind socket to port " + std::to_string(port) + " bind() failed with error " + std::to_string(errorCode) +
                                 ". Make sure that the port is available.";
    LOG_ERROR(m_idString) << errorMsg;
    throw sick::ConnectionError(errorCode, errorMsg);
  }
}

void UdpListeningSocket::joinMulticastGroup(IpV4Address const& multicastGroupAddress, IpV4Address const& localInterfaceAddress)
{
  sockaddr_in multicastGroupSockAddr {};
  inetPton(multicastGroupAddress.toString().c_str(), multicastGroupSockAddr);

  sockaddr_in localInterfaceSockAddr {};
  inetPton(localInterfaceAddress.toString().c_str(), localInterfaceSockAddr);

  struct ip_mreq multicastRequest {};

  multicastRequest.imr_multiaddr = multicastGroupSockAddr.sin_addr;
  multicastRequest.imr_interface = localInterfaceSockAddr.sin_addr;

  LOG_INFO(m_idString) << "Joining multicast group " << multicastGroupAddress << " on interface with address " << localInterfaceAddress;

  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  if (setsockopt(m_socket, IPPROTO_IP, IP_ADD_MEMBERSHIP, reinterpret_cast<char const*>(&multicastRequest), sizeof(multicastRequest)) == SOCKET_ERROR)
  {
    int const errorCode        = getErrorCode();
    std::string const errorMsg = "Unable to join multicast group. setsockopt() failed with error " + std::to_string(errorCode) + ".";
    LOG_ERROR(m_idString) << errorMsg;
    throw sick::ConnectionError(errorCode, errorMsg);
  }
}

UdpListeningSocket::~UdpListeningSocket()
{
  LOG_INFO(m_idString) << "Closing listening socket.";
  closeConnection();
}

} // namespace sick

// NOLINTEND(misc-include-cleaner)
