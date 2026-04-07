/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file MeanFilter.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /MeanFilter.
*/
struct MeanFilter
{

  constexpr static const char* variableName = "MeanFilter";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the mean filter settings. This filter smooths the distance value by calculating the arithmetic mean from the configured number of scans.
   */
  struct Get
  {
    struct Response
    {
      enum class eFilterMethod
      {
        Arithmetic = 0,
      };

      Response() = default;

      explicit Response(bool bEnable, NumericRange<std::uint16_t, 2, 100, 10> uiScanNumber, eFilterMethod eFilterMethod)
        : _bEnable(bEnable), _uiScanNumber(std::move(uiScanNumber)), _eFilterMethod(eFilterMethod)
      {}

      bool _bEnable;
      NumericRange<std::uint16_t, 2, 100, 10> _uiScanNumber;
      eFilterMethod _eFilterMethod;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the mean filter settings. This filter smooths the distance value by calculating the arithmetic mean from the configured number of scans.
   */
  struct Post
  {
    struct Request
    {
      enum class eFilterMethod
      {
        Arithmetic = 0,
      };

      Request() = default;

      explicit Request(bool bEnable, NumericRange<std::uint16_t, 2, 100, 10> uiScanNumber, eFilterMethod eFilterMethod)
        : _bEnable(bEnable), _uiScanNumber(std::move(uiScanNumber)), _eFilterMethod(eFilterMethod)
      {}

      bool _bEnable;
      NumericRange<std::uint16_t, 2, 100, 10> _uiScanNumber;
      eFilterMethod _eFilterMethod;
    };

  }; // struct Post

}; // struct MeanFilter

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
