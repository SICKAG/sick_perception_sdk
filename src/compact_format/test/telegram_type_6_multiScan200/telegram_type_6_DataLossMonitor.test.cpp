/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/telegram_type_6_multiScan200/DataLossMonitor.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_6_multiScan200/MultiScan200Data.hpp>

#include <gtest/gtest.h>

using namespace sick;
using namespace sick::compact;
using namespace sick::compact::multiscan200;

namespace {

auto makeData(std::size_t telegramSequenceNumber, std::size_t frameSequenceNumber, std::size_t segmentIndex) -> MultiScan200Data
{
  TelegramHeader header;
  SegmentMetaData metaData;

  header.telegramSequenceNumber = telegramSequenceNumber;
  metaData.frameSequenceNumber  = frameSequenceNumber;
  metaData.segmentIndex         = segmentIndex;

  return MultiScan200Data {header, metaData};
}

} // namespace

TEST(telegram_type_6_DataLossMonitorTest, check_uses_telegram_sequence_number_from_telegram_header)
{
  // Given
  constexpr std::size_t expectedFrameSequenceNumberIncrement = 1;
  constexpr std::size_t expectedNumberOfSegmentsPerFrame     = 12;
  DataLossMonitor monitor {expectedFrameSequenceNumberIncrement, expectedNumberOfSegmentsPerFrame};
  monitor.check(makeData(1, 10, 5)); // Initialize monitor

  // When
  auto const result = monitor.check(makeData(5, 10, 5)); // gap in telegram sequence number

  // Then
  EXPECT_EQ(result.numberOfLostTelegrams, 3);
}

TEST(telegram_type_6_DataLossMonitorTest, check_uses_frame_sequence_number_from_first_module_metadata)
{
  // Given
  constexpr std::size_t expectedFrameSequenceNumberIncrement = 1;
  constexpr std::size_t expectedNumberOfSegmentsPerFrame     = 12;
  DataLossMonitor monitor {expectedFrameSequenceNumberIncrement, expectedNumberOfSegmentsPerFrame};
  monitor.check(makeData(1, 10, 5)); // Initialize monitor

  // When
  auto const result = monitor.check(makeData(2, 15, 5)); // gap in frame sequence number

  // Then
  EXPECT_EQ(result.numberOfLostFrames, 4);
}

TEST(telegram_type_6_DataLossMonitorTest, check_uses_segment_index_from_first_module_metadata)
{
  // Given
  constexpr std::size_t expectedFrameSequenceNumberIncrement = 1;
  constexpr std::size_t expectedNumberOfSegmentsPerFrame     = 12;
  DataLossMonitor monitor {expectedFrameSequenceNumberIncrement, expectedNumberOfSegmentsPerFrame};
  monitor.check(makeData(1, 10, 5)); // Initialize monitor

  // When
  auto result = monitor.check(makeData(2, 10, 8)); // gap in segment index

  // Then
  EXPECT_EQ(result.numberOfLostSegments, 2);
}
