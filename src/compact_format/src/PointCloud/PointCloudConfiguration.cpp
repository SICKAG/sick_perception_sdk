/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/PointCloud/PointCloudConfiguration.hpp>

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
  result += "  enableLayerId: " + std::string(enableLayerId ? "true" : "false") + "\n";
  result += "  enableEchoIndex: " + std::string(enableEchoIndex ? "true" : "false") + "\n";
  result += "  enableIsReflector: " + std::string(enableIsReflector ? "true" : "false") + "\n";
  result += "  enableHasBlooming: " + std::string(enableHasBlooming ? "true" : "false") + "\n";
  result += "  enablePulseWidth: " + std::string(enablePulseWidth ? "true" : "false") + "\n";
  return result;
}

auto PointCloudConfiguration::Fields::toSet() const -> std::set<PointField::FieldType>
{
  std::set<PointField::FieldType> fields;
  if (enableCartesian)
  {
    fields.insert(PointField::FieldType::X);
    fields.insert(PointField::FieldType::Y);
    fields.insert(PointField::FieldType::Z);
  }
  if (enableSpherical)
  {
    fields.insert(PointField::FieldType::Range);
    fields.insert(PointField::FieldType::Azimuth);
    fields.insert(PointField::FieldType::Elevation);
  }
  if (enableIntensity)
  {
    fields.insert(PointField::FieldType::Intensity);
  }
  if (enableTimeOffset)
  {
    fields.insert(PointField::FieldType::TimeOffsetNanoseconds);
    fields.insert(PointField::FieldType::TimeOffsetSeconds);
  }
  if (enableRing)
  {
    fields.insert(PointField::FieldType::Ring);
  }
  if (enableLayerId)
  {
    fields.insert(PointField::FieldType::LayerId);
  }
  if (enableEchoIndex)
  {
    fields.insert(PointField::FieldType::EchoIndex);
  }
  if (enableIsReflector)
  {
    fields.insert(PointField::FieldType::IsReflector);
  }
  if (enableHasBlooming)
  {
    fields.insert(PointField::FieldType::HasBlooming);
  }
  if (enablePulseWidth)
  {
    fields.insert(PointField::FieldType::PulseWidth);
  }
  return fields;
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
  result += "  requiredReflectorFlag: ";
  if (requiredReflectorFlag)
  {
    result += (*requiredReflectorFlag ? "true" : "false");
  }
  else
  {
    result += "any";
  }
  result += "\n";

  result += "  requiredBloomingFlag: ";
  if (requiredBloomingFlag)
  {
    result += (*requiredBloomingFlag ? "true" : "false");
  }
  else
  {
    result += "any";
  }
  result += "\n";

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
