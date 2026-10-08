/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file This header defines the byte layout of the telegram type 6 (MultiScan200) in the compact format.
 * 
 * It is private within the context of its corresponding parser implementation and should not be used in other contexts.
 */

#pragma once

#include "../CompactTelegram.hpp"
#include <sick_perception_sdk/compact_format/CompactData.hpp>

#include <cstdint>

namespace sick::compact::multiscan200::telegram {

using compact::telegram::CompactArray;
using compact::telegram::CompactField;

namespace segment_meta_data {

constexpr CompactField<std::uint64_t> kFrameSequenceNumber;
constexpr CompactField<std::uint64_t> kFrameTimestamp;
constexpr CompactField<std::uint16_t> kSegmentIndex;
constexpr CompactField<std::uint16_t> kNumberOfSegmentsPerFrame;
constexpr CompactField<std::uint16_t> kNumberOfColumnsInSegment;
constexpr CompactField<std::uint16_t> kNumberOfColumnsInFrame;
constexpr CompactField<std::uint16_t> kNumberOfRows;
constexpr CompactField<std::uint8_t> kNumberOfEchoes;
constexpr CompactField<std::uint16_t> kNumberOfAmbientLightRows;
constexpr CompactField<std::uint8_t> kNumberOfInterlaceSteps;
constexpr CompactField<std::uint8_t> kInterlaceIndex;
constexpr CompactField<std::uint8_t> kScanConfigurationIdentifier;
constexpr CompactField<float32> kDistanceScalingFactor;
constexpr CompactField<std::uint8_t> kEchoDataContent;
constexpr std::size_t reservedSize = 91;

constexpr std::size_t sizeInBytes =
  kFrameSequenceNumber.sizeInBytes           //
  + kFrameTimestamp.sizeInBytes              //
  + kSegmentIndex.sizeInBytes                //
  + kNumberOfSegmentsPerFrame.sizeInBytes    //
  + kNumberOfColumnsInSegment.sizeInBytes    //
  + kNumberOfColumnsInFrame.sizeInBytes      //
  + kNumberOfRows.sizeInBytes                //
  + kNumberOfEchoes.sizeInBytes              //
  + kNumberOfAmbientLightRows.sizeInBytes    //
  + kNumberOfInterlaceSteps.sizeInBytes      //
  + kInterlaceIndex.sizeInBytes              //
  + kScanConfigurationIdentifier.sizeInBytes //
  + kDistanceScalingFactor.sizeInBytes       //
  + kEchoDataContent.sizeInBytes             //
  + reservedSize;

} // namespace segment_meta_data

namespace geometry {

constexpr CompactArray<float32> kElevationAngles;
constexpr CompactArray<float32> kAzimuthAngles;
constexpr CompactArray<std::uint32_t> kRelativeTimeStamps;
constexpr CompactArray<std::uint16_t> kReservedGeometry;

} // namespace geometry

constexpr CompactArray<std::uint16_t> kAmbientLightData;
constexpr CompactArray<std::uint16_t> kDistances;
constexpr std::size_t kNumberOfBitsPerIntensityValue = 12;
constexpr CompactArray<std::uint8_t> kEchoProperties;

} // namespace sick::compact::multiscan200::telegram
