/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file groundFilterType.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.4'.
 * Do not edit manually!
 */
#pragma once


namespace sick::multiScan100::v2_4_4::api::rest {

/**
 * @brief Payloads for endpoint /groundFilterType.
*/
struct groundFilterType
{

  constexpr static const char* variableName = "groundFilterType";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the ground filter type. Currently, the ground filter only works on plain measurement data (P3D-algorythm). The option IMU is currently not available.
   */
  struct Get
  {
    struct Response
    {
      enum class groundFilterType
      {
        P3d = 0,
        Imu = 1,
      };

      Response() = default;

      explicit Response(groundFilterType groundFilterType)
        : _groundFilterType(groundFilterType)
      {}

      groundFilterType _groundFilterType;
    };

  }; // struct Get

}; // struct groundFilterType

} // namespace sick::multiScan100::v2_4_4::api::rest
