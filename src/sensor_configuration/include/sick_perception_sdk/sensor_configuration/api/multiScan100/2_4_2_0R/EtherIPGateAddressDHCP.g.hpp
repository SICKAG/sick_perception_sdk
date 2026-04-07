/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EtherIPGateAddressDHCP.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /EtherIPGateAddressDHCP.
*/
struct EtherIPGateAddressDHCP
{

  constexpr static const char* variableName = "EtherIPGateAddressDHCP";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the assigned DHCP default gateway address.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::array<std::uint8_t, 4> EtherIPGateAddressDHCP)
        : _EtherIPGateAddressDHCP(EtherIPGateAddressDHCP)
      {}

      std::array<std::uint8_t, 4> _EtherIPGateAddressDHCP;
    };

  }; // struct Get

}; // struct EtherIPGateAddressDHCP

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
