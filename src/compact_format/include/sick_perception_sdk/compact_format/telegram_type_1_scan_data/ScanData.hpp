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
#include <vector>

/**
 * @brief This namespace contains data structures and converters for the Scan Data Compact telegram (telegram type 1).
 */
namespace sick::compact::scan_data {

enum class EchoContent
{
  None      = 0x00,
  Distance  = 0x01,
  Intensity = 0x02,
  All       = Distance | Intensity,
};

enum class BeamContent
{
  None       = 0x00,
  Properties = 0x01,
  Azimuth    = 0x02,
  All        = Properties | Azimuth,
};

enum class BeamProperties
{
  Reserved      = 0x00,
  Reflector     = 0x01,
  BloomingEcho0 = 0x20,
  BloomingEcho1 = 0x40,
  BloomingEcho2 = 0x80
};

// NOLINTBEGIN(misc-non-private-member-variables-in-classes)

/**
 * @brief Flat data structure for a single scan data module (Structure-of-Arrays layout).
 *
 * All echo data is stored in contiguous flat vectors for good cache locality.
 * Index into arrays with: columnIndex * (numberOfRows * numberOfEchoesPerBeam) + rowIndex * numberOfEchoesPerBeam + echoIndex
 */
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

  std::size_t numberOfColumns {0};
  std::size_t numberOfEchoesPerBeam {0};
  std::vector<RowMetaData> rowMetaData;

  std::vector<Distance> distances;                      ///< Flat array of all distance samples (empty if not present)
  std::vector<float> intensities;                       ///< Flat array of all intensity samples (empty if not present)
  std::vector<BitField<BeamProperties>> beamProperties; ///< Flat array of all beam properties (empty if not present)
  std::vector<Angle> beamAzimuths;                      ///< Flat array of all beam azimuths (empty if not present)
};

struct SDK_EXPORT ScanData
{
  TelegramHeader telegramHeader;
  std::size_t frameSequenceNumber {0};
  std::size_t segmentIndex {0};
  std::vector<Module> modules;
};

// NOLINTEND(misc-non-private-member-variables-in-classes)

/**
 * @brief Compute the flat index for a data sample given echo, column, and row inside a module.
 *
 * @param columnIndex The column index (0 to numberOfColumns-1).
 * @param rowIndex The row index (0 to numberOfRows-1).
 * @param echoIndex The echo index (  0 to numberOfEchoesPerBeam-1).
 * @return The flat index into the echo data arrays (distances, intensities).
 */
auto SDK_EXPORT computeSampleIndex(Module const& module, std::size_t columnIndex, std::size_t rowIndex, std::size_t echoIndex) -> std::size_t;

/**
 * @brief Compute the flat index for beam data given column and row.
 *
 * @param columnIndex The column index (0 to numberOfColumns-1).
 * @param rowIndex The row index (0 to numberOfRows-1).
 * @return The flat index into the beam data arrays (beamProperties, beamAzimuths).
 */
auto SDK_EXPORT computeBeamIndex(Module const& module, std::size_t columnIndex, std::size_t rowIndex) -> std::size_t;

// Convenience accessors for the flat-array data in Module.
auto SDK_EXPORT getDistance(Module const& module, std::size_t columnIndex, std::size_t rowIndex, std::size_t echoIndex) -> Distance;
auto SDK_EXPORT getIntensity(Module const& module, std::size_t columnIndex, std::size_t rowIndex, std::size_t echoIndex) -> float;
auto SDK_EXPORT getBeamProperties(Module const& module, std::size_t columnIndex, std::size_t rowIndex) -> BitField<BeamProperties>;
auto SDK_EXPORT getBeamAzimuth(Module const& module, std::size_t columnIndex, std::size_t rowIndex) -> Angle;

} // namespace sick::compact::scan_data
