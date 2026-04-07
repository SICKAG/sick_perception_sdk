/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LFPradialDistanceRangeFilter.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::picoScan150::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /LFPradialDistanceRangeFilter.
*/
struct LFPradialDistanceRangeFilter
{

  constexpr static const char* variableName = "LFPradialDistanceRangeFilter";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the scanning range filter settings. Restriction of the distance measurements to a specified distance range. Measurement distances outside of the specified range are assigned the distance and RSSI value 0.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool bEnable, NumericRange<std::int32_t, 0, 200000, 0> ulDistMin, NumericRange<std::int32_t, 0, 200000, 200000> ulDistMax)
        : _bEnable(bEnable), _ulDistMin(std::move(ulDistMin)), _ulDistMax(std::move(ulDistMax))
      {}

      bool _bEnable;
      NumericRange<std::int32_t, 0, 200000, 0> _ulDistMin;
      NumericRange<std::int32_t, 0, 200000, 200000> _ulDistMax;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the scanning range filter settings. Restriction of the distance measurements to a specified distance range. Measurement distances outside of the specified range are assigned the distance and RSSI value 0.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool bEnable, NumericRange<std::int32_t, 0, 200000, 0> ulDistMin, NumericRange<std::int32_t, 0, 200000, 200000> ulDistMax)
        : _bEnable(bEnable), _ulDistMin(std::move(ulDistMin)), _ulDistMax(std::move(ulDistMax))
      {}

      bool _bEnable;
      NumericRange<std::int32_t, 0, 200000, 0> _ulDistMin;
      NumericRange<std::int32_t, 0, 200000, 200000> _ulDistMax;
    };

  }; // struct Post

}; // struct LFPradialDistanceRangeFilter

} // namespace sick::picoScan150::v2_2_1_0R::api::rest
