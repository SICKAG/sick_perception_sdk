/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/*
 * Cross-platform compatibility superclass for sockets
 *
 * Copyright (C) 2019 Simon D. Levy
 * Modified by SICK AG
 *
 * Copyright
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished
 * to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
*/

// NOLINTBEGIN

#pragma once

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/logging/logging.hpp>
#include <sick_perception_sdk/common/socket/ReceiveError.hpp>

// Windows
#ifdef _WIN32
#  pragma comment(lib, "ws2_32.lib")
#  define WIN32_LEAN_AND_MEAN
#  undef TEXT
#  include <winsock2.h>
#  include <ws2tcpip.h>
typedef SSIZE_T ssize_t;

// Linux
#else
#  define sprintf_s sprintf
typedef int SOCKET;
#  include <arpa/inet.h>
#  include <netdb.h>
#  include <sys/socket.h>
#  include <sys/types.h>
#  include <unistd.h>
#  if !defined(INVALID_SOCKET)
#    define INVALID_SOCKET -1
#  elif INVALID_SOCKET != -1
#    error "Conflicting definition of INVALID_SOCKET. Must be defined as -1."
#  endif
static int const SOCKET_ERROR = -1;
#endif

#include <chrono>
#include <limits>
#include <stdexcept>
#include <vector>

namespace sick {
class SDK_EXPORT Socket
{
public:
  Socket()
    : m_socket(INVALID_SOCKET)
  {
    initWinsock();
  }

  static auto errorCodeIsTimeoutError(int errorCode) -> bool
  {
#ifdef _WIN32
    return errorCode == WSAETIMEDOUT;
#else
    return errorCode == EAGAIN || errorCode == EWOULDBLOCK;
#endif
  }

  void setTimeout(std::chrono::milliseconds timeout)
  {
    auto const timeoutCount = timeout.count();
    if (timeoutCount < 0)
    {
      throw std::invalid_argument("Timeout must be non-negative.");
    }
    if (timeoutCount > static_cast<std::chrono::milliseconds::rep>((std::numeric_limits<uint32_t>::max)()))
    {
      throw std::out_of_range("Timeout is too large.");
    }
    LOG_INFO("Socket") << "Setting socket options SO_RCVTIMEO and SO_SNDTIMEO to " << timeoutCount << " ms";

    auto const msec = static_cast<uint32_t>(timeoutCount);
#ifdef _WIN32
    setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&msec, sizeof(msec));
    setsockopt(m_socket, SOL_SOCKET, SO_SNDTIMEO, (char*)&msec, sizeof(msec));
#else
    struct timeval timeoutVal;
    timeoutVal.tv_sec  = msec / 1000;
    timeoutVal.tv_usec = (msec * 1000) % 1000000;
    setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, &timeoutVal, sizeof(timeoutVal));
    setsockopt(m_socket, SOL_SOCKET, SO_SNDTIMEO, &timeoutVal, sizeof(timeoutVal));
#endif
  }

  size_t receive(std::vector<std::uint8_t>& buffer)
  {
    if (buffer.size() > (std::numeric_limits<int>::max)())
    {
      throw std::runtime_error("Data length exceeds maximum limit for recv()");
    }
    LOG_FAST_LOOP_INFO("Socket") << "Calling recv() with buffer size " << buffer.size();
    ssize_t numberOfBytesReceived = recv(m_socket, (char*)buffer.data(), static_cast<int>(buffer.size()), 0);
    if (numberOfBytesReceived < 0)
    {
      throw ReceiveError(Socket::getErrorCode());
    }
    return (size_t)numberOfBytesReceived;
  }

  virtual void connect()
  { }

  void closeConnection(void)
  {
#ifdef _WIN32
    closesocket(m_socket);
#else
    close(m_socket);
#endif
  }

  int getErrorCode()
  {
#ifdef _WIN32
    return WSAGetLastError();
#else
    return errno;
#endif
  }

protected:
  SOCKET m_socket;

  void initWinsock(void)
  {
#ifdef _WIN32
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
      throw std::runtime_error("Failed to initialize winsock.");
    }
#endif
  }

  void cleanup(void)
  {
#ifdef _WIN32
    WSACleanup();
#endif
  }

  void inetPton(char const* host, struct sockaddr_in& saddr_in)
  {
#ifdef _WIN32
    InetPtonA(AF_INET, host, &(saddr_in.sin_addr.s_addr));
#else
    inet_pton(AF_INET, host, &(saddr_in.sin_addr));
#endif
  }
};
} // namespace sick

// NOLINTEND
