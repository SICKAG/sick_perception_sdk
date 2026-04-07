/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/quantities/Distance.hpp>

#include <cmath>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(DistanceTest, default_construction_is_nan)
{
  auto const distance = sick::Distance();
  EXPECT_TRUE(std::isnan(distance.meters()));
}

TEST(DistanceTest, fromMeters_converts_to_meters_roundtrip)
{
  auto const distance = sick::Distance::fromMeters(42.5f);
  EXPECT_FLOAT_EQ(distance.meters(), 42.5f);
}

TEST(DistanceTest, fromMillimeters_converts_to_meters_correctly)
{
  auto const distance = sick::Distance::fromMillimeters(42500.0f);
  EXPECT_FLOAT_EQ(distance.meters(), 42.5f);
}

TEST(DistanceTest, millimeters_converts_from_meters_correctly)
{
  auto const distance = sick::Distance::fromMeters(42.5f);
  EXPECT_FLOAT_EQ(distance.millimeters(), 42500.0f);
}

TEST(DistanceTest, fromMillimeters_converts_one_meter_correctly)
{
  auto const distance = sick::Distance::fromMillimeters(1000.0f);
  EXPECT_FLOAT_EQ(distance.meters(), 1.0f);
}

TEST(DistanceTest, less_than_operator_returns_true_for_smaller_distance)
{
  auto const d1 = sick::Distance::fromMeters(1.0f);
  auto const d2 = sick::Distance::fromMeters(2.0f);
  EXPECT_TRUE(d1 < d2);
  EXPECT_FALSE(d2 < d1);
}

TEST(DistanceTest, less_than_or_equal_operator_returns_true_for_smaller_or_equal_distance)
{
  auto const d1 = sick::Distance::fromMeters(1.0f);
  auto const d2 = sick::Distance::fromMeters(2.0f);
  auto const d3 = sick::Distance::fromMeters(1.0f);
  EXPECT_TRUE(d1 <= d2);
  EXPECT_TRUE(d1 <= d3);
}

TEST(DistanceTest, greater_than_operator_returns_true_for_larger_distance)
{
  auto const d1 = sick::Distance::fromMeters(2.0f);
  auto const d2 = sick::Distance::fromMeters(1.0f);
  EXPECT_TRUE(d1 > d2);
  EXPECT_FALSE(d2 > d1);
}

TEST(DistanceTest, greater_than_or_equal_operator_returns_true_for_larger_or_equal_distance)
{
  auto const d1 = sick::Distance::fromMeters(2.0f);
  auto const d2 = sick::Distance::fromMeters(1.0f);
  auto const d3 = sick::Distance::fromMeters(2.0f);
  EXPECT_TRUE(d1 >= d2);
  EXPECT_TRUE(d1 >= d3);
}

TEST(DistanceTest, negate_operator_returns_negated_value)
{
  auto const distance = sick::Distance::fromMeters(42.5f);
  auto const negated  = -distance;
  EXPECT_FLOAT_EQ(negated.meters(), -42.5f);
}

TEST(DistanceTest, divide_operator_divides_by_integer)
{
  auto const distance = sick::Distance::fromMeters(100.0f);
  auto const result   = distance / 4;
  EXPECT_FLOAT_EQ(result.meters(), 25.0f);
}

TEST(DistanceTest, literal_meter_constructs_correct_distance)
{
  using sick::literals::operator"" _m;
  auto const distance = 42.5_m;
  EXPECT_FLOAT_EQ(distance.meters(), 42.5f);
}

TEST(DistanceTest, fromMillimeters_converts_small_value_roundtrip)
{
  auto const smallMillimeters = 0.5f;
  auto const distance         = sick::Distance::fromMillimeters(smallMillimeters);
  auto const roundtripped     = distance.millimeters();
  EXPECT_FLOAT_EQ(roundtripped, smallMillimeters);
}

TEST(DistanceTest, to_string_returns_value_with_unit)
{
  auto const distance = sick::Distance::fromMeters(42.5f);
  EXPECT_THAT(std::to_string(distance), ::testing::HasSubstr("42.5"));
  EXPECT_THAT(std::to_string(distance), ::testing::EndsWith(" m"));
}
