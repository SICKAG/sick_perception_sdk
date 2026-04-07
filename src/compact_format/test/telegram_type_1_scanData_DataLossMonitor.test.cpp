/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <gtest/gtest.h>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/DataLossMonitor.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanData.hpp>

using namespace sick::compact;
using namespace sick::compact::scan_data;

namespace {

auto makeScanData(uint64_t telegramSequenceNumber, uint64_t frameSequenceNumber, uint64_t segmentIndex) -> ScanData
{
  TelegramHeader header;
  Module module;
  std::vector<Module> modules;

  header.telegramSequenceNumber       = telegramSequenceNumber;
  module.metaData.frameSequenceNumber = frameSequenceNumber;
  module.metaData.segmentIndex        = segmentIndex;

  modules.push_back(module);
  return ScanData {header, modules, 0};
}

} // namespace

TEST(Telegram_type_1_scanData_DataLossMonitorTest, check_uses_telegram_sequence_number_from_telegram_header)
{
  constexpr std::uint64_t expectedFrameSequenceNumberIncrement = 1;
  constexpr std::uint64_t expectedNumberOfSegmentsPerFrame     = 12;
  DataLossMonitor monitor {expectedFrameSequenceNumberIncrement, expectedNumberOfSegmentsPerFrame};

  monitor.check(makeScanData(1, 10, 5));
  auto result = monitor.check(makeScanData(5, 10, 5)); // gap in telegram sequence number

  EXPECT_EQ(result.numberOfLostTelegrams, 3);
}

TEST(Telegram_type_1_scanData_DataLossMonitorTest, check_uses_frame_sequence_number_from_first_module_metadata)
{
  constexpr std::uint64_t expectedFrameSequenceNumberIncrement = 1;
  constexpr std::uint64_t expectedNumberOfSegmentsPerFrame     = 12;
  DataLossMonitor monitor {expectedFrameSequenceNumberIncrement, expectedNumberOfSegmentsPerFrame};

  monitor.check(makeScanData(1, 10, 5));
  auto result = monitor.check(makeScanData(2, 15, 5)); // gap in frame sequence number

  EXPECT_EQ(result.numberOfLostFrames, 4);
}

TEST(Telegram_type_1_scanData_DataLossMonitorTest, check_uses_segment_index_from_first_module_metadata)
{
  constexpr std::uint64_t expectedFrameSequenceNumberIncrement = 1;
  constexpr std::uint64_t expectedNumberOfSegmentsPerFrame     = 12;
  DataLossMonitor monitor {expectedFrameSequenceNumberIncrement, expectedNumberOfSegmentsPerFrame};

  monitor.check(makeScanData(1, 10, 5));
  auto result = monitor.check(makeScanData(2, 10, 8)); // gap in segment index

  EXPECT_EQ(result.numberOfLostSegments, 2);
}
