/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloudCollector.hpp>

#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloudBuilder.hpp>

#include <future>
#include <gtest/gtest.h>
#include <thread>
#include <vector>

using FieldType = sick::point_cloud::PointField::FieldType;

namespace {

auto createPointCloud(sick::Timestamp timestamp, std::size_t numberOfPoints, std::set<FieldType> const& fields = {FieldType::X, FieldType::Y, FieldType::Z})
  -> sick::point_cloud::UnorganizedPointCloud
{
  sick::point_cloud::UnorganizedPointCloudBuilder builder({fields, fields}, timestamp, numberOfPoints);
  for (std::size_t i = 0; i < numberOfPoints; ++i)
  {
    builder.beginPoint();
    for (auto const& field : fields)
    {
      switch (field)
      {
      case FieldType::X:
        builder.writeNextFieldValueOrIgnore(FieldType::X, static_cast<float>(i));
        break;
      case FieldType::Y:
        builder.writeNextFieldValueOrIgnore(FieldType::Y, static_cast<float>(i * 2));
        break;
      case FieldType::Z:
        builder.writeNextFieldValueOrIgnore(FieldType::Z, static_cast<float>(i * 3));
        break;
      case FieldType::TimeOffsetSeconds:
        builder.writeNextFieldValueOrIgnore(FieldType::TimeOffsetSeconds, static_cast<std::uint32_t>(i));
        break;
      case FieldType::TimeOffsetNanoseconds:
        builder.writeNextFieldValueOrIgnore(FieldType::TimeOffsetNanoseconds, static_cast<std::uint32_t>(i * 1000));
        break;
      case FieldType::Ring:
        builder.writeNextFieldValueOrIgnore(FieldType::Ring, static_cast<std::uint8_t>(i % 16));
        break;
      case FieldType::LayerIndex:
        builder.writeNextFieldValueOrIgnore(FieldType::LayerIndex, static_cast<std::uint8_t>(i % 8));
        break;
      case FieldType::ColumnIndex:
        builder.writeNextFieldValueOrIgnore(FieldType::ColumnIndex, static_cast<std::uint16_t>(i % 16));
        break;
      case FieldType::Intensity:
        builder.writeNextFieldValueOrIgnore(FieldType::Intensity, static_cast<float>(i) / 100.0f);
        break;
      default:
        break;
      }
    }
  }
  return builder.build();
}

auto createPointCloudWithTimeOffset(
  sick::Timestamp timestamp,
  std::size_t numberOfPoints,
  std::uint32_t baseTimeOffsetSeconds,
  std::uint32_t baseTimeOffsetNanoseconds
) -> sick::point_cloud::UnorganizedPointCloud
{
  std::set<FieldType> const fields = {FieldType::X, FieldType::Y, FieldType::Z, FieldType::TimeOffsetSeconds, FieldType::TimeOffsetNanoseconds};
  sick::point_cloud::UnorganizedPointCloudBuilder builder({fields, fields}, timestamp, numberOfPoints);
  for (std::size_t i = 0; i < numberOfPoints; ++i)
  {
    builder.beginPoint();
    builder.writeNextFieldValueOrIgnore(FieldType::X, static_cast<float>(i));
    builder.writeNextFieldValueOrIgnore(FieldType::Y, static_cast<float>(i * 2));
    builder.writeNextFieldValueOrIgnore(FieldType::Z, static_cast<float>(i * 3));
    builder.writeNextFieldValueOrIgnore(FieldType::TimeOffsetSeconds, baseTimeOffsetSeconds + static_cast<std::uint32_t>(i));
    builder.writeNextFieldValueOrIgnore(FieldType::TimeOffsetNanoseconds, baseTimeOffsetNanoseconds);
  }
  return builder.build();
}

} // namespace

TEST(UnorganizedPointCloudCollectorTest, default_constructed_collector_is_empty)
{
  sick::point_cloud::UnorganizedPointCloudCollector collector;

  EXPECT_TRUE(collector.isEmpty());
  EXPECT_EQ(0, collector.numberOfPoints());
}

TEST(UnorganizedPointCloudCollectorTest, get_merged_point_cloud_throws_on_empty_collector)
{
  sick::point_cloud::UnorganizedPointCloudCollector collector;

  EXPECT_THROW(collector.getMergedPointCloud(), std::logic_error);
}

TEST(UnorganizedPointCloudCollectorTest, push_throws_on_empty_point_cloud)
{
  sick::point_cloud::UnorganizedPointCloudCollector collector;
  auto const emptyCloud = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(1000), 0);

  EXPECT_THROW(collector.push(emptyCloud), std::invalid_argument);
}

TEST(UnorganizedPointCloudCollectorTest, push_collects_all_points_from_single_cloud)
{
  sick::point_cloud::UnorganizedPointCloudCollector collector;
  auto const cloud = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(1000), 5);

  collector.push(cloud);

  EXPECT_FALSE(collector.isEmpty());
  EXPECT_EQ(5, collector.numberOfPoints());

  auto const merged = collector.getMergedPointCloud();
  EXPECT_EQ(5, merged.numberOfPoints());
}

TEST(UnorganizedPointCloudCollectorTest, push_collects_all_points_from_multiple_clouds)
{
  sick::point_cloud::UnorganizedPointCloudCollector collector;
  auto const cloud1 = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(1000), 3);
  auto const cloud2 = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(2000), 4);
  auto const cloud3 = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(3000), 2);

  collector.push(cloud1);
  collector.push(cloud2);
  collector.push(cloud3);

  EXPECT_EQ(9, collector.numberOfPoints());

  auto const merged = collector.getMergedPointCloud();
  EXPECT_EQ(9, merged.numberOfPoints());
}

TEST(UnorganizedPointCloudCollectorTest, merged_point_cloud_has_timestamp_of_first_collected_cloud)
{
  sick::point_cloud::UnorganizedPointCloudCollector collector;
  auto const cloud1 = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(1000), 2);
  auto const cloud2 = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(2000), 2);

  collector.push(cloud1);
  collector.push(cloud2);

  auto const merged = collector.getMergedPointCloud();
  EXPECT_EQ(sick::Timestamp::fromMicrosecondsSinceEpoch(1000), merged.timestamp());
}

TEST(UnorganizedPointCloudCollectorTest, push_throws_on_smaller_timestamp)
{
  sick::point_cloud::UnorganizedPointCloudCollector collector;
  auto const cloud1 = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(2000), 2);
  auto const cloud2 = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(1000), 2);

  collector.push(cloud1);

  EXPECT_THROW(collector.push(cloud2), std::invalid_argument);
}

TEST(UnorganizedPointCloudCollectorTest, push_allows_equal_timestamp)
{
  sick::point_cloud::UnorganizedPointCloudCollector collector;
  auto const cloud1 = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(1000), 2);
  auto const cloud2 = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(1000), 2);

  collector.push(cloud1);

  EXPECT_NO_THROW(collector.push(cloud2));
  EXPECT_EQ(4, collector.numberOfPoints());
}

TEST(UnorganizedPointCloudCollectorTest, clear_resets_collector_to_empty_state)
{
  sick::point_cloud::UnorganizedPointCloudCollector collector;
  auto const cloud = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(1000), 5);
  collector.push(cloud);

  collector.clear();

  EXPECT_TRUE(collector.isEmpty());
  EXPECT_EQ(0, collector.numberOfPoints());
  EXPECT_THROW(collector.getMergedPointCloud(), std::logic_error);
}

TEST(UnorganizedPointCloudCollectorTest, clear_allows_new_layout_on_subsequent_push)
{
  sick::point_cloud::UnorganizedPointCloudCollector collector;
  std::set<FieldType> const fields1 = {FieldType::X, FieldType::Y, FieldType::Z};
  std::set<FieldType> const fields2 = {FieldType::X, FieldType::Y, FieldType::Z, FieldType::Intensity};

  auto const cloud1 = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(1000), 2, fields1);
  auto const cloud2 = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(2000), 3, fields2);

  collector.push(cloud1);
  collector.clear();

  EXPECT_NO_THROW(collector.push(cloud2));
  EXPECT_EQ(3, collector.numberOfPoints());

  auto const merged = collector.getMergedPointCloud();
  EXPECT_EQ(4, merged.fields().size()); // X, Y, Z, Intensity
}

TEST(UnorganizedPointCloudCollectorTest, get_merged_point_cloud_can_be_called_multiple_times)
{
  sick::point_cloud::UnorganizedPointCloudCollector collector;
  auto const cloud = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(1000), 3);
  collector.push(cloud);

  auto const merged1 = collector.getMergedPointCloud();
  auto const merged2 = collector.getMergedPointCloud();

  EXPECT_EQ(merged1.numberOfPoints(), merged2.numberOfPoints());
  EXPECT_EQ(merged1.timestamp(), merged2.timestamp());
}

TEST(UnorganizedPointCloudCollectorTest, push_throws_on_different_number_of_fields)
{
  sick::point_cloud::UnorganizedPointCloudCollector collector;
  std::set<FieldType> const fields1 = {FieldType::X, FieldType::Y, FieldType::Z};
  std::set<FieldType> const fields2 = {FieldType::X, FieldType::Y, FieldType::Z, FieldType::Intensity};

  auto const cloud1 = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(1000), 2, fields1);
  auto const cloud2 = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(2000), 2, fields2);

  collector.push(cloud1);

  EXPECT_THROW(collector.push(cloud2), std::invalid_argument);
}

TEST(UnorganizedPointCloudCollectorTest, push_throws_on_different_field_types)
{
  sick::point_cloud::UnorganizedPointCloudCollector collector;
  std::set<FieldType> const fields1 = {FieldType::X, FieldType::Y, FieldType::Z};
  std::set<FieldType> const fields2 = {FieldType::X, FieldType::Y, FieldType::Intensity};

  auto const cloud1 = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(1000), 2, fields1);
  auto const cloud2 = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(2000), 2, fields2);

  collector.push(cloud1);

  EXPECT_THROW(collector.push(cloud2), std::invalid_argument);
}

TEST(UnorganizedPointCloudCollectorTest, push_throws_when_only_time_offset_seconds_present)
{
  sick::point_cloud::UnorganizedPointCloudCollector collector;
  std::set<FieldType> const fields = {FieldType::X, FieldType::Y, FieldType::Z, FieldType::TimeOffsetSeconds};

  auto const cloud = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(1000), 2, fields);

  EXPECT_THROW(collector.push(cloud), std::invalid_argument);
}

TEST(UnorganizedPointCloudCollectorTest, push_throws_when_only_time_offset_nanoseconds_present)
{
  sick::point_cloud::UnorganizedPointCloudCollector collector;
  std::set<FieldType> const fields = {FieldType::X, FieldType::Y, FieldType::Z, FieldType::TimeOffsetNanoseconds};

  auto const cloud = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(1000), 2, fields);

  EXPECT_THROW(collector.push(cloud), std::invalid_argument);
}

TEST(UnorganizedPointCloudCollectorTest, push_corrects_time_offset_values)
{
  sick::point_cloud::UnorganizedPointCloudCollector collector;

  // First cloud at timestamp 1000us with time offset (0s, 0ns)
  auto const cloud1 = createPointCloudWithTimeOffset(sick::Timestamp::fromMicrosecondsSinceEpoch(1000), 1, 0, 0);

  // Second cloud at timestamp 2000us (1000us later = 1ms = 1,000,000ns) with time offset (0s, 0ns)
  auto const cloud2 = createPointCloudWithTimeOffset(sick::Timestamp::fromMicrosecondsSinceEpoch(2000), 1, 0, 0);

  collector.push(cloud1);
  collector.push(cloud2);

  auto const merged = collector.getMergedPointCloud();
  ASSERT_EQ(2, merged.numberOfPoints());

  // First point should have original time offset (0s, 0ns)
  auto const [seconds0, nanos0] = merged.getTimeOffset(0);
  EXPECT_EQ(0, seconds0);
  EXPECT_EQ(0, nanos0);

  // Second point should have time offset corrected by 1000us = 1,000,000ns
  auto const [seconds1, nanos1] = merged.getTimeOffset(1);
  EXPECT_EQ(0, seconds1);
  EXPECT_EQ(1000000, nanos1);
}

TEST(UnorganizedPointCloudCollectorTest, push_corrects_time_offset_with_second_rollover)
{
  sick::point_cloud::UnorganizedPointCloudCollector collector;

  // First cloud at timestamp 0us with time offset (0s, 500,000,000ns)
  auto const cloud1 = createPointCloudWithTimeOffset(sick::Timestamp::fromMicrosecondsSinceEpoch(0), 1, 0, 500'000'000);

  // Second cloud 600ms later with time offset (0s, 600,000,000ns)
  // Total nanoseconds: 500,000,000 + 600,000,000 + 600,000,000 = 1,700,000,000 -> should be (1s, 700,000,000ns)
  auto const cloud2 = createPointCloudWithTimeOffset(sick::Timestamp::fromMicrosecondsSinceEpoch(600'000), 1, 0, 600'000'000);

  collector.push(cloud1);
  collector.push(cloud2);

  auto const merged             = collector.getMergedPointCloud();
  auto const [seconds1, nanos1] = merged.getTimeOffset(1);

  // The corrected offset should handle the rollover: 600,000,000 + 600,000us*1000 = 600,000,000 + 600,000,000,000ns
  // Wait - 600,000us = 600ms = 600,000,000ns, so: 600,000,000 + 600,000,000 = 1,200,000,000ns = (1s, 200,000,000ns)
  EXPECT_EQ(1, seconds1);
  EXPECT_EQ(200'000'000, nanos1);
}

TEST(UnorganizedPointCloudCollectorTest, push_ignores_time_offset_when_first_cloud_has_none)
{
  sick::point_cloud::UnorganizedPointCloudCollector collector;
  std::set<FieldType> const fields = {FieldType::X, FieldType::Y, FieldType::Z};

  auto const cloud1 = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(1000), 2, fields);
  auto const cloud2 = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(2000), 2, fields);

  collector.push(cloud1);
  collector.push(cloud2);

  auto const merged = collector.getMergedPointCloud();
  EXPECT_EQ(4, merged.numberOfPoints());
  // No time offset fields should be present
  EXPECT_EQ(3, merged.fields().size());
}

TEST(UnorganizedPointCloudCollectorTest, push_preserves_ring_and_layer_id_values)
{
  sick::point_cloud::UnorganizedPointCloudCollector collector;
  std::set<FieldType> const fields = {FieldType::X, FieldType::Y, FieldType::Z, FieldType::Ring, FieldType::LayerIndex};

  // Use more than 8 points so that Ring (i % 16) and LayerIndex (i % 8) diverge and are actually distinguishable.
  std::size_t const numberOfPoints = 20;
  auto const cloud                 = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(1000), numberOfPoints, fields);

  collector.push(cloud);

  auto const merged = collector.getMergedPointCloud();
  ASSERT_EQ(numberOfPoints, merged.numberOfPoints());

  for (std::size_t i = 0; i < numberOfPoints; ++i)
  {
    EXPECT_EQ(static_cast<std::uint8_t>(i % 16), merged.getRing(i));
    EXPECT_EQ(static_cast<std::uint8_t>(i % 8), merged.getLayerIndex(i));
  }
}

TEST(UnorganizedPointCloudCollectorTest, push_provides_strong_exception_guarantee)
{
  sick::point_cloud::UnorganizedPointCloudCollector collector;
  std::set<FieldType> const fields1 = {FieldType::X, FieldType::Y, FieldType::Z};
  std::set<FieldType> const fields2 = {FieldType::X, FieldType::Y, FieldType::Z, FieldType::Intensity};

  auto const cloud1 = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(1000), 3, fields1);
  auto const cloud2 = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(2000), 2, fields2);

  collector.push(cloud1);
  auto const pointCountBefore = collector.numberOfPoints();

  EXPECT_THROW(collector.push(cloud2), std::invalid_argument);

  // Collector should remain unchanged
  EXPECT_EQ(pointCountBefore, collector.numberOfPoints());
  auto const merged = collector.getMergedPointCloud();
  EXPECT_EQ(3, merged.numberOfPoints());
}

TEST(UnorganizedPointCloudCollectorTest, collector_is_not_copyable)
{
  EXPECT_FALSE(std::is_copy_constructible<sick::point_cloud::UnorganizedPointCloudCollector>::value);
  EXPECT_FALSE(std::is_copy_assignable<sick::point_cloud::UnorganizedPointCloudCollector>::value);
}

TEST(UnorganizedPointCloudCollectorTest, collector_is_not_movable)
{
  EXPECT_FALSE(std::is_move_constructible<sick::point_cloud::UnorganizedPointCloudCollector>::value);
  EXPECT_FALSE(std::is_move_assignable<sick::point_cloud::UnorganizedPointCloudCollector>::value);
}

TEST(UnorganizedPointCloudCollectorTest, concurrent_reads_are_safe)
{
  sick::point_cloud::UnorganizedPointCloudCollector collector;
  auto const cloud = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(1000), 100);
  collector.push(cloud);

  std::vector<std::future<std::size_t>> futures;
  constexpr int kNumberOfThreads = 10;

  for (int i = 0; i < kNumberOfThreads; ++i)
  {
    futures.push_back(std::async(std::launch::async, [&collector]() {
      std::size_t total = 0;
      for (int j = 0; j < 100; ++j)
      {
        total += collector.numberOfPoints();
        auto const isEmpty = collector.isEmpty();
        (void)isEmpty;
      }
      return total;
    }));
  }

  for (auto& future : futures)
  {
    EXPECT_EQ(10000, future.get()); // 100 iterations * 100 points
  }
}

TEST(UnorganizedPointCloudCollectorTest, concurrent_writes_are_safe)
{
  sick::point_cloud::UnorganizedPointCloudCollector collector;
  std::vector<std::future<void>> futures;
  constexpr int kNumberOfThreads = 10;
  constexpr int kPushesPerThread = 10;
  constexpr int kPointsPerCloud  = 5;
  constexpr int kTimestampBaseUs = 1000;
  constexpr int kTimestampStepUs = 100;

  for (int threadIdx = 0; threadIdx < kNumberOfThreads; ++threadIdx)
  {
    futures.push_back(std::async(std::launch::async, [&collector, threadIdx, kPushesPerThread, kTimestampBaseUs, kTimestampStepUs, kPointsPerCloud]() {
      for (int pushIdx = 0; pushIdx < kPushesPerThread; ++pushIdx)
      {
        // Use increasing timestamps to avoid rejection
        auto const timestampUs = kTimestampBaseUs + (threadIdx * kPushesPerThread + pushIdx) * kTimestampStepUs;
        auto const cloud       = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(timestampUs), kPointsPerCloud);
        try
        {
          collector.push(cloud);
        }
        catch (std::invalid_argument const&)
        {
          // Some pushes may fail due to timestamp ordering, that's expected
        }
      }
    }));
  }

  for (auto& future : futures)
  {
    future.get();
  }

  // At least some points should have been collected
  EXPECT_GT(collector.numberOfPoints(), 0);
}

TEST(UnorganizedPointCloudCollectorTest, push_preserves_point_coordinate_values)
{
  sick::point_cloud::UnorganizedPointCloudCollector collector;

  auto const cloud1 = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(1000), 2);
  auto const cloud2 = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(2000), 2);

  collector.push(cloud1);
  collector.push(cloud2);

  auto const merged = collector.getMergedPointCloud();
  ASSERT_EQ(4, merged.numberOfPoints());

  // Check first cloud's points
  EXPECT_FLOAT_EQ(0.0f, merged.getX(0));
  EXPECT_FLOAT_EQ(0.0f, merged.getY(0));
  EXPECT_FLOAT_EQ(0.0f, merged.getZ(0));

  EXPECT_FLOAT_EQ(1.0f, merged.getX(1));
  EXPECT_FLOAT_EQ(2.0f, merged.getY(1));
  EXPECT_FLOAT_EQ(3.0f, merged.getZ(1));

  // Check second cloud's points
  EXPECT_FLOAT_EQ(0.0f, merged.getX(2));
  EXPECT_FLOAT_EQ(0.0f, merged.getY(2));
  EXPECT_FLOAT_EQ(0.0f, merged.getZ(2));

  EXPECT_FLOAT_EQ(1.0f, merged.getX(3));
  EXPECT_FLOAT_EQ(2.0f, merged.getY(3));
  EXPECT_FLOAT_EQ(3.0f, merged.getZ(3));
}

TEST(UnorganizedPointCloudCollectorTest, merged_point_cloud_preserves_field_layout)
{
  sick::point_cloud::UnorganizedPointCloudCollector collector;
  std::set<FieldType> const fields = {FieldType::X, FieldType::Y, FieldType::Z, FieldType::Intensity, FieldType::Ring};

  auto const cloud = createPointCloud(sick::Timestamp::fromMicrosecondsSinceEpoch(1000), 2, fields);

  collector.push(cloud);

  auto const merged        = collector.getMergedPointCloud();
  auto const& mergedFields = merged.fields();
  auto const& cloudFields  = cloud.fields();

  ASSERT_EQ(cloudFields.size(), mergedFields.size());
  for (std::size_t i = 0; i < cloudFields.size(); ++i)
  {
    EXPECT_EQ(cloudFields[i].fieldType, mergedFields[i].fieldType);
    EXPECT_EQ(cloudFields[i].dataType, mergedFields[i].dataType);
    EXPECT_EQ(cloudFields[i].offset, mergedFields[i].offset);
  }
}
