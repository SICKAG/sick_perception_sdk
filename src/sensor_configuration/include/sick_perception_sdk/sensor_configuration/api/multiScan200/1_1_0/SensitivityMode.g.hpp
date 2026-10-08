/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file SensitivityMode.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once


namespace sick::multiScan200::v1_1_0::api::rest {

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

} // namespace sick::multiScan200::v1_1_0::api::rest
