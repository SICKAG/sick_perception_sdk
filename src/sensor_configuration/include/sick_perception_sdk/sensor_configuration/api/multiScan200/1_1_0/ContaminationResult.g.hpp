/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ContaminationResult.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once


namespace sick::multiScan200::v1_1_0::api::rest {

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

} // namespace sick::multiScan200::v1_1_0::api::rest
