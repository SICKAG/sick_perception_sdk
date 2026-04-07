/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ImuDataEthSettings.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /ImuDataEthSettings.
*/
struct ImuDataEthSettings
{

  constexpr static const char* variableName = "ImuDataEthSettings";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the destination IP address settings for IMU data streaming (UDP).
   */
  struct Get
  {
    struct Response
    {
      enum class Protocol
      {
        Udp = 1,
        Tcp = 2,
      };

      Response() = default;

      explicit Response(Protocol Protocol, std::vector<std::uint8_t> IPAddress, std::uint16_t Port)
        : _Protocol(Protocol), _IPAddress(IPAddress), _Port(Port)
      {}

      Protocol _Protocol;
      std::vector<std::uint8_t> _IPAddress;
      std::uint16_t _Port;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the destination IP address settings for IMU data streaming (UDP).

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      enum class Protocol
      {
        Udp = 1,
        Tcp = 2,
      };

      Request() = default;

      explicit Request(Protocol Protocol, std::vector<std::uint8_t> IPAddress, std::uint16_t Port)
        : _Protocol(Protocol), _IPAddress(IPAddress), _Port(Port)
      {}

      Protocol _Protocol;
      std::vector<std::uint8_t> _IPAddress;
      std::uint16_t _Port;
    };

  }; // struct Post

}; // struct ImuDataEthSettings

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
