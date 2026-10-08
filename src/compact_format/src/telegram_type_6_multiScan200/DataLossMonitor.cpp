/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/telegram_type_6_multiScan200/DataLossMonitor.hpp>

#include <sick_perception_sdk/compact_format/DataLoss/LossCounts.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_6_multiScan200/MultiScan200Data.hpp>

#include <cstdint>

namespace sick::compact::multiscan200 {

DataLossMonitor::DataLossMonitor(std::uint64_t expectedFrameSequenceNumberIncrement, std::uint64_t expectedNumberOfSegmentsPerFrame)
  : m_telegramLossMonitor(expectedFrameSequenceNumberIncrement)
  , m_frameLossMonitor(expectedFrameSequenceNumberIncrement)
  , m_segmentLossMonitor(expectedNumberOfSegmentsPerFrame)
{ }

auto DataLossMonitor::check(MultiScan200Data const& data) -> LossCounts
{
  auto const frameSequenceNumber = data.segmentMetaData.frameSequenceNumber;
  auto const segmentIndex        = data.segmentMetaData.segmentIndex;

  LossCounts ret {
    m_telegramLossMonitor.computeNumberOfMissingElements(data.telegramHeader.telegramSequenceNumber),
    m_frameLossMonitor.computeNumberOfMissingElements(frameSequenceNumber),
    m_segmentLossMonitor.computeNumberOfMissingElements(frameSequenceNumber, segmentIndex)
  };

  return ret;
}

} // namespace sick::compact::multiscan200
