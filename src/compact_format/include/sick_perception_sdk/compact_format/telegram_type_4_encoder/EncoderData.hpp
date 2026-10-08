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

struct SDK_EXPORT EncoderData
{
  TelegramHeader telegramHeader;
  std::uint64_t frameSequenceNumber {0};
  std::uint32_t tickCount {0};
  std::uint32_t tickCountAtReferenceSignal1 {0};
  std::uint32_t tickCountAtReferenceSignal2 {0};
  Speed speed;
  Timestamp timestampOfTickCount;
  Timestamp timestampOfReferenceSignal1;
  Timestamp timestampOfReferenceSignal2;
};

} // namespace sick::compact::encoder
