/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/PointCloud/PointCloudConfiguration.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloud.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/PointCloudConverter.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanData.hpp>

#include <utility>

namespace sick::compact::scan_data {

PointCloudConverter::PointCloudConverter()
  : m_collector(point_cloud::PointCloudConfiguration())
{ }

PointCloudConverter::PointCloudConverter(point_cloud::PointCloudConfiguration configuration)
  : m_collector(std::move(configuration))
{ }

auto PointCloudConverter::convert(ScanData const& scanData) -> point_cloud::UnorganizedPointCloud
{
  m_collector.reset();
  m_collector.collect(scanData);
  return m_collector.getPointCloud();
}

} // namespace sick::compact::scan_data
