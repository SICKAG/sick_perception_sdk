/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file This header defines the byte layout of the telegram type 3 (Ambient Light) in the compact format.
 * 
 * It is private within the context of its corresponding parser implementation and should not be used in other contexts.
 */

#pragma once

#include "../CompactTelegram.hpp"
#include <sick_perception_sdk/compact_format/CompactData.hpp>

#include <cstdint>

namespace sick::compact::ambient_light::telegram {

using compact::telegram::CompactArray;
using compact::telegram::CompactField;

constexpr CompactField<std::uint64_t> kFrameSequenceNumber;
constexpr CompactField<std::uint64_t> kStartTimestamp;
constexpr CompactField<std::uint64_t> kStopTimestamp;
constexpr CompactField<std::uint16_t> kNumberOfLayers;
constexpr CompactField<std::uint16_t> kNumberOfColumns;
constexpr CompactField<float32> kStartAzimuth;
constexpr CompactField<float32> kStopAzimuth;
constexpr CompactField<float32> kStartElevation;
constexpr CompactField<float32> kStopElevation;
constexpr CompactField<std::uint16_t> kEncoding;
constexpr CompactArray<std::uint16_t> kPixels;

} // namespace sick::compact::ambient_light::telegram
