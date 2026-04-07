/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/DataLoss/SegmentIndexLossMonitor.hpp>

#include <gtest/gtest.h>
#include <vector>

using namespace sick::compact;

namespace {

struct TestParams
{
  std::string description;

  struct Entry
  {
    std::uint64_t frameSequenceNumber;
    std::uint64_t segmentIndex;
    int expectedNumberOfLosses;
  };

  std::vector<Entry> entries;
};

// Overloading the << operator prevents access to uninitialized memory in gtest (valgrind).
auto operator<<(std::ostream& os, TestParams const& params) -> std::ostream&
{
  os << params.description;
  return os;
}

} // namespace

class SegmentIndexLossMonitorTest : public testing::TestWithParam<TestParams>
{ };

TEST_P(SegmentIndexLossMonitorTest, check_returns_expected_losses)
{
  auto const p                                             = GetParam();
  constexpr std::uint64_t expectedNumberOfSegmentsPerFrame = 3;
  SegmentIndexLossMonitor monitor {expectedNumberOfSegmentsPerFrame};

  // Initialize the monitor
  auto const numberOfLosses = monitor.computeNumberOfMissingElements(p.entries[0].frameSequenceNumber, p.entries[0].segmentIndex);

  for (std::size_t i = 1; i < p.entries.size(); ++i)
  {
    auto const frameSequenceNumber    = p.entries[i].frameSequenceNumber;
    auto const segmentIndex           = p.entries[i].segmentIndex;
    auto const numberOfLosses         = monitor.computeNumberOfMissingElements(frameSequenceNumber, segmentIndex);
    auto const expectedNumberOfLosses = p.entries[i].expectedNumberOfLosses;
    EXPECT_EQ(expectedNumberOfLosses, numberOfLosses) << "Failed at index " << i << " with frame sequence number " << frameSequenceNumber
                                                      << " and segment index " << segmentIndex << ": expected " << expectedNumberOfLosses << " losses but got "
                                                      << numberOfLosses << ".";
  }
}

INSTANTIATE_TEST_SUITE_P(
  SegmentIndexLossMonitor,
  SegmentIndexLossMonitorTest,
  testing::Values(
    // clang-format off
    //             {frameSeqNr, segIdx, expNrOfLosses }
    TestParams {"no_losses_for_sequence_without_gaps",
                  {{     1,       1,         0        },
                   {     1,       2,         0        }  // segment index 1 -> 2: 0 packets lost
               }},
    TestParams {"losses_for_gap_in_segment_index",
                  {{     1,       0,         0        },
                   {     1,       2,         1        }  // segment index 0 -> 2: 1 packet lost
               }},
    TestParams {"losses_for_segment_index_not_incrementing",
                  {{     1,       0,         0        },
                   {     1,       0,         1        }  // segment index 0 -> 0: no increment
               }},
    // We don't consider decrementing sequence numbers as losses 
    // because that may happen when the respective counter resets.
    TestParams {"losses_for_segment_index_decrementing",
                  {{     1,       1,         0        },
                   {     1,       0,         0        }  // segment index 1 -> 0: no loss
               }},
    TestParams {"losses_for_segment_index_decrementing_continues",
                  {{     1,       1,         0        },
                   {     1,       0,         0        }, // segment index 1 -> 0: decrement
                   {     1,       1,         0        }  // segment index 0 -> 1: increment must work as usual
               }},
    TestParams {"losses_for_frame_sequence_number_decrementing",
                  {{     2,       1,         0        },
                   {     1,       1,         0        }  // frame sequence number 2 -> 1: not considered as loss
               }},
    TestParams {"no_losses_across_segment_bounds",
                  {{     1,       2,         0        }, // segment index 2 = maximum of frame
                   {     2,       0,         0        }, // frame sequence number +1, segment index back to 0 = good case
                   {     2,       1,         0        }  // segment index +1 = expected next segment
               }},
    TestParams {"losses_across_segment_bounds_1",
                  {{     1,       2,         0        }, // segment index 2 = maximum of frame
                   {     2,       1,         1        }  // segment index 1: 1 package lost
               }},
    TestParams {"losses_across_segment_bounds_2",
                  {{     1,       2,         0        }, // segment index 2 = maximum of frame
                   {     2,       2,         2        }  // segment index 1: 2 packages lost
               }} //
    // clang-format on
  ),
  [](testing::TestParamInfo<TestParams> const& info) {
    return info.param.description;
  }
);

TEST(SegmentIndexLossMonitorTest, check_returns_no_losses_on_first_call)
{
  constexpr int expectedNumberOfSegmentsPerFrame = 1;
  SegmentIndexLossMonitor monitor {expectedNumberOfSegmentsPerFrame};

  auto const numberOfLosses = monitor.computeNumberOfMissingElements(1, 0);

  EXPECT_EQ(0u, numberOfLosses);
}

TEST(SegmentIndexLossMonitorTest, construction_fails_with_invalid_expected_increment)
{
  EXPECT_THROW(SegmentIndexLossMonitor monitor(0), std::invalid_argument);
}

TEST(SegmentIndexLossMonitorTest, check_fails_when_segment_index_greater_than_expectation)
{
  constexpr int expectedNumberOfSegmentsPerFrame = 3;
  SegmentIndexLossMonitor monitor {expectedNumberOfSegmentsPerFrame};

  // Initialize
  monitor.computeNumberOfMissingElements(1, 1);
  EXPECT_THROW(
    monitor.computeNumberOfMissingElements(1, 3),
    std::invalid_argument
  ); // segment index would exceed the range 0..expectedNumberOfSegmentsPerFrame-1
}
