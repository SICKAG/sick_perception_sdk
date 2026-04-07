/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloudBuilder.hpp>

#include <sick_perception_sdk/common/quantities/Timestamp.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudAttributes.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudConfiguration.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloud.hpp>

#include <cstddef>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <utility>
#include <vector>

namespace sick::point_cloud {

UnorganizedPointCloudBuilder::UnorganizedPointCloudBuilder(
  PointCloudBuilder::FieldConfig const& fieldConfig,
  Timestamp pointCloudTimestamp,
  std::size_t maxNumberOfPoints
)
  : PointCloudBuilder<UnorganizedPointCloud>(fieldConfig)
{
  m_pointCloud.m_timestamp      = pointCloudTimestamp;
  m_pointCloud.m_pointSizeBytes = this->addFields();

  m_pointCloud.m_data.resize(maxNumberOfPoints * m_pointCloud.pointSizeBytes());
}

void UnorganizedPointCloudBuilder::growBy(std::size_t numberOfPoints)
{
  // It is ok to compute the growth from the actual width of the point cloud so we don't waste too much memory.
  // It is the caller's intention to grow from the point cloud's current size, not from the maximum number of
  // points that was set at construction time or after.
  auto const newMaximumNumberOfPoints = this->m_numberOfAddedPoints + numberOfPoints;
  if (newMaximumNumberOfPoints > (std::numeric_limits<std::size_t>::max() / m_pointCloud.pointSizeBytes()))
  {
    throw std::overflow_error("Cannot grow point cloud because it would exceed maximum size");
  }
  m_pointCloud.m_data.resize(newMaximumNumberOfPoints * m_pointCloud.pointSizeBytes());
}

auto UnorganizedPointCloudBuilder::build() -> UnorganizedPointCloud
{
  // Shrink data vector to actual size
  m_pointCloud.m_data.resize(this->m_numberOfAddedPoints * m_pointCloud.pointSizeBytes());
  return std::move(m_pointCloud);
}

} // namespace sick::point_cloud
