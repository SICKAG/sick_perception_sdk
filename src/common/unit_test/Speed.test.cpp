/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/quantities/Speed.hpp>

#include <cmath>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(SpeedTest, fromMetersPerSecond_converts_positive_number)
{
  auto const speed = sick::Speed::fromMetersPerSecond(25.0f);
  EXPECT_FLOAT_EQ(speed.metersPerSecond(), 25.0f);
}

TEST(SpeedTest, fromMetersPerSecond_converts_zero)
{
  auto const speed = sick::Speed::fromMetersPerSecond(0.0f);
  EXPECT_FLOAT_EQ(speed.metersPerSecond(), 0.0f);
}

TEST(SpeedTest, default_construction_is_nan)
{
  auto const speed = sick::Speed();
  EXPECT_TRUE(std::isnan(speed.metersPerSecond()));
}

TEST(SpeedTest, to_string_returns_value_with_unit)
{
  auto const speed = sick::Speed::fromMetersPerSecond(25.0f);
  EXPECT_THAT(std::to_string(speed), ::testing::HasSubstr("25"));
  EXPECT_THAT(std::to_string(speed), ::testing::EndsWith(" m/s"));
}
