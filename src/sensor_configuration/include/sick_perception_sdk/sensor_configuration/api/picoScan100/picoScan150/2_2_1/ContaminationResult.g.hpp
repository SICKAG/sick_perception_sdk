/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ContaminationResult.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan150::v2_2_1::api::rest {

/**
 * @brief Payloads for endpoint /ContaminationResult.
*/
struct ContaminationResult
{

  constexpr static const char* variableName = "ContaminationResult";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the contamination indication state of the device.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool bWarningActive, bool bErrorActive)
        : _bWarningActive(bWarningActive), _bErrorActive(bErrorActive)
      {}

      bool _bWarningActive;
      bool _bErrorActive;
    };

  }; // struct Get

}; // struct ContaminationResult

} // namespace sick::picoScan150::v2_2_1::api::rest
