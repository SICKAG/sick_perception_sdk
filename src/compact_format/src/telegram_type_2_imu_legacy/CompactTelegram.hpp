/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file This header defines the byte layout of the telegram type 2 (IMU) in the compact format.
 * 
 * It is private within the context of its corresponding parser implementation and should not be used in other contexts.
 */

#pragma once

#include "../CompactTelegram.hpp"
#include <sick_perception_sdk/compact_format/CompactData.hpp>

#include <cstdint>

namespace sick::compact::imu_legacy::telegram {

using compact::telegram::CompactField;

constexpr CompactField<float32> kAccelerationX;
constexpr CompactField<float32> kAccelerationY;
constexpr CompactField<float32> kAccelerationZ;

constexpr CompactField<float32> kAngularVelocityX;
constexpr CompactField<float32> kAngularVelocityY;
constexpr CompactField<float32> kAngularVelocityZ;

constexpr CompactField<float32> kOrientationW;
constexpr CompactField<float32> kOrientationX;
constexpr CompactField<float32> kOrientationY;
constexpr CompactField<float32> kOrientationZ;

constexpr CompactField<std::uint64_t> kSensorTimestamp;

constexpr size_t sizeInBytes =
  compact::telegram::header::kStartOfFrame.sizeInBytes +    //
  compact::telegram::header::kTelegramType.sizeInBytes +    //
  compact::telegram::header::kTelegramVersion.sizeInBytes + //
  telegram::kAccelerationX.sizeInBytes +                    //
  telegram::kAccelerationY.sizeInBytes +                    //
  telegram::kAccelerationZ.sizeInBytes +                    //
  telegram::kAngularVelocityX.sizeInBytes +                 //
  telegram::kAngularVelocityY.sizeInBytes +                 //
  telegram::kAngularVelocityZ.sizeInBytes +                 //
  telegram::kOrientationW.sizeInBytes +                     //
  telegram::kOrientationX.sizeInBytes +                     //
  telegram::kOrientationY.sizeInBytes +                     //
  telegram::kOrientationZ.sizeInBytes +                     //
  telegram::kSensorTimestamp.sizeInBytes +                  //
  compact::telegram::kChecksum.sizeInBytes;

} // namespace sick::compact::imu_legacy::telegram
