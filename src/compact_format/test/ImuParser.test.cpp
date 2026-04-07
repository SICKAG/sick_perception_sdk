/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/telegram_type_2_imu/ImuParser.hpp>

#include "utils/TestParams.hpp"
#include "utils/test_utils.hpp"
#include <sick_perception_sdk/compact_format/Crc32Utils.hpp>

#include <exception>
#include <gtest/gtest.h>

class ImuParserTest : public testing::TestWithParam<sick::test::TestParams>
{ };

TEST_P(ImuParserTest, valid_data_can_be_parsed)
{
  auto const p    = GetParam();
  auto const data = sick::test::readBinary(p.fileIdentifier);

  constexpr bool validateChecksum = true;
  auto const parsedData           = sick::compact::imu::Parser::validateAndParse(data, validateChecksum);

  EXPECT_EQ(0x02020202, parsedData.header.startOfFrame);
  EXPECT_EQ(sick::compact::TelegramType::Imu, parsedData.header.telegramType);
  EXPECT_EQ(1, parsedData.header.telegramVersion);
}

TEST_P(ImuParserTest, invalid_data_is_detected)
{
  auto const p = GetParam();
  auto data    = sick::test::readBinary(p.fileIdentifier);
  data[42]     = 42; // Modify a byte to invalidate the checksum

  constexpr bool validateChecksum = true;
  EXPECT_THROW(sick::compact::imu::Parser::validateAndParse(data, validateChecksum), std::exception);
}

INSTANTIATE_TEST_SUITE_P(
  ImuParser,
  ImuParserTest,
  testing::Values(sick::test::TestParams {"multiScan100", "data/multiScan136_imu-frame_0.bin"}),
  [](testing::TestParamInfo<sick::test::TestParams> const& info) {
    return info.param.device;
  }
);

TEST(ImuParserTest, corrupted_start_of_frame_is_detected)
{
  auto data = sick::test::readBinary("data/multiScan136_imu-frame_0.bin");
  data[0]   = 42;

  // Recompute the checksum to ensure that the parser does not fail due to invalid checksum.
  sick::test::recomputeChecksum(data);

  constexpr bool validateChecksum = true;
  EXPECT_THROW(sick::compact::imu::Parser::validateAndParse(data, validateChecksum), std::exception);
}

TEST(ImuParserTest, corrupted_frame_id_is_detected)
{
  auto data = sick::test::readBinary("data/multiScan136_imu-frame_0.bin");
  data[4]   = 42; // Command ID is the 5th byte (index 4).

  // Recompute the checksum to ensure that the parser does not fail due to invalid checksum.
  sick::test::recomputeChecksum(data);

  constexpr bool validateChecksum = true;
  EXPECT_THROW(sick::compact::imu::Parser::validateAndParse(data, validateChecksum), std::exception);
}

TEST(ImuParserTest, corrupted_telegram_version_is_detected)
{
  auto data = sick::test::readBinary("data/multiScan136_imu-frame_0.bin");
  data[8]   = 42; // Telegram version is the 9th byte (index 8).

  // Recompute the checksum to ensure that the parser does not fail due to invalid checksum.
  sick::test::recomputeChecksum(data);

  constexpr bool validateChecksum = true;
  EXPECT_THROW(sick::compact::imu::Parser::validateAndParse(data, validateChecksum), std::exception);
}

TEST(ImuParserTest, injected_data_errors_are_detected)
{
  auto data = sick::test::readBinary("data/multiScan136_imu-frame_0.bin");
  data.insert(data.end() - 10, 42); // Inject an error byte. Do it close to the end so the test is faster.

  constexpr bool validateChecksum = true;
  EXPECT_THROW(sick::compact::imu::Parser::validateAndParse(data, validateChecksum), std::exception);
}

TEST(ImuParserTest, does_not_crash_with_empty_data)
{
  std::vector<std::uint8_t> const data {};

  constexpr bool validateChecksum = true;
  EXPECT_THROW(sick::compact::imu::Parser::validateAndParse(data, validateChecksum), std::exception);
}
