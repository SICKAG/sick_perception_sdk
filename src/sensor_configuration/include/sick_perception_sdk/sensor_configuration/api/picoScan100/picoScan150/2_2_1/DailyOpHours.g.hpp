/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file DailyOpHours.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan150::v2_2_1::api::rest {

/**
 * @brief Payloads for endpoint /DailyOpHours.
*/
struct DailyOpHours
{

  constexpr static const char* variableName = "DailyOpHours";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the runtime duration since the last power on (non-persistent).
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(float DailyOpHours)
        : _DailyOpHours(DailyOpHours)
      {}

      float _DailyOpHours;
    };

  }; // struct Get

}; // struct DailyOpHours

} // namespace sick::picoScan150::v2_2_1::api::rest
