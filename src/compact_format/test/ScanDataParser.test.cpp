/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanDataParser.hpp>

#include "utils/TestParams.hpp"
#include "utils/test_utils.hpp"
#include <sick_perception_sdk/compact_format/Crc32Utils.hpp>

#include <exception>
#include <gtest/gtest.h>

class ScanDataParserTest : public testing::TestWithParam<sick::test::TestParams>
{ };

TEST_P(ScanDataParserTest, valid_data_can_be_parsed)
{
  auto const p    = GetParam();
  auto const data = sick::test::readBinary(p.fileIdentifier);

  constexpr bool validateChecksum = true;
  auto const scanData             = sick::compact::scan_data::Parser::validateAndParse(data, validateChecksum);

  EXPECT_EQ(0x02020202, scanData.telegramHeader.startOfFrame);
  EXPECT_EQ(sick::compact::TelegramType::ScanData, scanData.telegramHeader.telegramType);
  EXPECT_EQ(4, scanData.telegramHeader.telegramVersion);
}

TEST_P(ScanDataParserTest, invalid_data_is_detected)
{
  auto const p = GetParam();
  auto data    = sick::test::readBinary(p.fileIdentifier);
  data[42]     = 42; // Modify a byte to invalidate the checksum

  constexpr bool validateChecksum = true;
  EXPECT_THROW(sick::compact::scan_data::Parser::validateAndParse(data, validateChecksum), std::exception);
}

INSTANTIATE_TEST_SUITE_P(
  ScanDataParser,
  ScanDataParserTest,
  testing::Values(
    sick::test::TestParams {"LRS4000", "data/LRS4581_scan-frame_0.bin"},
    sick::test::TestParams {"multiScan100", "data/multiScan136_scan-frame_0.bin"},
    sick::test::TestParams {"picoScan100", "data/picoScan150_profile1_scan-frame_0.bin"}
  ),
  [](testing::TestParamInfo<sick::test::TestParams> const& info) {
    return info.param.device;
  }
);

TEST(ScanDataParserTest, corrupted_start_of_frame_is_detected)
{
  auto data = sick::test::readBinary("data/multiScan136_scan-frame_0.bin");
  data[0]   = 42;

  // Recompute the checksum to ensure that the parser does not fail due to invalid checksum.
  sick::test::recomputeChecksum(data);

  constexpr bool validateChecksum = true;
  EXPECT_THROW(sick::compact::scan_data::Parser::validateAndParse(data, validateChecksum), std::exception);
}

TEST(ScanDataParserTest, corrupted_frame_id_is_detected)
{
  auto data = sick::test::readBinary("data/multiScan136_scan-frame_0.bin");
  data[4]   = 42; // Command ID is the 5th byte (index 4).

  // Recompute the checksum to ensure that the parser does not fail due to invalid checksum.
  sick::test::recomputeChecksum(data);

  constexpr bool validateChecksum = true;
  EXPECT_THROW(sick::compact::scan_data::Parser::validateAndParse(data, validateChecksum), std::exception);
}

TEST(ScanDataParserTest, corrupted_telegram_version_is_detected)
{
  auto data = sick::test::readBinary("data/multiScan136_scan-frame_0.bin");
  data[24]  = 42; // Telegram version is the 25th byte (index 24).

  // Recompute the checksum to ensure that the parser does not fail due to invalid checksum.
  sick::test::recomputeChecksum(data);

  constexpr bool validateChecksum = true;
  EXPECT_THROW(sick::compact::scan_data::Parser::validateAndParse(data, validateChecksum), std::exception);
}

TEST(ScanDataParserTest, injected_data_errors_are_detected)
{
  auto data = sick::test::readBinary("data/multiScan136_scan-frame_0.bin");
  data.insert(data.end() - 10, 42); // Inject an error byte. Do it close to the end so the test is faster.

  constexpr bool validateChecksum = true;
  EXPECT_THROW(sick::compact::scan_data::Parser::validateAndParse(data, validateChecksum), std::exception);
}

TEST(ScanDataParserTest, does_not_crash_with_empty_data)
{
  std::vector<std::uint8_t> const data {};

  constexpr bool validateChecksum = true;
  EXPECT_THROW(sick::compact::scan_data::Parser::validateAndParse(data, validateChecksum), std::exception);
}
