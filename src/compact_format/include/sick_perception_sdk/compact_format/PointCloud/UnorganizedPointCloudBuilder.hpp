/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/quantities/Timestamp.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudAttributes.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudBuilder.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudConfiguration.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloud.hpp>

#include <cassert>
#include <cstdint>
#include <cstring>
#include <functional>
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
 * @warning The builder's API relies on the data order of the underlying UnorganizedPointCloud. 
 * It is the caller's responsibility to write fields in the correct order.
 *
 * Usage:
 * @code
 * UnorganizedPointCloudBuilder builder(timestamp, configuration);
 * for (each point) {
 *   if (point is valid) {
 *     builder.beginPoint();
 *     builder.write(x);
 *     builder.write(y);
 *     builder.write(z);
 *     // ... write remaining fields in order
 *   }
 * }
 * auto cloud = builder.build();
 * @endcode
 */
class SDK_EXPORT UnorganizedPointCloudBuilder : public PointCloudBuilder<UnorganizedPointCloud>
{
public:
  /**
   * @brief Construct a builder for an unorganized point cloud with the given configuration and maximum number of points.
   * 
   * The maximum number of points is necessary to pre-allocate memory for the point cloud. The point cloud's memory will be shrunk
   * to the actual number of points when build() is called.
   */
  explicit UnorganizedPointCloudBuilder(PointCloudBuilder::FieldConfig const& fieldConfig, Timestamp pointCloudTimestamp, std::size_t maxNumberOfPoints);

  /**
   * @brief Grow the point cloud by the given number of points.
   * 
   * This function can be called to increase the maximum number of points. It will potentially reallocate memory.
   */
  void growBy(std::size_t numberOfPoints);

  /**
   * @brief Finalize and returns the built point cloud. Moves ownership to caller.
   *
   * @warning After calling build(), the builder is in an unspecified state. 
   *          The caller must not call any other methods on the builder after calling build().
   */
  auto build() -> UnorganizedPointCloud;

  void setPointCloudTimestamp(Timestamp timestamp)
  {
    m_pointCloud.m_timestamp = timestamp;
  }
};

} // namespace sick::point_cloud
