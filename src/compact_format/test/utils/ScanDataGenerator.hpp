/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/quantities/Timestamp.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanData.hpp>

#include <algorithm>
#include <cstdint>
#include <numeric>
#include <vector>

namespace sick::test {

/**
 * @brief Test helper to generate ScanData objects.
 * 
 * This generator is a simplified representation of a segmented lidar sensor that streams Compact data.
 * Like in a real sensor, the data it produces is organized in frames with numberOfSegmentsPerFrame segments 
 * in each frame.
 * 
 * The generator is stateful, i.e. calling next() "rotates" the sensor by one segment. If the last segment 
 * of the current frame has been generated after calling next() the generator will start the next frame.
 * 
 * The azimuth angles start at 0 for the first beam of the first segment and are incremented by 1 degree per beam. 
 * The elevation angles start at 0 for the first layer and are incremented by 1 degree per layer.
 * 
 * The distance values are always 1000 mm.
 * 
 */
class ScanDataGenerator
{
public:
  explicit ScanDataGenerator();

  auto withNumberOfColumns(int value) -> ScanDataGenerator&;
  auto withNumberOfEchoesPerBeam(int value) -> ScanDataGenerator&;
  auto withNumberOfRows(int value) -> ScanDataGenerator&;
  auto withNumberOfSegmentsPerFrame(int value) -> ScanDataGenerator&;
  auto withTelegramSequenceNumber(std::uint64_t value) -> ScanDataGenerator&;

  auto next(Timestamp transmitTimestamp = Timestamp::fromMicrosecondsSinceEpoch(0)) -> compact::scan_data::ScanData;
  void reset();

private:
  std::uint64_t m_frameSequenceNumber;
  int m_numberOfModules;
  std::uint32_t m_numberOfColumns;
  std::uint32_t m_numberOfEchoesPerBeam;
  std::uint32_t m_numberOfRows;
  int m_numberOfSegmentsPerFrame;
  std::uint64_t m_telegramSequenceNumber;
  std::uint64_t m_segmentIndex;

  auto createModule() -> compact::scan_data::Module;
};

} // namespace sick::test
