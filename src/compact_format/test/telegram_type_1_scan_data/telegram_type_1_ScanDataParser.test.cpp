/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanDataParser.hpp>

#include "../utils/TestParams.hpp"
#include "../utils/test_utils.hpp"
#include <sick_perception_sdk/compact_format/Crc32Utils.hpp>

#include <cmath>
#include <exception>
#include <gtest/gtest.h>

class telegram_type_1_ScanDataParserTest : public testing::TestWithParam<sick::test::TestParams>
{ };

TEST_P(telegram_type_1_ScanDataParserTest, validateAndParse_with_valid_data_does_not_throw_exception)
{
  // Given
  auto const p                    = GetParam();
  auto const data                 = sick::test::readBinary(p.fileIdentifier);
  constexpr bool validateChecksum = true;

  // When / Then
  EXPECT_NO_THROW(sick::compact::scan_data::Parser::validateAndParse(data, validateChecksum));
}

TEST_P(telegram_type_1_ScanDataParserTest, validateAndParse_sets_telegram_header_fields_correctly)
{
  // Given
  auto const p                    = GetParam();
  auto const data                 = sick::test::readBinary(p.fileIdentifier);
  constexpr bool validateChecksum = true;

  // When
  auto const parsed = sick::compact::scan_data::Parser::validateAndParse(data, validateChecksum);

  // Then
  EXPECT_NE(parsed.telegramHeader.telegramSequenceNumber, 0U);
  EXPECT_NE(parsed.telegramHeader.transmitTimestamp.microsecondsSinceEpoch(), 0U);
  EXPECT_NE(parsed.telegramHeader.senderSerialNumber, 0U);
}

TEST_P(telegram_type_1_ScanDataParserTest, validateAndParse_with_measured_data_returns_non_default_segment_metadata_and_values)
{
  // Given
  auto const p                    = GetParam();
  auto const data                 = sick::test::readBinary(p.fileIdentifier);
  constexpr bool validateChecksum = true;

  // When
  auto const parsed = sick::compact::scan_data::Parser::validateAndParse(data, validateChecksum);

  // Then
  EXPECT_GT(parsed.frameSequenceNumber, 0U);
  EXPECT_FALSE(parsed.modules.empty());

  for (auto const& module : parsed.modules)
  {
    EXPECT_GT(module.numberOfColumns, 0U);
    EXPECT_GT(module.numberOfEchoesPerBeam, 0U);
    EXPECT_FALSE(module.rowMetaData.empty());

    auto const numberOfRows        = module.rowMetaData.size();
    auto const expectedBeamCount   = module.numberOfColumns * numberOfRows;
    auto const expectedSampleCount = expectedBeamCount * module.numberOfEchoesPerBeam;

    EXPECT_EQ(module.distances.size(), expectedSampleCount);

    if (!module.intensities.empty())
    {
      EXPECT_EQ(module.intensities.size(), expectedSampleCount);
    }

    if (!module.beamProperties.empty())
    {
      EXPECT_EQ(module.beamProperties.size(), expectedBeamCount);
    }

    if (!module.beamAzimuths.empty())
    {
      EXPECT_EQ(module.beamAzimuths.size(), expectedBeamCount);
    }

    for (auto const& row : module.rowMetaData)
    {
      EXPECT_GT(row.firstBeamTimestamp.microsecondsSinceEpoch(), 0U);
      EXPECT_GE(row.lastBeamTimestamp.microsecondsSinceEpoch(), row.firstBeamTimestamp.microsecondsSinceEpoch());
      EXPECT_TRUE(std::isfinite(row.elevation.degrees()));
      EXPECT_TRUE(std::isfinite(row.firstBeamAzimuth.degrees()));
      EXPECT_TRUE(std::isfinite(row.lastBeamAzimuth.degrees()));
    }
  }
}

TEST_P(telegram_type_1_ScanDataParserTest, validateAndParse_with_invalid_checksum_throws_exception)
{
  // Given
  auto const p                    = GetParam();
  auto data                       = sick::test::readBinary(p.fileIdentifier);
  data[42]                        = 42; // Modify a byte to invalidate the checksum
  constexpr bool validateChecksum = true;

  // When / Then
  EXPECT_THROW(sick::compact::scan_data::Parser::validateAndParse(data, validateChecksum), std::exception);
}

INSTANTIATE_TEST_SUITE_P(
  telegram_type_1_ScanDataParserTest,
  telegram_type_1_ScanDataParserTest,
  testing::Values(
    sick::test::TestParams {"LRS4000", "data/telegram_type_1_LRS4581-frame_0.bin"},
    sick::test::TestParams {"multiScan100", "data/telegram_type_1_multiScan136-frame_0.bin"},
    sick::test::TestParams {"picoScan100", "data/telegram_type_1_picoScan150_profile_1-frame_0.bin"}
  ),
  [](testing::TestParamInfo<sick::test::TestParams> const& info) {
    return info.param.device;
  }
);

TEST(telegram_type_1_ScanDataParserTest, validateAndParse_with_corrupted_start_of_frame_throws_exception)
{
  // Given
  auto data = sick::test::readBinary("data/telegram_type_1_multiScan136-frame_0.bin");
  data[0]   = 42;
  // Recompute the checksum to ensure that the parser does not fail due to invalid checksum.
  sick::test::recomputeChecksum(data);
  constexpr bool validateChecksum = true;

  // When / Then
  EXPECT_THROW(sick::compact::scan_data::Parser::validateAndParse(data, validateChecksum), std::exception);
}

TEST(telegram_type_1_ScanDataParserTest, validateAndParse_with_corrupted_telegram_type_throws_exception)
{
  // Given
  auto data = sick::test::readBinary("data/telegram_type_1_multiScan136-frame_0.bin");
  data[4]   = 42; // Telegram type is the 5th byte (index 4).
  // Recompute the checksum to ensure that the parser does not fail due to invalid checksum.
  sick::test::recomputeChecksum(data);
  constexpr bool validateChecksum = true;

  // When / Then
  EXPECT_THROW(sick::compact::scan_data::Parser::validateAndParse(data, validateChecksum), std::exception);
}

TEST(telegram_type_1_ScanDataParserTest, validateAndParse_with_corrupted_telegram_version_throws_exception)
{
  // Given
  auto data = sick::test::readBinary("data/telegram_type_1_multiScan136-frame_0.bin");
  data[24]  = 42; // Telegram version is the 25th byte (index 24).
  // Recompute the checksum to ensure that the parser does not fail due to invalid checksum.
  sick::test::recomputeChecksum(data);
  constexpr bool validateChecksum = true;

  // When / Then
  EXPECT_THROW(sick::compact::scan_data::Parser::validateAndParse(data, validateChecksum), std::exception);
}

TEST(telegram_type_1_ScanDataParserTest, validateAndParse_with_injected_data_throws_exception)
{
  // Given
  auto data = sick::test::readBinary("data/telegram_type_1_multiScan136-frame_0.bin");
  data.insert(data.end() - 10, 42); // Inject an error byte. Do it close to the end so the test is faster.
  constexpr bool validateChecksum = true;

  // When / Then
  EXPECT_THROW(sick::compact::scan_data::Parser::validateAndParse(data, validateChecksum), std::exception);
}

TEST(telegram_type_1_ScanDataParserTest, validateAndParse_with_empty_data_throws_exception)
{
  // Given
  std::vector<std::uint8_t> const data {};
  constexpr bool validateChecksum = true;

  // When / Then
  EXPECT_THROW(sick::compact::scan_data::Parser::validateAndParse(data, validateChecksum), std::exception);
}

TEST(telegram_type_1_ScanDataParserTest, validateAndParse_returns_intensities_normalized_to_unit_range)
{
  // Given
  auto const data                 = sick::test::readBinary("data/telegram_type_1_picoScan150_profile_1-frame_0.bin");
  constexpr bool validateChecksum = true;

  // When
  auto const scanData = sick::compact::scan_data::Parser::validateAndParse(data, validateChecksum);

  // Then
  bool foundIntensity = false;
  for (auto const& module : scanData.modules)
  {
    for (auto const intensity : module.intensities)
    {
      foundIntensity = true;
      EXPECT_GE(intensity, 0.0f);
      EXPECT_LE(intensity, 1.0f);
    }
  }

  // Guard against the test silently passing because the telegram carries no intensity data.
  EXPECT_TRUE(foundIntensity);
}
