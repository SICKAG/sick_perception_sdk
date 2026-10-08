/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file OpHours.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once


namespace sick::multiScan200::v1_1_0::api::rest {

/**
 * @brief Payloads for endpoint /OpHours.
*/
struct OpHours
{

  constexpr static const char* variableName = "OpHours";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the total number of operating hours during the lifetime of the device. The resolution is 1/10 hour.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(int OpHours)
        : _OpHours(OpHours)
      {}

      int _OpHours;
    };

  }; // struct Get

}; // struct OpHours

} // namespace sick::multiScan200::v1_1_0::api::rest
