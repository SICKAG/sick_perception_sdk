/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/quantities/AngularVelocity.hpp>

#include <cmath>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(AngularVelocityTest, default_construction_is_nan)
{
  auto const angVel = sick::AngularVelocity();
  EXPECT_TRUE(std::isnan(angVel.radiansPerSecond()));
}

TEST(AngularVelocityTest, fromRadiansPerSecond_converts_positive_number)
{
  auto const angVel = sick::AngularVelocity::fromRadiansPerSecond(1.5f);
  EXPECT_FLOAT_EQ(angVel.radiansPerSecond(), 1.5f);
}

TEST(AngularVelocityTest, fromRadiansPerSecond_converts_negative_number)
{
  auto const angVel = sick::AngularVelocity::fromRadiansPerSecond(-0.5f);
  EXPECT_FLOAT_EQ(angVel.radiansPerSecond(), -0.5f);
}

TEST(AngularVelocityTest, to_string_returns_value_with_unit)
{
  auto const angVel = sick::AngularVelocity::fromRadiansPerSecond(1.5f);
  EXPECT_THAT(std::to_string(angVel), ::testing::HasSubstr("1.5"));
  EXPECT_THAT(std::to_string(angVel), ::testing::EndsWith(" rad/s"));
}

