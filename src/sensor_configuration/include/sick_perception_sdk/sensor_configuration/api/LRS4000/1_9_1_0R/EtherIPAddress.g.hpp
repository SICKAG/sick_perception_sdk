/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EtherIPAddress.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /EtherIPAddress.
*/
struct EtherIPAddress
{

  constexpr static const char* variableName = "EtherIPAddress";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets used static IP address.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::array<std::uint8_t, 4> EtherIPAddress)
        : _EtherIPAddress(EtherIPAddress)
      {}

      std::array<std::uint8_t, 4> _EtherIPAddress;
    };

  }; // struct Get

  /**
   * @brief Returns/sets used static IP address.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(std::array<std::uint8_t, 4> EtherIPAddress)
        : _EtherIPAddress(EtherIPAddress)
      {}

      std::array<std::uint8_t, 4> _EtherIPAddress;
    };

  }; // struct Post

}; // struct EtherIPAddress

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
