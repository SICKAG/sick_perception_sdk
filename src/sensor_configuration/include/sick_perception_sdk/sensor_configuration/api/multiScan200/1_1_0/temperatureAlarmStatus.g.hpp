/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file temperatureAlarmStatus.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once


namespace sick::multiScan200::v1_1_0::api::rest {

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

} // namespace sick::multiScan200::v1_1_0::api::rest
