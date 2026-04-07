/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file temperatureAlarmConfiguration.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>

namespace sick::picoScan150::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /temperatureAlarmConfiguration.
*/
struct temperatureAlarmConfiguration
{

  constexpr static const char* variableName = "temperatureAlarmConfiguration";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets temperature alarm thresholds.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::int8_t upperThreshold, std::int8_t lowerThreshold)
        : _upperThreshold(upperThreshold), _lowerThreshold(lowerThreshold)
      {}

      std::int8_t _upperThreshold;
      std::int8_t _lowerThreshold;
    };

  }; // struct Get

  /**
   * @brief Returns/sets temperature alarm thresholds.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(std::int8_t upperThreshold, std::int8_t lowerThreshold)
        : _upperThreshold(upperThreshold), _lowerThreshold(lowerThreshold)
      {}

      std::int8_t _upperThreshold;
      std::int8_t _lowerThreshold;
    };

  }; // struct Post

}; // struct temperatureAlarmConfiguration

} // namespace sick::picoScan150::v2_2_1_0R::api::rest
