/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file PowerOnCnt.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>

namespace sick::picoScan120::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /PowerOnCnt.
*/
struct PowerOnCnt
{

  constexpr static const char* variableName = "PowerOnCnt";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the number of power-on cycles.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::uint32_t PowerOnCnt)
        : _PowerOnCnt(PowerOnCnt)
      {}

      std::uint32_t _PowerOnCnt;
    };

  }; // struct Get

}; // struct PowerOnCnt

} // namespace sick::picoScan120::v2_2_1_0R::api::rest
