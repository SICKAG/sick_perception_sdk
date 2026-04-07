/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LFPcubicareafilter.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /LFPcubicareafilter.
*/
struct LFPcubicareafilter
{

  constexpr static const char* variableName = "LFPcubicareafilter";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the cuboid area filter settings. The cuboid area filter limits the measurement data box defined by its extension in the x- and y-axis.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool bEnable, NumericRange<std::int32_t, -200000, 200000, -20000> lXMin, NumericRange<std::int32_t, -200000, 200000, 20000> lXMax, NumericRange<std::int32_t, -200000, 200000, -20000> lYMin, NumericRange<std::int32_t, -200000, 200000, 20000> lYMax, NumericRange<std::int32_t, -200000, 200000, -20000> lZMin, NumericRange<std::int32_t, -200000, 200000, 20000> lZMax)
        : _bEnable(bEnable), _lXMin(std::move(lXMin)), _lXMax(std::move(lXMax)), _lYMin(std::move(lYMin)), _lYMax(std::move(lYMax)), _lZMin(std::move(lZMin)), _lZMax(std::move(lZMax))
      {}

      bool _bEnable;
      NumericRange<std::int32_t, -200000, 200000, -20000> _lXMin;
      NumericRange<std::int32_t, -200000, 200000, 20000> _lXMax;
      NumericRange<std::int32_t, -200000, 200000, -20000> _lYMin;
      NumericRange<std::int32_t, -200000, 200000, 20000> _lYMax;
      NumericRange<std::int32_t, -200000, 200000, -20000> _lZMin;
      NumericRange<std::int32_t, -200000, 200000, 20000> _lZMax;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the cuboid area filter settings. The cuboid area filter limits the measurement data box defined by its extension in the x- and y-axis.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool bEnable, NumericRange<std::int32_t, -200000, 200000, -20000> lXMin, NumericRange<std::int32_t, -200000, 200000, 20000> lXMax, NumericRange<std::int32_t, -200000, 200000, -20000> lYMin, NumericRange<std::int32_t, -200000, 200000, 20000> lYMax, NumericRange<std::int32_t, -200000, 200000, -20000> lZMin, NumericRange<std::int32_t, -200000, 200000, 20000> lZMax)
        : _bEnable(bEnable), _lXMin(std::move(lXMin)), _lXMax(std::move(lXMax)), _lYMin(std::move(lYMin)), _lYMax(std::move(lYMax)), _lZMin(std::move(lZMin)), _lZMax(std::move(lZMax))
      {}

      bool _bEnable;
      NumericRange<std::int32_t, -200000, 200000, -20000> _lXMin;
      NumericRange<std::int32_t, -200000, 200000, 20000> _lXMax;
      NumericRange<std::int32_t, -200000, 200000, -20000> _lYMin;
      NumericRange<std::int32_t, -200000, 200000, 20000> _lYMax;
      NumericRange<std::int32_t, -200000, 200000, -20000> _lZMin;
      NumericRange<std::int32_t, -200000, 200000, 20000> _lZMax;
    };

  }; // struct Post

}; // struct LFPcubicareafilter

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
