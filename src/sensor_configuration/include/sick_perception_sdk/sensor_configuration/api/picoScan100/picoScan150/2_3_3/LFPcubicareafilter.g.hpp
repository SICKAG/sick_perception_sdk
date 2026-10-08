/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LFPcubicareafilter.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::picoScan150::v2_3_3::api::rest {

/**
 * @brief Payloads for endpoint /LFPcubicareafilter.
*/
struct LFPcubicareafilter
{

  constexpr static const char* variableName = "LFPcubicareafilter";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the cuboid area filter settings. The cuboid area filter limits the measurement data to a box defined by its extension in the x- and y-axis.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool bEnable, NumericRange<std::int32_t, -200000, 200000, 0> lXMin, NumericRange<std::int32_t, -200000, 200000, 5000> lXMax, NumericRange<std::int32_t, -200000, 200000, -5000> lYMin, NumericRange<std::int32_t, -200000, 200000, 5000> lYMax, NumericRange<std::int32_t, -200000, 200000, -5> lZMin, NumericRange<std::int32_t, -200000, 200000, 5> lZMax)
        : _bEnable(bEnable), _lXMin(lXMin), _lXMax(lXMax), _lYMin(lYMin), _lYMax(lYMax), _lZMin(lZMin), _lZMax(lZMax)
      {}

      bool _bEnable;
      NumericRange<std::int32_t, -200000, 200000, 0> _lXMin;
      NumericRange<std::int32_t, -200000, 200000, 5000> _lXMax;
      NumericRange<std::int32_t, -200000, 200000, -5000> _lYMin;
      NumericRange<std::int32_t, -200000, 200000, 5000> _lYMax;
      NumericRange<std::int32_t, -200000, 200000, -5> _lZMin;
      NumericRange<std::int32_t, -200000, 200000, 5> _lZMax;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the cuboid area filter settings. The cuboid area filter limits the measurement data to a box defined by its extension in the x- and y-axis.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool bEnable, NumericRange<std::int32_t, -200000, 200000, 0> lXMin, NumericRange<std::int32_t, -200000, 200000, 5000> lXMax, NumericRange<std::int32_t, -200000, 200000, -5000> lYMin, NumericRange<std::int32_t, -200000, 200000, 5000> lYMax, NumericRange<std::int32_t, -200000, 200000, -5> lZMin, NumericRange<std::int32_t, -200000, 200000, 5> lZMax)
        : _bEnable(bEnable), _lXMin(lXMin), _lXMax(lXMax), _lYMin(lYMin), _lYMax(lYMax), _lZMin(lZMin), _lZMax(lZMax)
      {}

      bool _bEnable;
      NumericRange<std::int32_t, -200000, 200000, 0> _lXMin;
      NumericRange<std::int32_t, -200000, 200000, 5000> _lXMax;
      NumericRange<std::int32_t, -200000, 200000, -5000> _lYMin;
      NumericRange<std::int32_t, -200000, 200000, 5000> _lYMax;
      NumericRange<std::int32_t, -200000, 200000, -5> _lZMin;
      NumericRange<std::int32_t, -200000, 200000, 5> _lZMax;
    };

  }; // struct Post

}; // struct LFPcubicareafilter

} // namespace sick::picoScan150::v2_3_3::api::rest
