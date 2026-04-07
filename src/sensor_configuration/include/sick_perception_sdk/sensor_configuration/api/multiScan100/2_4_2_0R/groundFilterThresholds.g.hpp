/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file groundFilterThresholds.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /groundFilterThresholds.
*/
struct groundFilterThresholds
{

  constexpr static const char* variableName = "groundFilterThresholds";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/set the ground filter thresholds.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(NumericRange<std::int16_t, -10000, 0, -100> minimumDistance, NumericRange<std::int16_t, 0, 10000, 100> maximumDistance)
        : _minimumDistance(std::move(minimumDistance)), _maximumDistance(std::move(maximumDistance))
      {}

      NumericRange<std::int16_t, -10000, 0, -100> _minimumDistance;
      NumericRange<std::int16_t, 0, 10000, 100> _maximumDistance;
    };

  }; // struct Get

  /**
   * @brief Returns/set the ground filter thresholds.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(NumericRange<std::int16_t, -10000, 0, -100> minimumDistance, NumericRange<std::int16_t, 0, 10000, 100> maximumDistance)
        : _minimumDistance(std::move(minimumDistance)), _maximumDistance(std::move(maximumDistance))
      {}

      NumericRange<std::int16_t, -10000, 0, -100> _minimumDistance;
      NumericRange<std::int16_t, 0, 10000, 100> _maximumDistance;
    };

  }; // struct Post

}; // struct groundFilterThresholds

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
