/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file SensorPosition.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /SensorPosition.
*/
struct SensorPosition
{

  constexpr static const char* variableName = "SensorPosition";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Return/set the mounting position in 1/10000 deg.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(NumericRange<std::int32_t, -100000, 100000, 0> x, NumericRange<std::int32_t, -100000, 100000, 0> y, NumericRange<std::int32_t, -100000, 100000, 0> z, NumericRange<std::int32_t, -3600000, 3600000, 0> yaw, NumericRange<std::int32_t, -3600000, 3600000, 0> pitch, NumericRange<std::int32_t, -3600000, 3600000, 0> roll)
        : _x(std::move(x)), _y(std::move(y)), _z(std::move(z)), _yaw(std::move(yaw)), _pitch(std::move(pitch)), _roll(std::move(roll))
      {}

      NumericRange<std::int32_t, -100000, 100000, 0> _x;
      NumericRange<std::int32_t, -100000, 100000, 0> _y;
      NumericRange<std::int32_t, -100000, 100000, 0> _z;
      NumericRange<std::int32_t, -3600000, 3600000, 0> _yaw;
      NumericRange<std::int32_t, -3600000, 3600000, 0> _pitch;
      NumericRange<std::int32_t, -3600000, 3600000, 0> _roll;
    };

  }; // struct Get

  /**
   * @brief Return/set the mounting position in 1/10000 deg.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(NumericRange<std::int32_t, -100000, 100000, 0> x, NumericRange<std::int32_t, -100000, 100000, 0> y, NumericRange<std::int32_t, -100000, 100000, 0> z, NumericRange<std::int32_t, -3600000, 3600000, 0> yaw, NumericRange<std::int32_t, -3600000, 3600000, 0> pitch, NumericRange<std::int32_t, -3600000, 3600000, 0> roll)
        : _x(std::move(x)), _y(std::move(y)), _z(std::move(z)), _yaw(std::move(yaw)), _pitch(std::move(pitch)), _roll(std::move(roll))
      {}

      NumericRange<std::int32_t, -100000, 100000, 0> _x;
      NumericRange<std::int32_t, -100000, 100000, 0> _y;
      NumericRange<std::int32_t, -100000, 100000, 0> _z;
      NumericRange<std::int32_t, -3600000, 3600000, 0> _yaw;
      NumericRange<std::int32_t, -3600000, 3600000, 0> _pitch;
      NumericRange<std::int32_t, -3600000, 3600000, 0> _roll;
    };

  }; // struct Post

}; // struct SensorPosition

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
