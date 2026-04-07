/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file InertialMeasurementUnit.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /InertialMeasurementUnit.
*/
struct InertialMeasurementUnit
{

  constexpr static const char* variableName = "InertialMeasurementUnit";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the current IMU data (e.g. Acceleration, Orientation, ... ). The data is given in the following coordinate system which is based on the DIN70000 system. The x-axis lies on the 90-degree-beam of the 0-degree-layer. The y-axis is perpendicular to the x-axis and lies in the 0-degree-layer. The y-values are rising in the counterclockwise rotation direction (right-handed system). The z-axis is perpendicular to the x-y-plane and the scanner top points to rising z-values.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::vector<float> Acceleration, std::vector<float> AngularVelocity, std::vector<float> Orientation, std::uint64_t TimeStamp)
        : _Acceleration(Acceleration), _AngularVelocity(AngularVelocity), _Orientation(Orientation), _TimeStamp(TimeStamp)
      {}

      std::vector<float> _Acceleration;
      std::vector<float> _AngularVelocity;
      std::vector<float> _Orientation;
      std::uint64_t _TimeStamp;
    };

  }; // struct Get

}; // struct InertialMeasurementUnit

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
