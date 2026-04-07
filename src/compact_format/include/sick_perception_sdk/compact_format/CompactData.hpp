/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/quantities/Timestamp.hpp>

#include <cstdint>

namespace sick::compact {

/**
 * @brief Type of a Compact telegram.
 * 
 * @note In the format description this is referred to as command ID.
 */
enum class TelegramType : std::uint32_t
{
  Invalid  = 0,
  ScanData = 1,
  Imu      = 2,
  Encoder  = 4,
};

#pragma pack(push, 1) // add pragma to prevent the compiler from adding padding bytes for alignment

struct SDK_EXPORT TelegramHeader
{
  static_assert(sizeof(Timestamp) == sizeof(std::uint64_t), "Timestamp size mismatch in Compact TelegramHeader");

  std::uint32_t startOfFrame {0};
  TelegramType telegramType {TelegramType::Invalid};
  std::uint64_t telegramSequenceNumber {0};
  Timestamp transmitTimestamp;
  std::uint32_t telegramVersion {0};
  std::uint32_t payloadLength {0};
};

struct SDK_EXPORT TelegramHeaderWithSenderSerialNumber : public TelegramHeader
{
  std::uint32_t senderSerialNumber {0};
};

#pragma pack(pop)

} // namespace sick::compact
