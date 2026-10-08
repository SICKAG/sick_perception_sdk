/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanData.hpp>

#include <sick_perception_sdk/common/BitField.hpp>
#include <sick_perception_sdk/common/quantities/Angle.hpp>
#include <sick_perception_sdk/common/quantities/Distance.hpp>

#include <cstddef>

namespace sick::compact::scan_data {

auto computeSampleIndex(Module const& module, std::size_t columnIndex, std::size_t rowIndex, std::size_t echoIndex) -> std::size_t
{
  auto const numberOfRows   = module.rowMetaData.size();
  auto const numberOfEchoes = module.numberOfEchoesPerBeam;
  return columnIndex * (numberOfRows * numberOfEchoes) + rowIndex * numberOfEchoes + echoIndex;
}

auto computeBeamIndex(Module const& module, std::size_t columnIndex, std::size_t rowIndex) -> std::size_t
{
  auto const numberOfRows = module.rowMetaData.size();
  return columnIndex * numberOfRows + rowIndex;
}

auto getDistance(Module const& module, std::size_t columnIndex, std::size_t rowIndex, std::size_t echoIndex) -> Distance
{
  auto const index = computeSampleIndex(module, columnIndex, rowIndex, echoIndex);
  return module.distances[index];
}

auto getIntensity(Module const& module, std::size_t columnIndex, std::size_t rowIndex, std::size_t echoIndex) -> float
{
  auto const index = computeSampleIndex(module, columnIndex, rowIndex, echoIndex);
  return module.intensities[index];
}

auto getBeamProperties(Module const& module, std::size_t columnIndex, std::size_t rowIndex) -> BitField<BeamProperties>
{
  auto const index = computeBeamIndex(module, columnIndex, rowIndex);
  return module.beamProperties[index];
}

auto getBeamAzimuth(Module const& module, std::size_t columnIndex, std::size_t rowIndex) -> Angle
{
  auto const index = computeBeamIndex(module, columnIndex, rowIndex);
  return module.beamAzimuths[index];
}

} // namespace sick::compact::scan_data
