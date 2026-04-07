/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloud.hpp>

#include <iostream>
#include <string>

namespace sick::pcd {

SDK_EXPORT void convertToAscii(point_cloud::UnorganizedPointCloud const& pointCloud, std::ostream& outputStream);
SDK_EXPORT void convertToBinary(point_cloud::UnorganizedPointCloud const& pointCloud, std::ostream& outputStream);
SDK_EXPORT void writeToAsciiFile(point_cloud::UnorganizedPointCloud const& pointCloud, std::string const& filePath);

} // namespace sick::pcd
