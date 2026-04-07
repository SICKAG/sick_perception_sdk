/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/quantities/Acceleration.hpp>

#include <cmath>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(AccelerationTest, default_construction_is_nan)
{
  auto const acceleration = sick::Acceleration();
  EXPECT_TRUE(std::isnan(acceleration.metersPerSecondSquared()));
}

TEST(AccelerationTest, fromMetersPerSecondSquared_converts_positive_number)
{
  auto const acceleration = sick::Acceleration::fromMetersPerSecondSquared(9.81f);
  EXPECT_FLOAT_EQ(acceleration.metersPerSecondSquared(), 9.81f);
}

TEST(AccelerationTest, fromMetersPerSecondSquared_converts_negative_number)
{
  auto const acceleration = sick::Acceleration::fromMetersPerSecondSquared(-5.5f);
  EXPECT_FLOAT_EQ(acceleration.metersPerSecondSquared(), -5.5f);
}

TEST(AccelerationTest, to_string_returns_value_with_unit)
{
  auto const acceleration = sick::Acceleration::fromMetersPerSecondSquared(9.81f);
  EXPECT_THAT(std::to_string(acceleration), ::testing::HasSubstr("9.81"));
  EXPECT_THAT(std::to_string(acceleration), ::testing::EndsWith("m/s\xC2\xB2"));
}
