/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file temperatureAlarmConfiguration.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /temperatureAlarmConfiguration.
*/
struct temperatureAlarmConfiguration
{

  constexpr static const char* variableName = "temperatureAlarmConfiguration";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/set the thresholds for the device temperature alarm status.
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
   * @brief Returns/set the thresholds for the device temperature alarm status.

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

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
