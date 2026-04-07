/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>

#include <cstdint>
#include <functional>
#include <optional>

namespace sick::compact {

class SDK_EXPORT SegmentIndexLossMonitor
{
public:
  explicit SegmentIndexLossMonitor(std::uint64_t expectedNumberOfSegmentsPerFrame);
  virtual ~SegmentIndexLossMonitor() = default;

  SegmentIndexLossMonitor(SegmentIndexLossMonitor const&)                    = default;
  auto operator=(SegmentIndexLossMonitor const&) -> SegmentIndexLossMonitor& = default;
  SegmentIndexLossMonitor(SegmentIndexLossMonitor&&)                         = default;
  auto operator=(SegmentIndexLossMonitor&&) -> SegmentIndexLossMonitor&      = default;

  auto computeNumberOfMissingElements(std::uint64_t frameSequenceNumber, std::uint64_t segmentIndex) -> int;

private:
  std::uint64_t m_expectedNumberOfSegmentsPerFrame;
  std::optional<std::uint64_t> m_lastLinearSegmentIndex;
};

} // namespace sick::compact
