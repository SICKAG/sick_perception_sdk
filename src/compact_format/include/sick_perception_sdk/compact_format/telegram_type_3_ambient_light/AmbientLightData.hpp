/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/quantities/Angle.hpp>
#include <sick_perception_sdk/common/quantities/Timestamp.hpp>
#include <sick_perception_sdk/compact_format/CompactData.hpp>

#include <cstdint>
#include <vector>

/**
 * @brief This namespace contains data structures and converters for the Ambient Light Compact telegram (telegram type 3).
 */
namespace sick::compact::ambient_light {

enum class PixelEncoding
{
  Raw = 0
};

struct SDK_EXPORT MetaData
{
  std::uint64_t frameSequenceNumber {0};
  Timestamp startTimestamp;
  Timestamp stopTimestamp;
  std::size_t numberOfLayers {0};
  std::size_t numberOfColumns {0};
  Angle startAzimuth;
  Angle stopAzimuth;
  Angle startElevation;
  Angle stopElevation;
  PixelEncoding encoding {PixelEncoding::Raw};
};

using Column = std::vector<std::uint16_t>;

struct SDK_EXPORT Payload
{
  MetaData metaData;
  std::vector<Column> pixels;
};

struct SDK_EXPORT AmbientLightData
{
  TelegramHeader telegramHeader;
  Payload payload;
};

} // namespace sick::compact::ambient_light
