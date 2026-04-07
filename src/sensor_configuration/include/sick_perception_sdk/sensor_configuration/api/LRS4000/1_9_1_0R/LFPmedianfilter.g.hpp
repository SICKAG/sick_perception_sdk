/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LFPmedianfilter.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /LFPmedianfilter.
*/
struct LFPmedianfilter
{

  constexpr static const char* variableName = "LFPmedianfilter";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the median filter settings. This filter smooths the distance values by transmitting just the median value of the last X scans.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool bEnable, NumericRange<std::uint16_t, 3, 3, 3> uiMedianWidth)
        : _bEnable(bEnable), _uiMedianWidth(std::move(uiMedianWidth))
      {}

      bool _bEnable;
      NumericRange<std::uint16_t, 3, 3, 3> _uiMedianWidth;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the median filter settings. This filter smooths the distance values by transmitting just the median value of the last X scans.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool bEnable, NumericRange<std::uint16_t, 3, 3, 3> uiMedianWidth)
        : _bEnable(bEnable), _uiMedianWidth(std::move(uiMedianWidth))
      {}

      bool _bEnable;
      NumericRange<std::uint16_t, 3, 3, 3> _uiMedianWidth;
    };

  }; // struct Post

}; // struct LFPmedianfilter

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
