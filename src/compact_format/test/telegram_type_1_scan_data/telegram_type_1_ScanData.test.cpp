/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanData.hpp>

#include "ScanDataGenerator.hpp"
#include <sick_perception_sdk/common/quantities/Angle.hpp>
#include <sick_perception_sdk/common/quantities/Distance.hpp>

#include <gtest/gtest.h>

using namespace sick;
using namespace sick::test;
using namespace sick::compact::scan_data;

namespace {

constexpr std::uint32_t kNumberOfColumns = 10;
constexpr std::uint32_t kNumberOfRows    = 5;
constexpr std::uint32_t kNumberOfEchoes  = 3;

auto makeModule() -> Module
{
  auto scanData = ScanDataGenerator().withNumberOfColumns(kNumberOfColumns).withNumberOfRows(kNumberOfRows).withNumberOfEchoesPerBeam(kNumberOfEchoes).next();

  auto module = std::move(scanData.modules[0]);

  // Fill with distinct values for testing
  auto const totalSamples = module.distances.size();
  for (std::size_t i = 0; i < totalSamples; ++i)
  {
    module.distances[i]   = Distance::fromMillimeters(static_cast<float>(i));
    module.intensities[i] = static_cast<float>(i) / 100.0F;
  }

  // Populate beam data for testing
  auto const totalBeams = static_cast<std::size_t>(kNumberOfColumns * kNumberOfRows);
  module.beamProperties.resize(totalBeams);
  module.beamAzimuths.resize(totalBeams);
  for (std::size_t i = 0; i < totalBeams; ++i)
  {
    module.beamProperties[i] = BitField<BeamProperties>(static_cast<std::underlying_type_t<BeamProperties>>(i));
    module.beamAzimuths[i]   = Angle::fromDegrees(static_cast<float>(i));
  }

  return module;
}

} // namespace

// Tests for computeSampleIndex

TEST(telegram_type_1_ScanDataTest, computeSampleIndex_returns_zero_for_first_element)
{
  auto module = makeModule();

  EXPECT_EQ(computeSampleIndex(module, 0, 0, 0), 0U);
}

TEST(telegram_type_1_ScanDataTest, computeSampleIndex_increments_by_one_for_echo_index)
{
  auto module = makeModule();

  EXPECT_EQ(computeSampleIndex(module, 0, 0, 0), 0U);
  EXPECT_EQ(computeSampleIndex(module, 0, 0, 1), 1U);
  EXPECT_EQ(computeSampleIndex(module, 0, 0, 2), 2U);
}

TEST(telegram_type_1_ScanDataTest, computeSampleIndex_increments_by_numberOfEchoes_for_row_index)
{
  auto module = makeModule();

  // row 0 -> index 0, row 1 -> index 3, row 2 -> index 6
  EXPECT_EQ(computeSampleIndex(module, 0, 0, 0), 0U);
  EXPECT_EQ(computeSampleIndex(module, 0, 1, 0), 3U);
  EXPECT_EQ(computeSampleIndex(module, 0, 2, 0), 6U);
}

TEST(telegram_type_1_ScanDataTest, computeSampleIndex_increments_by_rows_times_echoes_for_column_index)
{
  auto module = makeModule();

  // column stride = 5 * 3 = 15
  EXPECT_EQ(computeSampleIndex(module, 0, 0, 0), 0U);
  EXPECT_EQ(computeSampleIndex(module, 1, 0, 0), 15U);
  EXPECT_EQ(computeSampleIndex(module, 2, 0, 0), 30U);
}

TEST(telegram_type_1_ScanDataTest, computeSampleIndex_computes_correct_combined_index)
{
  auto module = makeModule();

  // column=2, row=3, echo=1 -> 2 * (5*3) + 3 * 3 + 1 = 30 + 9 + 1 = 40
  EXPECT_EQ(computeSampleIndex(module, 2, 3, 1), 40U);
}

TEST(telegram_type_1_ScanDataTest, computeSampleIndex_returns_last_index_for_last_element)
{
  auto module = makeModule();

  // Last element: column=9, row=4, echo=2 -> 9*15 + 4*3 + 2 = 135 + 12 + 2 = 149
  EXPECT_EQ(computeSampleIndex(module, 9, 4, 2), 149U);
}

// Tests for computeBeamIndex

TEST(telegram_type_1_ScanDataTest, computeBeamIndex_returns_zero_for_first_element)
{
  auto module = makeModule();

  EXPECT_EQ(computeBeamIndex(module, 0, 0), 0U);
}

TEST(telegram_type_1_ScanDataTest, computeBeamIndex_increments_by_one_for_row_index)
{
  auto module = makeModule();

  EXPECT_EQ(computeBeamIndex(module, 0, 0), 0U);
  EXPECT_EQ(computeBeamIndex(module, 0, 1), 1U);
  EXPECT_EQ(computeBeamIndex(module, 0, 2), 2U);
}

TEST(telegram_type_1_ScanDataTest, computeBeamIndex_increments_by_numberOfRows_for_column_index)
{
  auto module = makeModule();

  EXPECT_EQ(computeBeamIndex(module, 0, 0), 0U);
  EXPECT_EQ(computeBeamIndex(module, 1, 0), 5U);
  EXPECT_EQ(computeBeamIndex(module, 2, 0), 10U);
}

TEST(telegram_type_1_ScanDataTest, computeBeamIndex_computes_correct_combined_index)
{
  auto module = makeModule();

  // column=3, row=2 -> 3 * 5 + 2 = 17
  EXPECT_EQ(computeBeamIndex(module, 3, 2), 17U);
}

// Tests for getDistance

TEST(telegram_type_1_ScanDataTest, getDistance_returns_correct_value_for_first_element)
{
  auto const module = makeModule();

  auto const distance = getDistance(module, 0, 0, 0);

  EXPECT_FLOAT_EQ(distance.millimeters(), 0.0F);
}

TEST(telegram_type_1_ScanDataTest, getDistance_returns_correct_value_for_arbitrary_element)
{
  auto const module = makeModule();

  // column=2, row=3, echo=1 -> index 40
  auto const distance = getDistance(module, 2, 3, 1);

  EXPECT_FLOAT_EQ(distance.millimeters(), 40.0F);
}

// Tests for getIntensity

TEST(telegram_type_1_ScanDataTest, getIntensity_returns_correct_value_for_first_element)
{
  auto const module = makeModule();

  auto const intensity = getIntensity(module, 0, 0, 0);

  EXPECT_FLOAT_EQ(intensity, 0.0F);
}

TEST(telegram_type_1_ScanDataTest, getIntensity_returns_correct_value_for_arbitrary_element)
{
  auto const module = makeModule();

  // column=2, row=3, echo=1 -> index 40 -> intensity = 40/100 = 0.4
  auto const intensity = getIntensity(module, 2, 3, 1);

  EXPECT_FLOAT_EQ(intensity, 0.4F);
}

// Tests for getBeamProperties

TEST(telegram_type_1_ScanDataTest, getBeamProperties_returns_correct_value_for_first_element)
{
  auto const module = makeModule();

  auto const properties = getBeamProperties(module, 0, 0);

  EXPECT_TRUE(properties.isEmpty());
}

TEST(telegram_type_1_ScanDataTest, getBeamProperties_returns_correct_value_for_arbitrary_element)
{
  auto const module = makeModule();

  // column=3, row=2 -> beam index 17
  auto const properties = getBeamProperties(module, 3, 2);

  EXPECT_EQ(properties.underlyingValue(), 17U);
}

// Tests for getBeamAzimuth

TEST(telegram_type_1_ScanDataTest, getBeamAzimuth_returns_correct_value_for_first_element)
{
  auto const module = makeModule();

  auto const azimuth = getBeamAzimuth(module, 0, 0);

  EXPECT_FLOAT_EQ(azimuth.degrees(), 0.0F);
}

TEST(telegram_type_1_ScanDataTest, getBeamAzimuth_returns_correct_value_for_arbitrary_element)
{
  auto const module = makeModule();

  // column=3, row=2 -> beam index 17 -> azimuth = 17 degrees
  auto const azimuth = getBeamAzimuth(module, 3, 2);

  EXPECT_FLOAT_EQ(azimuth.degrees(), 17.0F);
}
