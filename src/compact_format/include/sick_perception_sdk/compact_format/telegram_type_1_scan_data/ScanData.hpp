/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/BitField.hpp>
#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/quantities/Angle.hpp>
#include <sick_perception_sdk/common/quantities/Distance.hpp>
#include <sick_perception_sdk/common/quantities/Timestamp.hpp>
#include <sick_perception_sdk/compact_format/CompactData.hpp>

#include <cstdint>
#include <limits>
#include <type_traits>
#include <vector>

/**
 * @brief This namespace contains data structures and converters for the Scan Data Compact telegram (telegram type 1).
 */
namespace sick::compact::scan_data {

enum class EchoContent : std::uint8_t
{
  None      = 0x00,
  Distance  = 0x01,
  Intensity = 0x02,
  All       = Distance | Intensity,
};

enum class BeamContent : std::uint8_t
{
  None       = 0x00,
  Properties = 0x01,
  Azimuth    = 0x02,
  All        = Properties | Azimuth,
};

#pragma pack(push, 1) // add pragma to prevent the compiler from adding padding bytes for alignment

struct SDK_EXPORT Echo
{
  Distance distance;
  float intensity {std::numeric_limits<float>::quiet_NaN()};
};

struct SDK_EXPORT Beam
{
  std::vector<Echo> echoes;
  std::uint8_t properties {0};
  Angle azimuth;
};

using Column = std::vector<Beam>;

struct SDK_EXPORT Module
{
  struct SDK_EXPORT RowMetaData
  {
    Timestamp firstBeamTimestamp;
    Timestamp lastBeamTimestamp;
    Angle elevation;
    Angle firstBeamAzimuth;
    Angle lastBeamAzimuth;
  };

  struct SDK_EXPORT MetaData
  {
    std::uint64_t segmentIndex {0};
    std::uint64_t frameSequenceNumber {0};
    std::uint32_t senderSerialNumber {0};
    std::uint32_t numberOfRows {0};
    std::uint32_t numberOfColumns {0};
    std::uint32_t numberOfEchoesPerBeam {0};
    std::vector<RowMetaData> rowMetaData;
    float distanceScalingFactor {std::numeric_limits<float>::quiet_NaN()};
    std::uint32_t numberOfBytesOfNextModule {0};
    BitField<EchoContent> echoContent {EchoContent::None};
    BitField<BeamContent> beamContent {BeamContent::None};
  };

  MetaData metaData;
  std::vector<Column> columns;
};

struct SDK_EXPORT ScanData
{
  TelegramHeader telegramHeader;
  std::vector<Module> modules;
  std::uint32_t checksum {0};
};

#pragma pack(pop)

} // namespace sick::compact::scan_data
