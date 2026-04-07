/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/FrameSequenceNumberLossMonitor.hpp>

namespace sick::compact::scan_data {

FrameSequenceNumberLossMonitor::FrameSequenceNumberLossMonitor(std::uint64_t expectedFrameSequenceNumberIncrement)
  : SequenceNumberLossMonitor<std::uint64_t>(expectedFrameSequenceNumberIncrement)
{ }

auto FrameSequenceNumberLossMonitor::computeNumberOfMissingElements(std::uint64_t currentSequenceNumber) -> int
{
  if (m_lastSequenceNumber.has_value() && currentSequenceNumber == m_lastSequenceNumber.value())
  {
    return 0;
  }
  return SequenceNumberLossMonitor<std::uint64_t>::computeNumberOfMissingElements(currentSequenceNumber);
}

} // namespace sick::compact::scan_data
