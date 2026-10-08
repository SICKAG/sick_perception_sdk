/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/DataLossMonitor.hpp>

#include <sick_perception_sdk/compact_format/DataLoss/LossCounts.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanData.hpp>

#include <cstdint>

namespace sick::compact::scan_data {

DataLossMonitor::DataLossMonitor(std::uint64_t expectedFrameSequenceNumberIncrement, std::uint64_t expectedNumberOfSegmentsPerFrame)
  : m_telegramLossMonitor(expectedFrameSequenceNumberIncrement)
  , m_frameLossMonitor(expectedFrameSequenceNumberIncrement)
  , m_segmentLossMonitor(expectedNumberOfSegmentsPerFrame)
{ }

auto DataLossMonitor::check(ScanData const& scanData) -> LossCounts
{
  LossCounts ret;

  ret.numberOfLostTelegrams = m_telegramLossMonitor.computeNumberOfMissingElements(scanData.telegramHeader.telegramSequenceNumber);

  auto const frameSequenceNumber = scanData.frameSequenceNumber;
  auto const segmentIndex        = scanData.segmentIndex;
  ret.numberOfLostFrames         = m_frameLossMonitor.computeNumberOfMissingElements(frameSequenceNumber);
  ret.numberOfLostSegments       = m_segmentLossMonitor.computeNumberOfMissingElements(frameSequenceNumber, segmentIndex);

  return ret;
}

} // namespace sick::compact::scan_data
