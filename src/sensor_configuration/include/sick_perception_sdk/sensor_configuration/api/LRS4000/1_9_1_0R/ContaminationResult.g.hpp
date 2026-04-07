/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ContaminationResult.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::LRS4000::v1_9_1_0R::api::rest {

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

      explicit Response(bool warningActive, bool errorActive)
        : _warningActive(warningActive), _errorActive(errorActive)
      {}

      bool _warningActive;
      bool _errorActive;
    };

  }; // struct Get

}; // struct ContaminationResult

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
