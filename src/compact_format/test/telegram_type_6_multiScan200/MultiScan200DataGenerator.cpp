/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include "MultiScan200DataGenerator.hpp"

#include <sick_perception_sdk/common/quantities/Angle.hpp>
#include <sick_perception_sdk/common/quantities/Distance.hpp>

#include <algorithm>
#include <cmath>

namespace sick::test {

MultiScan200DataGenerator::MultiScan200DataGenerator()
  : m_frameSequenceNumber(0)
  , m_numberOfRows(16)
  , m_numberOfColumnsInSegment(10)
  , m_numberOfColumnsInFrame(100)
  , m_numberOfEchoes(1)
  , m_numberOfSegmentsPerFrame(10)
  , m_segmentIndex(0)
  , m_numberOfAmbientLightRows(0)
  , m_distanceScalingFactor(1.0f)
  , m_withIntensity(false)
  , m_withEchoProperties(false)
{ }

auto MultiScan200DataGenerator::withNumberOfRows(std::size_t value) -> MultiScan200DataGenerator&
{
  m_numberOfRows = value;
  return *this;
}

auto MultiScan200DataGenerator::withNumberOfColumnsInSegment(std::size_t value) -> MultiScan200DataGenerator&
{
  m_numberOfColumnsInSegment = value;
  return *this;
}

auto MultiScan200DataGenerator::withNumberOfColumnsInFrame(std::size_t value) -> MultiScan200DataGenerator&
{
  m_numberOfColumnsInFrame = value;
  return *this;
}

auto MultiScan200DataGenerator::withNumberOfEchoes(std::size_t value) -> MultiScan200DataGenerator&
{
  m_numberOfEchoes = value;
  return *this;
}

auto MultiScan200DataGenerator::withNumberOfSegmentsPerFrame(std::size_t value) -> MultiScan200DataGenerator&
{
  m_numberOfSegmentsPerFrame = value;
  return *this;
}

auto MultiScan200DataGenerator::withNumberOfAmbientLightRows(std::size_t value) -> MultiScan200DataGenerator&
{
  m_numberOfAmbientLightRows = value;
  return *this;
}

auto MultiScan200DataGenerator::withDistanceScalingFactor(float value) -> MultiScan200DataGenerator&
{
  m_distanceScalingFactor = value;
  return *this;
}

auto MultiScan200DataGenerator::withIntensity(bool value) -> MultiScan200DataGenerator&
{
  m_withIntensity = value;
  return *this;
}

auto MultiScan200DataGenerator::withEchoProperties(bool value) -> MultiScan200DataGenerator&
{
  m_withEchoProperties = value;
  return *this;
}

auto MultiScan200DataGenerator::next() -> sick::compact::multiscan200::MultiScan200Data
{
  sick::compact::multiscan200::MultiScan200Data data;

  // Fill telegram header
  // The generator has no separate telegram sequence number, so we use the frame sequence number here for simplicity.
  data.telegramHeader.telegramSequenceNumber = m_frameSequenceNumber;
  data.telegramHeader.transmitTimestamp      = Timestamp::fromMicrosecondsSinceEpoch(m_frameSequenceNumber * 1000);

  // Fill segment metadata
  data.segmentMetaData.frameSequenceNumber         = m_frameSequenceNumber;
  data.segmentMetaData.frameTimestamp              = data.telegramHeader.transmitTimestamp;
  data.segmentMetaData.segmentIndex                = m_segmentIndex;
  data.segmentMetaData.numberOfSegmentsPerFrame    = m_numberOfSegmentsPerFrame;
  data.segmentMetaData.numberOfColumnsInSegment    = m_numberOfColumnsInSegment;
  data.segmentMetaData.numberOfColumnsInFrame      = m_numberOfColumnsInFrame;
  data.segmentMetaData.numberOfRows                = m_numberOfRows;
  data.segmentMetaData.numberOfEchoes              = m_numberOfEchoes;
  data.segmentMetaData.numberOfAmbientLightRows    = m_numberOfAmbientLightRows;
  data.segmentMetaData.numberOfInterlaceSteps      = 1;
  data.segmentMetaData.interlaceIndex              = 0;
  data.segmentMetaData.scanConfigurationIdentifier = 0;

  // Fill ambient light data
  auto const numberOfAmbientLightValues = m_numberOfColumnsInSegment * m_numberOfAmbientLightRows;
  data.ambientLightData.resize(numberOfAmbientLightValues);
  for (std::size_t i = 0; i < numberOfAmbientLightValues; ++i)
  {
    data.ambientLightData[i] = static_cast<std::uint16_t>(100 + i);
  }

  // Fill geometry
  data.geometry.elevations.resize(m_numberOfRows);
  data.geometry.azimuths.resize(m_numberOfColumnsInSegment);
  data.geometry.relativeTimeStamps.resize(m_numberOfColumnsInSegment);

  for (std::uint16_t row = 0; row < m_numberOfRows; ++row)
  {
    // Elevation angles from -15° to +15° (spread across rows)
    auto const elevationDeg       = -15.0 + (30.0 * row / std::max<double>(m_numberOfRows - 1, 1));
    data.geometry.elevations[row] = Angle::fromDegrees(elevationDeg);
  }
  for (std::uint16_t col = 0; col < m_numberOfColumnsInSegment; ++col)
  {
    // Azimuth angles across the segment
    auto const columnIndexInFrame = m_segmentIndex * m_numberOfColumnsInSegment + col;
    auto const azimuthDeg         = (360.0 * columnIndexInFrame) / std::max<double>(m_numberOfColumnsInFrame, 1);
    data.geometry.azimuths[col]   = Angle::fromDegrees(azimuthDeg);

    data.geometry.relativeTimeStamps[col] = Duration::fromMicroseconds(col * 10);
  }

  // Fill scan data
  auto const numberOfSamples = static_cast<std::size_t>(m_numberOfEchoes) * m_numberOfRows * m_numberOfColumnsInSegment;
  data.distances.reserve(numberOfSamples);
  if (m_withIntensity)
  {
    data.intensities.reserve(numberOfSamples);
  }
  if (m_withEchoProperties)
  {
    data.echoProperties.reserve(numberOfSamples);
  }

  for (std::size_t col = 0; col < m_numberOfColumnsInSegment; ++col)
  {
    for (std::size_t row = 0; row < m_numberOfRows; ++row)
    {
      for (std::size_t echo = 0; echo < m_numberOfEchoes; ++echo)
      {
        // Distance values from 1m to 10m depending on echo
        data.distances.push_back(Distance::fromMillimeters(1000.0 + echo * 1000.0 + row * 100.0 + col * 10.0));

        if (m_withIntensity)
        {
          data.intensities.push_back(100.0F + echo * 10.0F + row * 1.0F);
        }

        if (m_withEchoProperties)
        {
          data.echoProperties.push_back(sick::BitField<sick::compact::multiscan200::EchoProperties>(sick::compact::multiscan200::EchoProperties::Reserved));
        }
      }
    }
  }

  // Advance to next segment
  m_segmentIndex++;
  if (m_segmentIndex >= m_numberOfSegmentsPerFrame)
  {
    m_segmentIndex = 0;
    m_frameSequenceNumber++;
  }

  return data;
}

void MultiScan200DataGenerator::reset()
{
  m_frameSequenceNumber = 0;
  m_segmentIndex        = 0;
}

} // namespace sick::test
