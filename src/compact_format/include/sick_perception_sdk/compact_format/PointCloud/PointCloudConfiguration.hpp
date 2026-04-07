/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/Interval.hpp>
#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/quantities/Angle.hpp>
#include <sick_perception_sdk/common/quantities/Distance.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudAttributes.hpp>

#include <cstdint>
#include <optional>
#include <set>
#include <string>

namespace sick::point_cloud {

// NOLINTBEGIN(misc-non-private-member-variables-in-classes)

struct SDK_EXPORT PointCloudConfiguration
{
  struct Fields
  {
    bool enableCartesian   = true;
    bool enableSpherical   = false;
    bool enableIntensity   = false;
    bool enableTimeOffset  = false;
    bool enableRing        = false;
    bool enableLayerId     = false;
    bool enableEchoIndex   = false;
    bool enableIsReflector = false;
    bool enableHasBlooming = false;
    bool enablePulseWidth  = false;

    auto toString() const -> std::string;
    auto toSet() const -> std::set<PointField::FieldType>;
  };

  struct Filters
  {
    /**
     * @brief The indices of the echos that shall be included in the point cloud. The first echo has index 0.
     * If not set, all echos are included.
     */
    std::optional<std::set<std::size_t>> selectedEchos;

    /**
     * @brief The indices of the layers that shall be included in the point cloud. The first layer has index 1.
     * If not set, all layers are included. The layer selection filter is applied in addition to the vertical angle
     * filter. A layer is included in the point cloud if it is selected by the layer filter and angle range filter.
     */
    std::optional<std::set<std::uint32_t>> selectedLayers;

    /**
     * @brief A filter for the vertical angle of the points in the point cloud. The angle is in radians. The vertical
     * angle filter is applied in addition to the layer selection filter. A layer is included in the point cloud if it
     * is selected by the layer filter and angle range filter.
     */
    Interval<Angle> azimuth;

    /**
     * @brief A filter for the horizontal angle of the points in the point cloud. The angle is in radians.
     */
    Interval<Angle> elevation;

    /**
     * @brief A filter for the range of the points in the point cloud. The filter is applied before multiplying with
     * the range scaling factor.
     */
    Interval<Distance> range;

    /**
     * @brief A filter for the intensity of the points in the point cloud.
     */
    Interval<float> intensity;

    /**
     * @brief Set to true to only include points that are marked as reflector in the point cloud. Set to false to only
     * include points that are not marked as reflector. Set to nullopt to include all points
     */
    std::optional<bool> requiredReflectorFlag;

    /** @brief Set to true to only include points that are marked as blooming in the point cloud. Set to false to only
     * include points that are not marked as blooming. Set to nullopt to include all points
     */
    std::optional<bool> requiredBloomingFlag;

    auto toString() const -> std::string;
  };

  Fields fields;

  /**
   * @brief A scaling factor that is applied to the distance values in the scan data before they are used to calculate
   * the point cloud coordinates. For example set this to 1'000.0f to convert the distance values from meters to millimeters.
   * The default value is 1.0f, the distance values are in meters.
   */
  float distanceScalingFactor = 1.0f;

  Filters filters;

  auto toString() const -> std::string;
};

// NOLINTEND(misc-non-private-member-variables-in-classes)

} // namespace sick::point_cloud
