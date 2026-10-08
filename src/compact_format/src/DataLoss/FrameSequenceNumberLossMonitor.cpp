/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/DataLoss/FrameSequenceNumberLossMonitor.hpp>

#include <sick_perception_sdk/compact_format/DataLoss/SequenceNumberLossMonitor.hpp>

#include <cstddef>

namespace sick::compact {

FrameSequenceNumberLossMonitor::FrameSequenceNumberLossMonitor(std::size_t expectedFrameSequenceNumberIncrement)
  : SequenceNumberLossMonitor<std::size_t>(expectedFrameSequenceNumberIncrement)
{ }

auto FrameSequenceNumberLossMonitor::computeNumberOfMissingElements(std::size_t currentFrameSequenceNumber) -> int
{
  if (m_lastSequenceNumber.has_value() && currentFrameSequenceNumber == m_lastSequenceNumber.value())
  {
    return 0;
  }
  return SequenceNumberLossMonitor<std::size_t>::computeNumberOfMissingElements(currentFrameSequenceNumber);
}

} // namespace sick::compact
