/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/telegram_type_3_ambient_light/AmbientLightParser.hpp>

#include "../utils/TestParams.hpp"
#include "../utils/test_utils.hpp"
#include <sick_perception_sdk/compact_format/Crc32Utils.hpp>

#include <exception>
#include <gtest/gtest.h>

class telegram_type_3_AmbientLightParserTest : public testing::TestWithParam<sick::test::TestParams>
{ };

TEST_P(telegram_type_3_AmbientLightParserTest, validateAndParse_with_valid_data_does_not_throw_exception)
{
  // Given
  auto const p                    = GetParam();
  auto const data                 = sick::test::readBinary(p.fileIdentifier);
  constexpr bool validateChecksum = true;

  // When / Then
  EXPECT_NO_THROW(sick::compact::ambient_light::Parser::validateAndParse(data, validateChecksum));
}

TEST_P(telegram_type_3_AmbientLightParserTest, validateAndParse_sets_telegram_header_fields_correctly)
{
  // Given
  auto const p                    = GetParam();
  auto const data                 = sick::test::readBinary(p.fileIdentifier);
  constexpr bool validateChecksum = true;

  // When
  auto const parsed = sick::compact::ambient_light::Parser::validateAndParse(data, validateChecksum);

  // Then
  EXPECT_NE(parsed.telegramHeader.telegramSequenceNumber, 0U);
  EXPECT_NE(parsed.telegramHeader.transmitTimestamp.microsecondsSinceEpoch(), 0U);
  EXPECT_NE(parsed.telegramHeader.senderSerialNumber, 0U);
}

TEST_P(telegram_type_3_AmbientLightParserTest, validateAndParse_with_measured_data_returns_non_default_segment_metadata_and_values)
{
  // Given
  auto const p                    = GetParam();
  auto const data                 = sick::test::readBinary(p.fileIdentifier);
  constexpr bool validateChecksum = true;

  // When
  auto const parsed = sick::compact::ambient_light::Parser::validateAndParse(data, validateChecksum);

  // Then
  auto const& metaData = parsed.payload.metaData;

  // Assert all metadata fields to ensure parsing does not silently return defaults.
  EXPECT_GT(metaData.frameSequenceNumber, 0U);
  EXPECT_GT(metaData.startTimestamp.microsecondsSinceEpoch(), 0U);
  EXPECT_GE(metaData.stopTimestamp.microsecondsSinceEpoch(), metaData.startTimestamp.microsecondsSinceEpoch());
  EXPECT_GT(metaData.numberOfColumns, 0U);
  EXPECT_GT(metaData.numberOfLayers, 0U);
  EXPECT_TRUE(std::isfinite(metaData.startAzimuth.radians()));
  EXPECT_TRUE(std::isfinite(metaData.stopAzimuth.radians()));
  EXPECT_TRUE(std::isfinite(metaData.startElevation.radians()));
  EXPECT_TRUE(std::isfinite(metaData.stopElevation.radians()));
  EXPECT_EQ(metaData.encoding, sick::compact::ambient_light::PixelEncoding::Raw);

  EXPECT_EQ(parsed.payload.pixels.size(), parsed.payload.metaData.numberOfColumns);

  bool hasAtLeastOnePixel = false;
  for (auto const& column : parsed.payload.pixels)
  {
    EXPECT_EQ(column.size(), parsed.payload.metaData.numberOfLayers);
    hasAtLeastOnePixel = hasAtLeastOnePixel || !column.empty();
  }

  EXPECT_TRUE(hasAtLeastOnePixel);
}

TEST_P(telegram_type_3_AmbientLightParserTest, validateAndParse_with_invalid_checksum_throws_exception)
{
  // Given
  auto const p                    = GetParam();
  auto data                       = sick::test::readBinary(p.fileIdentifier);
  data[42]                        = 42; // Modify a byte to invalidate the checksum
  constexpr bool validateChecksum = true;

  // When / Then
  EXPECT_THROW(sick::compact::ambient_light::Parser::validateAndParse(data, validateChecksum), std::exception);
}

INSTANTIATE_TEST_SUITE_P(
  telegram_type_3_AmbientLightParserTest,
  telegram_type_3_AmbientLightParserTest,
  testing::Values(sick::test::TestParams {"multiScan200", "data/telegram_type_3_multiScan270_profile_12-frame_0.bin"}),
  [](testing::TestParamInfo<sick::test::TestParams> const& info) {
    return info.param.device;
  }
);

TEST(telegram_type_3_AmbientLightParserTest, validateAndParse_with_corrupted_start_of_frame_throws_exception)
{
  // Given
  auto data = sick::test::readBinary("data/telegram_type_3_multiScan270_profile_12-frame_0.bin");
  data[0]   = 42;
  // Recompute the checksum to ensure that the parser does not fail due to invalid checksum.
  sick::test::recomputeChecksum(data);
  constexpr bool validateChecksum = true;

  // When / Then
  EXPECT_THROW(sick::compact::ambient_light::Parser::validateAndParse(data, validateChecksum), std::exception);
}

TEST(telegram_type_3_AmbientLightParserTest, validateAndParse_with_corrupted_telegram_type_throws_exception)
{
  // Given
  auto data = sick::test::readBinary("data/telegram_type_3_multiScan270_profile_12-frame_0.bin");
  data[4]   = 42; // Telegram type is the 5th byte (index 4).
  // Recompute the checksum to ensure that the parser does not fail due to invalid checksum.
  sick::test::recomputeChecksum(data);
  constexpr bool validateChecksum = true;

  // When / Then
  EXPECT_THROW(sick::compact::ambient_light::Parser::validateAndParse(data, validateChecksum), std::exception);
}

TEST(telegram_type_3_AmbientLightParserTest, validateAndParse_with_corrupted_telegram_version_throws_exception)
{
  // Given
  auto data = sick::test::readBinary("data/telegram_type_3_multiScan270_profile_12-frame_0.bin");
  data[24]  = 42; // Telegram version is the 25th byte (index 24).
  // Recompute the checksum to ensure that the parser does not fail due to invalid checksum.
  sick::test::recomputeChecksum(data);
  constexpr bool validateChecksum = true;

  // When / Then
  EXPECT_THROW(sick::compact::ambient_light::Parser::validateAndParse(data, validateChecksum), std::exception);
}

TEST(telegram_type_3_AmbientLightParserTest, validateAndParse_with_injected_data_throws_exception)
{
  // Given
  auto data = sick::test::readBinary("data/telegram_type_3_multiScan270_profile_12-frame_0.bin");
  data.insert(data.end() - 10, 42); // Inject an error byte. Do it close to the end so the test is faster.
  constexpr bool validateChecksum = true;

  // When / Then
  EXPECT_THROW(sick::compact::ambient_light::Parser::validateAndParse(data, validateChecksum), std::exception);
}

TEST(telegram_type_3_AmbientLightParserTest, validateAndParse_with_empty_data_throws_exception)
{
  // Given
  std::vector<std::uint8_t> const data {};
  constexpr bool validateChecksum = true;

  // When / Then
  EXPECT_THROW(sick::compact::ambient_light::Parser::validateAndParse(data, validateChecksum), std::exception);
}
