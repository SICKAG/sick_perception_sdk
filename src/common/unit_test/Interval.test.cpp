/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/Interval.hpp>

#include <cmath>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace {

struct EmptyIntervalTestParams
{
  float value;
  bool expectedContains;
  std::string description;
};

struct ConfiguredIntervalTestParams
{
  float min;
  float max;
  float value;
  bool expectedContains;
  std::string description;
};

constexpr auto nanVal = std::numeric_limits<float>::quiet_NaN();
constexpr auto posInf = std::numeric_limits<float>::infinity();
constexpr auto negInf = -std::numeric_limits<float>::infinity();

// Overloading the << operator prevents access to uninitialized memory in gtest (valgrind).
auto operator<<(std::ostream& os, EmptyIntervalTestParams const& params) -> std::ostream&
{
  os << params.description;
  return os;
}

auto operator<<(std::ostream& os, ConfiguredIntervalTestParams const& params) -> std::ostream&
{
  os << params.description;
  return os;
}

} // namespace

TEST(IntervalTest, default_construction_is_empty)
{
  auto const interval = sick::Interval<int> {};
  EXPECT_TRUE(interval.isEmpty());
}

TEST(IntervalTest, reversed_min_max_is_considered_empty)
{
  constexpr auto min    = 10.0f;
  constexpr auto max    = 0.0f;
  constexpr auto invert = false;
  auto const interval   = sick::Interval<float> {min, max, invert};
  EXPECT_TRUE(interval.isEmpty());
}

class EmptyIntervalTest : public testing::TestWithParam<EmptyIntervalTestParams>
{ };

TEST_P(EmptyIntervalTest, contains)
{
  auto const p        = GetParam();
  auto const interval = sick::Interval<float>();
  EXPECT_EQ(p.expectedContains, interval.contains(p.value));
}

INSTANTIATE_TEST_SUITE_P(
  Interval,
  EmptyIntervalTest,
  testing::Values(
    // clang-format off
    //                         value  expected result of contains()
    EmptyIntervalTestParams {  -0.1f, true, "returns_true_for_numeric_value" },
    EmptyIntervalTestParams { nanVal, true, "returns_true_for_value_nan" },
    EmptyIntervalTestParams { posInf, true, "returns_true_for_value_pos_inf" },
    EmptyIntervalTestParams { negInf, true, "returns_true_for_value_neg_inf" }
    //
    // clang-format on
  ),
  [](testing::TestParamInfo<EmptyIntervalTestParams> const& info) {
    return info.param.description;
  }
);

class ConfiguredIntervalTest : public testing::TestWithParam<ConfiguredIntervalTestParams>
{ };

TEST_P(ConfiguredIntervalTest, contains)
{
  auto const p                   = GetParam();
  auto const intervalNotInverted = sick::Interval<float>(p.min, p.max, false);
  EXPECT_EQ(p.expectedContains, intervalNotInverted.contains(p.value));

  auto const intervalInverted = sick::Interval<float>(p.min, p.max, true);
  EXPECT_EQ(!p.expectedContains, intervalInverted.contains(p.value));
}

constexpr auto minValue = std::numeric_limits<float>::lowest();
constexpr auto maxValue = std::numeric_limits<float>::max();

INSTANTIATE_TEST_SUITE_P(
  Interval,
  ConfiguredIntervalTest,
  testing::Values(
    // clang-format off
    //                                 min       max    value  expected result of contains()
    ConfiguredIntervalTestParams {     0.0f,    10.0f,   5.0f, true,  "returns_true_for_value_in_range" },
    ConfiguredIntervalTestParams {     0.0f,    10.0f,  -0.1f, false, "returns_false_for_value_out_of_range_1" },
    ConfiguredIntervalTestParams {     0.0f,    10.0f,  10.1f, false, "returns_false_for_value_out_of_range_2" },
    ConfiguredIntervalTestParams {     0.0f,    10.0f, nanVal, false, "returns_false_for_value_nan" },
    ConfiguredIntervalTestParams {     0.0f,    10.0f, posInf, false, "returns_false_for_value_pos_inf" },
    ConfiguredIntervalTestParams {     0.0f,    10.0f, negInf, false, "returns_false_for_value_neg_inf" },
    ConfiguredIntervalTestParams { minValue, maxValue,   5.0f, true,  "returns_true_for_max_range_and_value_in_range" },
    ConfiguredIntervalTestParams {   negInf, posInf,     5.0f, true,  "returns_true_for_inf_range_and_value_in_range" },
    ConfiguredIntervalTestParams {   negInf, posInf,   posInf, true,  "returns_true_for_inf_range_and_value_pos_inf" },
    ConfiguredIntervalTestParams {   negInf, posInf,   negInf, true,  "returns_true_for_inf_range_and_value_neg_inf" }
    //
    // clang-format on
  ),
  [](testing::TestParamInfo<ConfiguredIntervalTestParams> const& info) {
    return info.param.description;
  }
);
