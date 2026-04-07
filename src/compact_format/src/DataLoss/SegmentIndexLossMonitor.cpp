/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/DataLoss/SegmentIndexLossMonitor.hpp>

#include <cstdint>
#include <optional>
#include <stdexcept>

namespace sick::compact {

SegmentIndexLossMonitor::SegmentIndexLossMonitor(std::uint64_t expectedNumberOfSegmentsPerFrame)
  : m_expectedNumberOfSegmentsPerFrame(expectedNumberOfSegmentsPerFrame)
  , m_lastLinearSegmentIndex(std::nullopt)
{
  if (expectedNumberOfSegmentsPerFrame == 0u)
  {
    throw std::invalid_argument("expectedNumberOfSegmentsPerFrame must be greater than 0");
  }
}

auto SegmentIndexLossMonitor::computeNumberOfMissingElements(std::uint64_t frameSequenceNumber, std::uint64_t segmentIndex) -> int
{
  if (segmentIndex >= m_expectedNumberOfSegmentsPerFrame)
  {
    throw std::invalid_argument("segmentIndex must be smaller than expectedNumberOfSegmentsPerFrame");
  }

  if (!m_lastLinearSegmentIndex.has_value())
  {
    m_lastLinearSegmentIndex = frameSequenceNumber * m_expectedNumberOfSegmentsPerFrame + segmentIndex;
    return 0;
  }

  auto const newLinearSegmentIndex = frameSequenceNumber * m_expectedNumberOfSegmentsPerFrame + segmentIndex;
  auto const oldLinearSegmentIndex = m_lastLinearSegmentIndex.value();
  m_lastLinearSegmentIndex         = newLinearSegmentIndex;

  // The weird case first: if the sequence number does not change at all we don't really know
  // what's wrong so we'll assume that at least one element was lost.
  if (newLinearSegmentIndex == oldLinearSegmentIndex)
  {
    return 1;
  }

  // If the sequence number has decreased the underlying counter was most probably reset.
  // Therefore, we treat a decrement as no loss.
  if (newLinearSegmentIndex < oldLinearSegmentIndex)
  {
    return 0;
  }

  auto const segmentIndexDiff = newLinearSegmentIndex - oldLinearSegmentIndex;
  return static_cast<int>(segmentIndexDiff) - 1;
}

} // namespace sick::compact
