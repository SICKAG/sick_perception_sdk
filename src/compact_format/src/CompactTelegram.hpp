/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/compact_format/CompactData.hpp>

#include <cstdint>

namespace sick::compact::telegram {

template <typename ValueT>
struct SDK_EXPORT CompactField
{
  using value_type                         = ValueT;
  static constexpr std::size_t sizeInBytes = sizeof(ValueT);
};

template <typename ValueT>
struct SDK_EXPORT CompactArray : public CompactField<ValueT>
{ };

namespace header {

constexpr CompactField<std::uint32_t> kStartOfFrame;
constexpr CompactField<std::uint32_t> kTelegramType;
constexpr CompactField<std::uint64_t> kTelegramSequenceNumber;
constexpr CompactField<std::uint64_t> kTransmitTimestamp;
constexpr CompactField<std::uint32_t> kTelegramVersion;
constexpr CompactField<std::uint32_t> kPayloadLength;
constexpr CompactField<std::uint32_t> kSenderSerialNumber;

constexpr size_t sizeInBytes =
  kStartOfFrame.sizeInBytes             //
  + kTelegramType.sizeInBytes           //
  + kTelegramSequenceNumber.sizeInBytes //
  + kTransmitTimestamp.sizeInBytes      //
  + kTelegramVersion.sizeInBytes        //
  + kPayloadLength.sizeInBytes          //
  + kSenderSerialNumber.sizeInBytes;

} // namespace header

constexpr CompactField<std::uint32_t> kChecksum;

} // namespace sick::compact::telegram
