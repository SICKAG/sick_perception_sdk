/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include "MultiScan200DataGenerator.hpp"

#include <sick_perception_sdk/common/BitField.hpp>
#include <sick_perception_sdk/common/quantities/Angle.hpp>
#include <sick_perception_sdk/common/quantities/Distance.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/OrganizedPointCloud.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudAttributes.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudConfiguration.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloud.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_6_multiScan200/MultiScan200Data.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_6_multiScan200/PointCloudConverter.hpp>

#include <gtest/gtest.h>

#include <cmath>
#include <cstddef>
#include <tuple>
#include <vector>

namespace sick::test {

using FieldType = sick::point_cloud::PointField::FieldType;

inline auto hasField(sick::point_cloud::UnorganizedPointCloud const& pc, FieldType fieldType) -> bool
{
  for (auto const& field : pc.fields())
  {
    if (field.fieldType == fieldType)
    {
      return true;
    }
  }
  return false;
}

inline void expectHasFields(sick::point_cloud::UnorganizedPointCloud const& pc, std::vector<FieldType> const& expectedFields)
{
  ASSERT_EQ(pc.fields().size(), expectedFields.size());
  for (auto const fieldType : expectedFields)
  {
    EXPECT_TRUE(hasField(pc, fieldType));
  }
}

inline void expectDoesNotHaveFields(sick::point_cloud::UnorganizedPointCloud const& pc, std::vector<FieldType> const& missingFields)
{
  for (auto const fieldType : missingFields)
  {
    EXPECT_FALSE(hasField(pc, fieldType));
  }
}

inline auto makeConverter(sick::point_cloud::PointCloudConfiguration const& config) -> sick::compact::multiscan200::PointCloudConverter
{
  return sick::compact::multiscan200::PointCloudConverter(config);
}

/**
 * @brief Creates a default MultiScan200Data object for testing.
 *
 * The default data has
 * - 2 rows
 * - 2 columns
 * - 1 echo
 *
 * Exact generated values for this helper call:
 * - frameSequenceNumber = 0
 * - segmentIndex = 0
 * - frameTimestamp = 0 us since epoch
 * - numberOfColumnsInFrame = 100
 *
 * Geometry:
 * - elevations (row 0..1): [-15.0 deg, +15.0 deg]
 * - azimuths (column 0..1): [0.0 deg, 3.6 deg]
 * - relativeTimeStamps (column 0..1): [0 us, 10 us]
 *
 * Distances in storage order (column-major over row for each echo):
 * - index 0 -> (echo=0, col=0, row=0): 1000 mm
 * - index 1 -> (echo=0, col=0, row=1): 1100 mm
 * - index 2 -> (echo=0, col=1, row=0): 1010 mm
 * - index 3 -> (echo=0, col=1, row=1): 1110 mm
 *
 * Optional payloads:
 * - intensities: empty (not enabled)
 * - echoProperties: empty (not enabled)
 */
inline auto makeDefaultData() -> sick::compact::multiscan200::MultiScan200Data
{
  return sick::test::MultiScan200DataGenerator() //
    .withNumberOfRows(2)                         //
    .withNumberOfColumnsInSegment(2)             //
    .withNumberOfEchoes(1)                       //
    .next();
}

inline void expectContainsAtLeastOneValidPoint(sick::point_cloud::OrganizedPointCloud const& pc)
{
  bool hasValidPoint = false;
  for (std::size_t pointIndex = 0; pointIndex < pc.numberOfPoints(); ++pointIndex)
  {
    auto const [x, y, z] = pc.getCartesian(pointIndex);
    if (!(std::isnan(x) || std::isnan(y) || std::isnan(z)))
    {
      hasValidPoint = true;
      break;
    }
  }
  EXPECT_TRUE(hasValidPoint);
}

inline auto createConfigurationWithAllSupportedFields() -> sick::point_cloud::PointCloudConfiguration
{
  sick::point_cloud::PointCloudConfiguration config;
  config.fields.enableCartesian   = true;
  config.fields.enableSpherical   = true;
  config.fields.enableIntensity   = true;
  config.fields.enableTimeOffset  = true;
  config.fields.enableRing        = true;
  config.fields.enableLayerIndex  = true;
  config.fields.enableColumnIndex = true;
  config.fields.enableEchoIndex   = true;
  config.fields.enableProperties  = true;
  config.fields.enablePulseWidth  = false;
  return config;
}

inline void expectSelectedPointValuesMatchInput(
  sick::point_cloud::UnorganizedPointCloud const& pc,
  sick::compact::multiscan200::MultiScan200Data const& data,
  std::size_t columnIndex,
  std::size_t rowIndex,
  std::size_t echoIndex
)
{
  auto const pointIndex = rowIndex * data.segmentMetaData.numberOfColumnsInSegment * data.segmentMetaData.numberOfEchoes +
                          columnIndex * data.segmentMetaData.numberOfEchoes + echoIndex;
  auto const dataIndex = data.computeIndex(echoIndex, columnIndex, rowIndex);

  auto const distanceScaled                             = static_cast<float>(data.distances[dataIndex].meters());
  auto const azimuth                                    = static_cast<float>(data.geometry.azimuths[columnIndex].radians());
  auto const elevation                                  = static_cast<float>(data.geometry.elevations[rowIndex].radians());
  auto const intensity                                  = data.intensities[dataIndex];
  auto const [timeOffsetSeconds, timeOffsetNanoseconds] = data.geometry.relativeTimeStamps[columnIndex].secondsAndNanoseconds();

  auto const cosElevation = std::cos(elevation);
  auto const sinElevation = std::sin(elevation);
  auto const cosAzimuth   = std::cos(azimuth);
  auto const sinAzimuth   = std::sin(azimuth);

  auto const expectedX = cosElevation * cosAzimuth * distanceScaled;
  auto const expectedY = cosElevation * sinAzimuth * distanceScaled;
  auto const expectedZ = -sinElevation * distanceScaled;

  EXPECT_FLOAT_EQ(expectedX, pc.getX(pointIndex));
  EXPECT_FLOAT_EQ(expectedY, pc.getY(pointIndex));
  EXPECT_FLOAT_EQ(expectedZ, pc.getZ(pointIndex));
  EXPECT_FLOAT_EQ(distanceScaled, pc.getRange(pointIndex));
  EXPECT_FLOAT_EQ(azimuth, pc.getAzimuth(pointIndex));
  EXPECT_FLOAT_EQ(elevation, pc.getElevation(pointIndex));
  EXPECT_FLOAT_EQ(intensity, pc.getIntensity(pointIndex));
  EXPECT_EQ(timeOffsetSeconds, std::get<0>(pc.getTimeOffset(pointIndex)));
  EXPECT_EQ(timeOffsetNanoseconds, std::get<1>(pc.getTimeOffset(pointIndex)));
  EXPECT_EQ(static_cast<std::uint8_t>(rowIndex), pc.getRing(pointIndex));
  EXPECT_EQ(static_cast<std::uint8_t>(rowIndex), pc.getLayerIndex(pointIndex));
  EXPECT_EQ(static_cast<std::uint16_t>(columnIndex), pc.getColumnIndex(pointIndex));
  EXPECT_EQ(static_cast<std::uint8_t>(echoIndex), pc.getEchoIndex(pointIndex));

  sick::BitField<sick::point_cloud::Properties> expectedProperties;
  expectedProperties.set(sick::point_cloud::Properties::Reflector, true);
  expectedProperties.set(sick::point_cloud::Properties::Blooming, true);
  EXPECT_EQ(expectedProperties, pc.getProperties(pointIndex));
}

} // namespace sick::test
