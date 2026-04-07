/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file OpHours.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /OpHours.
*/
struct OpHours
{

  constexpr static const char* variableName = "OpHours";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the total number of operating hours during the lifetime of the device. The resolution is a 1/10 hour.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::uint32_t OpHours)
        : _OpHours(OpHours)
      {}

      std::uint32_t _OpHours;
    };

  }; // struct Get

}; // struct OpHours

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
