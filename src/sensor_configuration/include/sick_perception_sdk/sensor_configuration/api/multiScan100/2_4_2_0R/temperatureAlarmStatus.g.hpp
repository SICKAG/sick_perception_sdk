/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file temperatureAlarmStatus.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /temperatureAlarmStatus.
*/
struct temperatureAlarmStatus
{

  constexpr static const char* variableName = "temperatureAlarmStatus";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the current device temperature alarm status. If true, the configured temperature alarm is active.
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

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
