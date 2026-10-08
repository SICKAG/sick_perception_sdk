/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/quantities/Timestamp.hpp>

#include <cstdint>

namespace sick::compact {

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers): numbers are used to define sizes

/**
 * @brief Type of a Compact telegram.
 *
 * @note In the format description this is referred to as command ID.
 */
enum class TelegramType : std::uint32_t
{
  Invalid      = 0,
  ScanData     = 1,
  ImuLegacy    = 2,
  AmbientLight = 3,
  Encoder      = 4,
  MultiScan200 = 6,
  Imu          = 7,
};

using bool8 = bool;
static_assert(sizeof(bool) == 1, "bool must be exactly 1 byte in size to parse the Compact format");

using float32 = float;
static_assert(sizeof(float) == 4, "float must be exactly 4 bytes in size to parse the Compact format");

using float64 = double;
static_assert(sizeof(double) == 8, "double must be exactly 8 bytes in size to parse the Compact format");

struct SDK_EXPORT TelegramHeader
{
  static_assert(sizeof(Timestamp) == sizeof(std::uint64_t), "Timestamp size mismatch in Compact TelegramHeader");

  std::size_t telegramSequenceNumber {0};
  Timestamp transmitTimestamp;
  std::uint32_t senderSerialNumber {0};
};

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

} // namespace sick::compact
