/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file SensitivityMode.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /SensitivityMode.
*/
struct SensitivityMode
{

  constexpr static const char* variableName = "SensitivityMode";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief The sensitivity mode can be used to adjust the detection behavior. A higher sensitivity increases the scanning range.This setting should only be used when there is no direct sunlight and only low ambient light. A higher sensitivity increases the proneness to measurement noise and data loss. Ambient light can negatively affect the signal quality and impair the measurement performance.
   */
  struct Get
  {
    struct Response
    {
      enum class SensitivityMode
      {
        Normal = 0,
        Increased = 1,
        Highest = 2,
      };

      Response() = default;

      explicit Response(SensitivityMode SensitivityMode)
        : _SensitivityMode(SensitivityMode)
      {}

      SensitivityMode _SensitivityMode;
    };

  }; // struct Get

  /**
   * @brief The sensitivity mode can be used to adjust the detection behavior. A higher sensitivity increases the scanning range.This setting should only be used when there is no direct sunlight and only low ambient light. A higher sensitivity increases the proneness to measurement noise and data loss. Ambient light can negatively affect the signal quality and impair the measurement performance.
   */
  struct Post
  {
    struct Request
    {
      enum class SensitivityMode
      {
        Normal = 0,
        Increased = 1,
        Highest = 2,
      };

      Request() = default;

      explicit Request(SensitivityMode SensitivityMode)
        : _SensitivityMode(SensitivityMode)
      {}

      SensitivityMode _SensitivityMode;
    };

  }; // struct Post

}; // struct SensitivityMode

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
