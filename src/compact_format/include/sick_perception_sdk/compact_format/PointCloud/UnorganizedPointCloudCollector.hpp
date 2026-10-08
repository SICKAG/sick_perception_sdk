/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloud.hpp>

#include <cstdint>
#include <mutex>
#include <vector>

namespace sick::point_cloud {

/**
 * @brief Collect multiple UnorganizedPointCloud instances and merge them into a single point cloud.
 *
 * The collector is stateful and allows iterative collection of point clouds. The first pushed
 * point cloud defines the layout (fields) and density of the output. All subsequent point clouds
 * must have matching layout and density.
 *
 * Time offset values are corrected based on the timestamp difference between each input point cloud
 * and the first collected point cloud.
 *
 * This class is thread-safe. All public methods can be called concurrently from multiple threads.
 */
class SDK_EXPORT UnorganizedPointCloudCollector
{
public:
  UnorganizedPointCloudCollector() = default;

  UnorganizedPointCloudCollector(UnorganizedPointCloudCollector const&)                    = delete;
  auto operator=(UnorganizedPointCloudCollector const&) -> UnorganizedPointCloudCollector& = delete;

  UnorganizedPointCloudCollector(UnorganizedPointCloudCollector&&)                    = delete;
  auto operator=(UnorganizedPointCloudCollector&&) -> UnorganizedPointCloudCollector& = delete;

  ~UnorganizedPointCloudCollector() = default;

  /**
   * @brief Add a point cloud to the collector.
   *
   * The first pushed point cloud defines the layout (fields) and density for all subsequent pushes.
   * Time offset values are corrected by the difference between the input timestamp and the
   * timestamp of the first collected point cloud.
   *
   * @param pointCloud The point cloud to add.
   *
   * @throws std::invalid_argument if:
   *   - The point cloud is empty.
   *   - The point cloud has a smaller timestamp than the first collected point cloud.
   *   - The point cloud has different fields (number, order, or types) than the first collected point cloud.
   *   - The point cloud has a different density than the first collected point cloud.
   *   - The point cloud has only one of timeOffsetSeconds or timeOffsetNanoseconds fields.
   *   - Time offset correction would result in arithmetic underflow.
   *
   * @note Provides the strong exception guarantee: if an exception is thrown, the collector's state remains unchanged.
   */
  void push(UnorganizedPointCloud const& pointCloud);

  /**
   * @brief Resets the collector to its initial empty state.
   *
   * After calling clear(), the next push() defines the new layout and density.
   */
  void clear();

  /**
   * @brief Returns the merged point cloud containing all collected points.
   *
   * The collector retains its data after this call, allowing multiple calls to return the same result.
   *
   * @return The merged point cloud.
   *
   * @throws std::logic_error if the collector is empty.
   */
  auto getMergedPointCloud() const -> UnorganizedPointCloud;

  /**
   * @return The total number of points currently collected.
   */
  auto numberOfPoints() const -> std::size_t;

  /**
   * @return True if no points have been collected, false otherwise.
   */
  auto isEmpty() const -> bool;

private:
  mutable std::mutex m_mutex;

  Timestamp m_timestamp = Timestamp::fromMicrosecondsSinceEpoch(0);
  std::vector<PointField> m_fields;
  std::vector<int> m_fieldIndexesForFieldType;
  std::uint32_t m_pointSizeBytes = 0;
  std::vector<std::uint8_t> m_data;

  bool m_hasTimeOffsetFields            = false;
  int m_timeOffsetSecondsFieldIndex     = -1;
  int m_timeOffsetNanosecondsFieldIndex = -1;

  void validateAndInitializeLayout(UnorganizedPointCloud const& pointCloud);
  void validateLayoutMatch(UnorganizedPointCloud const& pointCloud) const;
  void appendPointsWithTimeOffsetCorrection(UnorganizedPointCloud const& pointCloud);
};

} // namespace sick::point_cloud
