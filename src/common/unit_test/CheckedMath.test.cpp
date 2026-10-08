/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/CheckedMath.hpp>

#include <limits>

#include <gtest/gtest.h>

TEST(CheckedMathTest, checkedAdd_with_2_arguments_adds_values_without_overflow)
{
  constexpr unsigned v1 = 10, v2 = 20;
  constexpr unsigned expected = 30;
  EXPECT_EQ(sick::checkedAdd(v1, v2), expected);
}

TEST(CheckedMathTest, checkedAdd_with_3_arguments_adds_values_without_overflow)
{
  constexpr unsigned v1 = 10, v2 = 20, v3 = 30;
  constexpr unsigned expected = 60;
  EXPECT_EQ(sick::checkedAdd(v1, v2, v3), expected);
}

TEST(CheckedMathTest, checkedAdd_with_4_arguments_adds_values_without_overflow)
{
  constexpr unsigned v1 = 10, v2 = 20, v3 = 30, v4 = 40;
  constexpr unsigned expected = 100;
  EXPECT_EQ(sick::checkedAdd(v1, v2, v3, v4), expected);
}

TEST(CheckedMathTest, checkedAdd_returns_max_for_boundary_case)
{
  constexpr unsigned maxValue = std::numeric_limits<unsigned>::max();
  constexpr unsigned v1       = maxValue - 1;
  constexpr unsigned v2       = 1;

  EXPECT_EQ(sick::checkedAdd(v1, v2), maxValue);
}

TEST(CheckedMathTest, checkedAdd_throws_for_overflow)
{
  EXPECT_THROW(sick::checkedAdd(std::numeric_limits<unsigned>::max(), 1u), std::overflow_error);
}

TEST(CheckedMathTest, checkedMultiply_with_2_arguments_multiplies_values_without_overflow)
{
  constexpr unsigned v1 = 12, v2 = 3;
  constexpr unsigned expected = 36;
  EXPECT_EQ(sick::checkedMultiply(v1, v2), expected);
}

TEST(CheckedMathTest, checkedMultiply_with_3_arguments_multiplies_values_without_overflow)
{
  constexpr unsigned v1 = 2, v2 = 3, v3 = 4;
  constexpr unsigned expected = 24;
  EXPECT_EQ(sick::checkedMultiply(v1, v2, v3), expected);
}

TEST(CheckedMathTest, checkedMultiply_with_4_arguments_multiplies_values_without_overflow)
{
  constexpr unsigned v1 = 2, v2 = 3, v3 = 4, v4 = 5;
  constexpr unsigned expected = 120;
  EXPECT_EQ(sick::checkedMultiply(v1, v2, v3, v4), expected);
}

TEST(CheckedMathTest, checkedMultiply_returns_max_for_boundary_case)
{
  constexpr unsigned maxValue = std::numeric_limits<unsigned>::max();
  constexpr unsigned left     = maxValue / 8;
  constexpr unsigned right    = 8;

  EXPECT_EQ(sick::checkedMultiply(left, right), maxValue - (maxValue % 8));
}

TEST(CheckedMathTest, checkedMultiply_throws_for_overflow)
{
  constexpr unsigned maxValue = std::numeric_limits<unsigned>::max();
  EXPECT_THROW(sick::checkedMultiply((maxValue / 2) + 1, 2u), std::overflow_error);
}

TEST(CheckedMathTest, checkedMultiply_handles_zero_without_overflow)
{
  constexpr unsigned maxValue = std::numeric_limits<unsigned>::max();
  EXPECT_EQ(sick::checkedMultiply(0u, maxValue), 0);
}
