/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/quantities/Angle.hpp>
#include <sick_perception_sdk/common/quantities/Duration.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudConfiguration.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloud.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloudBuilder.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanData.hpp>

#include <chrono>
#include <cstdint>
#include <iterator>
#include <limits>
#include <map>
#include <optional>
#include <set>
#include <vector>

namespace sick::compact::scan_data {

/**
 * @brief Information about a layer that is used during point cloud collection.
 */
struct SDK_EXPORT LayerInfo
{
  std::uint8_t id {0};
  bool isInPointCloud {false};
  float sinElevation {std::numeric_limits<float>::quiet_NaN()};
  float cosElevation {std::numeric_limits<float>::quiet_NaN()};
  Duration firstBeamTimestampOffset;
  Duration timestampIncrementPerBeam;
  Angle azimuthIncrementPerBeam;
};

/**
 * @brief A class that collects point cloud data from scan data messages.
 * @details Call collect() for each scan data message that shall be in one point cloud, then call getPointCloud() to get
 * all points collected so far. Call reset() to start a new point cloud.
 */
class SDK_EXPORT PointCloudCollector
{
public:
  PointCloudCollector();
  explicit PointCloudCollector(point_cloud::PointCloudConfiguration configuration);

  /**
   * @brief Collects the scan data into the point cloud.
   */
  void collect(ScanData const& scanData);

  /**
   * @brief Resets the collector to start a new point cloud.
   */
  void reset();

  /**
   * @brief Returns the collected point cloud.
   * 
   * @warning The collector is in an unspecified state after calling this function and must be resetted before collecting new data.
   */
  auto getPointCloud() -> point_cloud::UnorganizedPointCloud;

private:
  point_cloud::PointCloudConfiguration m_configuration;
  std::set<point_cloud::PointField::FieldType> m_desiredFields; // Cached set of desired fields from m_configuration
  point_cloud::UnorganizedPointCloudBuilder m_builder;
  BitField<BeamContent> m_requiredBeamContent;
  BitField<EchoContent> m_requiredEchoContent;
  Timestamp m_pointCloudTimestamp;
  bool m_hasCollectionStarted {false};

  auto calculateLayerInfo(Module::MetaData const& moduleMetaData, std::map<Angle, std::uint8_t> const& elevationToLayerIdMapping, bool useAzimuthFromHeader)
    const -> std::vector<LayerInfo>;

  auto isEchoInvalid(Beam const& beam, Echo const& echo, std::size_t echoIndex, bool echoIsTheLastValidEcho) const -> bool;

  void validateTimestamps(ScanData const& scanData);

  void writeEcho(
    Echo const& echo,
    float cosAzimuth,
    float sinAzimuth,
    Angle elevation,
    Angle azimuth,
    LayerInfo const& layerInfo,
    std::uint32_t beamTimestampOffsetNanoseconds,
    std::uint32_t beamTimestampOffsetSeconds,
    std::size_t echoIndex,
    bool isAReflector,
    bool hasBlooming
  );
};

} // namespace sick::compact::scan_data
