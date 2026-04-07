/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file RotationOffset.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /RotationOffset.
*/
struct RotationOffset
{

  constexpr static const char* variableName = "RotationOffset";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Read/Write the current rotation offset of the scan merge in x, y and z direction in mm.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(NumericRange<std::int32_t, -100000, 100000, 0> x, NumericRange<std::int32_t, -100000, 100000, 0> y, NumericRange<std::int32_t, -100000, 100000, 0> z)
        : _x(std::move(x)), _y(std::move(y)), _z(std::move(z))
      {}

      NumericRange<std::int32_t, -100000, 100000, 0> _x;
      NumericRange<std::int32_t, -100000, 100000, 0> _y;
      NumericRange<std::int32_t, -100000, 100000, 0> _z;
    };

  }; // struct Get

  /**
   * @brief Read/Write the current rotation offset of the scan merge in x, y and z direction in mm.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(NumericRange<std::int32_t, -100000, 100000, 0> x, NumericRange<std::int32_t, -100000, 100000, 0> y, NumericRange<std::int32_t, -100000, 100000, 0> z)
        : _x(std::move(x)), _y(std::move(y)), _z(std::move(z))
      {}

      NumericRange<std::int32_t, -100000, 100000, 0> _x;
      NumericRange<std::int32_t, -100000, 100000, 0> _y;
      NumericRange<std::int32_t, -100000, 100000, 0> _z;
    };

  }; // struct Post

}; // struct RotationOffset

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
