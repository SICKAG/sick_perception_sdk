/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LSPsetdatetime.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::picoScan150::v2_2_1::api::rest {

/**
 * @brief Payloads for endpoint /LSPsetdatetime.
*/
struct LSPsetdatetime
{

  constexpr static const char* methodName = "LSPsetdatetime";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Sets the time of the device (years, months, days, hours, minutes, seconds, microseconds).

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      struct DateTime
      {
        DateTime() = default;

        explicit DateTime(NumericRange<std::uint16_t, 0, 2105, 0> uiYear, NumericRange<std::uint8_t, 0, 12, 1> usiMonth, NumericRange<std::uint8_t, 0, 31, 1> usiDay, NumericRange<std::uint8_t, 0, 23, 0> usiHour, NumericRange<std::uint8_t, 0, 59, 0> usiMinute, NumericRange<std::uint8_t, 0, 59, 0> usiSec, NumericRange<std::uint32_t, 0, 999999, 0> udiUSec)
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

      Request() = default;

      explicit Request(DateTime DateTime)
        : _DateTime(DateTime)
      {}

      DateTime _DateTime;
    };

    struct Response
    {
      enum class ErrorCode
      {
        SopasErrNoErr = 0,
        SopasErrStateChangeNotPermitted = 1,
      };

      Response() = default;

      explicit Response(ErrorCode ErrorCode)
        : _ErrorCode(ErrorCode)
      {}

      ErrorCode _ErrorCode;
    };

  }; // struct Post

}; // struct LSPsetdatetime

} // namespace sick::picoScan150::v2_2_1::api::rest
