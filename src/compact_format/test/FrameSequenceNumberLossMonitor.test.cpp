/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/FrameSequenceNumberLossMonitor.hpp>

#include <gtest/gtest.h>
#include <limits>
#include <vector>

using namespace sick::compact::scan_data;

namespace {

void runLossTest(std::uint64_t expectedIncrement, std::vector<std::uint64_t> sequenceNumbers, std::vector<std::uint64_t> expectedLosses)
{
  FrameSequenceNumberLossMonitor monitor {expectedIncrement};

  // Initialize the monitor
  monitor.computeNumberOfMissingElements(sequenceNumbers[0]);

  for (std::size_t i = 0; i < sequenceNumbers.size() - 1; ++i)
  {
    auto const currentSequenceNumber = sequenceNumbers[i + 1];
    auto const expectedLoss          = expectedLosses[i];
    auto const numberOfLosses        = monitor.computeNumberOfMissingElements(currentSequenceNumber);
    EXPECT_EQ(expectedLoss, numberOfLosses) << "Failed at index " << i << " with sequence number " << currentSequenceNumber << ": expected " << expectedLoss
                                            << " losses but got " << numberOfLosses << ".";
  }
}

} // namespace

TEST(FrameSequenceNumberLossMonitorTest, check_returns_no_losses_for_sequence_without_gaps)
{
  runLossTest(1, {1, 2}, {0});
}

TEST(FrameSequenceNumberLossMonitorTest, check_returns_no_losses_with_expected_increment_greater_1_for_sequence_without_gaps)
{
  runLossTest(5, {1, 6}, {0});
}

TEST(FrameSequenceNumberLossMonitorTest, check_returns_losses_with_gap_less_than_expected_increment_0)
{
  runLossTest(2, {1, 2}, {1});
}

TEST(FrameSequenceNumberLossMonitorTest, check_returns_losses_with_gap_less_than_expected_increment_1)
{
  runLossTest(2, {1, 4}, {1});
}

TEST(FrameSequenceNumberLossMonitorTest, check_returns_losses_with_gap_less_than_expected_increment_2)
{
  runLossTest(2, {1, 5}, {1});
}

TEST(FrameSequenceNumberLossMonitorTest, check_returns_losses_with_gap_equal_than_expected_increment)
{
  runLossTest(2, {1, 6}, {2});
}

TEST(FrameSequenceNumberLossMonitorTest, check_returns_losses_with_gap_less_than_2_times_expected_increment)
{
  runLossTest(2, {1, 7}, {2});
}

TEST(FrameSequenceNumberLossMonitorTest, check_returns_losses_if_sequence_does_not_increment)
{
  runLossTest(2, {7, 7}, {0});
}

TEST(FrameSequenceNumberLossMonitorTest, check_returns_losses_if_sequence_decrements)
{
  // We don't consider decrementing sequence numbers as losses because that may happen
  // when the respective counter resets.
  runLossTest(2, {7, 6}, {0});
}

TEST(FrameSequenceNumberLossMonitorTest, check_returns_no_losses_with_max_range_values)
{
  runLossTest(2, {std::numeric_limits<std::uint64_t>::max() - 2, std::numeric_limits<std::uint64_t>::max()}, {0});
}

TEST(FrameSequenceNumberLossMonitorTest, check_returns_losses_with_max_range_values)
{
  runLossTest(2, {std::numeric_limits<std::uint64_t>::max() - 3, std::numeric_limits<std::uint64_t>::max()}, {1});
}

TEST(FrameSequenceNumberLossMonitorTest, check_returns_no_losses_on_first_call)
{
  constexpr int expectedIncrement = 1;
  FrameSequenceNumberLossMonitor monitor {expectedIncrement};

  auto const numberOfLosses = monitor.computeNumberOfMissingElements(1);

  EXPECT_EQ(0u, numberOfLosses);
}

TEST(FrameSequenceNumberLossMonitorTest, construction_fails_with_invalid_expected_increment)
{
  EXPECT_THROW(FrameSequenceNumberLossMonitor monitor {0}, std::invalid_argument);
}
