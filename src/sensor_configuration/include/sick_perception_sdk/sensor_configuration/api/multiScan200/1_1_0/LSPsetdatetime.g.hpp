/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LSPsetdatetime.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::multiScan200::v1_1_0::api::rest {

/**
 * @brief Payloads for endpoint /LSPsetdatetime.
*/
struct LSPsetdatetime
{

  constexpr static const char* methodName = "LSPsetdatetime";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Sets the current time of the device in local time by using the time zone as defined in TSCTCtimezone (years, months, days, hours, minutes, seconds, microseconds). Does only work if NTP-Client and PTP is not active.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      struct DateTime
      {
        DateTime() = default;

        explicit DateTime(NumericRange<int, 0, 2105, 0> uiYear, NumericRange<int, 0, 12, 1> usiMonth, NumericRange<int, 0, 31, 1> usiDay, NumericRange<int, 0, 23, 0> usiHour, NumericRange<int, 0, 59, 0> usiMinute, NumericRange<int, 0, 59, 0> usiSec, NumericRange<int, 0, 999999, 0> udiUSec)
          : _uiYear(uiYear), _usiMonth(usiMonth), _usiDay(usiDay), _usiHour(usiHour), _usiMinute(usiMinute), _usiSec(usiSec), _udiUSec(udiUSec)
        {}

        NumericRange<int, 0, 2105, 0> _uiYear;
        NumericRange<int, 0, 12, 1> _usiMonth;
        NumericRange<int, 0, 31, 1> _usiDay;
        NumericRange<int, 0, 23, 0> _usiHour;
        NumericRange<int, 0, 59, 0> _usiMinute;
        NumericRange<int, 0, 59, 0> _usiSec;
        NumericRange<int, 0, 999999, 0> _udiUSec;
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

} // namespace sick::multiScan200::v1_1_0::api::rest
