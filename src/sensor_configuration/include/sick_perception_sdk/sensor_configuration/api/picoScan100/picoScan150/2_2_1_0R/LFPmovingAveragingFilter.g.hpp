/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LFPmovingAveragingFilter.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::picoScan150::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /LFPmovingAveragingFilter.
*/
struct LFPmovingAveragingFilter
{

  constexpr static const char* variableName = "LFPmovingAveragingFilter";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the mean filter settings. This filter smooths the distance value by calculating the arithmetic mean from the configured number of scans (2..4 scans). Points with zero distance are treated as missing values and are not taken into account for averaging. If all distances considered for averaging have the value 0, the result will be 0 as well.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool bEnable, NumericRange<std::uint16_t, 2, 4, 3> uiAveragingDepth)
        : _bEnable(bEnable), _uiAveragingDepth(std::move(uiAveragingDepth))
      {}

      bool _bEnable;
      NumericRange<std::uint16_t, 2, 4, 3> _uiAveragingDepth;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the mean filter settings. This filter smooths the distance value by calculating the arithmetic mean from the configured number of scans (2..4 scans). Points with zero distance are treated as missing values and are not taken into account for averaging. If all distances considered for averaging have the value 0, the result will be 0 as well.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool bEnable, NumericRange<std::uint16_t, 2, 4, 3> uiAveragingDepth)
        : _bEnable(bEnable), _uiAveragingDepth(std::move(uiAveragingDepth))
      {}

      bool _bEnable;
      NumericRange<std::uint16_t, 2, 4, 3> _uiAveragingDepth;
    };

  }; // struct Post

}; // struct LFPmovingAveragingFilter

} // namespace sick::picoScan150::v2_2_1_0R::api::rest
