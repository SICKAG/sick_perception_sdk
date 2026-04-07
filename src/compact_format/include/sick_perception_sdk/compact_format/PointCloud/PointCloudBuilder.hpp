/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/quantities/Timestamp.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudAttributes.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudConfiguration.hpp>

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <functional>
#include <limits>
#include <set>
#include <stdexcept>
#include <vector>

namespace sick::point_cloud {

template <typename PointCloudT>
class PointCloudBuilder
{
public:
  struct FieldConfig
  {
    std::set<PointField::FieldType> desired;
    std::set<PointField::FieldType> available;
  };

  /**
   * @brief Begins writing a new valid point. Must be called before write() calls.
   */
  void beginPoint()
  {
    if (m_numberOfAddedPoints >= m_pointCloud.numberOfPoints())
    {
      throw std::runtime_error("Cannot begin point because it would exceed the maximum number of points");
    }

    m_numberOfBytesWrittenInCurrentPoint  = 0;
    m_numberOfFieldsWrittenInCurrentPoint = 0;
    m_numberOfAddedPoints++;
  }

  /**
   * @brief Write a value to the current point. Values must be written in field order and order the point cloud expects it.
   *
   * In debug builds, asserts that writes don't exceed the point size.
   */
  template <typename ValueT>
  void writeNextFieldValueOrIgnore(PointField::FieldType fieldType, ValueT value)
  {
    if (fieldType != m_fieldsAddedToPointCloud[m_numberOfFieldsWrittenInCurrentPoint])
    {
      // If the field is not the expected next field, we ignore it.
      return;
    }

    assert(m_pointCloudDataWritePosition + sizeof(ValueT) <= m_pointCloud.m_data.size() && "Write exceeds allocated buffer");

    m_numberOfBytesWrittenInCurrentPoint += sizeof(ValueT);
    assert(m_numberOfBytesWrittenInCurrentPoint <= m_pointCloud.pointSizeBytes() && "Write exceeds point size");

    std::memcpy(&m_pointCloud.m_data[m_pointCloudDataWritePosition], &value, sizeof(ValueT));
    m_pointCloudDataWritePosition += sizeof(ValueT);
    m_numberOfFieldsWrittenInCurrentPoint++;
  }

protected:
  /**
   * @brief Protected ctor for use by derived builders.
   * 
   * This ctor is called with two sets of field types (see `FieldConfig`):
   * 
   * 1. The desired set describes the fields that the caller of the builder wants to have in the point cloud. 
   *    This is typically based on the fields that are expected by downstream processing or by the user.
   * 2. The available set describes the fields that are actually available in the input data and can be provided in the point cloud.
   * 
   * The resulting point cloud will have the intersection of these two sets as its fields, in the order defined by the desired set.
   * 
   * @see FieldConfig
   */
  explicit PointCloudBuilder(FieldConfig const& fieldConfig)
    : m_pointCloud()
  {
    // Compute the intersection of desired and available fields while preserving the order of desired fields.
    // This ensures that the point cloud only contains fields that are both desired and available,
    // and that the fields are ordered according to the desired fields.
    auto const& [desiredFields, availableFields] = fieldConfig;
    std::set_intersection(
      desiredFields.begin(),
      desiredFields.end(),
      availableFields.begin(),
      availableFields.end(),
      std::back_inserter(m_fieldsAddedToPointCloud)
    );

    if (m_fieldsAddedToPointCloud.empty())
    {
      throw std::invalid_argument("Desired fields and available fields have no intersection, cannot create point cloud with zero fields");
    }
  };

  /**
   * @brief Calls `addField` for each field with the correct field and data types and the field offset in bytes.
   * 
   * @return The total size of one point in bytes.
   */
  auto addFields() -> std::uint32_t
  {
    using FieldType = PointField::FieldType;
    using DataType  = PointField::DataType;

    // Performance improvement for field access: Store the index of each field type in m_fields for O(1) access instead of O(n) search.
    // The m_fieldIndexesForFieldType vector is initialized with -1 for all field types, which indicates that the field type is
    // not present in the point cloud. Each time a field is added, the corresponding index for its field type is updated to the correct
    // index in m_fields.
    m_pointCloud.m_fieldIndexesForFieldType = std::vector<int>(static_cast<std::size_t>(PointField::FieldType::Last), -1);

    auto addField = [this](PointField::FieldType fieldType, PointField::DataType dataType, std::uint32_t fieldOffsetBytes) -> void {
      m_pointCloud.m_fields.emplace_back(PointField {fieldType, fieldOffsetBytes, dataType});
      m_pointCloud.m_fieldIndexesForFieldType[static_cast<std::size_t>(fieldType)] = static_cast<int>(m_pointCloud.m_fields.size() - 1);
    };

    std::uint32_t currentOffset = 0;

    for (auto const& field : m_fieldsAddedToPointCloud)
    {
      switch (field)
      {
      case FieldType::X:
      case FieldType::Y:
      case FieldType::Z:
        addField(field, DataType::Float32, currentOffset);
        currentOffset += sizeof(float);
        break;
      case FieldType::Range:
      case FieldType::Azimuth:
      case FieldType::Elevation:
        addField(field, DataType::Float32, currentOffset);
        currentOffset += sizeof(float);
        break;
      case FieldType::Intensity:
        addField(field, DataType::Float32, currentOffset);
        currentOffset += sizeof(float);
        break;
      case FieldType::TimeOffsetNanoseconds:
      case FieldType::TimeOffsetSeconds:
        addField(field, DataType::Uint32, currentOffset);
        currentOffset += sizeof(std::uint32_t);
        break;
      case FieldType::Ring:
      case FieldType::LayerId:
      case FieldType::EchoIndex:
      case FieldType::IsReflector:
      case FieldType::HasBlooming:
        addField(field, DataType::Uint8, currentOffset);
        currentOffset += sizeof(std::uint8_t);
        break;
      case FieldType::PulseWidth:
        addField(field, DataType::Float32, currentOffset);
        currentOffset += sizeof(float);
        break;
      default:
        throw std::runtime_error("Unsupported field type");
      }
    }

    return currentOffset;
  }

  std::size_t m_numberOfAddedPoints                 = 0;
  std::size_t m_pointCloudDataWritePosition         = 0;
  std::size_t m_numberOfBytesWrittenInCurrentPoint  = 0;
  std::size_t m_numberOfFieldsWrittenInCurrentPoint = 0;
  PointCloudT m_pointCloud;
  std::vector<PointField::FieldType> m_fieldsAddedToPointCloud;
};

} // namespace sick::point_cloud
