/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LFPintervalFilter.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::multiScan200::v1_1_0::api::rest {

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

      explicit Response(bool bEnable, NumericRange<int, 2, 50, 2> uiReductionFactor)
        : _bEnable(bEnable), _uiReductionFactor(uiReductionFactor)
      {}

      bool _bEnable;
      NumericRange<int, 2, 50, 2> _uiReductionFactor;
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

      explicit Request(bool bEnable, NumericRange<int, 2, 50, 2> uiReductionFactor)
        : _bEnable(bEnable), _uiReductionFactor(uiReductionFactor)
      {}

      bool _bEnable;
      NumericRange<int, 2, 50, 2> _uiReductionFactor;
    };

  }; // struct Post

}; // struct LFPintervalFilter

} // namespace sick::multiScan200::v1_1_0::api::rest
