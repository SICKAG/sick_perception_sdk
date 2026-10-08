/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file SensitivityMode.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan150::v2_2_1::api::rest {

/**
 * @brief Payloads for endpoint /SensitivityMode.
*/
struct SensitivityMode
{

  constexpr static const char* variableName = "SensitivityMode";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the sensitivity of the receiver unit.
   */
  struct Get
  {
    struct Response
    {
      enum class SensitivityMode
      {
        MaximumRobustness = 0,
        Standard = 1,
        MaximumDetectivity = 2,
      };

      Response() = default;

      explicit Response(SensitivityMode SensitivityMode)
        : _SensitivityMode(SensitivityMode)
      {}

      SensitivityMode _SensitivityMode;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the sensitivity of the receiver unit.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      enum class SensitivityMode
      {
        MaximumRobustness = 0,
        Standard = 1,
        MaximumDetectivity = 2,
      };

      Request() = default;

      explicit Request(SensitivityMode SensitivityMode)
        : _SensitivityMode(SensitivityMode)
      {}

      SensitivityMode _SensitivityMode;
    };

  }; // struct Post

}; // struct SensitivityMode

} // namespace sick::picoScan150::v2_2_1::api::rest
