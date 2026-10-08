/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <cstdint>

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/compact_format/DataLoss/SequenceNumberLossMonitor.hpp>

namespace sick::compact {

class SDK_EXPORT FrameSequenceNumberLossMonitor : public SequenceNumberLossMonitor<std::size_t>
{
public:
  explicit FrameSequenceNumberLossMonitor(std::size_t expectedFrameSequenceNumberIncrement = 1);

  auto computeNumberOfMissingElements(std::size_t currentFrameSequenceNumber) -> int;
};
} // namespace sick::compact
