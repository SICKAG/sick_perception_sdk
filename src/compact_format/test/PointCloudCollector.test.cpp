/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/PointCloudCollector.hpp>

#include "utils/ScanDataGenerator.hpp"
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudConfiguration.hpp>

#include <cstring> // For std::memcpy
#include <gtest/gtest.h>

TEST(PointCloudCollectorTest, collect_returns_empty_point_cloud_with_default_initalized_collector)
{
  sick::point_cloud::PointCloudConfiguration config;
  sick::compact::scan_data::PointCloudCollector collector(config);

  auto const pc = collector.getPointCloud();
  EXPECT_TRUE(pc.isEmpty());
  EXPECT_EQ(0, pc.rawByteSize());
  EXPECT_EQ(0, pc.numberOfPoints());
}

TEST(PointCloudCollectorTest, collect_collects_consecutive_segments)
{
  sick::point_cloud::PointCloudConfiguration config;
  sick::compact::scan_data::PointCloudCollector collector(config);

  auto g = sick::test::ScanDataGenerator {}   //
             .withNumberOfSegmentsPerFrame(2) //
             .withNumberOfColumns(4)          //
             .withNumberOfRows(3)             //
             .withTelegramSequenceNumber(1);

  // Collect the first segment
  collector.collect(g.next());
  collector.collect(g.next());

  auto const pc = collector.getPointCloud();
  // 2 collected scans with 4 beams per scan * 3 layers = 12 points each
  EXPECT_EQ(24, pc.numberOfPoints());
  EXPECT_EQ(1000, pc.timestamp().microsecondsSinceEpoch()); // Timestamp is set by the generator to telegramSequenceNumber * 1000 us
}

TEST(PointCloudCollectorTest, collect_collects_segments_with_gap)
{
  sick::point_cloud::PointCloudConfiguration config;
  sick::compact::scan_data::PointCloudCollector collector(config);

  auto g = sick::test::ScanDataGenerator {}   //
             .withNumberOfSegmentsPerFrame(3) //
             .withNumberOfColumns(1)          //
             .withNumberOfRows(1)             //
             .withTelegramSequenceNumber(2);

  // Collect the first segment
  collector.collect(g.next());
  EXPECT_EQ(1, collector.getPointCloud().numberOfPoints());

  // Skip the second segment
  g.next();

  // Collect the third segment
  collector.collect(g.next());

  auto const pc = collector.getPointCloud();
  EXPECT_EQ(2, pc.numberOfPoints());
  EXPECT_EQ(2000, pc.timestamp().microsecondsSinceEpoch()); // Timestamp is set by the generator to telegramSequenceNumber * 1000 us
}

TEST(PointCloudCollectorTest, collect_collects_empty_point_cloud_without_crash)
{
  sick::point_cloud::PointCloudConfiguration config;
  sick::compact::scan_data::PointCloudCollector collector(config);

  auto g = sick::test::ScanDataGenerator {}   //
             .withNumberOfSegmentsPerFrame(0) //
             .withNumberOfColumns(0)          //
             .withNumberOfRows(0)             //
             .withTelegramSequenceNumber(2);

  collector.collect(g.next());

  auto const pc = collector.getPointCloud();
  EXPECT_TRUE(pc.isEmpty());
  EXPECT_EQ(0, pc.timestamp().microsecondsSinceEpoch()); // Timestamp must stay 0 if only empty segments are collected.
}

TEST(PointCloudCollectorTest, collect_works_for_multiple_frames)
{
  sick::point_cloud::PointCloudConfiguration config;
  sick::compact::scan_data::PointCloudCollector collector(config);

  auto g = sick::test::ScanDataGenerator {}   //
             .withNumberOfSegmentsPerFrame(2) //
             .withNumberOfColumns(1)          //
             .withNumberOfRows(1)             //
             .withTelegramSequenceNumber(3);

  // Collect the segments of the first frame
  collector.collect(g.next());
  collector.collect(g.next());
  EXPECT_EQ(2, collector.getPointCloud().numberOfPoints());

  // Incrementing the generator switches to the next frame.
  // Collecting the first segment of the next frame must increase the size of the collected point cloud.
  collector.collect(g.next());

  auto const pc = collector.getPointCloud();
  EXPECT_EQ(3, pc.numberOfPoints());
  EXPECT_EQ(3000, pc.timestamp().microsecondsSinceEpoch()); // Timestamp is set by the generator to telegramSequenceNumber * 1000 us
}

TEST(PointCloudCollectorTest, collect_works_when_number_of_beams_per_scan_changes)
{
  sick::point_cloud::PointCloudConfiguration config;
  sick::compact::scan_data::PointCloudCollector collector(config);

  // Collect a first segment with 1 beam per scan
  collector.collect(sick::test::ScanDataGenerator {}   //
                      .withNumberOfSegmentsPerFrame(3) //
                      .withNumberOfColumns(1)          //
                      .withNumberOfRows(1)             //
                      .next());
  EXPECT_EQ(1, collector.getPointCloud().numberOfPoints());

  // Collect another segment with 42 beams per scan
  collector.collect(sick::test::ScanDataGenerator {}   //
                      .withNumberOfSegmentsPerFrame(3) //
                      .withNumberOfColumns(42)         //
                      .withNumberOfRows(1)             //
                      .next());
  EXPECT_EQ(43, collector.getPointCloud().numberOfPoints());
}

TEST(PointCloudCollectorTest, collect_works_when_number_of_layers_changes)
{
  sick::point_cloud::PointCloudConfiguration config;
  sick::compact::scan_data::PointCloudCollector collector(config);

  // Collect a first segment with 1 layer
  collector.collect(sick::test::ScanDataGenerator {}   //
                      .withNumberOfSegmentsPerFrame(3) //
                      .withNumberOfColumns(1)          //
                      .withNumberOfRows(1)             //
                      .next());
  EXPECT_EQ(1, collector.getPointCloud().numberOfPoints());

  // Collect another segment with 42 layers
  collector.collect(sick::test::ScanDataGenerator {}   //
                      .withNumberOfSegmentsPerFrame(3) //
                      .withNumberOfColumns(1)          //
                      .withNumberOfRows(42)            //
                      .next());
  EXPECT_EQ(43, collector.getPointCloud().numberOfPoints());
}

TEST(PointCloudCollectorTest, collect_computes_correct_geometry)
{
  sick::point_cloud::PointCloudConfiguration config;
  sick::compact::scan_data::PointCloudCollector collector(config);

  auto g = sick::test::ScanDataGenerator {}   //
             .withNumberOfSegmentsPerFrame(1) //
             .withNumberOfColumns(2)          //
             .withNumberOfRows(2);

  struct Point
  {
    float x, y, z;
  };

  collector.collect(g.next());
  auto const pc = collector.getPointCloud();

  std::vector<Point> points(pc.numberOfPoints());
  std::memcpy(reinterpret_cast<void*>(points.data()), reinterpret_cast<void const*>(pc.rawBytes()), pc.rawByteSize());

  constexpr float kDistanceTolerance = 0.00001f;

  ASSERT_EQ(4, points.size());
  // Row-major order: layer first, then column (beam)
  // Point 0 at layer 0, beam 0 has distance = 1000 mm, elevation = 0 deg, azimuth = 0 deg
  EXPECT_NEAR(1.0f, points[0].x, kDistanceTolerance);
  EXPECT_NEAR(0.0f, points[0].y, kDistanceTolerance);
  EXPECT_NEAR(0.0f, points[0].z, kDistanceTolerance);
  // Point 1 at layer 0, beam 1 has distance = 1000 mm, elevation = 0 deg, azimuth = 1 deg
  EXPECT_NEAR(0.999848f, points[1].x, kDistanceTolerance);
  EXPECT_NEAR(0.017452f, points[1].y, kDistanceTolerance);
  EXPECT_NEAR(0.0f, points[1].z, kDistanceTolerance);
  // Point 2 at layer 1, beam 0 has distance = 1000 mm, elevation = 1 deg, azimuth = 0 deg
  EXPECT_NEAR(0.999848f, points[2].x, kDistanceTolerance);
  EXPECT_NEAR(0.0f, points[2].y, kDistanceTolerance);
  EXPECT_NEAR(-0.017452f, points[2].z, kDistanceTolerance);
  // Point 3 at layer 1, beam 1 has distance = 1000 mm, elevation = 1 deg, azimuth = 1 deg
  EXPECT_NEAR(0.999695f, points[3].x, kDistanceTolerance);
  EXPECT_NEAR(0.017452f, points[3].y, kDistanceTolerance);
  EXPECT_NEAR(-0.017452f, points[3].z, kDistanceTolerance);
}

TEST(PointCloudCollectorTest, reset_clears_pointcloud)
{
  sick::point_cloud::PointCloudConfiguration config;
  sick::compact::scan_data::PointCloudCollector collector(config);

  auto g = sick::test::ScanDataGenerator {}   //
             .withNumberOfSegmentsPerFrame(2) //
             .withNumberOfColumns(1)          //
             .withNumberOfRows(1);
  collector.collect(g.next());

  EXPECT_EQ(1, collector.getPointCloud().numberOfPoints());

  collector.reset();
  EXPECT_EQ(0, collector.getPointCloud().numberOfPoints());
}
