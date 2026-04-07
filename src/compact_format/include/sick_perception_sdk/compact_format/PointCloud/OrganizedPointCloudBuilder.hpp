/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/quantities/Timestamp.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/OrganizedPointCloud.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudAttributes.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudBuilder.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudConfiguration.hpp>

#include <cassert>
#include <cstdint>
#include <cstring>
#include <limits>
#include <stdexcept>
#include <vector>

namespace sick::point_cloud {

/**
 * @brief A builder class for constructing point clouds with RAII design.
 *
 * All configuration happens at construction time. The builder pre-allocates memory
 * for the maximum number of points (width × height) and provides methods to write
 * point data sequentially.
 * 
 * @warning The builder's API relies on the data order of the underlying OrganizedPointCloud. 
 * It is the caller's responsibility to write fields in the correct order.
 *
 * Usage:
 * @code
 * OrganizedPointCloudBuilder builder(fieldConfig, timestamp, width, height, numberOfEchoesPerBeam);
 * for (each point) {
 *   if (point is valid) {
 *     builder.beginPoint();
 *     builder.write(x);
 *     builder.write(y);
 *     builder.write(z);
 *     // ... write remaining fields in order
 *   } else {
 *     builder.writeInvalidPoint();
 *   }
 * }
 * auto cloud = builder.build();
 * @endcode
 */
class SDK_EXPORT OrganizedPointCloudBuilder : public PointCloudBuilder<OrganizedPointCloud>
{
public:
  explicit OrganizedPointCloudBuilder(
    PointCloudBuilder::FieldConfig const& fieldConfig,
    Timestamp pointCloudTimestamp,
    std::size_t width,
    std::size_t height,
    std::size_t numberOfEchoesPerBeam
  );

  /**
   * @brief Write an invalid point with NaN for floats and 0 for integers.
   *
   * Use this for organized point clouds when a point is filtered out but
   * the grid structure must be preserved.
   */
  void writeInvalidPoint();

  /**
   * @brief Finalize and returns the built point cloud. Moves ownership to caller.
   *
   * After calling build(), the builder is in an unspecified state and should not be used.
   */
  auto build() -> OrganizedPointCloud;
};

} // namespace sick::point_cloud
