/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/PointCloud/PointCloudAttributes.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloudBuilder.hpp>

#include <gtest/gtest.h>

using DataType  = sick::point_cloud::PointField::DataType;
using Density   = sick::point_cloud::Density;
using FieldType = sick::point_cloud::PointField::FieldType;

namespace {

auto createBuilder(sick::Timestamp timestamp = sick::Timestamp::fromMicrosecondsSinceEpoch(1000)) -> sick::point_cloud::UnorganizedPointCloudBuilder
{
  sick::point_cloud::UnorganizedPointCloudBuilder builder(
    {{FieldType::X, FieldType::Y, FieldType::Z}, {FieldType::X, FieldType::Y, FieldType::Z}},
    timestamp,
    1
  );
  return builder;
}

} // namespace

TEST(UnorganizedPointCloudBuilderTest, build_returns_empty_point_cloud_when_no_points_added)
{
  auto builder = createBuilder();

  auto const cloud = builder.build();

  EXPECT_EQ(0, cloud.numberOfPoints());
  EXPECT_TRUE(cloud.isEmpty());
}

TEST(UnorganizedPointCloudBuilderTest, build_returns_point_cloud_with_single_point)
{
  auto builder = createBuilder();

  builder.beginPoint();
  builder.writeNextFieldValueOrIgnore(FieldType::X, 1.0f);
  builder.writeNextFieldValueOrIgnore(FieldType::Y, 2.0f);
  builder.writeNextFieldValueOrIgnore(FieldType::Z, 3.0f);

  auto const cloud = builder.build();

  EXPECT_EQ(1, cloud.numberOfPoints());
  EXPECT_EQ(Density::AllPointsValid, cloud.density());

  auto const [x, y, z] = cloud.getCartesian(0);
  EXPECT_FLOAT_EQ(1.0f, x);
  EXPECT_FLOAT_EQ(2.0f, y);
  EXPECT_FLOAT_EQ(3.0f, z);
}

TEST(UnorganizedPointCloudBuilderTest, build_returns_point_cloud_with_multiple_points)
{
  constexpr std::size_t numberOfPoints = 5;
  sick::point_cloud::UnorganizedPointCloudBuilder builder(
    {{FieldType::X, FieldType::Y, FieldType::Z}, {FieldType::X, FieldType::Y, FieldType::Z}},
    sick::Timestamp(),
    numberOfPoints
  );

  for (auto i = 0; i < numberOfPoints; ++i)
  {
    builder.beginPoint();
    builder.writeNextFieldValueOrIgnore(FieldType::X, static_cast<float>(i));
    builder.writeNextFieldValueOrIgnore(FieldType::Y, static_cast<float>(i * 2));
    builder.writeNextFieldValueOrIgnore(FieldType::Z, static_cast<float>(i * 3));
  }

  auto const cloud = builder.build();

  EXPECT_EQ(numberOfPoints, cloud.numberOfPoints());

  {
    auto const [x, y, z] = cloud.getCartesian(0);
    EXPECT_FLOAT_EQ(0.0f, x);
    EXPECT_FLOAT_EQ(0.0f, y);
    EXPECT_FLOAT_EQ(0.0f, z);
  }

  {
    auto const [x, y, z] = cloud.getCartesian(4);
    EXPECT_FLOAT_EQ(4.0f, x);
    EXPECT_FLOAT_EQ(8.0f, y);
    EXPECT_FLOAT_EQ(12.0f, z);
  }
}

TEST(UnorganizedPointCloudBuilderTest, build_preserves_timestamp)
{
  auto builder = createBuilder(sick::Timestamp::fromMicrosecondsSinceEpoch(123456789));

  auto const cloud = builder.build();

  EXPECT_EQ(sick::Timestamp::fromMicrosecondsSinceEpoch(123456789), cloud.timestamp());
}

struct FieldTestParams
{
  std::set<FieldType> fieldTypes;
};

// Overloading the << operator prevents access to uninitialized memory in gtest (valgrind).
auto operator<<(std::ostream& os, FieldTestParams const& params) -> std::ostream&
{
  os << std::to_string(params.fieldTypes.size()) << "_fields";
  return os;
}

class UnorganizedPointCloudBuilderTest : public testing::TestWithParam<FieldTestParams>
{ };

TEST_P(UnorganizedPointCloudBuilderTest, build_includes_field_when_enabled)
{
  auto const& [fieldTypes] = GetParam();
  sick::point_cloud::UnorganizedPointCloudBuilder builder({fieldTypes, fieldTypes}, sick::Timestamp(), 1);

  auto const cloud = builder.build();

  ASSERT_EQ(fieldTypes.size(), cloud.fields().size());
  for (auto i = 0; i < fieldTypes.size(); ++i)
  {
    EXPECT_EQ(*std::next(fieldTypes.begin(), i), cloud.fields()[i].fieldType);
  }
}

INSTANTIATE_TEST_SUITE_P(
  Fields,
  UnorganizedPointCloudBuilderTest,
  testing::Values(
    FieldTestParams {{FieldType::X}},                     //
    FieldTestParams {{FieldType::Y}},                     //
    FieldTestParams {{FieldType::Z}},                     //
    FieldTestParams {{FieldType::Range}},                 //
    FieldTestParams {{FieldType::Azimuth}},               //
    FieldTestParams {{FieldType::Elevation}},             //
    FieldTestParams {{FieldType::Intensity}},             //
    FieldTestParams {{FieldType::TimeOffsetNanoseconds}}, //
    FieldTestParams {{FieldType::TimeOffsetSeconds}},     //
    FieldTestParams {{FieldType::Ring}},                  //
    FieldTestParams {{FieldType::LayerId}},               //
    FieldTestParams {{FieldType::EchoIndex}},             //
    FieldTestParams {{FieldType::IsReflector}},           //
    FieldTestParams {{FieldType::HasBlooming}},           //
    FieldTestParams {{FieldType::PulseWidth}},            //
    FieldTestParams {
      {FieldType::X,                     //
       FieldType::Y,                     //
       FieldType::Z,                     //
       FieldType::Range,                 //
       FieldType::Azimuth,               //
       FieldType::Elevation,             //
       FieldType::Intensity,             //
       FieldType::TimeOffsetNanoseconds, //
       FieldType::TimeOffsetSeconds,     //
       FieldType::Ring,                  //
       FieldType::LayerId,               //
       FieldType::EchoIndex,             //
       FieldType::IsReflector,           //
       FieldType::HasBlooming,           //
       FieldType::PulseWidth}
    }
  )
);

TEST(UnorganizedPointCloudBuilderTest, build_sets_sequential_field_offsets)
{
  std::set<FieldType> fieldTypes {FieldType::X, FieldType::Y, FieldType::Z, FieldType::Intensity, FieldType::Ring};
  sick::point_cloud::UnorganizedPointCloudBuilder builder({fieldTypes, fieldTypes}, sick::Timestamp(), 1);
  auto const cloud = builder.build();

  ASSERT_EQ(5, cloud.fields().size());
  EXPECT_EQ(0, cloud.fields()[0].offset);  // X
  EXPECT_EQ(4, cloud.fields()[1].offset);  // Y
  EXPECT_EQ(8, cloud.fields()[2].offset);  // Z
  EXPECT_EQ(12, cloud.fields()[3].offset); // Intensity
  EXPECT_EQ(16, cloud.fields()[4].offset); // Ring
}

TEST(UnorganizedPointCloudBuilderTest, build_sets_correct_data_types_for_fields)
{
  std::set<FieldType> fieldTypes {FieldType::X, FieldType::Y, FieldType::Z, FieldType::TimeOffsetNanoseconds, FieldType::TimeOffsetSeconds, FieldType::Ring};
  sick::point_cloud::UnorganizedPointCloudBuilder builder({fieldTypes, fieldTypes}, sick::Timestamp(), 1);
  auto const cloud = builder.build();

  ASSERT_EQ(6, cloud.fields().size());
  EXPECT_EQ(DataType::Float32, cloud.fields()[0].dataType); // X
  EXPECT_EQ(DataType::Float32, cloud.fields()[1].dataType); // Y
  EXPECT_EQ(DataType::Float32, cloud.fields()[2].dataType); // Z
  EXPECT_EQ(DataType::Uint32, cloud.fields()[3].dataType);  // TimeOffsetNanoseconds
  EXPECT_EQ(DataType::Uint32, cloud.fields()[4].dataType);  // TimeOffsetSeconds
  EXPECT_EQ(DataType::Uint8, cloud.fields()[5].dataType);   // Ring
}

TEST(UnorganizedPointCloudBuilderTest, write_handles_different_value_types)
{
  std::set<FieldType> fieldTypes {FieldType::X, FieldType::Y, FieldType::Z, FieldType::TimeOffsetNanoseconds, FieldType::TimeOffsetSeconds, FieldType::Ring};
  sick::point_cloud::UnorganizedPointCloudBuilder builder({fieldTypes, fieldTypes}, sick::Timestamp(), 1);

  builder.beginPoint();
  builder.writeNextFieldValueOrIgnore(FieldType::X, 1.0f);
  builder.writeNextFieldValueOrIgnore(FieldType::Y, 2.0f);
  builder.writeNextFieldValueOrIgnore(FieldType::Z, 3.0f);
  builder.writeNextFieldValueOrIgnore(FieldType::TimeOffsetNanoseconds, std::uint32_t {4});
  builder.writeNextFieldValueOrIgnore(FieldType::TimeOffsetSeconds, std::uint32_t {5});
  builder.writeNextFieldValueOrIgnore(FieldType::Ring, std::uint8_t {6});

  auto const cloud = builder.build();

  auto const [x, y, z] = cloud.getCartesian(0);
  EXPECT_FLOAT_EQ(1.0f, x);
  EXPECT_FLOAT_EQ(2.0f, y);
  EXPECT_FLOAT_EQ(3.0f, z);
  auto const [timeOffsetSeconds, timeOffsetNanoseconds] = cloud.getTimeOffset(0);
  EXPECT_EQ(5, timeOffsetSeconds);
  EXPECT_EQ(4, timeOffsetNanoseconds);
  EXPECT_EQ(6, cloud.getRing(0));
}

TEST(UnorganizedPointCloudBuilderTest, build_sets_density_to_all_points_valid)
{
  auto builder = createBuilder();

  builder.beginPoint();
  builder.writeNextFieldValueOrIgnore(FieldType::X, 1.0f);
  builder.writeNextFieldValueOrIgnore(FieldType::Y, 2.0f);
  builder.writeNextFieldValueOrIgnore(FieldType::Z, 3.0f);

  auto const cloud = builder.build();

  EXPECT_EQ(Density::AllPointsValid, cloud.density());
}

TEST(UnorganizedPointCloudBuilderTest, setPointCloudTimestamp_updates_timestamp)
{
  auto const initialTs = sick::Timestamp::fromMicrosecondsSinceEpoch(100);
  auto const updatedTs = sick::Timestamp::fromMicrosecondsSinceEpoch(999999);

  auto builder = createBuilder(initialTs);

  builder.setPointCloudTimestamp(updatedTs);
  auto const cloud = builder.build();

  EXPECT_EQ(updatedTs, cloud.timestamp());
}

TEST(UnorganizedPointCloudBuilderTest, beginPoint_throws_if_max_number_of_points_exceeded)
{
  auto builder = createBuilder();

  builder.beginPoint();
  builder.writeNextFieldValueOrIgnore(FieldType::X, 1.0f);
  builder.writeNextFieldValueOrIgnore(FieldType::Y, 2.0f);
  builder.writeNextFieldValueOrIgnore(FieldType::Z, 3.0f);

  EXPECT_THROW(builder.beginPoint(), std::runtime_error);
}

TEST(UnorganizedPointCloudBuilderTest, growBy_allows_adding_more_points)
{
  auto builder = createBuilder();

  builder.beginPoint();
  builder.writeNextFieldValueOrIgnore(FieldType::X, 1.0f);
  builder.writeNextFieldValueOrIgnore(FieldType::Y, 2.0f);
  builder.writeNextFieldValueOrIgnore(FieldType::Z, 3.0f);

  builder.growBy(2); // Increase max number of points to 3

  builder.beginPoint();
  builder.writeNextFieldValueOrIgnore(FieldType::X, 4.0f);
  builder.writeNextFieldValueOrIgnore(FieldType::Y, 5.0f);
  builder.writeNextFieldValueOrIgnore(FieldType::Z, 6.0f);

  builder.beginPoint();
  builder.writeNextFieldValueOrIgnore(FieldType::X, 7.0f);
  builder.writeNextFieldValueOrIgnore(FieldType::Y, 8.0f);
  builder.writeNextFieldValueOrIgnore(FieldType::Z, 9.0f);

  auto const cloud = builder.build();

  EXPECT_EQ(3, cloud.numberOfPoints());
  {
    auto const [x, y, z] = cloud.getCartesian(0);
    EXPECT_FLOAT_EQ(1.0f, x);
    EXPECT_FLOAT_EQ(2.0f, y);
    EXPECT_FLOAT_EQ(3.0f, z);
  }

  {
    auto const [x, y, z] = cloud.getCartesian(1);
    EXPECT_FLOAT_EQ(4.0f, x);
    EXPECT_FLOAT_EQ(5.0f, y);
    EXPECT_FLOAT_EQ(6.0f, z);
  }

  {
    auto const [x, y, z] = cloud.getCartesian(2);
    EXPECT_FLOAT_EQ(7.0f, x);
    EXPECT_FLOAT_EQ(8.0f, y);
    EXPECT_FLOAT_EQ(9.0f, z);
  }
}

