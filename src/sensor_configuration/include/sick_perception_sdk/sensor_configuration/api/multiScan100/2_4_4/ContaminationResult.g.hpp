/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ContaminationResult.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.4'.
 * Do not edit manually!
 */
#pragma once


namespace sick::multiScan100::v2_4_4::api::rest {

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

} // namespace sick::multiScan100::v2_4_4::api::rest
