/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/BitField.hpp>
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
    bool enableLayerIndex  = false;
    bool enableColumnIndex = false;
    bool enableEchoIndex   = false;
    bool enableProperties  = false;
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
     * @brief The indices of the layers that shall be included in the point cloud. The first layer has index 0.
     * If not set, all layers are included. The layer selection filter is applied in addition to the elevation angle
     * filter. A layer is included in the point cloud if it is selected by the layer filter and elevation angle range filter.
     */
    std::optional<std::set<std::uint32_t>> selectedLayers;

    /**
     * @brief A filter for the horizontal angle of the points in the point cloud. The angle is in radians.
     * The azimuth filter is applied independently of the layer selection filter.
     */
    Interval<Angle> azimuth;

    /**
     * @brief A filter for the vertical angle of the points in the point cloud. The angle is in radians. The elevation
     * angle filter is applied in addition to the layer selection filter. A layer is included in the point cloud if it
     * is selected by the layer filter and elevation angle range filter.
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
     * @brief Only points with the specified properties pattern are included in the point cloud. Set and unset bits are 
     * taken into account. Set to nullopt to include all points.
     */
    std::optional<BitField<Properties>> requiredProperties;

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
