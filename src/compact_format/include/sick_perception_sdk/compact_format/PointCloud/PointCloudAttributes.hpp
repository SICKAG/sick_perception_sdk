/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>

#include <cstdint>
#include <cstring>

namespace sick::point_cloud {

enum class Density
{
  AllPointsValid,        ///< Point cloud is dense, i.e. all points are valid (no NaN coordinates).
  InvalidPointsContained ///< Point cloud is sparse, i.e. may contain invalid points (NaN coordinates, 0 for integers).
};

struct SDK_EXPORT PointField
{
  enum class DataType
  {
    Bool    = 0,
    Int8    = 1,
    Uint8   = 2,
    Int16   = 3,
    Uint16  = 4,
    Int32   = 5,
    Uint32  = 6,
    Int64   = 7,
    Uint64  = 8,
    Float32 = 9,
    Float64 = 10,
  };

  enum class FieldType
  {
    X,                     // Distance in x-direction, meters, float32.
    Y,                     // Distance in y-direction, meters, float32.
    Z,                     // Distance in z-direction, meters, float32.
    Range,                 // Radial distance from the sensor to the point, meters, float32.
    Azimuth,               // Horizontal angle of the beam, radians, float32.
    Elevation,             // Vertical angle of the beam, radians, float32.
    Intensity,             // Intensity of the reflected laser pulse, normalized [0..1], float32.
    TimeOffsetNanoseconds, // Nanoseconds part of the time offset of the beam relative to the point cloud timestamp, nanoseconds, uint32.
    TimeOffsetSeconds,     // Seconds part of the time offset of the beam relative to the point cloud timestamp, seconds, uint32.
    Ring,                  // Ring/row index of the beam, uint8.
    LayerId,               // Layer id of the beam, uint8.
    EchoIndex,             // Echo index of the laser beam, uint8.
    IsReflector,           // bool
    HasBlooming,           // bool
    PulseWidth,            // Pulse width of the reflected laser pulse, nanoseconds, float32.
    Last,                  // Marker after the last valid field type. Must always be last enum value!
  };

  FieldType fieldType  = FieldType::X;
  std::uint32_t offset = 0;
  DataType dataType    = DataType::Float32;
};

} // namespace sick::point_cloud
