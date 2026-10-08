/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/telegram_type_7_imu/ImuParser.hpp>

#include "../utils/TestParams.hpp"
#include "../utils/test_utils.hpp"
#include <sick_perception_sdk/compact_format/Crc32Utils.hpp>

#include <cmath>
#include <exception>
#include <gtest/gtest.h>

class telegram_type_7_ImuParserTest : public testing::TestWithParam<sick::test::TestParams>
{ };

TEST_P(telegram_type_7_ImuParserTest, validateAndParse_with_valid_data_does_not_throw_exception)
{
  // Given
  auto const p                    = GetParam();
  auto const data                 = sick::test::readBinary(p.fileIdentifier);
  constexpr bool validateChecksum = true;

  // When / Then
  EXPECT_NO_THROW(sick::compact::imu::Parser::validateAndParse(data, validateChecksum));
}

TEST_P(telegram_type_7_ImuParserTest, validateAndParse_fills_all_imu_fields)
{
  // Given
  auto const p                    = GetParam();
  auto const data                 = sick::test::readBinary(p.fileIdentifier);
  constexpr bool validateChecksum = true;

  // When
  auto const parsed = sick::compact::imu::Parser::validateAndParse(data, validateChecksum);

  // Then
  EXPECT_GT(parsed.sensorTimestamp.microsecondsSinceEpoch(), 0U);

  EXPECT_TRUE(std::isfinite(parsed.acceleration.x.metersPerSecondSquared()));
  EXPECT_TRUE(std::isfinite(parsed.acceleration.y.metersPerSecondSquared()));
  EXPECT_TRUE(std::isfinite(parsed.acceleration.z.metersPerSecondSquared()));

  EXPECT_TRUE(std::isfinite(parsed.angularVelocity.x.radiansPerSecond()));
  EXPECT_TRUE(std::isfinite(parsed.angularVelocity.y.radiansPerSecond()));
  EXPECT_TRUE(std::isfinite(parsed.angularVelocity.z.radiansPerSecond()));

  EXPECT_TRUE(std::isfinite(parsed.orientation.w));
  EXPECT_TRUE(std::isfinite(parsed.orientation.x));
  EXPECT_TRUE(std::isfinite(parsed.orientation.y));
  EXPECT_TRUE(std::isfinite(parsed.orientation.z));
}

TEST_P(telegram_type_7_ImuParserTest, validateAndParse_with_invalid_checksum_throws_exception)
{
  // Given
  auto const p                    = GetParam();
  auto data                       = sick::test::readBinary(p.fileIdentifier);
  data[42]                        = 42; // Modify a byte to invalidate the checksum
  constexpr bool validateChecksum = true;

  // When / Then
  EXPECT_THROW(sick::compact::imu::Parser::validateAndParse(data, validateChecksum), std::exception);
}

INSTANTIATE_TEST_SUITE_P(
  telegram_type_7_ImuParser,
  telegram_type_7_ImuParserTest,
  testing::Values(
    sick::test::TestParams {"multiScan200_frame_0", "data/telegram_type_7_multiScan270-frame_0.bin"},
    sick::test::TestParams {"multiScan200_frame_1", "data/telegram_type_7_multiScan270-frame_1.bin"},
    sick::test::TestParams {"multiScan200_frame_2", "data/telegram_type_7_multiScan270-frame_2.bin"}
  ),
  [](testing::TestParamInfo<sick::test::TestParams> const& info) {
    return info.param.device;
  }
);

TEST(telegram_type_7_ImuParserTest, validateAndParse_reads_timestamp_before_imu_values)
{
  auto const data   = sick::test::readBinary("data/telegram_type_7_multiScan270-frame_0.bin");
  auto const parsed = sick::compact::imu::Parser::validateAndParse(data, true);

  EXPECT_EQ(parsed.sensorTimestamp.microsecondsSinceEpoch(), 4393683178U);
  EXPECT_FLOAT_EQ(parsed.acceleration.x.metersPerSecondSquared(), 0.25379312F);
  EXPECT_FLOAT_EQ(parsed.acceleration.y.metersPerSecondSquared(), -0.119713739F);
  EXPECT_FLOAT_EQ(parsed.acceleration.z.metersPerSecondSquared(), 9.69920731F);
}

TEST(telegram_type_7_ImuParserTest, validateAndParse_with_corrupted_start_of_frame_throws_exception)
{
  // Given
  auto data = sick::test::readBinary("data/telegram_type_7_multiScan270-frame_0.bin");
  data[0]   = 42;
  // Recompute the checksum to ensure that the parser does not fail due to invalid checksum.
  sick::test::recomputeChecksum(data);
  constexpr bool validateChecksum = true;

  // When / Then
  EXPECT_THROW(sick::compact::imu::Parser::validateAndParse(data, validateChecksum), std::exception);
}

TEST(telegram_type_7_ImuParserTest, validateAndParse_with_corrupted_telegram_type_throws_exception)
{
  // Given
  auto data = sick::test::readBinary("data/telegram_type_7_multiScan270-frame_0.bin");
  data[4]   = 42; // Telegram type is the 5th byte (index 4).
  // Recompute the checksum to ensure that the parser does not fail due to invalid checksum.
  sick::test::recomputeChecksum(data);
  constexpr bool validateChecksum = true;

  // When / Then
  EXPECT_THROW(sick::compact::imu::Parser::validateAndParse(data, validateChecksum), std::exception);
}

TEST(telegram_type_7_ImuParserTest, validateAndParse_with_corrupted_telegram_version_throws_exception)
{
  // Given
  auto data = sick::test::readBinary("data/telegram_type_7_multiScan270-frame_0.bin");
  data[24]  = 42; // Telegram version is the 25th byte (index 24).
  // Recompute the checksum to ensure that the parser does not fail due to invalid checksum.
  sick::test::recomputeChecksum(data);
  constexpr bool validateChecksum = true;

  // When / Then
  EXPECT_THROW(sick::compact::imu::Parser::validateAndParse(data, validateChecksum), std::exception);
}

TEST(telegram_type_7_ImuParserTest, validateAndParse_with_injected_data_throws_exception)
{
  // Given
  auto data = sick::test::readBinary("data/telegram_type_7_multiScan270-frame_0.bin");
  data.insert(data.end() - 10, 42); // Inject an error byte. Do it close to the end so the test is faster.
  constexpr bool validateChecksum = true;

  // When / Then
  EXPECT_THROW(sick::compact::imu::Parser::validateAndParse(data, validateChecksum), std::exception);
}

TEST(telegram_type_7_ImuParserTest, validateAndParse_with_empty_data_throws_exception)
{
  // Given
  std::vector<std::uint8_t> const data {};
  constexpr bool validateChecksum = true;

  // When / Then
  EXPECT_THROW(sick::compact::imu::Parser::validateAndParse(data, validateChecksum), std::exception);
}
