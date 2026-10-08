/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EtherAuxIPPort.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>

namespace sick::picoScan150::v2_3_3::api::rest {

/**
 * @brief Payloads for endpoint /EtherAuxIPPort.
*/
struct EtherAuxIPPort
{

  constexpr static const char* variableName = "EtherAuxIPPort";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the port settings for the LMDscandata output 2 (CoLa ASCII TCP).
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::uint16_t EtherAuxIPPort)
        : _EtherAuxIPPort(EtherAuxIPPort)
      {}

      std::uint16_t _EtherAuxIPPort;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the port settings for the LMDscandata output 2 (CoLa ASCII TCP).

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(std::uint16_t EtherAuxIPPort)
        : _EtherAuxIPPort(EtherAuxIPPort)
      {}

      std::uint16_t _EtherAuxIPPort;
    };

  }; // struct Post

}; // struct EtherAuxIPPort

} // namespace sick::picoScan150::v2_3_3::api::rest
