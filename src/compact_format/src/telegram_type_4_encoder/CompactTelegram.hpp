/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file This header defines the byte layout of the telegram type 4 (Encoder) in the compact format.
 * 
 * It is private within the context of its corresponding parser implementation and should not be used in other contexts.
 */

#pragma once

#include "../CompactTelegram.hpp"
#include <sick_perception_sdk/compact_format/CompactData.hpp>

#include <cstdint>

namespace sick::compact::encoder::telegram {

using compact::telegram::CompactField;

constexpr CompactField<std::uint32_t> kSenderSerialNumber;
constexpr CompactField<std::uint64_t> kFrameSequenceNumber;
constexpr CompactField<std::uint32_t> kTickCount;
constexpr CompactField<std::uint32_t> kTickCountAtReferenceSignal1;
constexpr CompactField<std::uint32_t> kTickCountAtReferenceSignal2;
constexpr CompactField<float32> kSpeed;
constexpr CompactField<std::uint64_t> kTimestampOfTickCount;
constexpr CompactField<std::uint64_t> kTimestampOfReferenceSignal1;
constexpr CompactField<std::uint64_t> kTimestampOfReferenceSignal2;

constexpr size_t sizeInBytes =
  compact::telegram::header::kStartOfFrame.sizeInBytes +           //
  compact::telegram::header::kTelegramType.sizeInBytes +           //
  compact::telegram::header::kTelegramSequenceNumber.sizeInBytes + //
  compact::telegram::header::kTransmitTimestamp.sizeInBytes +      //
  compact::telegram::header::kTelegramVersion.sizeInBytes +        //
  compact::telegram::header::kPayloadLength.sizeInBytes +          //
  kSenderSerialNumber.sizeInBytes +                                //
  kFrameSequenceNumber.sizeInBytes +                               //
  kTickCount.sizeInBytes +                                         //
  kTickCountAtReferenceSignal1.sizeInBytes +                       //
  kTickCountAtReferenceSignal2.sizeInBytes +                       //
  kSpeed.sizeInBytes +                                             //
  kTimestampOfTickCount.sizeInBytes +                              //
  kTimestampOfReferenceSignal1.sizeInBytes +                       //
  kTimestampOfReferenceSignal2.sizeInBytes +                       //
  compact::telegram::kChecksum.sizeInBytes;

} // namespace sick::compact::encoder::telegram
