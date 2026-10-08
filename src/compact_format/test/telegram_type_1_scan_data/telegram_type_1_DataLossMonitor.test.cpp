/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/DataLossMonitor.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanData.hpp>

#include <gtest/gtest.h>

using namespace sick::compact;
using namespace sick::compact::scan_data;

namespace {

auto makeScanData(std::size_t telegramSequenceNumber, std::size_t frameSequenceNumber, std::size_t segmentIndex) -> ScanData
{
  TelegramHeader header;
  Module module;
  std::vector<Module> modules;

  header.telegramSequenceNumber = telegramSequenceNumber;

  modules.push_back(module);
  return ScanData {header, frameSequenceNumber, segmentIndex, modules};
}

} // namespace

TEST(telegram_type_1_DataLossMonitorTest, check_uses_telegram_sequence_number_from_telegram_header)
{
  constexpr std::size_t expectedFrameSequenceNumberIncrement = 1;
  constexpr std::size_t expectedNumberOfSegmentsPerFrame     = 12;
  DataLossMonitor monitor {expectedFrameSequenceNumberIncrement, expectedNumberOfSegmentsPerFrame};

  monitor.check(makeScanData(1, 10, 5));
  auto result = monitor.check(makeScanData(5, 10, 5)); // gap in telegram sequence number

  EXPECT_EQ(result.numberOfLostTelegrams, 3);
}

TEST(telegram_type_1_DataLossMonitorTest, check_uses_frame_sequence_number_from_first_module_metadata)
{
  constexpr std::size_t expectedFrameSequenceNumberIncrement = 1;
  constexpr std::size_t expectedNumberOfSegmentsPerFrame     = 12;
  DataLossMonitor monitor {expectedFrameSequenceNumberIncrement, expectedNumberOfSegmentsPerFrame};

  monitor.check(makeScanData(1, 10, 5));
  auto result = monitor.check(makeScanData(2, 15, 5)); // gap in frame sequence number

  EXPECT_EQ(result.numberOfLostFrames, 4);
}

TEST(telegram_type_1_DataLossMonitorTest, check_uses_segment_index_from_first_module_metadata)
{
  constexpr std::size_t expectedFrameSequenceNumberIncrement = 1;
  constexpr std::size_t expectedNumberOfSegmentsPerFrame     = 12;
  DataLossMonitor monitor {expectedFrameSequenceNumberIncrement, expectedNumberOfSegmentsPerFrame};

  monitor.check(makeScanData(1, 10, 5));
  auto result = monitor.check(makeScanData(2, 10, 8)); // gap in segment index

  EXPECT_EQ(result.numberOfLostSegments, 2);
}
