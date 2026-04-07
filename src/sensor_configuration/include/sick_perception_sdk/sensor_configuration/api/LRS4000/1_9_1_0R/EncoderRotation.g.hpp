/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EncoderRotation.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /EncoderRotation.
*/
struct EncoderRotation
{

  constexpr static const char* methodName = "EncoderRotation";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Set the start orientation when the encoder transformation type is set to rotation.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(NumericRange<std::int32_t, -3600000, 3600000, 0> yaw, NumericRange<std::int32_t, -3600000, 3600000, 0> pitch, NumericRange<std::int32_t, -3600000, 3600000, 0> roll)
        : _yaw(std::move(yaw)), _pitch(std::move(pitch)), _roll(std::move(roll))
      {}

      NumericRange<std::int32_t, -3600000, 3600000, 0> _yaw;
      NumericRange<std::int32_t, -3600000, 3600000, 0> _pitch;
      NumericRange<std::int32_t, -3600000, 3600000, 0> _roll;
    };

  }; // struct Post

}; // struct EncoderRotation

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
