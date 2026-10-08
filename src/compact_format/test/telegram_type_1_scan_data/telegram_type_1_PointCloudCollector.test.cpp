/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/PointCloudCollector.hpp>

#include "ScanDataGenerator.hpp"
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudConfiguration.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanData.hpp>

#include <cstring> // For std::memcpy
#include <gtest/gtest.h>

TEST(telegram_type_1_PointCloudCollectorTest, collect_returns_empty_point_cloud_with_default_initalized_collector)
{
  sick::point_cloud::PointCloudConfiguration config;
  sick::compact::scan_data::PointCloudCollector collector(config);

  auto const pc = collector.getPointCloud();
  EXPECT_TRUE(pc.isEmpty());
  EXPECT_EQ(0, pc.rawByteSize());
  EXPECT_EQ(0, pc.numberOfPoints());
}

TEST(telegram_type_1_PointCloudCollectorTest, collect_collects_consecutive_segments)
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

TEST(telegram_type_1_PointCloudCollectorTest, collect_collects_segments_with_gap)
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

TEST(telegram_type_1_PointCloudCollectorTest, collect_collects_empty_point_cloud_without_crash)
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

TEST(telegram_type_1_PointCloudCollectorTest, collect_ignores_points_with_zero_distance)
{
  sick::point_cloud::PointCloudConfiguration config;
  sick::compact::scan_data::PointCloudCollector collector(config);

  auto g = sick::test::ScanDataGenerator {}   //
             .withNumberOfSegmentsPerFrame(1) //
             .withNumberOfColumns(2)          //
             .withNumberOfRows(2)             //
             .withTelegramSequenceNumber(1);

  auto segment                    = g.next();
  segment.modules[0].distances[0] = sick::Distance::fromMeters(0.0f); // Set the first point to zero distance

  collector.collect(segment);

  auto const pc = collector.getPointCloud();
  EXPECT_EQ(3, pc.numberOfPoints()); // 2x2 points minus 1 with zero distance
}

TEST(telegram_type_1_PointCloudCollectorTest, collect_works_for_multiple_frames)
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

TEST(telegram_type_1_PointCloudCollectorTest, collect_works_when_number_of_beams_per_scan_changes)
{
  sick::point_cloud::PointCloudConfiguration config;
  sick::compact::scan_data::PointCloudCollector collector(config);

  // Collect a first segment with 1 beam per scan
  collector.collect(
    sick::test::ScanDataGenerator {}   //
      .withNumberOfSegmentsPerFrame(3) //
      .withNumberOfColumns(1)          //
      .withNumberOfRows(1)             //
      .next()
  );
  EXPECT_EQ(1, collector.getPointCloud().numberOfPoints());

  // Collect another segment with 42 beams per scan
  collector.collect(
    sick::test::ScanDataGenerator {}   //
      .withNumberOfSegmentsPerFrame(3) //
      .withNumberOfColumns(42)         //
      .withNumberOfRows(1)             //
      .next()
  );
  EXPECT_EQ(43, collector.getPointCloud().numberOfPoints());
}

TEST(telegram_type_1_PointCloudCollectorTest, collect_works_when_number_of_layers_changes)
{
  sick::point_cloud::PointCloudConfiguration config;
  sick::compact::scan_data::PointCloudCollector collector(config);

  // Collect a first segment with 1 layer
  collector.collect(
    sick::test::ScanDataGenerator {}   //
      .withNumberOfSegmentsPerFrame(3) //
      .withNumberOfColumns(1)          //
      .withNumberOfRows(1)             //
      .next()
  );
  EXPECT_EQ(1, collector.getPointCloud().numberOfPoints());

  // Collect another segment with 42 layers
  collector.collect(
    sick::test::ScanDataGenerator {}   //
      .withNumberOfSegmentsPerFrame(3) //
      .withNumberOfColumns(1)          //
      .withNumberOfRows(42)            //
      .next()
  );
  EXPECT_EQ(43, collector.getPointCloud().numberOfPoints());
}

TEST(telegram_type_1_PointCloudCollectorTest, collect_computes_correct_geometry)
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
  // Column-major order: column (beam) first, then layer
  // Point 0 at layer 0, beam 0 has distance = 1000 mm, elevation = 0 deg, azimuth = 0 deg
  EXPECT_NEAR(1.0f, points[0].x, kDistanceTolerance);
  EXPECT_NEAR(0.0f, points[0].y, kDistanceTolerance);
  EXPECT_NEAR(0.0f, points[0].z, kDistanceTolerance);
  // Point 1 at layer 1, beam 0 has distance = 1000 mm, elevation = 0 deg, azimuth = 1 deg
  EXPECT_NEAR(0.999848f, points[1].x, kDistanceTolerance);
  EXPECT_NEAR(0.0f, points[1].y, kDistanceTolerance);
  EXPECT_NEAR(-0.017452f, points[1].z, kDistanceTolerance);
  // Point 2 at layer 1, beam 0 has distance = 1000 mm, elevation = 1 deg, azimuth = 0 deg
  EXPECT_NEAR(0.999848f, points[2].x, kDistanceTolerance);
  EXPECT_NEAR(0.017452f, points[2].y, kDistanceTolerance);
  EXPECT_NEAR(0.0f, points[2].z, kDistanceTolerance);
  // Point 3 at layer 1, beam 1 has distance = 1000 mm, elevation = 1 deg, azimuth = 1 deg
  EXPECT_NEAR(0.999695f, points[3].x, kDistanceTolerance);
  EXPECT_NEAR(0.017452f, points[3].y, kDistanceTolerance);
  EXPECT_NEAR(-0.017452f, points[3].z, kDistanceTolerance);
}

TEST(telegram_type_1_PointCloudCollectorTest, reset_clears_pointcloud)
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

TEST(telegram_type_1_PointCloudCollectorTest, collect_uses_sample_index_layout_for_multi_echo_ranges)
{
  using sick::Angle;
  using sick::Distance;
  using sick::Duration;
  using sick::Timestamp;

  sick::point_cloud::PointCloudConfiguration config;
  config.fields.enableCartesian = false;
  config.fields.enableSpherical = true;
  config.fields.enableEchoIndex = true;
  config.filters.selectedEchos  = std::set<std::size_t> {1};

  sick::compact::scan_data::PointCloudCollector collector(config);

  sick::compact::scan_data::Module module;
  module.numberOfColumns       = 2;
  module.numberOfEchoesPerBeam = 2;
  module.rowMetaData.resize(1);

  auto const baseTs                        = Timestamp::fromMicrosecondsSinceEpoch(2'000);
  module.rowMetaData[0].firstBeamTimestamp = baseTs;
  module.rowMetaData[0].lastBeamTimestamp  = baseTs + Duration::fromMicroseconds(1);
  module.rowMetaData[0].elevation          = Angle::fromDegrees(0.0f);
  module.rowMetaData[0].firstBeamAzimuth   = Angle::fromDegrees(0.0f);
  module.rowMetaData[0].lastBeamAzimuth    = Angle::fromDegrees(1.0f);

  auto const numberOfSamples = module.numberOfColumns * module.rowMetaData.size() * module.numberOfEchoesPerBeam;
  module.distances.resize(numberOfSamples);

  // Fill the distance array according to computeSampleIndex(column, row, echo).
  module.distances[sick::compact::scan_data::computeSampleIndex(module, 0, 0, 0)] = Distance::fromMeters(10.0f);
  module.distances[sick::compact::scan_data::computeSampleIndex(module, 0, 0, 1)] = Distance::fromMeters(20.0f);
  module.distances[sick::compact::scan_data::computeSampleIndex(module, 1, 0, 0)] = Distance::fromMeters(30.0f);
  module.distances[sick::compact::scan_data::computeSampleIndex(module, 1, 0, 1)] = Distance::fromMeters(40.0f);

  module.beamAzimuths.resize(module.numberOfColumns * module.rowMetaData.size());
  module.beamAzimuths[sick::compact::scan_data::computeBeamIndex(module, 0, 0)] = Angle::fromDegrees(0.0f);
  module.beamAzimuths[sick::compact::scan_data::computeBeamIndex(module, 1, 0)] = Angle::fromDegrees(1.0f);

  sick::compact::scan_data::ScanData scanData;
  scanData.telegramHeader.telegramSequenceNumber = 2;
  scanData.telegramHeader.transmitTimestamp      = baseTs;
  scanData.frameSequenceNumber                   = 0;
  scanData.segmentIndex                          = 0;
  scanData.modules.push_back(std::move(module));

  collector.collect(scanData);
  auto const pc = collector.getPointCloud();

  ASSERT_EQ(2U, pc.numberOfPoints());

  // With selected echo index 1, expected ranges for columns 0 and 1 are 20 m and 40 m.
  EXPECT_FLOAT_EQ(20.0f, pc.getRange(0));
  EXPECT_FLOAT_EQ(40.0f, pc.getRange(1));
  EXPECT_EQ(1U, pc.getEchoIndex(0));
  EXPECT_EQ(1U, pc.getEchoIndex(1));
}
