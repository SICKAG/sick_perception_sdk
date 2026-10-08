/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EtherIPGateAddress.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <array>
#include <cstdint>

namespace sick::multiScan200::v1_1_0::api::rest {

/**
 * @brief Payloads for endpoint /EtherIPGateAddress.
*/
struct EtherIPGateAddress
{

  constexpr static const char* variableName = "EtherIPGateAddress";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the default gateway address.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::array<std::uint8_t, 4> EtherIPGateAddress)
        : _EtherIPGateAddress(EtherIPGateAddress)
      {}

      std::array<std::uint8_t, 4> _EtherIPGateAddress;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the default gateway address.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(std::array<std::uint8_t, 4> EtherIPGateAddress)
        : _EtherIPGateAddress(EtherIPGateAddress)
      {}

      std::array<std::uint8_t, 4> _EtherIPGateAddress;
    };

  }; // struct Post

}; // struct EtherIPGateAddress

} // namespace sick::multiScan200::v1_1_0::api::rest
