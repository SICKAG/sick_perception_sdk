/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/telegram_type_4_encoder/EncoderParser.hpp>

#include "utils/TestParams.hpp"
#include "utils/test_utils.hpp"
#include <sick_perception_sdk/compact_format/Crc32Utils.hpp>

#include <exception>
#include <gtest/gtest.h>

class EncoderParserTest : public testing::TestWithParam<sick::test::TestParams>
{ };

TEST_P(EncoderParserTest, valid_data_can_be_parsed)
{
  auto const p    = GetParam();
  auto const data = sick::test::readBinary(p.fileIdentifier);

  constexpr bool validateChecksum = true;
  auto const parsedData           = sick::compact::encoder::Parser::validateAndParse(data, validateChecksum);

  EXPECT_EQ(0x02020202, parsedData.telegramHeader.startOfFrame);
  EXPECT_EQ(sick::compact::TelegramType::Encoder, parsedData.telegramHeader.telegramType);
  EXPECT_EQ(1, parsedData.telegramHeader.telegramVersion);
}

TEST_P(EncoderParserTest, invalid_data_is_detected)
{
  auto const p = GetParam();
  auto data    = sick::test::readBinary(p.fileIdentifier);
  data[42]     = 42; // Modify a byte to invalidate the checksum

  constexpr bool validateChecksum = true;
  EXPECT_THROW(sick::compact::encoder::Parser::validateAndParse(data, validateChecksum), std::exception);
}

INSTANTIATE_TEST_SUITE_P(
  EncoderParser,
  EncoderParserTest,
  testing::Values(sick::test::TestParams {"picoScan150", "data/picoScan150_encoder-frame_0.bin"}),
  [](testing::TestParamInfo<sick::test::TestParams> const& info) {
    return info.param.device;
  }
);

TEST(EncoderParserTest, corrupted_start_of_frame_is_detected)
{
  auto data = sick::test::readBinary("data/picoScan150_encoder-frame_0.bin");
  data[0]   = 42;

  // Recompute the checksum to ensure that the parser does not fail due to invalid checksum.
  sick::test::recomputeChecksum(data);

  constexpr bool validateChecksum = true;
  EXPECT_THROW(sick::compact::encoder::Parser::validateAndParse(data, validateChecksum), std::exception);
}

TEST(EncoderParserTest, corrupted_frame_id_is_detected)
{
  auto data = sick::test::readBinary("data/picoScan150_encoder-frame_0.bin");
  data[4]   = 42; // Command ID is the 5th byte (index 4).

  // Recompute the checksum to ensure that the parser does not fail due to invalid checksum.
  sick::test::recomputeChecksum(data);

  constexpr bool validateChecksum = true;
  EXPECT_THROW(sick::compact::encoder::Parser::validateAndParse(data, validateChecksum), std::exception);
}

TEST(EncoderParserTest, corrupted_telegram_version_is_detected)
{
  auto data = sick::test::readBinary("data/picoScan150_encoder-frame_0.bin");
  data[24]  = 42; // Telegram version is the 25th byte (index 24).

  // Recompute the checksum to ensure that the parser does not fail due to invalid checksum.
  sick::test::recomputeChecksum(data);

  constexpr bool validateChecksum = true;
  EXPECT_THROW(sick::compact::encoder::Parser::validateAndParse(data, validateChecksum), std::exception);
}

TEST(EncoderParserTest, injected_data_errors_are_detected)
{
  auto data = sick::test::readBinary("data/picoScan150_encoder-frame_0.bin");
  data.insert(data.end() - 10, 42); // Inject an error byte. Do it close to the end so the test is faster.

  constexpr bool validateChecksum = true;
  EXPECT_THROW(sick::compact::encoder::Parser::validateAndParse(data, validateChecksum), std::exception);
}

TEST(EncoderParserTest, does_not_crash_with_empty_data)
{
  std::vector<std::uint8_t> const data {};

  constexpr bool validateChecksum = true;
  EXPECT_THROW(sick::compact::encoder::Parser::validateAndParse(data, validateChecksum), std::exception);
}
