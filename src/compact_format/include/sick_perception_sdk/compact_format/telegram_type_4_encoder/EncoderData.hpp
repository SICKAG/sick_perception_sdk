/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/quantities/Speed.hpp>
#include <sick_perception_sdk/common/quantities/Timestamp.hpp>
#include <sick_perception_sdk/compact_format/CompactData.hpp>

#include <cstdint>

/**
 * @brief This namespace contains data structures and converters for the Encoder Compact telegram (telegram type 4).
 */
namespace sick::compact::encoder {

#pragma pack(push, 1) // add pragma to prevent the compiler from adding padding bytes for alignment

struct SDK_EXPORT Payload
{
  std::uint32_t senderId {0};
  std::uint64_t frameSequenceNumber {0};
  std::uint32_t tickCounter {0};
  std::uint32_t tickCounterReference1 {0};
  std::uint32_t tickCounterReference2 {0};
  Speed speed;
  Timestamp tickCounterTimestamp;
  Timestamp timestampReference1;
  Timestamp timestampReference2;
};

struct SDK_EXPORT EncoderData
{
  TelegramHeader telegramHeader;
  Payload payload;
  std::uint32_t checksum {0};
};

#pragma pack(pop)

} // namespace sick::compact::encoder
