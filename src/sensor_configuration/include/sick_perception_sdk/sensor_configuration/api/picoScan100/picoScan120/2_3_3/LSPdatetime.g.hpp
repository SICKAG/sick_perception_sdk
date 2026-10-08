/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LSPdatetime.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::picoScan120::v2_3_3::api::rest {

/**
 * @brief Payloads for endpoint /LSPdatetime.
*/
struct LSPdatetime
{

  constexpr static const char* variableName = "LSPdatetime";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the current time of the device (years, months, days, hours, minutes, seconds, microseconds).
   */
  struct Get
  {
    struct Response
    {
      struct LSPdatetime
      {
        LSPdatetime() = default;

        explicit LSPdatetime(NumericRange<std::uint16_t, 0, 2105, 0> uiYear, NumericRange<std::uint8_t, 0, 12, 1> usiMonth, NumericRange<std::uint8_t, 0, 31, 1> usiDay, NumericRange<std::uint8_t, 0, 23, 0> usiHour, NumericRange<std::uint8_t, 0, 59, 0> usiMinute, NumericRange<std::uint8_t, 0, 59, 0> usiSec, NumericRange<std::uint32_t, 0, 999999, 0> udiUSec)
          : _uiYear(uiYear), _usiMonth(usiMonth), _usiDay(usiDay), _usiHour(usiHour), _usiMinute(usiMinute), _usiSec(usiSec), _udiUSec(udiUSec)
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

      explicit Response(LSPdatetime LSPdatetime)
        : _LSPdatetime(LSPdatetime)
      {}

      LSPdatetime _LSPdatetime;
    };

  }; // struct Get

}; // struct LSPdatetime

} // namespace sick::picoScan120::v2_3_3::api::rest
