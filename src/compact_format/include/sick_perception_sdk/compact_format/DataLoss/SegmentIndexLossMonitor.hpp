/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>

#include <functional>
#include <optional>

namespace sick::compact {

class SDK_EXPORT SegmentIndexLossMonitor
{
public:
  explicit SegmentIndexLossMonitor(std::size_t expectedNumberOfSegmentsPerFrame);
  virtual ~SegmentIndexLossMonitor() = default;

  SegmentIndexLossMonitor(SegmentIndexLossMonitor const&)                    = default;
  auto operator=(SegmentIndexLossMonitor const&) -> SegmentIndexLossMonitor& = default;
  SegmentIndexLossMonitor(SegmentIndexLossMonitor&&)                         = default;
  auto operator=(SegmentIndexLossMonitor&&) -> SegmentIndexLossMonitor&      = default;

  auto computeNumberOfMissingElements(std::size_t frameSequenceNumber, std::size_t segmentIndex) -> int;

private:
  std::size_t m_expectedNumberOfSegmentsPerFrame;
  std::optional<std::size_t> m_lastLinearSegmentIndex;
};

} // namespace sick::compact
