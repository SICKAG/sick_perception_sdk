/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/quantities/Timestamp.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudAttributes.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloud.hpp>

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <vector>

namespace sick::point_cloud {

class OrganizedPointCloudBuilder;

/**
 * @brief Data structure representing a multi-echo point cloud.
 *
 * This is a common transfer format for point clouds in the sick_perception_sdk.
 * 
 * The order of fields in the raw data is defined by the order of `fields` in the point cloud.
 * The offset and datatype information for each field can be used to interpret the point data correctly.
 * 
 * **Data Layout:**
 * 
 * The point values are stored in a row-major order with all echoes of a point forming a tuple.
 * The first `width * numberOfEchoesPerBeam` points in `m_data` belong to the first row,
 * the second `width` points belong to the second row, and so on. 
 * 
 * An example is given below.
 * 
 * ```
 * memory address:   0                                           ...        width * height * numberOfEchoesPerBeam * pointSizeBytes - 1
 *                   |                                                                                                             |
 *                   v                                                                                                             v
 *                 +-----------------------------------+-----------------------------------+ ... +-----------------------------------+
 *                 | x | y | z | x | y | z | x | y | z | x | y | z | x | y | z | x | y | z | ... | x | y | z | x | y | z | x | y | z |
 *                 + ----------------------------------+ ----------------------------------+ ... + ----------------------------------+
 *                 |  echo 0   |  echo 1   |  echo 2   |  echo 0   |  echo 1   |  echo 2   | ... |  echo 0   |  echo 1   |  echo 2   |
 *                 |          row 0 column 0           |          row 0 column 1           | ... |   row (height-1) column (width-1) |
 * ```
 * 
 */
class SDK_EXPORT OrganizedPointCloud : public UnorganizedPointCloud
{
public:
  // Classes that can create point clouds get access to the raw data.
  template <typename PointCloudT>
  friend class PointCloudBuilder;
  friend class OrganizedPointCloudBuilder;

  auto numberOfEchoesPerBeam() const -> std::size_t
  {
    return m_numberOfEchoesPerBeam;
  }

  auto numberOfBeams() const -> std::size_t
  {
    return m_width * m_height;
  }

  auto width() const -> std::size_t
  {
    return m_width;
  }

  auto height() const -> std::size_t
  {
    return m_height;
  }

  /**
   * @brief Returns the linear point index for grid coordinates.
   *
   * Data is stored in row-major order: all columns and echoes for a row are stored
   * before moving to the next row.
   *
   * @param column Column index (0 to numberOfColumns-1, where numberOfColumns = width / numberOfEchoesPerBeam).
   * @param row Row index (0 to height-1).
   * @param echoIndex Echo index (0 to numberOfEchoesPerBeam-1).
   * @throws std::logic_error if the point cloud is unorganized.
   * @throws std::out_of_range if coordinates are out of bounds.
   */
  auto pointIndex(std::size_t column, std::size_t row, std::size_t echoIndex) const -> std::size_t
  {
    auto const numberOfColumns = m_width / m_numberOfEchoesPerBeam;
    if (column >= numberOfColumns || row >= m_height || echoIndex >= m_numberOfEchoesPerBeam)
    {
      throw std::out_of_range("Grid coordinates out of range");
    }

    return row * m_width + column * m_numberOfEchoesPerBeam + echoIndex;
  }

private:
  std::size_t m_width                 = 0; ///< Number of columns
  std::size_t m_height                = 1; ///< Number of rows
  std::size_t m_numberOfEchoesPerBeam = 1; ///< Number of echoes per beam

  /**
   * @brief ctor is private because only builders may create point cloud instances.
   */
  OrganizedPointCloud() = default;
};

} // namespace sick::point_cloud
