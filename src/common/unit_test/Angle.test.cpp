/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/numbers.hpp>
#include <sick_perception_sdk/common/quantities/Angle.hpp>

#include <cmath>
#include <gtest/gtest.h>

TEST(AngleTest, default_construction_is_nan)
{
  auto const angle = sick::Angle();
  EXPECT_TRUE(std::isnan(angle.radians()));
}

TEST(AngleTest, fromDegrees_converts_to_degrees_roundtrip)
{
  auto const angle = sick::Angle::fromDegrees(90.0f);
  EXPECT_NEAR(angle.degrees(), 90.0f, 1e-6f);
}

TEST(AngleTest, fromRadians_converts_to_radians_roundtrip)
{
  auto const angle = sick::Angle::fromRadians(sick::numbers::pi / 2.0f);
  EXPECT_NEAR(angle.radians(), sick::numbers::pi / 2.0f, 1e-6f);
}

TEST(AngleTest, fromDegrees_converts_to_radians_correctly)
{
  auto const angle = sick::Angle::fromDegrees(180.0f);
  EXPECT_NEAR(angle.radians(), sick::numbers::pi, 1e-6f);
}

TEST(AngleTest, fromRadians_converts_to_degrees_correctly)
{
  auto const angle = sick::Angle::fromRadians(sick::numbers::pi);
  EXPECT_NEAR(angle.degrees(), 180.0f, 1e-6f);
}

TEST(AngleTest, less_than_operator_returns_true_for_smaller_angle)
{
  auto const a1 = sick::Angle::fromDegrees(45.0f);
  auto const a2 = sick::Angle::fromDegrees(90.0f);
  EXPECT_TRUE(a1 < a2);
  EXPECT_FALSE(a2 < a1);
}

TEST(AngleTest, less_than_or_equal_operator_returns_true_for_smaller_or_equal_angle)
{
  auto const a1 = sick::Angle::fromDegrees(45.0f);
  auto const a2 = sick::Angle::fromDegrees(90.0f);
  auto const a3 = sick::Angle::fromDegrees(45.0f);
  EXPECT_TRUE(a1 <= a2);
  EXPECT_TRUE(a1 <= a3);
  EXPECT_FALSE(a2 <= a1);
}

TEST(AngleTest, greater_than_operator_returns_true_for_larger_angle)
{
  auto const a1 = sick::Angle::fromDegrees(90.0f);
  auto const a2 = sick::Angle::fromDegrees(45.0f);
  EXPECT_TRUE(a1 > a2);
  EXPECT_FALSE(a2 > a1);
}

TEST(AngleTest, greater_than_or_equal_operator_returns_true_for_larger_or_equal_angle)
{
  auto const a1 = sick::Angle::fromDegrees(90.0f);
  auto const a2 = sick::Angle::fromDegrees(45.0f);
  auto const a3 = sick::Angle::fromDegrees(90.0f);
  EXPECT_TRUE(a1 >= a2);
  EXPECT_TRUE(a1 >= a3);
  EXPECT_FALSE(a2 >= a1);
}

TEST(AngleTest, fromDegrees_converts_small_angle_roundtrip)
{
  auto const smallDegrees = 0.001f;
  auto const angle        = sick::Angle::fromDegrees(smallDegrees);
  auto const roundtripped = angle.degrees();
  EXPECT_NEAR(roundtripped, smallDegrees, 1e-8f);
}
