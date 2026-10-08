/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LSPdatetime.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::multiScan200::v1_1_0::api::rest {

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

        explicit LSPdatetime(NumericRange<int, 0, 2105, 0> uiYear, NumericRange<int, 0, 12, 1> usiMonth, NumericRange<int, 0, 31, 1> usiDay, NumericRange<int, 0, 23, 0> usiHour, NumericRange<int, 0, 59, 0> usiMinute, NumericRange<int, 0, 59, 0> usiSec, NumericRange<int, 0, 999999, 0> udiUSec)
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

      Response() = default;

      explicit Response(LSPdatetime LSPdatetime)
        : _LSPdatetime(LSPdatetime)
      {}

      LSPdatetime _LSPdatetime;
    };

  }; // struct Get

}; // struct LSPdatetime

} // namespace sick::multiScan200::v1_1_0::api::rest
