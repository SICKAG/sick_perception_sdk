/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloudCollector.hpp>

#include <sick_perception_sdk/compact_format/PointCloud/PointCloudAttributes.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloud.hpp>

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <mutex>
#include <stdexcept>

namespace sick::point_cloud {

namespace {

constexpr std::uint64_t kNanosecondsPerSecond      = 1'000'000'000ULL;
constexpr std::uint64_t kNanosecondsPerMicrosecond = 1'000ULL;

} // namespace

// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic) point cloud collection is done with direct memory access.

void UnorganizedPointCloudCollector::push(UnorganizedPointCloud const& pointCloud)
{
  std::scoped_lock<std::mutex> const lock(m_mutex);

  if (pointCloud.isEmpty())
  {
    throw std::invalid_argument("Cannot push empty point cloud");
  }

  if (m_data.empty())
  {
    validateAndInitializeLayout(pointCloud);
  }
  else
  {
    validateLayoutMatch(pointCloud);
  }

  appendPointsWithTimeOffsetCorrection(pointCloud);
}

void UnorganizedPointCloudCollector::clear()
{
  std::scoped_lock<std::mutex> const lock(m_mutex);

  m_timestamp = Timestamp::fromMicrosecondsSinceEpoch(0);
  m_fields.clear();
  m_fieldIndexesForFieldType.clear();
  m_pointSizeBytes = 0;
  m_data.clear();
  m_hasTimeOffsetFields             = false;
  m_timeOffsetSecondsFieldIndex     = -1;
  m_timeOffsetNanosecondsFieldIndex = -1;
}

auto UnorganizedPointCloudCollector::getMergedPointCloud() const -> UnorganizedPointCloud
{
  std::scoped_lock<std::mutex> const lock(m_mutex);

  if (m_data.empty())
  {
    throw std::logic_error("Cannot get merged point cloud from empty collector");
  }

  UnorganizedPointCloud result;
  result.m_timestamp                = m_timestamp;
  result.m_fields                   = m_fields;
  result.m_fieldIndexesForFieldType = m_fieldIndexesForFieldType;
  result.m_pointSizeBytes           = m_pointSizeBytes;
  result.m_data                     = m_data;

  return result;
}

auto UnorganizedPointCloudCollector::numberOfPoints() const -> std::size_t
{
  std::scoped_lock<std::mutex> const lock(m_mutex);

  if (m_pointSizeBytes == 0)
  {
    return 0;
  }
  return m_data.size() / m_pointSizeBytes;
}

auto UnorganizedPointCloudCollector::isEmpty() const -> bool
{
  std::scoped_lock<std::mutex> const lock(m_mutex);
  return m_data.empty();
}

void UnorganizedPointCloudCollector::validateAndInitializeLayout(UnorganizedPointCloud const& pointCloud)
{
  // Check for invalid time offset field configuration (only one of the pair present)
  auto const hasTimeOffsetSeconds     = std::any_of(pointCloud.m_fields.begin(), pointCloud.m_fields.end(), [](PointField const& field) -> bool {
    return field.fieldType == PointField::FieldType::TimeOffsetSeconds;
  });
  auto const hasTimeOffsetNanoseconds = std::any_of(pointCloud.m_fields.begin(), pointCloud.m_fields.end(), [](PointField const& field) -> bool {
    return field.fieldType == PointField::FieldType::TimeOffsetNanoseconds;
  });

  if (hasTimeOffsetSeconds != hasTimeOffsetNanoseconds)
  {
    throw std::invalid_argument("Point cloud must have both TimeOffsetSeconds and TimeOffsetNanoseconds fields or neither");
  }

  m_timestamp                = pointCloud.m_timestamp;
  m_fields                   = pointCloud.m_fields;
  m_fieldIndexesForFieldType = pointCloud.m_fieldIndexesForFieldType;
  m_pointSizeBytes           = pointCloud.m_pointSizeBytes;
  m_hasTimeOffsetFields      = hasTimeOffsetSeconds && hasTimeOffsetNanoseconds;

  if (m_hasTimeOffsetFields)
  {
    m_timeOffsetSecondsFieldIndex     = m_fieldIndexesForFieldType[static_cast<std::size_t>(PointField::FieldType::TimeOffsetSeconds)];
    m_timeOffsetNanosecondsFieldIndex = m_fieldIndexesForFieldType[static_cast<std::size_t>(PointField::FieldType::TimeOffsetNanoseconds)];
  }
}

void UnorganizedPointCloudCollector::validateLayoutMatch(UnorganizedPointCloud const& pointCloud) const
{
  // Check timestamp ordering
  if (pointCloud.m_timestamp < m_timestamp)
  {
    throw std::invalid_argument("Point cloud timestamp is smaller than the first collected point cloud timestamp");
  }

  // Check field count
  if (pointCloud.m_fields.size() != m_fields.size())
  {
    throw std::invalid_argument("Point cloud has different number of fields than the first collected point cloud");
  }

  // Check field types and order
  for (std::size_t i = 0; i < m_fields.size(); ++i)
  {
    if (pointCloud.m_fields[i].fieldType != m_fields[i].fieldType || pointCloud.m_fields[i].dataType != m_fields[i].dataType)
    {
      throw std::invalid_argument("Point cloud has different field types than the first collected point cloud");
    }
  }
}

void UnorganizedPointCloudCollector::appendPointsWithTimeOffsetCorrection(UnorganizedPointCloud const& pointCloud)
{
  auto const numberOfPointsToAdd = pointCloud.numberOfPoints();
  auto const bytesToAdd          = numberOfPointsToAdd * m_pointSizeBytes;

  // Calculate time offset correction in nanoseconds
  auto const timestampDifferenceUs = pointCloud.m_timestamp.microsecondsSinceEpoch() - m_timestamp.microsecondsSinceEpoch();
  auto const timestampDifferenceNs = static_cast<std::uint64_t>(timestampDifferenceUs) * kNanosecondsPerMicrosecond;

  // Store current size for strong exception guarantee
  auto const previousSize = m_data.size();

  try
  {
    // Reserve space for new data
    m_data.resize(previousSize + bytesToAdd);

    if (!m_hasTimeOffsetFields || timestampDifferenceNs == 0)
    {
      // No time offset correction needed, just copy the data
      std::memcpy(m_data.data() + previousSize, pointCloud.m_data.data(), bytesToAdd);
    }
    else
    {
      // Copy data and correct time offsets
      auto const timeOffsetSecondsOffset     = m_fields[static_cast<std::size_t>(m_timeOffsetSecondsFieldIndex)].offset;
      auto const timeOffsetNanosecondsOffset = m_fields[static_cast<std::size_t>(m_timeOffsetNanosecondsFieldIndex)].offset;

      for (std::size_t pointIdx = 0; pointIdx < numberOfPointsToAdd; ++pointIdx)
      {
        auto const srcPointOffset = pointIdx * m_pointSizeBytes;
        auto const dstPointOffset = previousSize + srcPointOffset;

        // Copy the entire point first
        std::memcpy(m_data.data() + dstPointOffset, pointCloud.m_data.data() + srcPointOffset, m_pointSizeBytes);

        // Read original time offset values
        std::uint32_t originalSeconds     = 0;
        std::uint32_t originalNanoseconds = 0;
        std::memcpy(&originalSeconds, pointCloud.m_data.data() + srcPointOffset + timeOffsetSecondsOffset, sizeof(std::uint32_t));
        std::memcpy(&originalNanoseconds, pointCloud.m_data.data() + srcPointOffset + timeOffsetNanosecondsOffset, sizeof(std::uint32_t));

        // Calculate corrected time offset
        auto const originalTotalNs  = static_cast<std::uint64_t>(originalSeconds) * kNanosecondsPerSecond + static_cast<std::uint64_t>(originalNanoseconds);
        auto const correctedTotalNs = originalTotalNs + timestampDifferenceNs;

        // Split back into seconds and nanoseconds
        auto const correctedSeconds     = static_cast<std::uint32_t>(correctedTotalNs / kNanosecondsPerSecond);
        auto const correctedNanoseconds = static_cast<std::uint32_t>(correctedTotalNs % kNanosecondsPerSecond);

        // Write corrected values
        std::memcpy(m_data.data() + dstPointOffset + timeOffsetSecondsOffset, &correctedSeconds, sizeof(std::uint32_t));
        std::memcpy(m_data.data() + dstPointOffset + timeOffsetNanosecondsOffset, &correctedNanoseconds, sizeof(std::uint32_t));
      }
    }
  }
  catch (...)
  {
    // Strong exception guarantee: restore previous state
    m_data.resize(previousSize);
    throw;
  }
}

// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)

} // namespace sick::point_cloud
