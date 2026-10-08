/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file This header defines the byte layout of the telegram type 1 (ScanData) in the compact format.
 * 
 * It is private within the context of its corresponding parser implementation and should not be used in other contexts.
 */

#pragma once

#include "../CompactTelegram.hpp"

#include <cstdint>

namespace sick::compact::scan_data::telegram {

using compact::telegram::CompactArray;
using compact::telegram::CompactField;

namespace module_meta_data {

constexpr CompactField<std::uint64_t> kSegmentIndex;
constexpr CompactField<std::uint64_t> kFrameSequenceNumber;
constexpr CompactField<std::uint32_t> kSenderSerialNumber;
constexpr CompactField<std::uint32_t> kNumberOfRows;
constexpr CompactField<std::uint32_t> kNumberOfColumns;
constexpr CompactField<std::uint32_t> kNumberOfEchoesPerBeam;
constexpr CompactArray<std::uint64_t> kStartTimestamp;
constexpr CompactArray<std::uint64_t> kEndTimestamp;
constexpr CompactArray<float32> kElevations;
constexpr CompactArray<float32> kFirstBeamAzimuths;
constexpr CompactArray<float32> kLastBeamAzimuths;
constexpr CompactField<float32> kDistanceScalingFactor;
constexpr CompactField<std::uint32_t> kNextModulePayloadSize;
constexpr CompactField<bool8> kAvailability;
constexpr CompactField<std::uint8_t> kEchoContent;
constexpr CompactField<std::uint8_t> kBeamContent;
constexpr CompactField<std::uint8_t> kReserved;

} // namespace module_meta_data

namespace beam_data {

constexpr CompactField<std::uint16_t> kAngle;
constexpr CompactField<std::uint16_t> kDistance;
constexpr CompactField<std::uint16_t> kIntensity;
constexpr CompactField<std::uint8_t> kProperties;

} // namespace beam_data

} // namespace sick::compact::scan_data::telegram
