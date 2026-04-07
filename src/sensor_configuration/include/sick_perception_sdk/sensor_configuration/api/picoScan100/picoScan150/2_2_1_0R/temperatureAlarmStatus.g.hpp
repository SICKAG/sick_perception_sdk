/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file temperatureAlarmStatus.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan150::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /temperatureAlarmStatus.
*/
struct temperatureAlarmStatus
{

  constexpr static const char* variableName = "temperatureAlarmStatus";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the current temperature alarm status.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool temperatureAlarmStatus)
        : _temperatureAlarmStatus(temperatureAlarmStatus)
      {}

      bool _temperatureAlarmStatus;
    };

  }; // struct Get

}; // struct temperatureAlarmStatus

} // namespace sick::picoScan150::v2_2_1_0R::api::rest
