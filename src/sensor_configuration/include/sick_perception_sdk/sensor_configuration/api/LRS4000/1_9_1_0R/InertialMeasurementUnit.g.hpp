/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file InertialMeasurementUnit.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /InertialMeasurementUnit.
*/
struct InertialMeasurementUnit
{

  constexpr static const char* variableName = "InertialMeasurementUnit";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the current IMU data (e.g. Acceleration, Orientation, ... ). The data is given in the following coordinate system which is based on the DIN70000 system: The x-axis lies on the 90 degree beam of the 0 degree layer. The y-axis is perpendicular to the x-axis and lies in the 0 degree layer. The y-values are rising in the counterclockwise rotation direction (right-handed system). The z-axis is perpendicular to the x-y-plane and the scanner top points to rising z-values.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::array<float, 3> Acceleration, std::array<float, 3> AngularVelocity, std::array<float, 3> MagneticField, std::array<float, 4> Orientation, std::uint32_t TimeStamp)
        : _Acceleration(Acceleration), _AngularVelocity(AngularVelocity), _MagneticField(MagneticField), _Orientation(Orientation), _TimeStamp(TimeStamp)
      {}

      std::array<float, 3> _Acceleration;
      std::array<float, 3> _AngularVelocity;
      std::array<float, 3> _MagneticField;
      std::array<float, 4> _Orientation;
      std::uint32_t _TimeStamp;
    };

  }; // struct Get

}; // struct InertialMeasurementUnit

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
