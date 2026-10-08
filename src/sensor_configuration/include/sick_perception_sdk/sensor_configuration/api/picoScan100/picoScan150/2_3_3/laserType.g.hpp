/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file laserType.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>

namespace sick::picoScan150::v2_3_3::api::rest {

/**
 * @brief Payloads for endpoint /laserType.
*/
struct laserType
{

  constexpr static const char* variableName = "laserType";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the type of the sending unit.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::uint8_t laserType)
        : _laserType(laserType)
      {}

      std::uint8_t _laserType;
    };

  }; // struct Get

}; // struct laserType

} // namespace sick::picoScan150::v2_3_3::api::rest
