/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LFPintervalFilter.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::picoScan150::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /LFPintervalFilter.
*/
struct LFPintervalFilter
{

  constexpr static const char* variableName = "LFPintervalFilter";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the interval filter settings. The filter reduces the scan output rate by a given factor.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool bEnable, NumericRange<std::int32_t, 2, 50, 2> uiReductionFactor)
        : _bEnable(bEnable), _uiReductionFactor(std::move(uiReductionFactor))
      {}

      bool _bEnable;
      NumericRange<std::int32_t, 2, 50, 2> _uiReductionFactor;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the interval filter settings. The filter reduces the scan output rate by a given factor.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool bEnable, NumericRange<std::int32_t, 2, 50, 2> uiReductionFactor)
        : _bEnable(bEnable), _uiReductionFactor(std::move(uiReductionFactor))
      {}

      bool _bEnable;
      NumericRange<std::int32_t, 2, 50, 2> _uiReductionFactor;
    };

  }; // struct Post

}; // struct LFPintervalFilter

} // namespace sick::picoScan150::v2_2_1_0R::api::rest
