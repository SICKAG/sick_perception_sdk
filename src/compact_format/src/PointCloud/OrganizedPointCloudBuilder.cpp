/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/PointCloud/OrganizedPointCloudBuilder.hpp>

#include <sick_perception_sdk/common/quantities/Timestamp.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/OrganizedPointCloud.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudAttributes.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudConfiguration.hpp>

#include <cstddef>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace sick::point_cloud {

OrganizedPointCloudBuilder::OrganizedPointCloudBuilder(
  PointCloudBuilder::FieldConfig const& fieldConfig,
  Timestamp pointCloudTimestamp,
  std::size_t width,
  std::size_t height,
  std::size_t numberOfEchoesPerBeam
)
  : PointCloudBuilder<OrganizedPointCloud>(fieldConfig)
{
  m_pointCloud.m_timestamp             = pointCloudTimestamp;
  auto const pointSizeBytes            = this->addFields();
  m_pointCloud.m_pointSizeBytes        = pointSizeBytes;
  m_pointCloud.m_width                 = width;
  m_pointCloud.m_height                = height;
  m_pointCloud.m_numberOfEchoesPerBeam = numberOfEchoesPerBeam;

  auto const numberOfPoints = width * height * numberOfEchoesPerBeam;
  m_pointCloud.m_data.resize(numberOfPoints * pointSizeBytes);
}

void OrganizedPointCloudBuilder::writeInvalidPoint()
{
  this->beginPoint();

  // From now on the point cloud is marked as containing invalid points because there is a least one invalid point.
  m_pointCloud.m_density = Density::InvalidPointsContained;

  for (auto const& field : m_pointCloud.m_fields)
  {
    switch (field.dataType)
    {
    case PointField::DataType::Float32:
      this->writeNextFieldValueOrIgnore(field.fieldType, std::numeric_limits<float>::quiet_NaN());
      break;
    case PointField::DataType::Float64:
      this->writeNextFieldValueOrIgnore(field.fieldType, std::numeric_limits<double>::quiet_NaN());
      break;
    case PointField::DataType::Int8:
      this->writeNextFieldValueOrIgnore(field.fieldType, static_cast<std::int8_t>(0));
      break;
    case PointField::DataType::Uint8:
    case PointField::DataType::Bool:
      this->writeNextFieldValueOrIgnore(field.fieldType, static_cast<std::uint8_t>(0));
      break;
    case PointField::DataType::Int16:
      this->writeNextFieldValueOrIgnore(field.fieldType, static_cast<std::int16_t>(0));
      break;
    case PointField::DataType::Uint16:
      this->writeNextFieldValueOrIgnore(field.fieldType, static_cast<std::uint16_t>(0));
      break;
    case PointField::DataType::Int32:
      this->writeNextFieldValueOrIgnore(field.fieldType, static_cast<std::int32_t>(0));
      break;
    case PointField::DataType::Uint32:
      this->writeNextFieldValueOrIgnore(field.fieldType, static_cast<std::uint32_t>(0));
      break;
    case PointField::DataType::Int64:
      this->writeNextFieldValueOrIgnore(field.fieldType, static_cast<std::int64_t>(0));
      break;
    case PointField::DataType::Uint64:
      this->writeNextFieldValueOrIgnore(field.fieldType, static_cast<std::uint64_t>(0));
      break;
    }
  }
}

auto OrganizedPointCloudBuilder::build() -> OrganizedPointCloud
{
  if (this->m_numberOfAddedPoints != m_pointCloud.numberOfPoints())
  {
    throw std::runtime_error(
      "Number of added points (" + std::to_string(this->m_numberOfAddedPoints) + ") does not match expected number of points based on layout (" +
      std::to_string(m_pointCloud.numberOfPoints()) + ")."
    );
  }

  return std::move(m_pointCloud);
}

} // namespace sick::point_cloud
