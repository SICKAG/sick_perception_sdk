/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EtherIPMaskDHCP.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <array>
#include <cstdint>

namespace sick::multiScan200::v1_1_0::api::rest {

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

} // namespace sick::multiScan200::v1_1_0::api::rest
