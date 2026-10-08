/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EtherHostIPPort.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>

namespace sick::picoScan150::v2_3_3::api::rest {

/**
 * @brief Payloads for endpoint /EtherHostIPPort.
*/
struct EtherHostIPPort
{

  constexpr static const char* variableName = "EtherHostIPPort";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the port settings for the LMDscandata output (CoLa Binary TCP).
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::uint16_t EtherHostIPPort)
        : _EtherHostIPPort(EtherHostIPPort)
      {}

      std::uint16_t _EtherHostIPPort;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the port settings for the LMDscandata output (CoLa Binary TCP).

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(std::uint16_t EtherHostIPPort)
        : _EtherHostIPPort(EtherHostIPPort)
      {}

      std::uint16_t _EtherHostIPPort;
    };

  }; // struct Post

}; // struct EtherHostIPPort

} // namespace sick::picoScan150::v2_3_3::api::rest
