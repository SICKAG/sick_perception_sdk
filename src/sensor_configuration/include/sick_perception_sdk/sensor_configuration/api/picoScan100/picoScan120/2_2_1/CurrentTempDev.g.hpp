/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file CurrentTempDev.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan120::v2_2_1::api::rest {

/**
 * @brief Payloads for endpoint /CurrentTempDev.
*/
struct CurrentTempDev
{

  constexpr static const char* variableName = "CurrentTempDev";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the current device temperature.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(float CurrentTempDev)
        : _CurrentTempDev(CurrentTempDev)
      {}

      float _CurrentTempDev;
    };

  }; // struct Get

}; // struct CurrentTempDev

} // namespace sick::picoScan120::v2_2_1::api::rest
