/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/StreamExtractor.hpp>

#include "utils/TestParams.hpp"
#include "utils/test_utils.hpp"

#include <exception>
#include <gtest/gtest.h>

class StreamExtractorTest : public testing::TestWithParam<sick::test::TestParams>
{ };

TEST_P(StreamExtractorTest, valid_data_with_single_frame_can_be_parsed)
{
  auto const p    = GetParam();
  auto const data = sick::test::readBinary("data/" + p.fileIdentifier + "-frame_0.bin");

  sick::compact::StreamExtractor extractor;
  auto const packets = extractor.extractTelegrams(data);

  ASSERT_EQ(1, packets.size());
  EXPECT_EQ(0x02, packets[0][0]);
  EXPECT_EQ(0x02, packets[0][1]);
  EXPECT_EQ(0x02, packets[0][2]);
  EXPECT_EQ(0x02, packets[0][3]);
}

TEST_P(StreamExtractorTest, valid_data_with_multiple_frames_can_be_parsed)
{
  auto const p     = GetParam();
  auto const data0 = sick::test::readBinary("data/" + p.fileIdentifier + "-frame_0.bin");
  auto const data1 = sick::test::readBinary("data/" + p.fileIdentifier + "-frame_1.bin");
  auto const data2 = sick::test::readBinary("data/" + p.fileIdentifier + "-frame_2.bin");

  std::vector<std::uint8_t> data;
  data.insert(data.end(), data0.begin(), data0.end());
  data.insert(data.end(), data1.begin(), data1.end());
  data.insert(data.end(), data2.begin(), data2.end());

  sick::compact::StreamExtractor extractor;
  auto const packets = extractor.extractTelegrams(data);

  ASSERT_EQ(3, packets.size());
  for (size_t i = 0; i < 3; ++i)
  {
    EXPECT_EQ(0x02, packets[i][0]);
    EXPECT_EQ(0x02, packets[i][1]);
    EXPECT_EQ(0x02, packets[i][2]);
    EXPECT_EQ(0x02, packets[i][3]);
  }
}

TEST_P(StreamExtractorTest, partial_frames_are_assembled)
{
  auto const p    = GetParam();
  auto const data = sick::test::readBinary("data/" + p.fileIdentifier + "-frame_0.bin");

  // The increment should be 1 but needs to be slightly larger for very large files or otherwise the test will take too long to run.
  std::size_t const increment = std::max(data.size() / 10000, std::size_t {1});
  sick::compact::StreamExtractor extractor;
  for (auto cutIndex = 1; cutIndex < data.size(); cutIndex += increment)
  {
    // Parse a few bytes from the beginning. Since this is not the complete packet the returned list must be empty.
    auto packets = extractor.extractTelegrams(std::vector<std::uint8_t>(data.begin(), data.begin() + cutIndex));
    ASSERT_EQ(0, packets.size());

    // Parse the rest of the available data.
    packets = extractor.extractTelegrams(std::vector<std::uint8_t>(data.begin() + cutIndex, data.end()));
    ASSERT_EQ(1, packets.size());
  }
}

TEST_P(StreamExtractorTest, corrupted_data_is_detected)
{
  auto const p = GetParam();
  auto data    = sick::test::readBinary("data/" + p.fileIdentifier + "-frame_0.bin");
  data[42]     = 42;

  sick::compact::StreamExtractor extractor;
  auto packets = extractor.extractTelegrams(data);
  ASSERT_EQ(0, packets.size());

  // Now it must be possible to parse a valid packet again.
  data    = sick::test::readBinary("data/multiScan136_scan-frame_0.bin");
  packets = extractor.extractTelegrams(data);
  ASSERT_EQ(1, packets.size());
}

#ifndef UNSAFE_MEMCPY_ALLOWED // This test cannot be executed when unsafe memcpy is allowed because it will provoke access violations.
TEST_P(StreamExtractorTest, injected_data_errors_are_detected)
{
  auto const p = GetParam();
  auto data    = sick::test::readBinary("data/" + p.fileIdentifier + "-frame_0.bin");

  // Note about this strange parameter choice: for best test coverage the cut index should be iterated over the whole range of data.
  // However, for multi-module Compact packages there will always be a constellation where the data corruption coincides with the field for the
  // next module size. In this case the extractor may require a lot more than one packet until it detects that the checksum is invalid and the
  // last assert in this test case won't hold true. The choice of cutIndex1 and cutIndex2 is tuned manually for all known test files.
  auto const cutIndex1 = data.size() * 3 / 4;
  auto const cutIndex2 = data.size() / 2;

  sick::compact::StreamExtractor extractor;

  // Parse a few bytes from the beginning. Since this is not the complete packet the returned list must be empty.
  auto packets = extractor.extractTelegrams(std::vector<std::uint8_t>(data.begin(), data.begin() + cutIndex1));
  ASSERT_EQ(0, packets.size());

  // Collect some of the already collected data plus the rest of the data. The extractor must detect that the data packet is now corrupted.
  packets = extractor.extractTelegrams(std::vector<std::uint8_t>(data.begin() + cutIndex2, data.end()));
  ASSERT_EQ(0, packets.size());

  // Now it must be possible to parse a valid packet again.
  packets = extractor.extractTelegrams(data);
  ASSERT_EQ(1, packets.size());
}
#endif

INSTANTIATE_TEST_SUITE_P(
  StreamExtractor,
  StreamExtractorTest,
  testing::Values(
    sick::test::TestParams {"LRS4000_scan", "LRS4581_scan"},
    sick::test::TestParams {"multiScan100_imu", "multiScan136_imu"},
    sick::test::TestParams {"multiScan100_scan", "multiScan136_scan"},
    sick::test::TestParams {"picoScan100_encoder", "picoScan150_encoder"},
    sick::test::TestParams {"picoScan100_scan", "picoScan150_profile1_scan"}
  ),
  [](testing::TestParamInfo<sick::test::TestParams> const& info) {
    return info.param.device;
  }
);

TEST(StreamExtractorTest, valid_data_with_multiple_frames_of_different_type_can_be_parsed)
{
  std::vector<std::uint8_t> data;
  auto load = [&data](std::string const& filePath) {
    auto const newData = sick::test::readBinary(filePath);
    data.insert(data.end(), newData.begin(), newData.end());
  };
  load("data/picoScan150_encoder-frame_0.bin");
  load("data/multiScan136_scan-frame_0.bin");

  sick::compact::StreamExtractor extractor;
  auto const packets = extractor.extractTelegrams(data);

  ASSERT_EQ(2, packets.size());
}

TEST(StreamExtractorTest, corrupted_start_of_frame_is_detected)
{
  auto data = sick::test::readBinary("data/multiScan136_scan-frame_0.bin");
  data[0]   = 42;

  sick::compact::StreamExtractor extractor;
  auto packets = extractor.extractTelegrams(data);
  ASSERT_EQ(0, packets.size());

  // Now it must be possible to parse a valid packet again.
  data    = sick::test::readBinary("data/multiScan136_scan-frame_0.bin");
  packets = extractor.extractTelegrams(data);
  ASSERT_EQ(1, packets.size());
}

TEST(StreamExtractorTest, corrupted_frame_id_is_detected)
{
  auto data = sick::test::readBinary("data/multiScan136_scan-frame_0.bin");
  data[4]   = 42; // Command ID is the 5th byte (index 4).

  sick::compact::StreamExtractor extractor;
  auto packets = extractor.extractTelegrams(data);
  ASSERT_EQ(0, packets.size());

  // Now it must be possible to parse a valid packet again.
  data    = sick::test::readBinary("data/multiScan136_scan-frame_0.bin");
  packets = extractor.extractTelegrams(data);
  ASSERT_EQ(1, packets.size());
}

TEST(StreamExtractorTest, does_not_crash_with_empty_data)
{
  std::vector<std::uint8_t> const data {};

  sick::compact::StreamExtractor extractor;
  auto const packets = extractor.extractTelegrams(data);
  ASSERT_EQ(0, packets.size());
}
