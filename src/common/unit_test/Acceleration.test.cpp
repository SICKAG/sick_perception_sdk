/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/quantities/Acceleration.hpp>

#include <cmath>
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
