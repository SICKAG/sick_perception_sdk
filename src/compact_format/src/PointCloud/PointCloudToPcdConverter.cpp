/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/PointCloud/PointCloudToPcdConverter.hpp>

#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloud.hpp>

#include <cstdint>
#include <cstring> // for std::memcpy
#include <fstream>
#include <iomanip>
#include <ios>
#include <ostream>
#include <stdexcept>

namespace sick::pcd {

namespace {

using FieldType = point_cloud::PointField::FieldType;
using DataType  = point_cloud::PointField::DataType;

auto toPcdFieldName(FieldType type) -> char const*
{
  switch (type)
  {
  case FieldType::X:
    return "x";
  case FieldType::Y:
    return "y";
  case FieldType::Z:
    return "z";
  case FieldType::Range:
    return "range";
  case FieldType::Azimuth:
    return "azimuth";
  case FieldType::Elevation:
    return "elevation";
  case FieldType::Intensity:
    return "intensity";
  case FieldType::TimeOffsetNanoseconds:
    return "t";
  case FieldType::TimeOffsetSeconds:
    return "ts";
  case FieldType::Ring:
    return "ring";
  case FieldType::LayerId:
    return "layer";
  case FieldType::EchoIndex:
    return "echo";
  case FieldType::IsReflector:
    return "isReflector";
  case FieldType::HasBlooming:
    return "hasBlooming";
  case FieldType::PulseWidth:
    return "pulseWidth";
  default:
    return "unknown";
  }
}

struct PcdFieldInfo
{
  char type; // 'F', 'I', 'U'
  int size;
};

auto getPcdFieldInfo(DataType type) -> PcdFieldInfo
{
  switch (type)
  {
  case DataType::Bool:
    return {'U', sizeof(bool)};
  case DataType::Int8:
    return {'I', sizeof(std::int8_t)};
  case DataType::Uint8:
    return {'U', sizeof(std::uint8_t)};
  case DataType::Int16:
    return {'I', sizeof(std::int16_t)};
  case DataType::Uint16:
    return {'U', sizeof(std::uint16_t)};
  case DataType::Int32:
    return {'I', sizeof(std::int32_t)};
  case DataType::Uint32:
    return {'U', sizeof(std::uint32_t)};
  case DataType::Int64:
    return {'I', sizeof(std::int64_t)};
  case DataType::Uint64:
    return {'U', sizeof(std::uint64_t)};
  case DataType::Float32:
    return {'F', sizeof(float)};
  case DataType::Float64:
    return {'F', sizeof(double)};
  default:
    throw std::runtime_error("Unsupported PointField datatype");
  }
}

// Helper to write PCD header for all fields
void writePcdHeader(std::ostream& stream, point_cloud::UnorganizedPointCloud const& cloud, bool binary)
{
  stream << "# .PCD v.7 - Point Cloud Data file format\n";
  stream << "VERSION .7\n";
  stream << "FIELDS";
  for (auto const& field : cloud.fields())
  {
    stream << " " << toPcdFieldName(field.fieldType);
  }
  stream << "\nSIZE";
  for (auto const& field : cloud.fields())
  {
    stream << " " << getPcdFieldInfo(field.dataType).size;
  }
  stream << "\nTYPE";
  for (auto const& field : cloud.fields())
  {
    stream << " " << getPcdFieldInfo(field.dataType).type;
  }
  stream << "\nCOUNT";
  for (auto const& field : cloud.fields())
  {
    stream << " 1";
  }
  stream << "\nWIDTH " << cloud.numberOfPoints() << "\nHEIGHT 1\n"; // Always unorganized
  stream << "VIEWPOINT 0 0 0 1 0 0 0\n";
  stream << "POINTS " << cloud.numberOfPoints() << "\n";
  stream << "DATA " << (binary ? "binary" : "ascii") << "\n";
}

// Helper to write one point in ASCII
void writePointAscii(point_cloud::UnorganizedPointCloud const& cloud, std::size_t pointIndex, std::ostream& stream)
{
  constexpr int kFloatPrecision = 6;

  for (std::size_t fieldIndex = 0; fieldIndex < cloud.fields().size(); ++fieldIndex)
  {
    auto const& field = cloud.fields()[fieldIndex];

    switch (field.fieldType)
    {
    case FieldType::X:
      stream << std::fixed << std::setprecision(kFloatPrecision) << cloud.getX(pointIndex);
      break;
    case FieldType::Y:
      stream << std::fixed << std::setprecision(kFloatPrecision) << cloud.getY(pointIndex);
      break;
    case FieldType::Z:
      stream << std::fixed << std::setprecision(kFloatPrecision) << cloud.getZ(pointIndex);
      break;
    case FieldType::Range:
      stream << std::fixed << std::setprecision(kFloatPrecision) << cloud.getRange(pointIndex);
      break;
    case FieldType::Azimuth:
      stream << std::fixed << std::setprecision(kFloatPrecision) << cloud.getAzimuth(pointIndex);
      break;
    case FieldType::Elevation:
      stream << std::fixed << std::setprecision(kFloatPrecision) << cloud.getElevation(pointIndex);
      break;
    case FieldType::Intensity:
      stream << std::fixed << std::setprecision(kFloatPrecision) << cloud.getIntensity(pointIndex);
      break;
    case FieldType::TimeOffsetNanoseconds:
      stream << std::get<1>(cloud.getTimeOffset(pointIndex));
      break;
    case FieldType::TimeOffsetSeconds:
      stream << std::get<0>(cloud.getTimeOffset(pointIndex));
      break;
    case FieldType::Ring:
      stream << static_cast<unsigned int>(cloud.getRing(pointIndex));
      break;
    case FieldType::LayerId:
      stream << static_cast<unsigned int>(cloud.getLayer(pointIndex));
      break;
    case FieldType::EchoIndex:
      stream << static_cast<unsigned int>(cloud.getEcho(pointIndex));
      break;
    case FieldType::IsReflector:
      stream << (cloud.isReflector(pointIndex) ? "1" : "0");
      break;
    case FieldType::HasBlooming:
      stream << (cloud.hasBlooming(pointIndex) ? "1" : "0");
      break;
    case FieldType::PulseWidth:
      stream << std::fixed << std::setprecision(kFloatPrecision) << cloud.getPulseWidth(pointIndex);
      break;
    default:
      throw std::runtime_error("Unsupported PointField type");
    }

    if (fieldIndex + 1 < cloud.fields().size())
    {
      stream << " ";
    }
  }
  stream << "\n";
}

} // anonymous namespace

void convertToBinary(point_cloud::UnorganizedPointCloud const& pointCloud, std::ostream& outputStream)
{
  writePcdHeader(outputStream, pointCloud, true);
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  outputStream.write(reinterpret_cast<char const*>(pointCloud.rawBytes()), static_cast<std::streamsize>(pointCloud.rawByteSize()));
}

void convertToAscii(point_cloud::UnorganizedPointCloud const& pointCloud, std::ostream& outputStream)
{
  writePcdHeader(outputStream, pointCloud, false);
  for (auto pointIndex = 0; pointIndex < pointCloud.numberOfPoints(); ++pointIndex)
  {
    writePointAscii(pointCloud, pointIndex, outputStream);
  }
}

void writeToAsciiFile(point_cloud::UnorganizedPointCloud const& pointCloud, std::string const& filePath)
{
  // open in binary mode to prevent the compiler from converting \n to \r\n on windows
  std::ofstream file(filePath, std::ios_base::binary);
  if (!file.is_open())
  {
    std::cout << "Could not open file " << filePath << " for writing.\n";
    return;
  }
  convertToAscii(pointCloud, file);
  std::cout << "Wrote point cloud with " << pointCloud.numberOfPoints() << " points to " << filePath << "\n";
  file.close();
}

} // namespace sick::pcd
