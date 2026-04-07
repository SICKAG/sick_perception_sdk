/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EtherIPMask.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>

namespace sick::picoScan150::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /EtherIPMask.
*/
struct EtherIPMask
{

  constexpr static const char* variableName = "EtherIPMask";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the subnet mask.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::array<std::uint8_t, 4> EtherIPMask)
        : _EtherIPMask(EtherIPMask)
      {}

      std::array<std::uint8_t, 4> _EtherIPMask;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the subnet mask.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(std::array<std::uint8_t, 4> EtherIPMask)
        : _EtherIPMask(EtherIPMask)
      {}

      std::array<std::uint8_t, 4> _EtherIPMask;
    };

  }; // struct Post

}; // struct EtherIPMask

} // namespace sick::picoScan150::v2_2_1_0R::api::rest
