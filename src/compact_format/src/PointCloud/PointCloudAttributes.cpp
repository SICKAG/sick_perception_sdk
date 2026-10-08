/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/PointCloud/PointCloudAttributes.hpp>

#include <string>

namespace sick::point_cloud {

auto PointField::fieldTypeToString(FieldType fieldType) -> std::string
{
  switch (fieldType)
  {
  case FieldType::X:
    return "X";
  case FieldType::Y:
    return "Y";
  case FieldType::Z:
    return "Z";
  case FieldType::Range:
    return "Range";
  case FieldType::Azimuth:
    return "Azimuth";
  case FieldType::Elevation:
    return "Elevation";
  case FieldType::Intensity:
    return "Intensity";
  case FieldType::TimeOffsetNanoseconds:
    return "TimeOffsetNanoseconds";
  case FieldType::TimeOffsetSeconds:
    return "TimeOffsetSeconds";
  case FieldType::Ring:
    return "Ring";
  case FieldType::LayerIndex:
    return "LayerIndex";
  case FieldType::ColumnIndex:
    return "ColumnIndex";
  case FieldType::EchoIndex:
    return "EchoIndex";
  case FieldType::Properties:
    return "Properties";
  case FieldType::PulseWidth:
    return "PulseWidth";
  case FieldType::Last:
    return "Last";
  default:
    return "Unknown";
  }
}

auto PointField::dataTypeToString(DataType dataType) -> std::string
{
  switch (dataType)
  {
  case DataType::Bool:
    return "Bool";
  case DataType::Int8:
    return "Int8";
  case DataType::Uint8:
    return "Uint8";
  case DataType::Int16:
    return "Int16";
  case DataType::Uint16:
    return "Uint16";
  case DataType::Int32:
    return "Int32";
  case DataType::Uint32:
    return "Uint32";
  case DataType::Int64:
    return "Int64";
  case DataType::Uint64:
    return "Uint64";
  case DataType::Float32:
    return "Float32";
  case DataType::Float64:
    return "Float64";
  default:
    return "Unknown";
  }
}

} // namespace sick::point_cloud
