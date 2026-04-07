/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file DateTime.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /DateTime.
*/
struct DateTime
{

  constexpr static const char* variableName = "DateTime";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the current time of the device (years, months, days, hours, minutes, seconds, microseconds).
   */
  struct Get
  {
    struct Response
    {
      struct DateTime
      {
        DateTime() = default;

        explicit DateTime(NumericRange<std::uint16_t, 0, 2105, 0> uiYear, NumericRange<std::uint8_t, 0, 12, 1> usiMonth, NumericRange<std::uint8_t, 0, 31, 1> usiDay, NumericRange<std::uint8_t, 0, 23, 0> usiHour, NumericRange<std::uint8_t, 0, 59, 0> usiMinute, NumericRange<std::uint8_t, 0, 59, 0> usiSec, NumericRange<std::uint32_t, 0, 999999, 0> udiUSec)
          : _uiYear(std::move(uiYear)), _usiMonth(std::move(usiMonth)), _usiDay(std::move(usiDay)), _usiHour(std::move(usiHour)), _usiMinute(std::move(usiMinute)), _usiSec(std::move(usiSec)), _udiUSec(std::move(udiUSec))
        {}

        NumericRange<std::uint16_t, 0, 2105, 0> _uiYear;
        NumericRange<std::uint8_t, 0, 12, 1> _usiMonth;
        NumericRange<std::uint8_t, 0, 31, 1> _usiDay;
        NumericRange<std::uint8_t, 0, 23, 0> _usiHour;
        NumericRange<std::uint8_t, 0, 59, 0> _usiMinute;
        NumericRange<std::uint8_t, 0, 59, 0> _usiSec;
        NumericRange<std::uint32_t, 0, 999999, 0> _udiUSec;
      };

      Response() = default;

      explicit Response(DateTime DateTime)
        : _DateTime(DateTime)
      {}

      DateTime _DateTime;
    };

  }; // struct Get

}; // struct DateTime

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
