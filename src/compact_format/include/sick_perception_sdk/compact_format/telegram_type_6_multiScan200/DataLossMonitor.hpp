/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/compact_format/DataLoss/FrameSequenceNumberLossMonitor.hpp>
#include <sick_perception_sdk/compact_format/DataLoss/LossCounts.hpp>
#include <sick_perception_sdk/compact_format/DataLoss/SegmentIndexLossMonitor.hpp>
#include <sick_perception_sdk/compact_format/DataLoss/SequenceNumberLossMonitor.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_6_multiScan200/MultiScan200Data.hpp>

namespace sick::compact::multiscan200 {

/**
 * @brief Detect data losses in a MultiScan200 stream.
 *
 * The detection is based on the telegram index, segment index, and frame index.
 * A telegram loss happens on ethernet level and indicates an issue with sending or receiving.
 * Segment and frame losses are caused on the sensor, for example due to high system load.
 */
class SDK_EXPORT DataLossMonitor
{
public:
  explicit DataLossMonitor(std::uint64_t expectedFrameSequenceNumberIncrement, std::uint64_t expectedNumberOfSegmentsPerFrame);

  auto check(MultiScan200Data const& data) -> LossCounts;

private:
  SequenceNumberLossMonitor<std::uint64_t> m_telegramLossMonitor;
  FrameSequenceNumberLossMonitor m_frameLossMonitor;
  SegmentIndexLossMonitor m_segmentLossMonitor;
};

} // namespace sick::compact::multiscan200
