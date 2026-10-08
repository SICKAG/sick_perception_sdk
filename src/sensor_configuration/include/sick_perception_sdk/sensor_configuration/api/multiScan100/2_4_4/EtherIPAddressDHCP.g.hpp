/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EtherIPAddressDHCP.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.4'.
 * Do not edit manually!
 */
#pragma once

#include <array>
#include <cstdint>

namespace sick::multiScan100::v2_4_4::api::rest {

/**
 * @brief Payloads for endpoint /EtherIPAddressDHCP.
*/
struct EtherIPAddressDHCP
{

  constexpr static const char* variableName = "EtherIPAddressDHCP";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the assigned DHCP IP address.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::array<std::uint8_t, 4> EtherIPAddressDHCP)
        : _EtherIPAddressDHCP(EtherIPAddressDHCP)
      {}

      std::array<std::uint8_t, 4> _EtherIPAddressDHCP;
    };

  }; // struct Get

}; // struct EtherIPAddressDHCP

} // namespace sick::multiScan100::v2_4_4::api::rest
