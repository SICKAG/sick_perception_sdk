/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/telegram_type_6_multiScan200/MultiScan200Parser.hpp>

#include "../utils/TestParams.hpp"
#include "../utils/test_utils.hpp"

#include <cmath>
#include <exception>
#include <gtest/gtest.h>

TEST(telegram_type_6_MultiScan200ParserTest, validateAndParse_with_valid_data_does_not_throw_exception)
{
  // Given
  auto const data                 = sick::test::readBinary("data/telegram_type_6_multiScan270_profile_12_full-frame_0.bin");
  constexpr bool validateChecksum = true;

  // When / Then
  EXPECT_NO_THROW(sick::compact::multiscan200::Parser::validateAndParse(data, validateChecksum));
}

TEST(telegram_type_6_MultiScan200ParserTest, validateAndParse_sets_telegram_header_fields_correctly)
{
  // Given
  auto const data                 = sick::test::readBinary("data/telegram_type_6_multiScan270_profile_12_full-frame_0.bin");
  constexpr bool validateChecksum = true;

  // When
  auto const parsed = sick::compact::multiscan200::Parser::validateAndParse(data, validateChecksum);

  // Then
  EXPECT_NE(parsed.telegramHeader.telegramSequenceNumber, 0U);
  EXPECT_NE(parsed.telegramHeader.transmitTimestamp.microsecondsSinceEpoch(), 0U);
  EXPECT_NE(parsed.telegramHeader.senderSerialNumber, 0U);
}

TEST(telegram_type_6_MultiScan200ParserTest, validateAndParse_with_measured_data_returns_non_default_segment_metadata_and_distances)
{
  // Given
  auto const data                 = sick::test::readBinary("data/telegram_type_6_multiScan270_profile_12_full-frame_0.bin");
  constexpr bool validateChecksum = true;

  // When
  auto const parsed = sick::compact::multiscan200::Parser::validateAndParse(data, validateChecksum);

  // Then
  auto const& metaData = parsed.segmentMetaData;
  EXPECT_GT(metaData.frameSequenceNumber, 0U);
  EXPECT_GT(metaData.frameTimestamp.microsecondsSinceEpoch(), 0U);
  EXPECT_GT(metaData.numberOfSegmentsPerFrame, 0U);
  EXPECT_LT(metaData.segmentIndex, metaData.numberOfSegmentsPerFrame);
  EXPECT_GT(metaData.numberOfColumnsInSegment, 0U);
  EXPECT_GT(metaData.numberOfColumnsInFrame, 0U);
  EXPECT_GE(metaData.numberOfColumnsInFrame, metaData.numberOfColumnsInSegment);
  EXPECT_GT(metaData.numberOfRows, 0U);
  EXPECT_GT(metaData.numberOfEchoes, 0U);
  EXPECT_GT(metaData.numberOfInterlaceSteps, 0U);
  EXPECT_LT(metaData.interlaceIndex, metaData.numberOfInterlaceSteps);
  EXPECT_GT(metaData.scanConfigurationIdentifier, 0U);
  EXPECT_EQ(parsed.ambientLightData.size(), metaData.numberOfColumnsInSegment * metaData.numberOfAmbientLightRows);
  EXPECT_EQ(parsed.geometry.elevations.size(), metaData.numberOfRows);
  EXPECT_EQ(parsed.geometry.azimuths.size(), metaData.numberOfColumnsInSegment);
  EXPECT_EQ(parsed.geometry.relativeTimeStamps.size(), metaData.numberOfColumnsInSegment);

  auto const expectedSampleCount = metaData.numberOfColumnsInSegment * metaData.numberOfRows * metaData.numberOfEchoes;
  EXPECT_EQ(parsed.distances.size(), expectedSampleCount);

  // Recorded file is required to have all fields present, so we can check that the other fields are also present.
  EXPECT_EQ(parsed.intensities.size(), expectedSampleCount);
  EXPECT_EQ(parsed.echoProperties.size(), expectedSampleCount);

  bool hasAtLeastOneFiniteDistance = false;
  for (auto const& distance : parsed.distances)
  {
    hasAtLeastOneFiniteDistance = hasAtLeastOneFiniteDistance || std::isfinite(distance.meters());
  }
  EXPECT_TRUE(hasAtLeastOneFiniteDistance);
}

TEST(telegram_type_6_MultiScan200ParserTest, validateAndParse_with_reflector_blooming_and_particle_points_sets_echo_properties)
{
  // Given
  auto const data                 = sick::test::readBinary("data/telegram_type_6_multiScan270_profile_12_full-frame_0.bin");
  constexpr bool validateChecksum = true;

  // When
  auto const parsed = sick::compact::multiscan200::Parser::validateAndParse(data, validateChecksum);

  // Then
  EXPECT_FALSE(parsed.echoProperties.empty());

  bool hasReflector = false;
  bool hasBlooming  = false;
  bool hasParticle  = false;

  for (auto const& echoProperty : parsed.echoProperties)
  {
    hasReflector = hasReflector || echoProperty.isSet(sick::compact::multiscan200::EchoProperties::Reflector);
    hasBlooming  = hasBlooming || echoProperty.isSet(sick::compact::multiscan200::EchoProperties::Blooming);
    hasParticle  = hasParticle || echoProperty.isSet(sick::compact::multiscan200::EchoProperties::Particle);
  }

  EXPECT_TRUE(hasReflector);
  EXPECT_TRUE(hasBlooming);
  EXPECT_TRUE(hasParticle);
}

TEST(telegram_type_6_MultiScan200ParserTest, validateAndParse_with_invalid_checksum_throws_exception)
{
  // Given
  auto data = sick::test::readBinary("data/telegram_type_6_multiScan270_profile_12_full-frame_0.bin");

  data[42]                        = 42; // Modify a byte to invalidate the checksum
  constexpr bool validateChecksum = true;

  // When / Then
  EXPECT_THROW(sick::compact::multiscan200::Parser::validateAndParse(data, validateChecksum), std::exception);
}

TEST(telegram_type_6_MultiScan200ParserTest, validateAndParse_with_corrupted_start_of_frame_throws_exception)
{
  // Given
  auto data = sick::test::readBinary("data/telegram_type_6_multiScan270_profile_12_full-frame_0.bin");
  data[0]   = 42;
  // Recompute the checksum to ensure that the parser does not fail due to invalid checksum.
  sick::test::recomputeChecksum(data);
  constexpr bool validateChecksum = true;

  // When / Then
  EXPECT_THROW(sick::compact::multiscan200::Parser::validateAndParse(data, validateChecksum), std::exception);
}

TEST(telegram_type_6_MultiScan200ParserTest, validateAndParse_with_corrupted_telegram_type_throws_exception)
{
  // Given
  auto data = sick::test::readBinary("data/telegram_type_6_multiScan270_profile_12_full-frame_0.bin");
  data[4]   = 42; // Telegram type is the 5th byte (index 4).
  // Recompute the checksum to ensure that the parser does not fail due to invalid checksum.
  sick::test::recomputeChecksum(data);
  constexpr bool validateChecksum = true;

  // When / Then
  EXPECT_THROW(sick::compact::multiscan200::Parser::validateAndParse(data, validateChecksum), std::exception);
}

TEST(telegram_type_6_MultiScan200ParserTest, validateAndParse_with_corrupted_telegram_version_throws_exception)
{
  // Given
  auto data = sick::test::readBinary("data/telegram_type_6_multiScan270_profile_12_full-frame_0.bin");
  data[24]  = 42; // Telegram version is the 25th byte (index 24).
  // Recompute the checksum to ensure that the parser does not fail due to invalid checksum.
  sick::test::recomputeChecksum(data);
  constexpr bool validateChecksum = true;

  // When / Then
  EXPECT_THROW(sick::compact::multiscan200::Parser::validateAndParse(data, validateChecksum), std::exception);
}

TEST(telegram_type_6_MultiScan200ParserTest, validateAndParse_with_injected_data_throws_exception)
{
  // Given
  auto data = sick::test::readBinary("data/telegram_type_6_multiScan270_profile_12_full-frame_0.bin");
  data.insert(data.end() - 10'000, 42); // Inject an error byte. Do it close to the end so the test is faster.
  constexpr bool validateChecksum = true;

  // When / Then
  EXPECT_THROW(sick::compact::multiscan200::Parser::validateAndParse(data, validateChecksum), std::exception);
}

TEST(telegram_type_6_MultiScan200ParserTest, validateAndParse_with_empty_data_throws_exception)
{
  // Given
  std::vector<std::uint8_t> const data {};
  constexpr bool validateChecksum = true;

  // When / Then
  EXPECT_THROW(sick::compact::multiscan200::Parser::validateAndParse(data, validateChecksum), std::exception);
}
