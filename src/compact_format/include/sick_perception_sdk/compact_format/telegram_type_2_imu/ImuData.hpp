/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/quantities/Acceleration.hpp>
#include <sick_perception_sdk/common/quantities/AngularVelocity.hpp>
#include <sick_perception_sdk/common/quantities/Timestamp.hpp>
#include <sick_perception_sdk/compact_format/CompactData.hpp>

#include <cstdint>
#include <limits>

/**
 * @brief This namespace contains data structures and converters for the Imu Compact telegram (telegram type 2).
 */
namespace sick::compact::imu {

#pragma pack(push, 1) // add pragma to prevent the compiler from adding padding bytes for alignment

struct SDK_EXPORT Header
{
  std::uint32_t startOfFrame {0};
  TelegramType telegramType {TelegramType::Invalid};
  std::uint32_t telegramVersion {0};
};

struct SDK_EXPORT AccelerationData
{
  Acceleration x;
  Acceleration y;
  Acceleration z;
};

struct SDK_EXPORT AngularVelocityData
{
  AngularVelocity x;
  AngularVelocity y;
  AngularVelocity z;
};

struct SDK_EXPORT Quaternion
{
  float w {std::numeric_limits<float>::quiet_NaN()};
  float x {std::numeric_limits<float>::quiet_NaN()};
  float y {std::numeric_limits<float>::quiet_NaN()};
  float z {std::numeric_limits<float>::quiet_NaN()};
};

struct SDK_EXPORT ImuData
{
  Header header;
  AccelerationData acceleration;
  AngularVelocityData angularVelocity;
  Quaternion orientation;
  Timestamp sensorTimestamp;
  std::uint32_t checksum {0};
};

#pragma pack(pop)

} // namespace sick::compact::imu
