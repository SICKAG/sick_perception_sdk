/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/quantities/Duration.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(DurationTest, default_construction_is_zero)
{
  auto const duration = sick::Duration();
  EXPECT_EQ(duration.microseconds(), 0);
}

TEST(DurationTest, fromSeconds_converts_to_microseconds)
{
  auto const duration = sick::Duration::fromSeconds(5);
  EXPECT_EQ(duration.microseconds(), 5'000'000);
}

TEST(DurationTest, fromMilliseconds_converts_to_microseconds)
{
  auto const duration = sick::Duration::fromMilliseconds(5000);
  EXPECT_EQ(duration.microseconds(), 5'000'000);
}

TEST(DurationTest, microseconds_converts_from_microseconds)
{
  auto const duration = sick::Duration::fromMicroseconds(5'000'000);
  EXPECT_EQ(duration.microseconds(), 5'000'000);
}

TEST(DurationTest, seconds_converts_from_microseconds)
{
  auto const duration = sick::Duration::fromMicroseconds(5'000'000);
  EXPECT_EQ(duration.seconds(), 5);
}

TEST(DurationTest, milliseconds_converts_from_microseconds)
{
  auto const duration = sick::Duration::fromMicroseconds(5'000'000);
  EXPECT_EQ(duration.milliseconds(), 5'000);
}

TEST(DurationTest, nanoseconds_converts_from_microseconds)
{
  auto const duration = sick::Duration::fromMicroseconds(1'000);
  EXPECT_EQ(duration.nanoseconds(), 1'000'000);
}

TEST(DurationTest, fromSeconds_converts_one_second_to_one_million_microseconds)
{
  auto const duration = sick::Duration::fromSeconds(1);
  EXPECT_EQ(duration.microseconds(), 1'000'000);
}

TEST(DurationTest, literal_seconds_constructs_correct_duration)
{
  using sick::literals::operator"" _s;
  auto const duration = 42_s;
  EXPECT_EQ(duration.seconds(), 42);
}

TEST(DurationTest, literal_milliseconds_constructs_correct_duration)
{
  using sick::literals::operator"" _ms;
  auto const duration = 5000_ms;
  EXPECT_EQ(duration.seconds(), 5);
}

TEST(DurationTest, literal_microseconds_constructs_correct_duration)
{
  using sick::literals::operator"" _us;
  auto const duration = 5'000'000_us;
  EXPECT_EQ(duration.seconds(), 5);
}

TEST(DurationTest, fromSeconds_converts_to_seconds_roundtrip)
{
  auto const original_seconds  = static_cast<sick::Duration::value_type>(42);
  auto const duration          = sick::Duration::fromSeconds(original_seconds);
  auto const retrieved_seconds = duration.seconds();
  EXPECT_EQ(retrieved_seconds, original_seconds);
}

TEST(DurationTest, fromMilliseconds_converts_to_microseconds_roundtrip)
{
  auto const original_milliseconds  = static_cast<sick::Duration::value_type>(5000);
  auto const duration               = sick::Duration::fromMilliseconds(original_milliseconds);
  auto const retrieved_milliseconds = duration.microseconds() / 1'000;
  EXPECT_EQ(retrieved_milliseconds, original_milliseconds);
}

TEST(DurationTest, fromMicroseconds_converts_to_microseconds_roundtrip)
{
  auto const original_microseconds  = static_cast<sick::Duration::value_type>(5'000'000);
  auto const duration               = sick::Duration::fromMicroseconds(original_microseconds);
  auto const retrieved_microseconds = duration.microseconds();
  EXPECT_EQ(retrieved_microseconds, original_microseconds);
}

TEST(DurationTest, less_than_operator_returns_true_for_smaller_duration)
{
  auto const d1 = sick::Duration::fromSeconds(1);
  auto const d2 = sick::Duration::fromSeconds(2);
  EXPECT_TRUE(d1 < d2);
  EXPECT_FALSE(d2 < d1);
}

TEST(DurationTest, add_operator_adds_two_durations)
{
  auto const d1     = sick::Duration::fromSeconds(2);
  auto const d2     = sick::Duration::fromSeconds(3);
  auto const result = d1 + d2;
  EXPECT_EQ(result.seconds(), 5);
}

TEST(DurationTest, subtract_operator_subtracts_two_durations)
{
  auto const d1     = sick::Duration::fromSeconds(5);
  auto const d2     = sick::Duration::fromSeconds(2);
  auto const result = d1 - d2;
  EXPECT_EQ(result.seconds(), 3);
}

TEST(DurationTest, multiply_operator_multiplies_by_size)
{
  auto const duration = sick::Duration::fromSeconds(2);
  auto const result   = duration * static_cast<std::size_t>(3);
  EXPECT_EQ(result.seconds(), 6);
}

TEST(DurationTest, divide_operator_divides_by_unsigned_int)
{
  auto const duration = sick::Duration::fromSeconds(10);
  auto const result   = duration / 2u;
  EXPECT_EQ(result.seconds(), 5);
}

TEST(DurationTest, to_string_returns_value_with_unit)
{
  auto const duration = sick::Duration::fromMicroseconds(5'000'000);

  EXPECT_THAT(std::to_string(duration), ::testing::HasSubstr("5000000"));
  EXPECT_THAT(std::to_string(duration), ::testing::EndsWith(" microseconds"));
}
