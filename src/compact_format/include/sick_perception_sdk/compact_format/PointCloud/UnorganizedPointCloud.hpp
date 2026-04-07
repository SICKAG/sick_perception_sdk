/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/quantities/Timestamp.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudAttributes.hpp>

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <tuple>
#include <vector>

namespace sick::point_cloud {

/**
 * @brief Data structure representing an unorganized point cloud.
 *
 * This is a common transfer format for point clouds in the sick_perception_sdk.
 *
 * The sick_perception_sdk provides converters from Compact format representations that contain data convertible to point clouds
 * into this point cloud structure.
 *
 * @see `sick::compact::scan_data::PointCloudConverter`
 * 
 * The order of fields in the raw data is defined by the order of `fields` in the point cloud.
 * The offset and datatype information for each field can be used to interpret the point data correctly.
 * 
 * The point values are stored sequentially without any particular order.
 */
class SDK_EXPORT UnorganizedPointCloud
{
public:
  template <typename PointCloudT>
  friend class PointCloudBuilder;
  friend class UnorganizedPointCloudBuilder;

  auto density() const -> Density
  {
    return m_density;
  }

  auto fields() const -> std::vector<PointField> const&
  {
    return m_fields;
  }

  auto isEmpty() const -> bool
  {
    return m_data.empty();
  }

  auto numberOfPoints() const -> std::size_t
  {
    return m_data.size() / m_pointSizeBytes;
  }

  auto pointSizeBytes() const -> std::uint32_t
  {
    return m_pointSizeBytes;
  }

  auto rawBytes() const -> std::uint8_t const*
  {
    return m_data.data();
  }

  auto rawByteSize() const -> std::size_t
  {
    return m_data.size();
  }

  auto timestamp() const -> Timestamp
  {
    return m_timestamp;
  }

  // Convenience accessors for the point cloud fields.
  // Each of them throws std::invalid_argument if the required field is not present in the point cloud or std::out_of_range if the point index is out of bounds.

  auto getX(std::size_t pointIndex) const -> float
  {
    return getFieldValue<float>(PointField::FieldType::X, pointIndex);
  }

  auto getY(std::size_t pointIndex) const -> float
  {
    return getFieldValue<float>(PointField::FieldType::Y, pointIndex);
  }

  auto getZ(std::size_t pointIndex) const -> float
  {
    return getFieldValue<float>(PointField::FieldType::Z, pointIndex);
  }

  /**
   * @return Tuple of (x, y, z) coordinates.
   */
  auto getCartesian(std::size_t pointIndex) const -> std::tuple<float, float, float>
  {
    return {getX(pointIndex), getY(pointIndex), getZ(pointIndex)};
  }

  auto getRange(std::size_t pointIndex) const -> float
  {
    return getFieldValue<float>(PointField::FieldType::Range, pointIndex);
  }

  auto getAzimuth(std::size_t pointIndex) const -> float
  {
    return getFieldValue<float>(PointField::FieldType::Azimuth, pointIndex);
  }

  auto getElevation(std::size_t pointIndex) const -> float
  {
    return getFieldValue<float>(PointField::FieldType::Elevation, pointIndex);
  }

  /**
   * @return Tuple of (range, azimuth, elevation).
   */
  auto getSpherical(std::size_t pointIndex) const -> std::tuple<float, float, float>
  {
    return {getRange(pointIndex), getAzimuth(pointIndex), getElevation(pointIndex)};
  }

  auto getIntensity(std::size_t pointIndex) const -> float
  {
    return getFieldValue<float>(PointField::FieldType::Intensity, pointIndex);
  }

  /**
   * @return Tuple of (timeOffsetSeconds, timeOffsetNanoseconds).
   */
  auto getTimeOffset(std::size_t pointIndex) const -> std::tuple<std::uint32_t, std::uint32_t>
  {
    return {
      getFieldValue<std::uint32_t>(PointField::FieldType::TimeOffsetSeconds, pointIndex),
      getFieldValue<std::uint32_t>(PointField::FieldType::TimeOffsetNanoseconds, pointIndex)
    };
  }

  auto getRing(std::size_t pointIndex) const -> std::uint8_t
  {
    return getFieldValue<std::uint8_t>(PointField::FieldType::Ring, pointIndex);
  }

  auto getLayer(std::size_t pointIndex) const -> std::uint8_t
  {
    return getRing(pointIndex);
  }

  auto getEcho(std::size_t pointIndex) const -> std::uint8_t
  {
    return getFieldValue<std::uint8_t>(PointField::FieldType::EchoIndex, pointIndex);
  }

  auto isReflector(std::size_t pointIndex) const -> bool
  {
    return getFieldValue<bool>(PointField::FieldType::IsReflector, pointIndex);
  }

  auto hasBlooming(std::size_t pointIndex) const -> bool
  {
    return getFieldValue<bool>(PointField::FieldType::HasBlooming, pointIndex);
  }

  auto getPulseWidth(std::size_t pointIndex) const -> float
  {
    return getFieldValue<float>(PointField::FieldType::PulseWidth, pointIndex);
  }

protected:
  Timestamp m_timestamp = Timestamp::fromMicrosecondsSinceEpoch(0);
  Density m_density     = Density::AllPointsValid;
  std::vector<PointField> m_fields;
  std::vector<int> m_fieldIndexesForFieldType; ///< Index in m_fields for each PointField::FieldType, -1 if field type is not present.
  std::uint32_t m_pointSizeBytes = 0;
  std::vector<std::uint8_t> m_data; ///< Actual point data, size is (number of points * point step).

  /**
   * @brief ctor is private because only builders may create point cloud instances.
   */
  UnorganizedPointCloud() = default;

  template <typename OutputT>
  static auto convertFromRuntimeType(std::uint8_t const* dataPtr, PointField::DataType runtimeType) -> OutputT
  {
    // NOLINTBEGIN(cppcoreguidelines-init-variables) variables are not initialized intentionally to avoid unnecessary initialization overhead before memcpy
    switch (runtimeType)
    {
    case PointField::DataType::Bool:
    {
      std::uint8_t value;
      std::memcpy(&value, dataPtr, sizeof(std::uint8_t));
      return static_cast<OutputT>(value != 0);
    }
    case PointField::DataType::Int8:
    {
      std::int8_t value;
      std::memcpy(&value, dataPtr, sizeof(std::int8_t));
      return static_cast<OutputT>(value);
    }
    case PointField::DataType::Uint8:
    {
      std::uint8_t value;
      std::memcpy(&value, dataPtr, sizeof(std::uint8_t));
      return static_cast<OutputT>(value);
    }
    case PointField::DataType::Int16:
    {
      std::int16_t value;
      std::memcpy(&value, dataPtr, sizeof(std::int16_t));
      return static_cast<OutputT>(value);
    }
    case PointField::DataType::Uint16:
    {
      std::uint16_t value;
      std::memcpy(&value, dataPtr, sizeof(std::uint16_t));
      return static_cast<OutputT>(value);
    }
    case PointField::DataType::Int32:
    {
      std::int32_t value;
      std::memcpy(&value, dataPtr, sizeof(std::int32_t));
      return static_cast<OutputT>(value);
    }
    case PointField::DataType::Uint32:
    {
      std::uint32_t value;
      std::memcpy(&value, dataPtr, sizeof(std::uint32_t));
      return static_cast<OutputT>(value);
    }
    case PointField::DataType::Int64:
    {
      std::int64_t value;
      std::memcpy(&value, dataPtr, sizeof(std::int64_t));
      return static_cast<OutputT>(value);
    }
    case PointField::DataType::Uint64:
    {
      std::uint64_t value;
      std::memcpy(&value, dataPtr, sizeof(std::uint64_t));
      return static_cast<OutputT>(value);
    }
    case PointField::DataType::Float32:
    {
      float value;
      std::memcpy(&value, dataPtr, sizeof(float));
      return static_cast<OutputT>(value);
    }
    case PointField::DataType::Float64:
    {
      double value;
      std::memcpy(&value, dataPtr, sizeof(double));
      return static_cast<OutputT>(value);
    }
    default:
      throw std::invalid_argument("Unsupported PointField::DataType");
    }
    // NOLINTEND(cppcoreguidelines-init-variables)
  }

  /**
   * @brief Access a field value by linear point index and return type.
   * 
   * @warning Caution! This expects that the return type matches the field's actual type. 
   *          The function does not perform any type conversions or checks that 
   *          the requested type is compatible with the field's actual type.
   * 
   * @tparam ValueT The type to return the field value as.
   * @param fieldType The type of the field to access.
   * @param pointIndex The linear index of the point (0 to numberOfPoints-1).
   * 
   * @throws std::out_of_range if point index is out of bounds or field not found.
   */
  template <typename ValueT>
  auto getFieldValue(PointField::FieldType fieldType, std::size_t pointIndex) const -> ValueT
  {
    auto const searchIndex = static_cast<std::size_t>(fieldType);
    if (searchIndex >= m_fieldIndexesForFieldType.size())
    {
      throw std::out_of_range("Field type not found");
    }

    auto const fieldIndex = m_fieldIndexesForFieldType[searchIndex];
    if (fieldIndex < 0)
    {
      throw std::out_of_range("Field type not found");
    }

    auto const& field = m_fields[fieldIndex];

    auto const byteIndexForPoint = field.offset + pointIndex * m_pointSizeBytes;
    if (byteIndexForPoint + sizeof(ValueT) > m_data.size())
    {
      throw std::out_of_range("Point index out of range");
    }

    std::uint8_t const* dataPtr = &m_data[byteIndexForPoint];
    return convertFromRuntimeType<ValueT>(dataPtr, field.dataType);
  }
};

} // namespace sick::point_cloud
