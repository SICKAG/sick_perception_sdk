/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EncoderTranslation.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::LRS4000::v1_9_1::api::rest {

/**
 * @brief Payloads for endpoint /EncoderTranslation.
*/
struct EncoderTranslation
{

  constexpr static const char* methodName = "EncoderTranslation";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Set the start orientation when the encoder transformation type is set to translation.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(NumericRange<std::int32_t, -100000, 100000, 0> x, NumericRange<std::int32_t, -100000, 100000, 0> y, NumericRange<std::int32_t, -100000, 100000, 0> z)
        : _x(x), _y(y), _z(z)
      {}

      NumericRange<std::int32_t, -100000, 100000, 0> _x;
      NumericRange<std::int32_t, -100000, 100000, 0> _y;
      NumericRange<std::int32_t, -100000, 100000, 0> _z;
    };

  }; // struct Post

}; // struct EncoderTranslation

} // namespace sick::LRS4000::v1_9_1::api::rest
