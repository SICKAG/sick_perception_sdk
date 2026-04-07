/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/compact_format/DataLoss/SegmentIndexLossMonitor.hpp>
#include <sick_perception_sdk/compact_format/DataLoss/SequenceNumberLossMonitor.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/FrameSequenceNumberLossMonitor.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanData.hpp>

namespace sick::compact::scan_data {

/**
 * @brief Detect data losses in a ScanData stream.
 *
 * The detection is based on the telegram index, segment index, and frame index.
 * A telegram loss happens on ethernet level and indicates an issue with sending or receiving.
 * Segment and frame losses are caused on the sensor, for example due to high system load.
 */
class SDK_EXPORT DataLossMonitor
{
public:
  struct SDK_EXPORT LossCounts
  {
    int numberOfLostTelegrams = 0;
    int numberOfLostFrames    = 0;
    int numberOfLostSegments  = 0;

    auto operator+=(LossCounts const& other) -> LossCounts&
    {
      numberOfLostTelegrams += other.numberOfLostTelegrams;
      numberOfLostFrames += other.numberOfLostFrames;
      numberOfLostSegments += other.numberOfLostSegments;
      return *this;
    }
  };

  explicit DataLossMonitor(std::uint64_t expectedFrameSequenceNumberIncrement, std::uint64_t expectedNumberOfSegmentsPerFrame);

  auto check(ScanData const& scanData) -> LossCounts;

private:
  SequenceNumberLossMonitor<std::uint64_t> m_telegramLossMonitor;
  FrameSequenceNumberLossMonitor m_frameLossMonitor;
  SegmentIndexLossMonitor m_segmentLossMonitor;
};

} // namespace sick::compact::scan_data
