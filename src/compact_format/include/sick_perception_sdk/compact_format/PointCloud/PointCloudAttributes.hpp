/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>

#include <cstdint>
#include <cstring>
#include <string>

namespace sick::point_cloud {

/**
 * @brief Properties of a point in the point cloud. 
 * 
 * These are stored as a BitField in the properties field of the point cloud.
 * 
 * @note The values of the enum entries are not the same as in any of the Compact format telegrams. 
 *       Don't use reserved bits here, just add new values to the end as necessary.
 * 
 * @note Not all sensors support all properties.
 */
enum class Properties : std::uint16_t
{
  Reflector                    = 0x0001, ///< The value was reflected by a reflector. This is only set if the sensor supports reflector detection.
  Blooming                     = 0x0002, ///< The value has been over-saturated by reflections from neighboring beams.
  EnvironmentConditionFiltered = 0x0004, ///< The value has been filtered due to environmental conditions.
  Inaccurate                   = 0x0008, ///< Multiple beams have coalesced and the value has a low accuracy.
};

struct SDK_EXPORT PointField
{
  /**
   * @brief Data types that can be used for point cloud fields.
   * 
   * @attention Remember to update the string conversion functions in PointCloudAttributes.cpp if you change or add new data types.
   */
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

  /**
   * @brief Types of fields that can be present in a point cloud.
   * 
   * @attention Remember to update the string conversion functions in PointCloudAttributes.cpp if you change or add new field types.
   */
  enum class FieldType
  {
    X                     = 0,  // Distance in x-direction, meters, float32.
    Y                     = 1,  // Distance in y-direction, meters, float32.
    Z                     = 2,  // Distance in z-direction, meters, float32.
    Range                 = 3,  // Radial distance from the sensor to the point, meters, float32.
    Azimuth               = 4,  // Horizontal angle of the beam, radians, float32.
    Elevation             = 5,  // Vertical angle of the beam, radians, float32.
    Intensity             = 6,  // Intensity of the reflected laser pulse, normalized [0..1], float32.
    TimeOffsetNanoseconds = 7,  // Nanoseconds part of the time offset of the beam relative to the point cloud timestamp, nanoseconds, uint32.
    TimeOffsetSeconds     = 8,  // Seconds part of the time offset of the beam relative to the point cloud timestamp, seconds, uint32.
    Ring                  = 9,  // Ring/row index of the beam, uint8.
    LayerIndex            = 10, // Layer index of the beam in the sensor's internal point cloud representation, uint8.
    ColumnIndex           = 11, // Column index of the beam in the sensor's internal point cloud representation, uint16.
    EchoIndex             = 12, // Echo index of the laser beam, uint8.
    Properties            = 13, // Properties of the point, uint16.
    PulseWidth            = 14, // Pulse width of the reflected laser pulse, nanoseconds, float32.
    Last                  = 15, // Marker after the last valid field type. Must always be last enum value!
  };

  static auto fieldTypeToString(FieldType fieldType) -> std::string;
  static auto dataTypeToString(DataType dataType) -> std::string;

  FieldType fieldType  = FieldType::X;
  std::uint32_t offset = 0;
  DataType dataType    = DataType::Float32;
};

} // namespace sick::point_cloud
