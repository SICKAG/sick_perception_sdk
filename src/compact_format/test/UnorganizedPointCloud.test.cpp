/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloud.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloudBuilder.hpp>

#include <gtest/gtest.h>

using DataType  = sick::point_cloud::PointField::DataType;
using FieldType = sick::point_cloud::PointField::FieldType;

namespace {

auto createBuilder(sick::Timestamp timestamp = sick::Timestamp::fromMicrosecondsSinceEpoch(1000)) -> sick::point_cloud::UnorganizedPointCloudBuilder
{
  sick::point_cloud::UnorganizedPointCloudBuilder builder(
    {                         // Desired fields
     {FieldType::X,           //
      FieldType::Y,           //
      FieldType::Z,           //
                              // Leave a gap to test indexing behavior
      FieldType::PulseWidth}, //
     // Available fields
     {FieldType::X, //
      FieldType::Y, //
      FieldType::Z, //
      FieldType::PulseWidth}
    },
    timestamp,
    1
  );
  return builder;
}

} // namespace

TEST(UnorganizedPointCloudTest, field_access_returns_value_if_it_exists)
{
  auto builder = createBuilder();

  builder.beginPoint();
  builder.writeNextFieldValueOrIgnore(FieldType::X, 1.0f);
  builder.writeNextFieldValueOrIgnore(FieldType::Y, 2.0f);
  builder.writeNextFieldValueOrIgnore(FieldType::Z, 3.0f);
  builder.writeNextFieldValueOrIgnore(FieldType::PulseWidth, 4.0f);

  auto const cloud = builder.build();

  auto const [x, y, z] = cloud.getCartesian(0);
  EXPECT_FLOAT_EQ(1.0f, x);
  EXPECT_FLOAT_EQ(2.0f, y);
  EXPECT_FLOAT_EQ(3.0f, z);
  EXPECT_FLOAT_EQ(4.0f, cloud.getPulseWidth(0));
}

TEST(UnorganizedPointCloudTest, field_access_fails_if_point_cloud_is_empty)
{
  auto builder = createBuilder();

  auto const cloud = builder.build();

  EXPECT_THROW(cloud.getIntensity(0), std::out_of_range);
}

TEST(UnorganizedPointCloudTest, field_access_fails_if_field_does_not_exist)
{
  auto builder = createBuilder();

  builder.beginPoint();
  builder.writeNextFieldValueOrIgnore(FieldType::X, 1.0f);
  builder.writeNextFieldValueOrIgnore(FieldType::Y, 2.0f);
  builder.writeNextFieldValueOrIgnore(FieldType::Z, 3.0f);

  auto const cloud = builder.build();

  EXPECT_THROW(cloud.getIntensity(0), std::out_of_range);
}
