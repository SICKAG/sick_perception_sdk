/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file sipmType.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>

namespace sick::picoScan150::v2_3_3::api::rest {

/**
 * @brief Payloads for endpoint /sipmType.
*/
struct sipmType
{

  constexpr static const char* variableName = "sipmType";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the type of the receiving unit.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::uint8_t sipmType)
        : _sipmType(sipmType)
      {}

      std::uint8_t _sipmType;
    };

  }; // struct Get

}; // struct sipmType

} // namespace sick::picoScan150::v2_3_3::api::rest
