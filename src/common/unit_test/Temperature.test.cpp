/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/quantities/Temperature.hpp>

#include <cmath>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(TemperatureTest, default_construction_is_nan)
{
  auto const temp = sick::Temperature();
  EXPECT_TRUE(std::isnan(temp.degreesCelsius()));
}

TEST(TemperatureTest, fromDegreesCelsius_converts_positive_number)
{
  auto const temp = sick::Temperature::fromDegreesCelsius(25.5f);
  EXPECT_FLOAT_EQ(temp.degreesCelsius(), 25.5f);
}

TEST(TemperatureTest, fromDegreesCelsius_converts_negative_number)
{
  auto const temp = sick::Temperature::fromDegreesCelsius(-10.0f);
  EXPECT_FLOAT_EQ(temp.degreesCelsius(), -10.0f);
}

TEST(TemperatureTest, literal_degrees_celsius_constructs_integer_value)
{
  using sick::literals::operator"" _degC;
  auto const temp = 25_degC;
  EXPECT_FLOAT_EQ(temp.degreesCelsius(), 25.0f);
}

TEST(TemperatureTest, literal_degrees_celsius_constructs_floating_point_value)
{
  using sick::literals::operator"" _degC;
  auto const temp = 25.5_degC;
  EXPECT_FLOAT_EQ(temp.degreesCelsius(), 25.5f);
}

TEST(TemperatureTest, fromDegreesCelsius_converts_to_degrees_roundtrip)
{
  auto const original_degrees  = static_cast<sick::Temperature::value_type>(42.5f);
  auto const temp              = sick::Temperature::fromDegreesCelsius(original_degrees);
  auto const retrieved_degrees = temp.degreesCelsius();
  EXPECT_FLOAT_EQ(retrieved_degrees, original_degrees);
}

TEST(TemperatureTest, to_string_returns_value_with_unit)
{
  auto const temp = sick::Temperature::fromDegreesCelsius(25.5f);
  EXPECT_THAT(std::to_string(temp), ::testing::HasSubstr("25.5"));
  EXPECT_THAT(std::to_string(temp), ::testing::EndsWith(" degC"));
}

