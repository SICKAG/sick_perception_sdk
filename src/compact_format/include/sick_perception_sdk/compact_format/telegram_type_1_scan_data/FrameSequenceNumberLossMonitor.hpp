/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <cstdint>

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/compact_format/DataLoss/SequenceNumberLossMonitor.hpp>

namespace sick::compact::scan_data {
class SDK_EXPORT FrameSequenceNumberLossMonitor : public SequenceNumberLossMonitor<std::uint64_t>
{
public:
  explicit FrameSequenceNumberLossMonitor(std::uint64_t expectedIncrement = 1);

  auto computeNumberOfMissingElements(std::uint64_t currentSequenceNumber) -> int;
};
} // namespace sick::compact::scan_data
