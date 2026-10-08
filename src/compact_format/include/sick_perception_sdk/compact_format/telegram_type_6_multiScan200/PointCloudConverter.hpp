/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/OrganizedPointCloud.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudAttributes.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudConfiguration.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloud.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_6_multiScan200/MultiScan200Data.hpp>

#include <set>

namespace sick::compact::multiscan200 {

/**
 * @brief Converter from the intermediate `MultiScan200Data` representation into the internal `PointCloud` representation.
 */
class SDK_EXPORT PointCloudConverter
{
public:
  explicit PointCloudConverter(point_cloud::PointCloudConfiguration configuration);

  auto convertToOrganized(MultiScan200Data const& data) const -> point_cloud::OrganizedPointCloud;
  auto convertToUnorganized(MultiScan200Data const& data) const -> point_cloud::UnorganizedPointCloud;

private:
  point_cloud::PointCloudConfiguration m_configuration;
  std::set<point_cloud::PointField::FieldType> m_desiredFields; // Cached set of desired fields from m_configuration
};

} // namespace sick::compact::multiscan200
