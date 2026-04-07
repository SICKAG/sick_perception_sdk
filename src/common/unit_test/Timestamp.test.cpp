/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/quantities/Duration.hpp>
#include <sick_perception_sdk/common/quantities/Timestamp.hpp>

#include <gtest/gtest.h>

TEST(TimestampTest, fromMicrosecondsSinceEpoch_stores_value_correctly)
{
  auto const timestamp = sick::Timestamp::fromMicrosecondsSinceEpoch(42);
  EXPECT_EQ(timestamp.microsecondsSinceEpoch(), 42);
}

TEST(TimestampTest, less_than_operator_returns_true_for_earlier_timestamp)
{
  auto const t1 = sick::Timestamp::fromMicrosecondsSinceEpoch(100);
  auto const t2 = sick::Timestamp::fromMicrosecondsSinceEpoch(200);
  EXPECT_TRUE(t1 < t2);
  EXPECT_FALSE(t2 < t1);
}

TEST(TimestampTest, equal_operator_returns_true_for_same_timestamp)
{
  auto const t1 = sick::Timestamp::fromMicrosecondsSinceEpoch(123);
  auto const t2 = sick::Timestamp::fromMicrosecondsSinceEpoch(123);
  EXPECT_TRUE(t1 == t2);
}

TEST(TimestampTest, equal_operator_returns_false_for_different_timestamps)
{
  auto const t1 = sick::Timestamp::fromMicrosecondsSinceEpoch(123);
  auto const t2 = sick::Timestamp::fromMicrosecondsSinceEpoch(456);
  EXPECT_FALSE(t1 == t2);
}

TEST(TimestampTest, not_equal_operator_returns_true_for_different_timestamps)
{
  auto const t1 = sick::Timestamp::fromMicrosecondsSinceEpoch(123);
  auto const t2 = sick::Timestamp::fromMicrosecondsSinceEpoch(456);
  EXPECT_TRUE(t1 != t2);
}

TEST(TimestampTest, not_equal_operator_returns_false_for_same_timestamp)
{
  auto const t1 = sick::Timestamp::fromMicrosecondsSinceEpoch(123);
  auto const t2 = sick::Timestamp::fromMicrosecondsSinceEpoch(123);
  EXPECT_FALSE(t1 != t2);
}

TEST(TimestampTest, add_operator_adds_duration_to_timestamp)
{
  auto const timestamp = sick::Timestamp::fromMicrosecondsSinceEpoch(100);
  auto const duration  = sick::Duration::fromMicroseconds(50);
  auto const result    = timestamp + duration;
  EXPECT_EQ(result.microsecondsSinceEpoch(), 150);
}

TEST(TimestampTest, subtract_operator_returns_duration_between_timestamps)
{
  auto const t1     = sick::Timestamp::fromMicrosecondsSinceEpoch(200);
  auto const t2     = sick::Timestamp::fromMicrosecondsSinceEpoch(100);
  auto const result = t1 - t2;
  EXPECT_EQ(result.microseconds(), 100);
}

TEST(TimestampTest, default_construction_is_zero)
{
  auto const timestamp = sick::Timestamp();
  EXPECT_EQ(timestamp.microsecondsSinceEpoch(), 0);
}

TEST(TimestampTest, to_string_returns_value_with_unit)
{
  auto const timestamp = sick::Timestamp::fromMicrosecondsSinceEpoch(1000000);
  EXPECT_EQ(std::to_string(timestamp), "1000000 microseconds since epoch");
}
