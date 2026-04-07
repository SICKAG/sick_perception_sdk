/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EtherIPMaskDHCP.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /EtherIPMaskDHCP.
*/
struct EtherIPMaskDHCP
{

  constexpr static const char* variableName = "EtherIPMaskDHCP";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the assigned DHCP subnet mask.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::array<std::uint8_t, 4> EtherIPMaskDHCP)
        : _EtherIPMaskDHCP(EtherIPMaskDHCP)
      {}

      std::array<std::uint8_t, 4> _EtherIPMaskDHCP;
    };

  }; // struct Get

}; // struct EtherIPMaskDHCP

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
