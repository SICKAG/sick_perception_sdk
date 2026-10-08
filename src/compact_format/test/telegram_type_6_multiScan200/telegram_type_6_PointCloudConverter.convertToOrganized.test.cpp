/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include "telegram_type_6_PointCloudConverterTestUtils.hpp"

#include <algorithm>
#include <gtest/gtest.h>
#include <limits>
#include <set>
#include <string>
#include <vector>

namespace {

using namespace sick::literals;
using namespace sick::test;
using FieldType = sick::point_cloud::PointField::FieldType;

// ----------------------------------------------------------------------------------------------------
// Test that enabling a field in the PointCloudConfiguration results in the expected field being present
// in the output point cloud.
// ----------------------------------------------------------------------------------------------------
struct EnableFieldParams
{
  std::string enabledFieldName;
  std::string expectedFieldNames;
  std::function<void(sick::point_cloud::PointCloudConfiguration::Fields&)> configMutator;
  std::vector<FieldType> expectedFields;
};

auto operator<<(std::ostream& os, EnableFieldParams const& params) -> std::ostream&
{
  os << params.enabledFieldName << "_creates_" << params.expectedFieldNames;
  return os;
}

class EnableFieldTest : public ::testing::TestWithParam<EnableFieldParams>
{ };

TEST_P(EnableFieldTest, convertToOrganized_with_enabled_field_creates_expected_fields)
{
  // Given
  sick::point_cloud::PointCloudConfiguration config;
  config.fields.enableCartesian = false;
  GetParam().configMutator(config.fields);

  auto converter = makeConverter(config);

  auto const data =
    MultiScan200DataGenerator()        //
      .withNumberOfRows(1)             //
      .withNumberOfColumnsInSegment(1) //
      .withNumberOfEchoes(1)           //
      .withIntensity(true)             //
      .next();

  // When
  auto const pc = converter.convertToOrganized(data);

  // Then
  expectHasFields(pc, GetParam().expectedFields);
}

INSTANTIATE_TEST_SUITE_P(
  telegram_type_6_PointCloudConverterTest,
  EnableFieldTest,
  ::testing::Values(
    // clang-format off
    EnableFieldParams {"cartesian",   "xyz",         [](auto& fields) { fields.enableCartesian = true; },   {FieldType::X, FieldType::Y, FieldType::Z}},
    EnableFieldParams {"spherical",   "spherical",   [](auto& fields) { fields.enableSpherical = true; },   {FieldType::Range, FieldType::Azimuth, FieldType::Elevation}},
    EnableFieldParams {"intensity",   "intensity",   [](auto& fields) { fields.enableIntensity = true; },   {FieldType::Intensity}},
    EnableFieldParams {"time_offset", "time_offset", [](auto& fields) { fields.enableTimeOffset = true; },  {FieldType::TimeOffsetNanoseconds, FieldType::TimeOffsetSeconds}},
    EnableFieldParams {"ring",        "ring",        [](auto& fields) { fields.enableRing = true; },        {FieldType::Ring}},
    EnableFieldParams {"layer",       "layer",       [](auto& fields) { fields.enableLayerIndex = true; },  {FieldType::LayerIndex}},
    EnableFieldParams {"echo",        "echo",        [](auto& fields) { fields.enableEchoIndex = true; },   {FieldType::EchoIndex}},
    EnableFieldParams {"column",      "column",      [](auto& fields) { fields.enableColumnIndex = true; }, {FieldType::ColumnIndex}} //
    // clang-format on
  ),
  [](auto const& info) {
    return info.param.enabledFieldName + "_creates_" + info.param.expectedFieldNames;
  }
);

// ----------------------------------------------------------------------------------------------------
// Test that enabling a field in the PointCloudConfiguration but not providing the corresponding
// payload in the MultiScan200Data results in the field being omitted from the output point cloud.
// ----------------------------------------------------------------------------------------------------
struct OptionalFieldUnavailableParam
{
  std::string fieldName;
  std::function<void(sick::point_cloud::PointCloudConfiguration::Fields&)> enableField;
  FieldType missingField;
};

auto operator<<(std::ostream& os, OptionalFieldUnavailableParam const& params) -> std::ostream&
{
  os << params.fieldName;
  return os;
}

class OptionalFieldUnavailableTest : public ::testing::TestWithParam<OptionalFieldUnavailableParam>
{ };

TEST_P(OptionalFieldUnavailableTest, convertToOrganized_with_optional_field_enabled_but_payload_missing_omits_field)
{
  // Given
  sick::point_cloud::PointCloudConfiguration config;
  GetParam().enableField(config.fields); // Let the parameter function enable the desired fields
  auto converter  = makeConverter(config);
  auto const data = makeDefaultData();

  // When
  auto const pc = converter.convertToOrganized(data);

  // Then
  expectDoesNotHaveFields(pc, {GetParam().missingField});
  EXPECT_EQ(4, pc.numberOfPoints());
}

INSTANTIATE_TEST_SUITE_P(
  telegram_type_6_PointCloudConverterTest,
  OptionalFieldUnavailableTest,
  ::testing::Values(
    // clang-format off
    OptionalFieldUnavailableParam { "intensity",  [](auto& fields) { fields.enableIntensity = true; },  FieldType::Intensity},
    OptionalFieldUnavailableParam { "properties", [](auto& fields) { fields.enableProperties = true; }, FieldType::Properties}//
    // clang-format on
  ),
  [](auto const& info) {
    return info.param.fieldName;
  }
);

// ----------------------------------------------------------------------------------------------------
// Test that applying dimensional filters results in the expected point cloud dimensions and number of
// points, i.e. that the point cloud is shrunk according to the filter settings.
// ----------------------------------------------------------------------------------------------------
struct DimensionalFilterParam
{
  std::string name;
  std::function<void(sick::point_cloud::PointCloudConfiguration::Filters&)> filterMutator;
  std::size_t expectedWidth;
  std::size_t expectedHeight;
  std::size_t expectedEchoesPerBeam;
};

auto operator<<(std::ostream& os, DimensionalFilterParam const& params) -> std::ostream&
{
  os << params.name;
  return os;
}

class DimensionalFilterTest : public ::testing::TestWithParam<DimensionalFilterParam>
{ };

TEST_P(DimensionalFilterTest, convertToOrganized_with_dimensional_filters_shrinks_point_cloud)
{
  // Given
  auto& p = GetParam();
  sick::point_cloud::PointCloudConfiguration config;
  p.filterMutator(config.filters);

  auto converter = makeConverter(config);

  auto const data =
    MultiScan200DataGenerator()         //
      .withNumberOfRows(7)              //
      .withNumberOfColumnsInSegment(10) //
      .withNumberOfColumnsInFrame(360)  //
      .withNumberOfEchoes(3)            //
      .next();

  // When
  auto const pc = converter.convertToOrganized(data);

  // Then
  auto const expectedNumberOfPoints = p.expectedWidth * p.expectedHeight * p.expectedEchoesPerBeam;
  EXPECT_EQ(p.expectedWidth, pc.width());
  EXPECT_EQ(p.expectedHeight, pc.height());
  EXPECT_EQ(p.expectedEchoesPerBeam, pc.numberOfEchoesPerBeam());
  EXPECT_EQ(expectedNumberOfPoints, pc.numberOfPoints());
}

INSTANTIATE_TEST_SUITE_P(
  telegram_type_6_PointCloudConverterTest,
  DimensionalFilterTest,
  ::testing::Values(
    // clang-format off
    //                                                                                                                          w  h #echoes
    DimensionalFilterParam { "echo",                [](auto& f) { f.selectedEchos = {1}; },                                    10, 7,   1   },
    DimensionalFilterParam { "layer",               [](auto& f) { f.selectedLayers = {1, 3}; },                                10, 2,   3   },
    DimensionalFilterParam { "azimuth",             [](auto& f) { f.azimuth = sick::Interval<sick::Angle> {4_deg, 8_deg};},     5, 7,   3   },
    DimensionalFilterParam { "elevation",           [](auto& f) { f.elevation = sick::Interval<sick::Angle> {-1_deg, 6_deg};}, 10, 2,   3   },
    DimensionalFilterParam { "layer_and_elevation", [](auto& f) {
        f.selectedLayers = {1, 2, 3};
        f.elevation      = sick::Interval<sick::Angle> {-1_deg, 6_deg};
      },                                                                                                                       10, 1,   3 } //

    // clang-format on
  ),
  [](auto const& info) {
    return info.param.name + "_filter";
  }
);

// ----------------------------------------------------------------------------------------------------
// Individual tests
// ----------------------------------------------------------------------------------------------------
TEST(
  telegram_type_6_PointCloudConverterTest,
  convertToOrganized_with_combined_layer_and_elevation_filter_without_overlap_returns_empty_cloud_with_preserved_non_filtered_dimensions
)
{
  // Given
  sick::point_cloud::PointCloudConfiguration config;
  config.filters.selectedLayers = {0};
  config.filters.elevation      = sick::Interval<sick::Angle> {10_deg, 12_deg};

  auto converter = makeConverter(config);

  auto const data =
    MultiScan200DataGenerator()        //
      .withNumberOfRows(7)             //
      .withNumberOfColumnsInSegment(2) //
      .withNumberOfEchoes(2)           //
      .next();

  // When
  auto const pc = converter.convertToOrganized(data);

  // Then
  EXPECT_TRUE(pc.isEmpty());
  EXPECT_EQ(0, pc.numberOfPoints());
  EXPECT_EQ(2, pc.width());
  EXPECT_EQ(0, pc.height());
  EXPECT_EQ(2, pc.numberOfEchoesPerBeam());
}

TEST(telegram_type_6_PointCloudConverterTest, convertToOrganized_with_range_filter_sets_filtered_points_to_nan_and_sets_density_to_invalid_points_contained)
{
  // Given
  sick::point_cloud::PointCloudConfiguration config;
  config.filters.range = sick::Interval<sick::Distance> {sick::Distance::fromMillimeters(1500.0), sick::Distance::fromMillimeters(2500.0), false};

  auto converter = makeConverter(config);

  auto const data =
    MultiScan200DataGenerator()         //
      .withNumberOfRows(10)             //
      .withNumberOfColumnsInSegment(10) //
      .withNumberOfEchoes(1)            //
      .next();

  // When
  auto const pc = converter.convertToOrganized(data);

  // Then
  auto const firstPointIndex = pc.pointIndex(0, 0, 0);
  auto const [x, y, z]       = pc.getCartesian(firstPointIndex);
  EXPECT_TRUE(std::isnan(x));
  EXPECT_TRUE(std::isnan(y));
  EXPECT_TRUE(std::isnan(z));

  expectContainsAtLeastOneValidPoint(pc);
}

TEST(telegram_type_6_PointCloudConverterTest, convertToOrganized_with_zero_rows_and_columns_returns_empty_point_cloud)
{
  // Given
  sick::point_cloud::PointCloudConfiguration config;
  auto converter = makeConverter(config);

  auto const data =
    MultiScan200DataGenerator()        //
      .withNumberOfRows(0)             //
      .withNumberOfColumnsInSegment(0) //
      .next();

  // When
  auto const pc = converter.convertToOrganized(data);

  // Then
  EXPECT_TRUE(pc.isEmpty());
}

TEST(telegram_type_6_PointCloudConverterTest, convertToOrganized_with_rows_columns_and_echoes_returns_expected_number_of_points)
{
  // Given
  sick::point_cloud::PointCloudConfiguration config;
  auto converter = makeConverter(config);

  auto const data =
    MultiScan200DataGenerator()        //
      .withNumberOfRows(4)             //
      .withNumberOfColumnsInSegment(5) //
      .withNumberOfEchoes(2)           //
      .next();

  // When
  auto const pc = converter.convertToOrganized(data);

  // Then
  EXPECT_EQ(40, pc.numberOfPoints());
}

TEST(telegram_type_6_PointCloudConverterTest, convertToOrganized_with_single_echo_returns_expected_number_of_points)
{
  // Given
  sick::point_cloud::PointCloudConfiguration config;
  auto converter = makeConverter(config);

  auto const data =
    MultiScan200DataGenerator()        //
      .withNumberOfRows(3)             //
      .withNumberOfColumnsInSegment(3) //
      .withNumberOfEchoes(1)           //
      .next();

  // When
  auto const pc = converter.convertToOrganized(data);

  // Then
  EXPECT_EQ(9, pc.numberOfPoints());
}

TEST(telegram_type_6_PointCloudConverterTest, convertToOrganized_with_zero_echoes_returns_empty_point_cloud)
{
  // Given
  sick::point_cloud::PointCloudConfiguration config;
  auto converter = makeConverter(config);

  auto const data =
    MultiScan200DataGenerator()        //
      .withNumberOfRows(5)             //
      .withNumberOfColumnsInSegment(5) //
      .withNumberOfEchoes(0)           //
      .next();

  // When
  auto const pc = converter.convertToOrganized(data);

  // Then
  EXPECT_EQ(0, pc.numberOfPoints());
}

TEST(telegram_type_6_PointCloudConverterTest, convertToOrganized_with_distance_scaling_factor_scales_cartesian_and_range_fields)
{
  // Given
  sick::point_cloud::PointCloudConfiguration config;
  config.distanceScalingFactor  = 1000.0F;
  config.fields.enableSpherical = true;

  auto converter = makeConverter(config);

  auto const data =
    MultiScan200DataGenerator()        //
      .withNumberOfRows(1)             //
      .withNumberOfColumnsInSegment(1) //
      .withNumberOfEchoes(1)           //
      .next();

  // When
  auto const pc = converter.convertToOrganized(data);

  // Then
  ASSERT_EQ(1, pc.numberOfPoints());

  auto const distanceMeters = data.distances[0].meters();
  auto const expectedRange  = distanceMeters * config.distanceScalingFactor;

  EXPECT_FLOAT_EQ(expectedRange, pc.getRange(0));
  auto const [x, y, z] = pc.getCartesian(0);
  auto const norm      = std::sqrt(x * x + y * y + z * z);
  EXPECT_FLOAT_EQ(expectedRange, norm);
}

TEST(telegram_type_6_PointCloudConverterTest, convertToOrganized_with_zero_distance_scaling_factor_sets_cartesian_and_range_fields_to_zero)
{
  // Given
  sick::point_cloud::PointCloudConfiguration config;
  config.distanceScalingFactor  = 0.0F;
  config.fields.enableSpherical = true;

  auto converter = makeConverter(config);

  auto const data =
    MultiScan200DataGenerator()        //
      .withNumberOfRows(1)             //
      .withNumberOfColumnsInSegment(1) //
      .withNumberOfEchoes(1)           //
      .next();

  // When
  auto const pc = converter.convertToOrganized(data);

  // Then
  ASSERT_EQ(1, pc.numberOfPoints());
  EXPECT_FLOAT_EQ(0.0F, pc.getRange(0));

  auto const [x, y, z] = pc.getCartesian(0);
  EXPECT_FLOAT_EQ(0.0F, x);
  EXPECT_FLOAT_EQ(0.0F, y);
  EXPECT_FLOAT_EQ(0.0F, z);
}

TEST(telegram_type_6_PointCloudConverterTest, convertToOrganized_with_invalid_geometry_size_throws_runtime_error)
{
  // Given
  sick::point_cloud::PointCloudConfiguration config;
  auto converter = makeConverter(config);

  auto data =
    MultiScan200DataGenerator()        //
      .withNumberOfRows(3)             //
      .withNumberOfColumnsInSegment(3) //
      .withNumberOfEchoes(1)           //
      .next();

  data.geometry.azimuths.resize(2);

  // When / Then
  EXPECT_THROW(converter.convertToOrganized(data), std::runtime_error);
}

TEST(telegram_type_6_PointCloudConverterTest, convertToOrganized_preserves_nan_distance_from_input)
{
  // Given
  sick::point_cloud::PointCloudConfiguration config;
  auto converter = makeConverter(config);

  auto data         = makeDefaultData();
  data.distances[0] = sick::Distance::fromMillimeters(std::numeric_limits<double>::quiet_NaN());

  // When
  auto const pc = converter.convertToOrganized(data);

  // Then
  EXPECT_EQ(4, pc.numberOfPoints());

  auto const firstPointIndex = pc.pointIndex(0, 0, 0);
  auto const [x, y, z]       = pc.getCartesian(firstPointIndex);
  EXPECT_TRUE(std::isnan(x));
  EXPECT_TRUE(std::isnan(y));
  EXPECT_TRUE(std::isnan(z));
}

TEST(telegram_type_6_PointCloudConverterTest, convertToOrganized_preserves_inf_distance_from_input)
{
  // Given
  sick::point_cloud::PointCloudConfiguration config;
  auto converter = makeConverter(config);

  auto data         = makeDefaultData();
  data.distances[0] = sick::Distance::fromMillimeters(std::numeric_limits<double>::infinity());

  // When
  auto const pc = converter.convertToOrganized(data);

  // Then
  EXPECT_EQ(4, pc.numberOfPoints());

  auto const firstPointIndex = pc.pointIndex(0, 0, 0);
  auto const [x, y, z]       = pc.getCartesian(firstPointIndex);
  EXPECT_FALSE(std::isfinite(x)); // inf is not always carried over to inf for the cartesian coordinates (0 * inf = -nan)
  EXPECT_FALSE(std::isfinite(y)); // inf is not always carried over to inf for the cartesian coordinates (0 * inf = -nan)
  EXPECT_FALSE(std::isfinite(z)); // inf is not always carried over to inf for the cartesian coordinates (0 * inf = -nan)
}

TEST(telegram_type_6_PointCloudConverterTest, convertToOrganized_accepts_negative_distances)
{
  // Negative distances don't make sense in the real world but the converter must not handle them differently than positive distances.

  // Given
  sick::point_cloud::PointCloudConfiguration config;
  auto converter = makeConverter(config);

  auto data         = makeDefaultData();
  data.distances[0] = sick::Distance::fromMillimeters(-1000.0);

  // When
  auto const pc = converter.convertToOrganized(data);

  // Then
  EXPECT_EQ(4, pc.numberOfPoints());

  auto const firstPointIndex = pc.pointIndex(0, 0, 0);
  auto const [x, y, z]       = pc.getCartesian(firstPointIndex);
  EXPECT_LE(x, 0);
  EXPECT_LE(y, 0);
  EXPECT_LE(z, 0);
}

TEST(telegram_type_6_PointCloudConverterTest, convertToOrganized_with_nan_angles_marks_affected_point_invalid)
{
  // Given
  sick::point_cloud::PointCloudConfiguration config;
  auto converter = makeConverter(config);

  auto data                   = makeDefaultData();
  data.geometry.azimuths[0]   = sick::Angle::fromRadians(std::numeric_limits<double>::quiet_NaN());
  data.geometry.elevations[0] = sick::Angle::fromRadians(std::numeric_limits<double>::quiet_NaN());

  // When
  auto const pc = converter.convertToOrganized(data);

  // Then
  EXPECT_EQ(4, pc.numberOfPoints());

  auto const firstPointIndex = pc.pointIndex(0, 0, 0);
  auto const [x, y, z]       = pc.getCartesian(firstPointIndex);
  EXPECT_TRUE(std::isnan(x));
  EXPECT_TRUE(std::isnan(y));
  EXPECT_TRUE(std::isnan(z));
}

TEST(telegram_type_6_PointCloudConverterTest, convertToOrganized_with_enabled_fields_sets_point_data_size_consistently)
{
  // Given
  sick::point_cloud::PointCloudConfiguration config;
  config.fields.enableCartesian = true;
  config.fields.enableIntensity = true;

  auto converter = makeConverter(config);

  auto const data =
    MultiScan200DataGenerator()        //
      .withNumberOfRows(1)             //
      .withNumberOfColumnsInSegment(1) //
      .withNumberOfEchoes(1)           //
      .withIntensity(true)             //
      .next();

  // When
  auto const pc = converter.convertToOrganized(data);

  // Then
  EXPECT_GT(pc.pointSizeBytes(), 0);
  EXPECT_EQ(pc.rawByteSize(), pc.numberOfPoints() * pc.pointSizeBytes());
}

TEST(telegram_type_6_PointCloudConverterTest, convertToOrganized_with_non_empty_data_sets_timestamp_from_segment_metadata)
{
  // Given
  sick::point_cloud::PointCloudConfiguration config;
  auto converter = makeConverter(config);

  auto const data =
    MultiScan200DataGenerator()        //
      .withNumberOfRows(1)             //
      .withNumberOfColumnsInSegment(1) //
      .withNumberOfEchoes(1)           //
      .next();

  // When
  auto const pc = converter.convertToOrganized(data);

  // Then
  EXPECT_EQ(pc.timestamp(), data.segmentMetaData.frameTimestamp);
}

TEST(telegram_type_6_PointCloudConverterTest, convertToOrganized_with_multiple_calls_returns_independent_results)
{
  // Given
  sick::point_cloud::PointCloudConfiguration config;
  auto converter = makeConverter(config);

  auto generator =
    MultiScan200DataGenerator()        //
      .withNumberOfRows(2)             //
      .withNumberOfColumnsInSegment(2) //
      .withNumberOfEchoes(1)           //
      .withNumberOfSegmentsPerFrame(1);

  // When
  auto const data1 = generator.next();
  auto const pc1   = converter.convertToOrganized(data1);

  auto const data2 = generator.next();
  auto const pc2   = converter.convertToOrganized(data2);

  // Then
  EXPECT_EQ(4, pc1.numberOfPoints());
  EXPECT_EQ(4, pc2.numberOfPoints());
  EXPECT_NE(pc1.timestamp(), pc2.timestamp());
}

} // namespace
