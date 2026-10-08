/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file SensorPosition.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::multiScan200::v1_1_0::api::rest {

/**
 * @brief Payloads for endpoint /SensorPosition.
*/
struct SensorPosition
{

  constexpr static const char* variableName = "SensorPosition";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the mounting position.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(NumericRange<int, -100000, 100000, 0> x, NumericRange<int, -100000, 100000, 0> y, NumericRange<int, -100000, 100000, 0> z, NumericRange<int, -3600000, 3600000, 0> yaw, NumericRange<int, -3600000, 3600000, 0> pitch, NumericRange<int, -3600000, 3600000, 0> roll)
        : _x(x), _y(y), _z(z), _yaw(yaw), _pitch(pitch), _roll(roll)
      {}

      NumericRange<int, -100000, 100000, 0> _x;
      NumericRange<int, -100000, 100000, 0> _y;
      NumericRange<int, -100000, 100000, 0> _z;
      NumericRange<int, -3600000, 3600000, 0> _yaw;
      NumericRange<int, -3600000, 3600000, 0> _pitch;
      NumericRange<int, -3600000, 3600000, 0> _roll;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the mounting position.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(NumericRange<int, -100000, 100000, 0> x, NumericRange<int, -100000, 100000, 0> y, NumericRange<int, -100000, 100000, 0> z, NumericRange<int, -3600000, 3600000, 0> yaw, NumericRange<int, -3600000, 3600000, 0> pitch, NumericRange<int, -3600000, 3600000, 0> roll)
        : _x(x), _y(y), _z(z), _yaw(yaw), _pitch(pitch), _roll(roll)
      {}

      NumericRange<int, -100000, 100000, 0> _x;
      NumericRange<int, -100000, 100000, 0> _y;
      NumericRange<int, -100000, 100000, 0> _z;
      NumericRange<int, -3600000, 3600000, 0> _yaw;
      NumericRange<int, -3600000, 3600000, 0> _pitch;
      NumericRange<int, -3600000, 3600000, 0> _roll;
    };

  }; // struct Post

}; // struct SensorPosition

} // namespace sick::multiScan200::v1_1_0::api::rest
