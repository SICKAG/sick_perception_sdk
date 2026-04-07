/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudConfiguration.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloud.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/PointCloudCollector.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanData.hpp>

namespace sick::compact::scan_data {

class SDK_EXPORT PointCloudConverter
{
public:
  PointCloudConverter();
  explicit PointCloudConverter(point_cloud::PointCloudConfiguration configuration);

  auto convert(ScanData const& scanData) -> point_cloud::UnorganizedPointCloud;

private:
  PointCloudCollector m_collector;
};

} // namespace sick::compact::scan_data
