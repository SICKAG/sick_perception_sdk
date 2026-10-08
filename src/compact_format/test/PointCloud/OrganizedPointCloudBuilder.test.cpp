/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/PointCloud/OrganizedPointCloudBuilder.hpp>

#include <cmath>
#include <gtest/gtest.h>

using DataType  = sick::point_cloud::PointField::DataType;
using FieldType = sick::point_cloud::PointField::FieldType;

namespace {

auto createBuilder(std::size_t width = 4, std::size_t height = 3, std::size_t numberOfEchoesPerBeam = 2) -> sick::point_cloud::OrganizedPointCloudBuilder
{
  return sick::point_cloud::OrganizedPointCloudBuilder(
    sick::point_cloud::OrganizedPointCloudBuilder::FieldConfig {{FieldType::X, FieldType::Y, FieldType::Z}, {FieldType::X, FieldType::Y, FieldType::Z}},
    sick::Timestamp::fromMicrosecondsSinceEpoch(1000),
    width,
    height,
    numberOfEchoesPerBeam
  );
}

// Builds a fully populated grid so OrganizedPointCloudBuilder::build() succeeds. The point values are
// irrelevant here; only the grid geometry matters for pointIndex() tests.
auto buildFullGrid(std::size_t width = 4, std::size_t height = 3, std::size_t numberOfEchoesPerBeam = 2) -> sick::point_cloud::OrganizedPointCloud
{
  auto builder = createBuilder(width, height, numberOfEchoesPerBeam);
  for (std::size_t i = 0; i < width * height * numberOfEchoesPerBeam; ++i)
  {
    builder.writeInvalidPoint();
  }
  return builder.build();
}

} // namespace

TEST(OrganizedPointCloudBuilderTest, build_fails_if_not_enough_points_are_added)
{
  auto builder = createBuilder();

  // Don't add any points, just call build immediately.
  // This must fail because the builder expects more than 1 point based on the layout.

  EXPECT_THROW(builder.build(), std::runtime_error);

  // Add a point and try again.
  // This must also fail because we still haven't added all points.
  builder.beginPoint();
  builder.writeNextFieldValueOrIgnore(FieldType::X, 1.0f);
  builder.writeNextFieldValueOrIgnore(FieldType::Y, 2.0f);
  builder.writeNextFieldValueOrIgnore(FieldType::Z, 3.0f);
  EXPECT_THROW(builder.build(), std::runtime_error);
}

TEST(OrganizedPointCloudBuilderTest, build_returns_point_cloud_with_single_point)
{
  constexpr std::size_t width                 = 1;
  constexpr std::size_t height                = 1;
  constexpr std::size_t numberOfEchoesPerBeam = 1;

  auto builder = createBuilder(width, height, numberOfEchoesPerBeam);

  builder.beginPoint();
  builder.writeNextFieldValueOrIgnore(FieldType::X, 1.0f);
  builder.writeNextFieldValueOrIgnore(FieldType::Y, 2.0f);
  builder.writeNextFieldValueOrIgnore(FieldType::Z, 3.0f);

  auto const cloud = builder.build();

  EXPECT_EQ(1, cloud.numberOfPoints());
  EXPECT_EQ(1, cloud.width());
  EXPECT_EQ(1, cloud.height());
  EXPECT_EQ(12, cloud.rawByteSize());

  auto const [x, y, z] = cloud.getCartesian(0);

  EXPECT_FLOAT_EQ(1.0f, x);
  EXPECT_FLOAT_EQ(2.0f, y);
  EXPECT_FLOAT_EQ(3.0f, z);
}

TEST(OrganizedPointCloudBuilderTest, build_returns_point_cloud_with_multiple_points)
{
  constexpr std::size_t width                 = 5;
  constexpr std::size_t height                = 1;
  constexpr std::size_t numberOfEchoesPerBeam = 1;

  auto builder = createBuilder(width, height, numberOfEchoesPerBeam);

  for (int i = 0; i < 5; ++i)
  {
    builder.beginPoint();
    builder.writeNextFieldValueOrIgnore(FieldType::X, static_cast<float>(i));
    builder.writeNextFieldValueOrIgnore(FieldType::Y, static_cast<float>(i * 2));
    builder.writeNextFieldValueOrIgnore(FieldType::Z, static_cast<float>(i * 3));
  }

  auto const cloud = builder.build();

  EXPECT_EQ(5, cloud.numberOfPoints());
  EXPECT_EQ(5, cloud.width());
  EXPECT_EQ(1, cloud.height());
  EXPECT_EQ(60, cloud.rawByteSize());

  // Verify last point
  auto const [x, y, z] = cloud.getCartesian(4);
  EXPECT_FLOAT_EQ(4.0f, x);
  EXPECT_FLOAT_EQ(8.0f, y);
  EXPECT_FLOAT_EQ(12.0f, z);
}

TEST(OrganizedPointCloudBuilderTest, write_invalid_point_writes_nan_for_floats)
{
  constexpr std::size_t width         = 1;
  constexpr std::size_t height        = 1;
  constexpr std::size_t echoesPerBeam = 1;
  auto builder                        = createBuilder(width, height, echoesPerBeam);

  builder.writeInvalidPoint();

  auto const cloud = builder.build();

  auto const [x, y, z] = cloud.getCartesian(0);
  EXPECT_TRUE(std::isnan(x));
  EXPECT_TRUE(std::isnan(y));
  EXPECT_TRUE(std::isnan(z));
}

TEST(OrganizedPointCloudBuilderTest, build_handles_mixed_valid_and_invalid_points)
{
  constexpr std::size_t width         = 3;
  constexpr std::size_t height        = 1;
  constexpr std::size_t echoesPerBeam = 1;

  auto builder = createBuilder(width, height, echoesPerBeam);

  builder.beginPoint();
  builder.writeNextFieldValueOrIgnore(FieldType::X, 1.0f);
  builder.writeNextFieldValueOrIgnore(FieldType::Y, 2.0f);
  builder.writeNextFieldValueOrIgnore(FieldType::Z, 3.0f);

  builder.writeInvalidPoint();

  builder.beginPoint();
  builder.writeNextFieldValueOrIgnore(FieldType::X, 4.0f);
  builder.writeNextFieldValueOrIgnore(FieldType::Y, 5.0f);
  builder.writeNextFieldValueOrIgnore(FieldType::Z, 6.0f);

  auto const cloud = builder.build();

  EXPECT_EQ(3, cloud.numberOfPoints());

  // Check second point is NaN
  auto const [x1, y1, z1] = cloud.getCartesian(1);
  EXPECT_TRUE(std::isnan(x1));
  EXPECT_TRUE(std::isnan(y1));
  EXPECT_TRUE(std::isnan(z1));

  // Check third point
  auto const [x2, y2, z2] = cloud.getCartesian(2);
  EXPECT_FLOAT_EQ(4.0f, x2);
  EXPECT_FLOAT_EQ(5.0f, y2);
  EXPECT_FLOAT_EQ(6.0f, z2);
}

TEST(OrganizedPointCloudBuilderTest, build_preserves_timestamp)
{
  sick::point_cloud::OrganizedPointCloudBuilder builder(
    sick::point_cloud::OrganizedPointCloudBuilder::FieldConfig {{FieldType::X, FieldType::Y, FieldType::Z}, {FieldType::X, FieldType::Y, FieldType::Z}},
    sick::Timestamp::fromMicrosecondsSinceEpoch(123456789),
    0, // No points necessary for this test
    0, // No points necessary for this test
    1
  );

  auto const cloud = builder.build();

  EXPECT_EQ(sick::Timestamp::fromMicrosecondsSinceEpoch(123456789), cloud.timestamp());
}

TEST(OrganizedPointCloudBuilderTest, build_preserves_fields)
{
  sick::point_cloud::OrganizedPointCloudBuilder builder(
    sick::point_cloud::OrganizedPointCloudBuilder::FieldConfig {{FieldType::X, FieldType::Y, FieldType::Z}, {FieldType::X, FieldType::Y, FieldType::Z}},
    sick::Timestamp::fromMicrosecondsSinceEpoch(123456789),
    0, // No points necessary for this test
    0, // No points necessary for this test
    1
  );
  auto const cloud = builder.build();

  ASSERT_EQ(3, cloud.fields().size());
  EXPECT_EQ(FieldType::X, cloud.fields()[0].fieldType);
  EXPECT_EQ(FieldType::Y, cloud.fields()[1].fieldType);
  EXPECT_EQ(FieldType::Z, cloud.fields()[2].fieldType);
}

TEST(OrganizedPointCloudBuilderTest, write_next_field_value_or_ignore_silently_ignores_more_fields_than_expected)
{
  auto builder = createBuilder(1, 1, 1);

  builder.beginPoint();
  builder.writeNextFieldValueOrIgnore(FieldType::X, 1.0f);
  builder.writeNextFieldValueOrIgnore(FieldType::Y, 2.0f);
  builder.writeNextFieldValueOrIgnore(FieldType::Z, 3.0f);

  builder.writeNextFieldValueOrIgnore(FieldType::Range, 4.0f);

  auto const cloud     = builder.build();
  auto const [x, y, z] = cloud.getCartesian(cloud.pointIndex(0, 0, 0));

  EXPECT_FLOAT_EQ(1.0F, x);
  EXPECT_FLOAT_EQ(2.0F, y);
  EXPECT_FLOAT_EQ(3.0F, z);
}

TEST(OrganizedPointCloudTest, point_index_matches_row_major_echo_innermost_layout)
{
  // Storage layout (documented and produced by the builder/converters) is row-major with echoes
  // innermost: a row spans width * echoes points, a beam's echoes are contiguous, so
  //   index = (row * width + column) * echoes + echo
  // This mirrors the ground-truth formula used in the type-6 converter test utilities.
  constexpr std::size_t width         = 4;
  constexpr std::size_t height        = 3;
  constexpr std::size_t echoesPerBeam = 2;

  auto const cloud = buildFullGrid(width, height, echoesPerBeam);

  EXPECT_EQ(0, cloud.pointIndex(0, 0, 0));

  // Echo is the fastest-varying dimension.
  EXPECT_EQ(1, cloud.pointIndex(0, 0, 1));
  // Column stride is the number of echoes.
  EXPECT_EQ(echoesPerBeam, cloud.pointIndex(1, 0, 0));
  // Row stride is width * echoes. This is the term the previous implementation got wrong.
  EXPECT_EQ(width * echoesPerBeam, cloud.pointIndex(0, 1, 0));
  // Last valid coordinate maps to the last point.
  EXPECT_EQ(width * height * echoesPerBeam - 1, cloud.pointIndex(width - 1, height - 1, echoesPerBeam - 1));
}

TEST(OrganizedPointCloudTest, point_index_round_trips_written_points)
{
  constexpr std::size_t width         = 4;
  constexpr std::size_t height        = 3;
  constexpr std::size_t echoesPerBeam = 2;

  auto encode = [](std::size_t row, std::size_t column, std::size_t echo) -> float {
    return static_cast<float>(row * 100 + column * 10 + echo);
  };

  auto builder = createBuilder(width, height, echoesPerBeam);

  // Points are written sequentially. Writing in row -> column -> echo order lays them out in the
  // exact storage order, so the k-th written point must be addressable via pointIndex(column, row, echo).
  for (std::size_t row = 0; row < height; ++row)
  {
    for (std::size_t column = 0; column < width; ++column)
    {
      for (std::size_t echo = 0; echo < echoesPerBeam; ++echo)
      {
        builder.beginPoint();
        builder.writeNextFieldValueOrIgnore(FieldType::X, encode(row, column, echo));
        builder.writeNextFieldValueOrIgnore(FieldType::Y, 0.0f);
        builder.writeNextFieldValueOrIgnore(FieldType::Z, 0.0f);
      }
    }
  }

  auto const cloud = builder.build();

  for (std::size_t row = 0; row < height; ++row)
  {
    for (std::size_t column = 0; column < width; ++column)
    {
      for (std::size_t echo = 0; echo < echoesPerBeam; ++echo)
      {
        EXPECT_FLOAT_EQ(encode(row, column, echo), cloud.getX(cloud.pointIndex(column, row, echo)));
      }
    }
  }
}

TEST(OrganizedPointCloudTest, point_index_throws_on_out_of_range_coordinates)
{
  constexpr std::size_t width         = 4;
  constexpr std::size_t height        = 3;
  constexpr std::size_t echoesPerBeam = 2;

  auto const cloud = buildFullGrid(width, height, echoesPerBeam);

  EXPECT_THROW(static_cast<void>(cloud.pointIndex(width, 0, 0)), std::out_of_range);
  EXPECT_THROW(static_cast<void>(cloud.pointIndex(0, height, 0)), std::out_of_range);
  EXPECT_THROW(static_cast<void>(cloud.pointIndex(0, 0, echoesPerBeam)), std::out_of_range);

  // Highest column index must be accepted (it was rejected by the previous width/echoes derivation).
  EXPECT_NO_THROW(static_cast<void>(cloud.pointIndex(width - 1, height - 1, echoesPerBeam - 1)));
}
