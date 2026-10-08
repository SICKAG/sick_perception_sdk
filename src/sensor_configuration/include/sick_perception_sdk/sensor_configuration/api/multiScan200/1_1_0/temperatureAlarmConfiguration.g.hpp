/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file temperatureAlarmConfiguration.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once


namespace sick::multiScan200::v1_1_0::api::rest {

/**
 * @brief Payloads for endpoint /temperatureAlarmConfiguration.
*/
struct temperatureAlarmConfiguration
{

  constexpr static const char* variableName = "temperatureAlarmConfiguration";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets temperature alarm thresholds.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(int upperThreshold, int lowerThreshold)
        : _upperThreshold(upperThreshold), _lowerThreshold(lowerThreshold)
      {}

      int _upperThreshold;
      int _lowerThreshold;
    };

  }; // struct Get

}; // struct temperatureAlarmConfiguration

} // namespace sick::multiScan200::v1_1_0::api::rest
