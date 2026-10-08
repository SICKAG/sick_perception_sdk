/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/PointCloud/PointCloudConfiguration.hpp>

#include <sick_perception_sdk/compact_format/PointCloud/PointCloudAttributes.hpp>

#include <set>
#include <string>

namespace sick::point_cloud {

auto PointCloudConfiguration::Fields::toString() const -> std::string
{
  std::string result;
  result += "  enableCartesian: " + std::string(enableCartesian ? "true" : "false") + "\n";
  result += "  enableSpherical: " + std::string(enableSpherical ? "true" : "false") + "\n";
  result += "  enableIntensity: " + std::string(enableIntensity ? "true" : "false") + "\n";
  result += "  enableTimeOffset: " + std::string(enableTimeOffset ? "true" : "false") + "\n";
  result += "  enableRing: " + std::string(enableRing ? "true" : "false") + "\n";
  result += "  enableLayerIndex: " + std::string(enableLayerIndex ? "true" : "false") + "\n";
  result += "  enableColumnIndex: " + std::string(enableColumnIndex ? "true" : "false") + "\n";
  result += "  enableEchoIndex: " + std::string(enableEchoIndex ? "true" : "false") + "\n";
  result += "  enableProperties: " + std::string(enableProperties ? "true" : "false") + "\n";
  result += "  enablePulseWidth: " + std::string(enablePulseWidth ? "true" : "false") + "\n";
  return result;
}

auto PointCloudConfiguration::Fields::toSet() const -> std::set<PointField::FieldType>
{
  std::set<PointField::FieldType> ret;
  if (enableCartesian)
  {
    ret.insert(PointField::FieldType::X);
    ret.insert(PointField::FieldType::Y);
    ret.insert(PointField::FieldType::Z);
  }
  if (enableSpherical)
  {
    ret.insert(PointField::FieldType::Range);
    ret.insert(PointField::FieldType::Azimuth);
    ret.insert(PointField::FieldType::Elevation);
  }
  if (enableIntensity)
  {
    ret.insert(PointField::FieldType::Intensity);
  }
  if (enableTimeOffset)
  {
    ret.insert(PointField::FieldType::TimeOffsetNanoseconds);
    ret.insert(PointField::FieldType::TimeOffsetSeconds);
  }
  if (enableRing)
  {
    ret.insert(PointField::FieldType::Ring);
  }
  if (enableLayerIndex)
  {
    ret.insert(PointField::FieldType::LayerIndex);
  }
  if (enableColumnIndex)
  {
    ret.insert(PointField::FieldType::ColumnIndex);
  }
  if (enableEchoIndex)
  {
    ret.insert(PointField::FieldType::EchoIndex);
  }
  if (enableProperties)
  {
    ret.insert(PointField::FieldType::Properties);
  }
  if (enablePulseWidth)
  {
    ret.insert(PointField::FieldType::PulseWidth);
  }
  return ret;
}

auto PointCloudConfiguration::Filters::toString() const -> std::string
{
  std::string result;
  result += "  selectedEchos: ";
  if (selectedEchos)
  {
    result += "{";
    for (auto const& echo : *selectedEchos)
    {
      result += std::to_string(echo) + ", ";
    }
    if (!selectedEchos->empty())
    {
      result.pop_back();
      result.pop_back();
    }
    result += "}\n";
  }
  else
  {
    result += "all\n";
  }

  result += "  selectedLayers: ";
  if (selectedLayers)
  {
    result += "{";
    for (auto const& layer : *selectedLayers)
    {
      result += std::to_string(layer) + ", ";
    }
    if (!selectedLayers->empty())
    {
      result.pop_back();
      result.pop_back();
    }
    result += "}\n";
  }
  else
  {
    result += "all\n";
  }

  result += "  elevation: " + elevation.toString() + "\n";
  result += "  azimuth: " + azimuth.toString() + "\n";
  result += "  range: " + range.toString() + "\n";
  result += "  intensity: " + intensity.toString() + "\n";
  result += "  requiredProperties ";
  result += requiredProperties.has_value() ? std::to_string(requiredProperties->underlyingValue()) : "any";

  return result;
}

auto PointCloudConfiguration::toString() const -> std::string
{
  std::string result = "Fields:\n";
  result += fields.toString();
  result += "distanceScalingFactor: " + std::to_string(distanceScalingFactor) + "\n";
  result += "Filters:\n";
  result += filters.toString();
  return result;
}

} // namespace sick::point_cloud
