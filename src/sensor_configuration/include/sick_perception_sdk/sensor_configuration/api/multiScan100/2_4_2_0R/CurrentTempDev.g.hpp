/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file CurrentTempDev.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /CurrentTempDev.
*/
struct CurrentTempDev
{

  constexpr static const char* variableName = "CurrentTempDev";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the current device temperature in °C.
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

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
