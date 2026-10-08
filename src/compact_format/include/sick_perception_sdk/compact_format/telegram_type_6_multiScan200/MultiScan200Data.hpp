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
 * @brief This namespace contains data structures and converters for the MultiScan200 Compact telegram (telegram type 6).
 */
namespace sick::compact::multiscan200 {

// NOLINTBEGIN(misc-non-private-member-variables-in-classes)

enum class EchoProperties
{
  Reserved   = 0x00,
  Reflector  = 0x01,
  Blooming   = 0x02,
  Particle   = 0x04,
  Inaccurate = 0x10,
};

struct SDK_EXPORT SegmentMetaData
{
  std::size_t frameSequenceNumber = 0;
  Timestamp frameTimestamp;
  std::size_t segmentIndex                 = 0;
  std::size_t numberOfSegmentsPerFrame     = 0;
  std::size_t numberOfColumnsInSegment     = 0;
  std::size_t numberOfColumnsInFrame       = 0;
  std::size_t numberOfRows                 = 0;
  std::size_t numberOfEchoes               = 0;
  std::size_t numberOfAmbientLightRows     = 0;
  std::size_t numberOfInterlaceSteps       = 0;
  std::size_t interlaceIndex               = 0;
  std::uint8_t scanConfigurationIdentifier = 0;
};

using AmbientLightColumn = std::vector<std::uint16_t>;

struct Geometry
{
  std::vector<Angle> elevations;
  std::vector<Angle> azimuths;
  std::vector<Duration> relativeTimeStamps;
  // There's a block of reserved geometry data in the telegram, but we don't need to store it in the data structure.
};

/**
 * @brief Flat data structure for MultiScan200 scan data (Structure-of-Arrays layout).
 *
 * All echo data is stored in contiguous flat vectors for good cache locality while writing and reading.
 * Index into arrays with: echoIndex * (numberOfRows * numberOfColumns) + columnIndex * numberOfRows + rowIndex
 */
struct SDK_EXPORT MultiScan200Data
{
  TelegramHeader telegramHeader;
  SegmentMetaData segmentMetaData;
  Geometry geometry;

  std::vector<std::uint16_t> ambientLightData;          ///< Flat array of all ambient light data (empty if not present)
  std::vector<Distance> distances;                      ///< Flat array of all distances
  std::vector<float> intensities;                       ///< Flat array of all intensities (empty if not present)
  std::vector<BitField<EchoProperties>> echoProperties; ///< Flat array of all echo properties (empty if not present)

  /**
   * @brief Compute the flat index for a given echo, column, and row.
   * @param echoIndex The echo index (0 to numberOfEchoes-1).
   * @param columnIndex The column index (0 to numberOfColumnsInSegment-1).
   * @param rowIndex The row index (0 to numberOfRows-1).
   * @return The flat index into the data arrays.
   */
  auto computeIndex(std::size_t echoIndex, std::size_t columnIndex, std::size_t rowIndex) const -> std::size_t
  {
    auto const numberOfRows    = static_cast<std::size_t>(segmentMetaData.numberOfRows);
    auto const numberOfColumns = static_cast<std::size_t>(segmentMetaData.numberOfColumnsInSegment);
    return echoIndex * (numberOfRows * numberOfColumns) + columnIndex * numberOfRows + rowIndex;
  }

  /**
   * @brief Compute the flat ambient light data index for a given column and row.
   * @param columnIndex The column index (0 to numberOfColumnsInSegment-1).
   * @param rowIndex The row index (0 to numberOfAmbientLightRows-1).
   * @return The flat index into the ambient light data array.
   */
  auto computeAmbientLightIndex(std::size_t columnIndex, std::size_t rowIndex) const -> std::size_t
  {
    auto const numberOfRows = static_cast<std::size_t>(segmentMetaData.numberOfAmbientLightRows);
    return columnIndex * numberOfRows + rowIndex;
  }
};

// NOLINTEND(misc-non-private-member-variables-in-classes)

} // namespace sick::compact::multiscan200
