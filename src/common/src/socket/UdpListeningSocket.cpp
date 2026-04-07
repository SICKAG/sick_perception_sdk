/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/logging/logging.hpp>
#include <sick_perception_sdk/common/socket/ConnectionError.hpp>
#include <sick_perception_sdk/common/socket/UdpListeningSocket.hpp>

#include <cerrno>
#include <stdexcept>
#include <string>

// NOLINTBEGIN(misc-include-cleaner): socket definitions are platform dependent

namespace sick {

UdpListeningSocket::UdpListeningSocket(std::uint16_t port)
{
  LOG_INFO("UdpListeningSocket") << "Creating socket.";
  m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (m_socket == INVALID_SOCKET)
  {
    LOG_ERROR("UdpListeningSocket") << "Creating socket failed";
    cleanup();
    throw std::runtime_error("socket() failed");
  }

  // Prepare the sockaddr_in structure
  struct sockaddr_in server
  { };

  server.sin_family      = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port        = htons(port);

  LOG_INFO("UdpListeningSocket") << "Binding socket to port " << port;
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  if (bind(m_socket, reinterpret_cast<struct sockaddr*>(&server), sizeof(server)) == SOCKET_ERROR)
  {
    int const errorCode        = getErrorCode();
    std::string const errorMsg = "Unable to bind socket to port " + std::to_string(port) + " bind() failed with error " + std::to_string(errorCode) +
                                 ". Make sure that the port is available.";
    LOG_ERROR("UdpListeningSocket") << errorMsg;
    throw sick::ConnectionError(errorCode, errorMsg);
  }
}

void UdpListeningSocket::joinMulticastGroup(IpV4Address const& multicastGroupAddress, IpV4Address const& localInterfaceAddress)
{
  struct ip_mreq multicastRequest;
  multicastRequest.imr_multiaddr.s_addr = inet_addr(multicastGroupAddress.toString().c_str());
  multicastRequest.imr_interface.s_addr = inet_addr(localInterfaceAddress.toString().c_str());
  LOG_INFO("UdpListeningSocket") << "Joining multicast group " << multicastGroupAddress.toString() << " on interface with address "
                                 << localInterfaceAddress.toString();
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  if (setsockopt(m_socket, IPPROTO_IP, IP_ADD_MEMBERSHIP, reinterpret_cast<char const*>(&multicastRequest), sizeof(multicastRequest)) == SOCKET_ERROR)
  {
    int const errorCode        = getErrorCode();
    std::string const errorMsg = "Unable to join multicast group. setsockopt() failed with error " + std::to_string(errorCode) + ".";
    LOG_ERROR("UdpListeningSocket") << errorMsg;
    throw sick::ConnectionError(errorCode, errorMsg);
  }
}

UdpListeningSocket::~UdpListeningSocket()
{
  LOG_INFO("UdpListeningSocket") << "Closing UDP socket.";
  closeConnection();
}

} // namespace sick

// NOLINTEND(misc-include-cleaner)
