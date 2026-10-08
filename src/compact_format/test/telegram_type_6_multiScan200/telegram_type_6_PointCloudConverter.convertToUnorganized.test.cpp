/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include "telegram_type_6_PointCloudConverterTestUtils.hpp"

#include <gtest/gtest.h>
#include <set>
#include <string>
#include <vector>

namespace {

using namespace sick::literals;
using namespace sick::test;
using FieldType = sick::point_cloud::PointField::FieldType;

struct FilterParam
{
  std::string name;
  std::function<void(sick::point_cloud::PointCloudConfiguration::Filters&)> filterMutator;
  std::size_t numberOfRows;
  std::size_t numberOfColumns;
  std::size_t numberOfEchoes;
  std::size_t expectedNumberOfPoints;
};

auto operator<<(std::ostream& os, FilterParam const& params) -> std::ostream&
{
  os << params.name;
  return os;
}

class FilterTest : public ::testing::TestWithParam<FilterParam>
{ };

TEST_P(FilterTest, convertToUnorganized_with_filter_returns_expected_number_of_points)
{
  // Given
  auto& p = GetParam();
  sick::point_cloud::PointCloudConfiguration config;
  p.filterMutator(config.filters);

  auto converter = makeConverter(config);

  auto const data =
    MultiScan200DataGenerator()                        //
      .withNumberOfRows(p.numberOfRows)                //
      .withNumberOfColumnsInSegment(p.numberOfColumns) //
      .withNumberOfEchoes(p.numberOfEchoes)            //
      .next();

  // When
  auto const pc = converter.convertToUnorganized(data);

  // Then
  EXPECT_EQ(p.expectedNumberOfPoints, pc.numberOfPoints());
}

INSTANTIATE_TEST_SUITE_P(
  telegram_type_6_PointCloudConverterTest,
  FilterTest,
  ::testing::Values(
    // clang-format off
    //                                                                                                     #rows #columns  #echoes  #points
    FilterParam {"echo_filter_multiple_values",  [](auto& filters) { filters.selectedEchos = {0, 2}; },      2,     2,        3,       8 }, // 2x2x3, keep 2 echoes => 8 points
    FilterParam {"echo_filter_single_value",     [](auto& filters) { filters.selectedEchos = {1}; },         3,     3,        3,       9 }, // 3x3x3, keep 1 echo => 9 points
    FilterParam {"echo_filter_no_values",        [](auto& filters) { filters.selectedEchos = {}; },          3,     3,        3,      27 }, // 3x3x3, don't filter echoes => 27 points
    FilterParam {"echo_filter_out_of_bounds",    [](auto& filters) { filters.selectedEchos = {10, 20}; },    2,     2,        2,       0 }, // 2x2x2, echo indexes not in data => 0 points
    FilterParam {"layer_filter_multiple_values", [](auto& filters) { filters.selectedLayers = {1, 3}; },     5,     2,        1,       4 }, // 5x2x1, keep 2 layers => 4 points
    FilterParam {"layer_filter_out_of_bounds",   [](auto& filters) { filters.selectedLayers = {100, 200}; }, 5,     2,        1,       0 } // 5x2x1, layer indexes not in data => 0 points
    // clang-format on
  ),
  [](auto const& info) {
    return info.param.name;
  }
);

// ----------------------------------------------------------------------------------------------------
// Individual tests
// ----------------------------------------------------------------------------------------------------
TEST(telegram_type_6_PointCloudConverterTest, convertToUnorganized_with_impossible_range_filter_returns_empty_point_cloud)
{
  sick::point_cloud::PointCloudConfiguration config;
  config.filters.range = sick::Interval<sick::Distance> {sick::Distance::fromMillimeters(5000.0), sick::Distance::fromMillimeters(1000.0), false};

  auto converter = makeConverter(config);

  auto const data =
    MultiScan200DataGenerator()        //
      .withNumberOfRows(3)             //
      .withNumberOfColumnsInSegment(3) //
      .withNumberOfEchoes(1)           //
      .next();
  auto const pc = converter.convertToUnorganized(data);

  EXPECT_EQ(0, pc.numberOfPoints());
}

TEST(telegram_type_6_PointCloudConverterTest, convertToUnorganized_with_all_supported_fields_preserves_selected_point_values)
{
  auto const config = createConfigurationWithAllSupportedFields();
  auto converter    = makeConverter(config);

  auto data =
    MultiScan200DataGenerator()        //
      .withNumberOfRows(3)             //
      .withNumberOfColumnsInSegment(4) //
      .withNumberOfEchoes(2)           //
      .withIntensity(true)             //
      .withEchoProperties(true)        //
      .next();

  auto const selectedPointIndex = data.computeIndex(1, 2, 1);
  sick::BitField<sick::compact::multiscan200::EchoProperties> echoProperties;
  echoProperties.set(sick::compact::multiscan200::EchoProperties::Reflector);
  echoProperties.set(sick::compact::multiscan200::EchoProperties::Blooming);
  data.echoProperties[selectedPointIndex] = echoProperties;

  auto const pc = converter.convertToUnorganized(data);

  expectHasFields(
    pc,
    {
      FieldType::X,
      FieldType::Y,
      FieldType::Z,
      FieldType::Range,
      FieldType::Azimuth,
      FieldType::Elevation,
      FieldType::Intensity,
      FieldType::TimeOffsetNanoseconds,
      FieldType::TimeOffsetSeconds,
      FieldType::Ring,
      FieldType::LayerIndex,
      FieldType::ColumnIndex,
      FieldType::EchoIndex,
      FieldType::Properties,
    }
  );

  expectSelectedPointValuesMatchInput(pc, data, 2, 1, 1);
}

TEST(telegram_type_6_PointCloudConverterTest, convertToUnorganized_with_range_filter_excludes_points_outside_interval)
{
  // Given
  sick::point_cloud::PointCloudConfiguration config;
  config.filters.range = sick::Interval<sick::Distance> {1500_mm, 2500_mm};

  auto converter = makeConverter(config);

  // This configuration will give distances in the range from 1000 mm to 1990 mm.
  auto const data =
    MultiScan200DataGenerator()         //
      .withNumberOfRows(10)             //
      .withNumberOfColumnsInSegment(10) //
      .withNumberOfEchoes(1)            //
      .next();

  // When
  auto const pc = converter.convertToUnorganized(data);

  // Then
  EXPECT_LT(pc.numberOfPoints(), 100); // would be 100 if no points were filtered out
  EXPECT_GT(pc.numberOfPoints(), 0);
}

TEST(telegram_type_6_PointCloudConverterTest, convertToUnorganized_with_inverted_range_filter_excludes_points_inside_interval)
{
  // Given
  sick::point_cloud::PointCloudConfiguration config;
  config.filters.range = sick::Interval<sick::Distance> {1300_mm, 3000_mm, true};

  auto converter = makeConverter(config);

  // This configuration will give distances in the range from 1000 mm to 1440 mm.
  auto const data =
    MultiScan200DataGenerator()        //
      .withNumberOfRows(5)             //
      .withNumberOfColumnsInSegment(5) //
      .withNumberOfEchoes(1)           //
      .next();

  // When
  auto const pc = converter.convertToUnorganized(data);

  // Then
  EXPECT_LT(pc.numberOfPoints(), 25); // would be 25 if no points were filtered out
  EXPECT_GT(pc.numberOfPoints(), 0);
}

TEST(telegram_type_6_PointCloudConverterTest, convertToUnorganized_with_azimuth_filter_returns_expected_number_of_points)
{
  // Given
  sick::point_cloud::PointCloudConfiguration config;
  config.filters.azimuth = sick::Interval<sick::Angle> {4_deg, 8_deg};

  auto converter = makeConverter(config);

  // This configuration will give azimuths in the range from 0 deg to 19 deg with 1 deg increments.
  auto const data =
    MultiScan200DataGenerator()         //
      .withNumberOfRows(4)              //
      .withNumberOfColumnsInSegment(20) //
      .withNumberOfColumnsInFrame(360)  //
      .withNumberOfEchoes(1)            //
      .next();

  // When
  auto const pc = converter.convertToUnorganized(data);

  // Then
  // Azimuth 4 deg .. 8 deg includes 5 points, each with 4 rows and 1 echo => 20 points.
  EXPECT_EQ(20, pc.numberOfPoints());
}

TEST(telegram_type_6_PointCloudConverterTest, convertToUnorganized_with_elevation_returns_expected_number_of_points)
{
  // Given
  sick::point_cloud::PointCloudConfiguration config;
  config.filters.elevation = sick::Interval<sick::Angle> {sick::Angle::fromDegrees(-5.0), sick::Angle::fromDegrees(5.0), false};

  auto converter = makeConverter(config);

  // This configuration will give elevations in the range from -15 deg to 15 deg with 2 deg increments.
  auto const data =
    MultiScan200DataGenerator()         //
      .withNumberOfRows(16)             //
      .withNumberOfColumnsInSegment(10) //
      .withNumberOfEchoes(1)            //
      .next();

  // When
  auto const pc = converter.convertToUnorganized(data);

  // Then
  // Elevation -5 deg .. 5 deg includes 6 points, each with 10 columns and 1 echo => 60 points.
  EXPECT_EQ(60, pc.numberOfPoints());
}

TEST(telegram_type_6_PointCloudConverterTest, convertToUnorganized_with_intensity_filter_returns_expected_number_of_points)
{
  // Given
  sick::point_cloud::PointCloudConfiguration config;
  config.filters.intensity = sick::Interval<float> {105.0F, 115.0F, false};

  auto converter = makeConverter(config);

  // This configuration will give intensities in the range from 100.0 to 109.0 with increments of 1.0.
  auto const data =
    MultiScan200DataGenerator()         //
      .withNumberOfRows(10)             //
      .withNumberOfColumnsInSegment(10) //
      .withNumberOfEchoes(1)            //
      .withIntensity(true)              //
      .next();

  // When
  auto const pc = converter.convertToUnorganized(data);

  // Then
  // Intensity 105 .. 115 includes 5 points, each with 10 columns and 1 echo => 50 points.
  EXPECT_EQ(50, pc.numberOfPoints());
}

TEST(telegram_type_6_PointCloudConverterTest, convertToUnorganized_with_combined_filters_reduces_number_of_points)
{
  // Given
  sick::point_cloud::PointCloudConfiguration config;
  config.filters.selectedEchos  = {0};
  config.filters.selectedLayers = {1, 2, 3};
  config.filters.range          = sick::Interval<sick::Distance> {1000_mm, 5000_mm};

  auto converter = makeConverter(config);

  auto const data =
    MultiScan200DataGenerator()        //
      .withNumberOfRows(5)             //
      .withNumberOfColumnsInSegment(5) //
      .withNumberOfEchoes(2)           //
      .next();

  // When
  auto const pc = converter.convertToUnorganized(data);

  // Then
  EXPECT_LT(pc.numberOfPoints(), 50);
  EXPECT_GT(pc.numberOfPoints(), 0);
}

} // namespace
