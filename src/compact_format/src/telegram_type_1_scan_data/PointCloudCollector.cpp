/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/PointCloudCollector.hpp>

#include <sick_perception_sdk/common/BitField.hpp>
#include <sick_perception_sdk/common/logging/logging.hpp>
#include <sick_perception_sdk/common/quantities/Angle.hpp>
#include <sick_perception_sdk/common/quantities/Duration.hpp>
#include <sick_perception_sdk/common/quantities/Timestamp.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloud.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanData.hpp>

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring> // for std::memcpy
#include <functional>
#include <iterator>
#include <limits>
#include <map>
#include <stdexcept>
#include <utility>
#include <vector>

namespace sick::compact::scan_data {

namespace {

auto bloomingMask(std::size_t echoIndex) -> std::uint8_t
{
  // bits 5 = Echo 0 has blooming, 6 = Echo 1 has blooming, 7 = Echo 2 has blooming
  constexpr std::size_t maskOffset = 5;
  return 0x01 << (maskOffset + echoIndex);
}

/**
 * @brief Validates that the module meta data contains the required beam content.
 * @throws std::runtime_error if the module does not contain the required beam content.
 */
void validateBeamContent(Module::MetaData const& moduleMetaData, BitField<BeamContent> requiredBeamContent)
{
  if (requiredBeamContent.isEmpty())
  {
    return;
  }

  if ((moduleMetaData.beamContent.isUnset(requiredBeamContent)))
  {
    if ((requiredBeamContent.isSet(BeamContent::Azimuth)))
    {
      if (moduleMetaData.numberOfRows != moduleMetaData.rowMetaData.size())
      {
        throw std::runtime_error("Module does not contain the required beam content. The module does not provide meta data for each row."
                                 "The beam azimuth cannot be replaced by the row azimuth.");
      }
    }
    else
    {
      throw std::runtime_error("Module does not contain the required beam content.");
    }
  }
}

/**
 * @brief Validates that the module meta data contains the required echo content.
 * @throws std::runtime_error if the module does not contain the required echo content.
 */
void validateEchoContent(Module::MetaData const& moduleMetaData, BitField<EchoContent> requiredEchoContent)
{
  if (moduleMetaData.echoContent.isUnset(requiredEchoContent))
  {
    throw std::runtime_error("Module does not contain the required echo content.");
  }
}

/**
 * @brief Validates that the module meta data contains consistent number of rows.
 * @throws std::runtime_error if the module meta data contains inconsistent number of rows.
 */
void validateNumberOfRows(Module::MetaData const& moduleMetaData)
{
  if (moduleMetaData.numberOfRows != moduleMetaData.rowMetaData.size())
  {
    throw std::runtime_error("Module meta data has inconsistent number of rows.");
  }
}

void validateScanData(ScanData const& scanData, BitField<BeamContent> requiredBeamContent, BitField<EchoContent> requiredEchoContent)
{
  for (auto const& module : scanData.modules)
  {
    validateBeamContent(module.metaData, requiredBeamContent);
    validateEchoContent(module.metaData, requiredEchoContent);
    validateNumberOfRows(module.metaData);
  }
}

/**
 * @brief Computes the layer id from the elevation angles.
 * @details The compact format does not contain layer ids. However, layer ids are used in filtering and can be added as
 * an additional field to the point cloud. CAUTION: LayerIds computed here might not correspond to the layers in the
 * sensor GUI if some layers are deactivated. This is because layer which are deactivated in the GUI are not sent in the
 * scan data at all. Layer IDs are descending with ascending elevation angle. LayerIds start at 1.
 */
auto getElevationToLayerIdMapping(ScanData const& scanData) -> std::map<Angle, std::uint8_t>
{
  std::vector<Angle> allElevations;
  for (auto const& module : scanData.modules)
  {
    std::transform(
      module.metaData.rowMetaData.cbegin(),
      module.metaData.rowMetaData.cend(),
      std::back_inserter(allElevations),
      [](Module::RowMetaData const& rowMetaData) -> Angle {
        return rowMetaData.elevation;
      }
    );
  }

  std::map<Angle, std::uint8_t> elevationToLayerIdMapping;
  std::sort(allElevations.begin(), allElevations.end(), std::greater<>());
  for (std::size_t i = 1; i <= allElevations.size(); ++i)
  {
    elevationToLayerIdMapping[allElevations[i - 1]] = static_cast<std::uint8_t>(i);
  }
  return elevationToLayerIdMapping;
}

/**
 * @brief Computes the maximum number of points that can be added to the point cloud from the given scan data.
 * @details The actual number of points which are added depends on the filter settings and the contents of the scan
 * data.
 */
auto getMaximumNumberOfPoints(ScanData const& scanData) -> std::size_t
{
  std::size_t maximumNumberOfNewPoints = 0;
  for (auto const& module : scanData.modules)
  {
    maximumNumberOfNewPoints += static_cast<std::size_t>(module.metaData.numberOfRows) * static_cast<std::size_t>(module.metaData.numberOfColumns) *
                                static_cast<std::size_t>(module.metaData.numberOfEchoesPerBeam);
  }
  return maximumNumberOfNewPoints;
}

auto getAvailableFields(ScanData const& scanData) -> std::set<point_cloud::PointField::FieldType>
{
  using FieldType = point_cloud::PointField::FieldType;
  std::set<point_cloud::PointField::FieldType> availableFields {
    FieldType::X,
    FieldType::Y,
    FieldType::Z,
    FieldType::Range, // Distance is set to mandatory in the m_requiredEchoContent, so Range is always available
    FieldType::Azimuth,
    FieldType::Elevation,
    // Intensity is optional
    FieldType::TimeOffsetNanoseconds,
    FieldType::TimeOffsetSeconds,
    FieldType::Ring,
    FieldType::LayerId,
    FieldType::EchoIndex,
    // IsReflector is optional
    // HasBlooming is not available
    // PulseWidth is not available
  };
  for (auto const& module : scanData.modules)
  {
    if (module.metaData.beamContent.isSet(BeamContent::Properties))
    {
      availableFields.insert(point_cloud::PointField::FieldType::IsReflector);
    }
    if (module.metaData.echoContent.isSet(EchoContent::Intensity))
    {
      availableFields.insert(point_cloud::PointField::FieldType::Intensity);
    }
  }
  return availableFields;
}

template <typename ValueT>
auto writeValueToPointCloudData(std::vector<std::uint8_t>::iterator const& pointCloudDataWritePosition, ValueT const& value)
  -> std::vector<std::uint8_t>::iterator
{
  std::memcpy(&*(pointCloudDataWritePosition), &value, sizeof(ValueT));
  return pointCloudDataWritePosition + sizeof(ValueT);
}

auto getBeamAzimuth(
  Module::MetaData const& moduleMetaData,
  Beam const& beam,
  std::size_t layerIndex,
  std::size_t columnIndex,
  bool useAzimuthFromHeader,
  LayerInfo const& layerInfo
) -> Angle
{
  return useAzimuthFromHeader ? moduleMetaData.rowMetaData[layerIndex].firstBeamAzimuth + layerInfo.azimuthIncrementPerBeam * columnIndex : beam.azimuth;
}

auto getSmallestTimestampInScanData(ScanData const& scanData) -> Timestamp
{
  auto smallestTimestampInScanData = Timestamp::fromMicrosecondsSinceEpoch(std::numeric_limits<std::uint64_t>::max());
  for (auto const& module : scanData.modules)
  {
    for (auto const& row : module.metaData.rowMetaData)
    {
      smallestTimestampInScanData = sick::min(smallestTimestampInScanData, row.firstBeamTimestamp);
    }
  }
  return smallestTimestampInScanData;
}

auto getTotalNumberOfPoints(ScanData const& scanData) -> std::size_t
{
  std::size_t totalNumberOfPoints = 0;
  for (auto const& module : scanData.modules)
  {
    totalNumberOfPoints += static_cast<std::size_t>(module.metaData.numberOfRows) * static_cast<std::size_t>(module.metaData.numberOfColumns) *
                           static_cast<std::size_t>(module.metaData.numberOfEchoesPerBeam);
  }
  return totalNumberOfPoints;
}

auto createDefaultBuilder(std::set<point_cloud::PointField::FieldType> const& desiredFields) -> point_cloud::UnorganizedPointCloudBuilder
{
  return point_cloud::UnorganizedPointCloudBuilder({desiredFields, desiredFields}, Timestamp(), 0);
}

} // namespace

PointCloudCollector::PointCloudCollector()
  : PointCloudCollector(point_cloud::PointCloudConfiguration())
{ }

PointCloudCollector::PointCloudCollector(point_cloud::PointCloudConfiguration configuration)
  : m_configuration(std::move(configuration))
  , m_desiredFields(m_configuration.fields.toSet())
  , m_builder(createDefaultBuilder(m_desiredFields)) // empty point cloud builder with default fields. This will never actually be used.
  , m_requiredBeamContent(BeamContent::None)
  , m_requiredEchoContent(EchoContent::None)
{
  LOG_INFO("PointCloudCollector") << "Creating PointCloudCollector with configuration:\n" << m_configuration.toString();

  if (!m_configuration.fields.enableCartesian && !m_configuration.fields.enableSpherical)
  {
    throw std::invalid_argument("At least one of cartesian or spherical coordinates must be enabled");
  }

  m_requiredEchoContent.set(EchoContent::Distance);

  if (m_configuration.fields.enableIntensity || !m_configuration.filters.intensity.isEmpty())
  {
    m_requiredEchoContent.set(EchoContent::Intensity);
  }

  if (m_configuration.fields.enableIsReflector || m_configuration.fields.enableHasBlooming || m_configuration.filters.requiredReflectorFlag ||
      m_configuration.filters.requiredBloomingFlag)
  {
    m_requiredBeamContent.set(BeamContent::Properties);
  }

  reset();
}

void PointCloudCollector::collect(ScanData const& scanData)
{
  if (getTotalNumberOfPoints(scanData) == 0)
  {
    // We silently ignore empty segments.
    return;
  }

  if (!m_hasCollectionStarted)
  {
    point_cloud::UnorganizedPointCloudBuilder::FieldConfig fieldConfig {m_desiredFields, getAvailableFields(scanData)};

    m_pointCloudTimestamp  = getSmallestTimestampInScanData(scanData);
    m_builder              = point_cloud::UnorganizedPointCloudBuilder(fieldConfig, m_pointCloudTimestamp, getTotalNumberOfPoints(scanData));
    m_hasCollectionStarted = true;
  }
  validateScanData(scanData, m_requiredBeamContent, m_requiredEchoContent);
  validateTimestamps(scanData);

  // Make sure there's enough space for the new segment in the builder's point cloud.
  m_builder.growBy(getMaximumNumberOfPoints(scanData));

  auto const elevationToLayerIdMapping = getElevationToLayerIdMapping(scanData);

  for (auto const& module : scanData.modules)
  {
    // True if the azimuth angles are required but not provided as part of the beam data.
    bool const useAzimuthFromHeader = (module.metaData.beamContent.isSet(BeamContent::Azimuth) && m_requiredBeamContent.isSet(BeamContent::Azimuth));

    auto const layerInfos = calculateLayerInfo(module.metaData, elevationToLayerIdMapping, useAzimuthFromHeader);

    // Iterate in row-major order: layer (row) first, then column
    auto const numberOfLayers = module.metaData.numberOfRows;
    for (std::size_t layerIndex = 0; layerIndex < numberOfLayers; layerIndex++)
    {
      auto const& layerInfo = layerInfos[layerIndex];
      // AXIVION Next Construct CertC++-MEM30: False positive, layerInfo is only a reference to the current element in the vector, so it is not a dangling reference.
      // AXIVION Next Construct CertC++-MEM50
      if (!layerInfo.isInPointCloud)
      {
        continue;
      }

      for (std::size_t columnIndex = 0; columnIndex < module.columns.size(); columnIndex++)
      {
        auto const& column     = module.columns[columnIndex];
        auto const& beam       = column[layerIndex];
        auto const beamAzimuth = getBeamAzimuth(module.metaData, beam, layerIndex, columnIndex, useAzimuthFromHeader, layerInfo);

        // Filter by azimuth
        if (!m_configuration.filters.azimuth.contains(beamAzimuth))
        {
          continue;
        }

        float sinAzimuth = 0.0f;
        float cosAzimuth = 0.0f;
        if (m_configuration.fields.enableCartesian)
        {
          sinAzimuth = sin(beamAzimuth);
          cosAzimuth = cos(beamAzimuth);
        }

        auto const beamTimestampOffset = layerInfo.firstBeamTimestampOffset + layerInfo.timestampIncrementPerBeam * columnIndex;
        auto const [beamTimestampOffsetSeconds, beamTimestampOffsetNanoseconds] = beamTimestampOffset.secondsAndNanoseconds();

        bool foundValidEcho = false;
        for (auto echoIt = beam.echoes.rbegin(); echoIt != beam.echoes.rend(); ++echoIt)
        {
          std::size_t const echoIndex = std::distance(beam.echoes.begin(), echoIt.base()) - 1;

          bool echoIsTheLastValidEcho = false;
          Echo const& echo            = beam.echoes[echoIndex];
          if (!foundValidEcho && echo.distance.meters() > 0.0f)
          {
            foundValidEcho         = true;
            echoIsTheLastValidEcho = true;
          }

          if (isEchoInvalid(beam, echo, echoIndex, echoIsTheLastValidEcho))
          {
            continue;
          }

          writeEcho(
            echo,
            cosAzimuth,
            sinAzimuth,
            module.metaData.rowMetaData[layerIndex].elevation,
            beamAzimuth,
            layerInfo,
            beamTimestampOffsetNanoseconds,
            beamTimestampOffsetSeconds,
            echoIndex,
            echoIsTheLastValidEcho && (beam.properties & 0x01) != 0,
            (beam.properties & bloomingMask(echoIndex)) != 0
          );
        }
      }
    }
  }
}

auto PointCloudCollector::getPointCloud() -> point_cloud::UnorganizedPointCloud
{
  return m_builder.build();
}

auto PointCloudCollector::calculateLayerInfo(
  Module::MetaData const& moduleMetaData,
  std::map<Angle, std::uint8_t> const& elevationToLayerIdMapping,
  bool useAzimuthFromHeader
) const -> std::vector<LayerInfo>
{
  using namespace sick::literals; // NOLINT(google-build-using-namespace)
  std::vector<LayerInfo> layerInfos(moduleMetaData.numberOfRows, {0, false, 0.0f, 0.0f, 0_ms, 0_ms, 0_rad});

  for (std::size_t layerIndex = 0; layerIndex < moduleMetaData.numberOfRows; layerIndex++)
  {
    auto const elevation = moduleMetaData.rowMetaData[layerIndex].elevation;
    auto const layerIdIt = elevationToLayerIdMapping.find(elevation);
    assert(layerIdIt != elevationToLayerIdMapping.end());

    std::uint8_t const layerId = layerIdIt->second;

    layerInfos[layerIndex].id = layerId;
  }

  for (std::size_t layerIndex = 0; layerIndex < moduleMetaData.numberOfRows; layerIndex++)
  {
    if (m_configuration.filters.selectedLayers.has_value() &&
        m_configuration.filters.selectedLayers->find(static_cast<std::uint32_t>(layerInfos[layerIndex].id)) == m_configuration.filters.selectedLayers->end())
    {
      continue;
    }

    if (!m_configuration.filters.elevation.contains(moduleMetaData.rowMetaData[layerIndex].elevation))
    {
      continue;
    }

    layerInfos[layerIndex].isInPointCloud = true;
  }

  if (m_configuration.fields.enableCartesian)
  {
    for (std::size_t layerIndex = 0; layerIndex < moduleMetaData.numberOfRows; layerIndex++)
    {
      layerInfos[layerIndex].sinElevation = sin(moduleMetaData.rowMetaData[layerIndex].elevation);
      layerInfos[layerIndex].cosElevation = cos(moduleMetaData.rowMetaData[layerIndex].elevation);
    }
  }

  if (m_configuration.fields.enableTimeOffset)
  {
    for (std::size_t layerIndex = 0; layerIndex < moduleMetaData.numberOfRows; layerIndex++)
    {
      auto const firstBeamTimestampOffset              = moduleMetaData.rowMetaData[layerIndex].firstBeamTimestamp - m_pointCloudTimestamp;
      layerInfos[layerIndex].firstBeamTimestampOffset  = firstBeamTimestampOffset;
      auto const layerStopOffset                       = moduleMetaData.rowMetaData[layerIndex].lastBeamTimestamp - m_pointCloudTimestamp;
      layerInfos[layerIndex].timestampIncrementPerBeam = (layerStopOffset - firstBeamTimestampOffset) / std::max(1u, moduleMetaData.numberOfColumns - 1);
    }
  }

  if (useAzimuthFromHeader)
  {
    for (std::size_t layerIndex = 0; layerIndex < moduleMetaData.numberOfRows; layerIndex++)
    {
      layerInfos[layerIndex].azimuthIncrementPerBeam =
        (moduleMetaData.rowMetaData[layerIndex].lastBeamAzimuth - moduleMetaData.rowMetaData[layerIndex].firstBeamAzimuth) /
        std::max(1u, moduleMetaData.numberOfColumns - 1);
    }
  }

  return layerInfos;
}

void PointCloudCollector::writeEcho(
  Echo const& echo,
  float cosAzimuth,
  float sinAzimuth,
  Angle elevation,
  Angle azimuth,
  LayerInfo const& layerInfo,
  std::uint32_t beamTimestampOffsetNanoseconds,
  std::uint32_t beamTimestampOffsetSeconds,
  std::size_t echoIndex,
  bool isAReflector,
  bool hasBlooming
)
{
  using FieldType = point_cloud::PointField::FieldType;

  if (echo.distance.meters() < 0.0f)
  {
    return;
  }

  m_builder.beginPoint();

  float const distanceScaled = echo.distance.meters() * m_configuration.distanceScalingFactor;
  if (m_configuration.fields.enableCartesian)
  {
    float const x = layerInfo.cosElevation * cosAzimuth * distanceScaled; // NOLINT(readability-identifier-length)
    float const y = layerInfo.cosElevation * sinAzimuth * distanceScaled; // NOLINT(readability-identifier-length)
    float const z = -layerInfo.sinElevation * distanceScaled;             // NOLINT(readability-identifier-length)

    m_builder.writeNextFieldValueOrIgnore(FieldType::X, x);
    m_builder.writeNextFieldValueOrIgnore(FieldType::Y, y);
    m_builder.writeNextFieldValueOrIgnore(FieldType::Z, z);
  }

  if (m_configuration.fields.enableSpherical)
  {
    m_builder.writeNextFieldValueOrIgnore(FieldType::Range, distanceScaled);
    m_builder.writeNextFieldValueOrIgnore(FieldType::Azimuth, azimuth);
    m_builder.writeNextFieldValueOrIgnore(FieldType::Elevation, elevation);
  }

  if (m_configuration.fields.enableIntensity)
  {
    m_builder.writeNextFieldValueOrIgnore(FieldType::Intensity, echo.intensity);
  }

  if (m_configuration.fields.enableTimeOffset)
  {
    m_builder.writeNextFieldValueOrIgnore(FieldType::TimeOffsetNanoseconds, beamTimestampOffsetNanoseconds);
    m_builder.writeNextFieldValueOrIgnore(FieldType::TimeOffsetSeconds, beamTimestampOffsetSeconds);
  }

  if (m_configuration.fields.enableRing)
  {
    m_builder.writeNextFieldValueOrIgnore(FieldType::Ring, layerInfo.id);
  }

  if (m_configuration.fields.enableLayerId)
  {
    m_builder.writeNextFieldValueOrIgnore(FieldType::LayerId, layerInfo.id);
  }

  if (m_configuration.fields.enableEchoIndex)
  {
    auto const echoId = static_cast<std::uint8_t>(echoIndex);
    m_builder.writeNextFieldValueOrIgnore(FieldType::EchoIndex, echoId);
  }

  if (m_configuration.fields.enableIsReflector)
  {
    std::uint8_t const isReflector = isAReflector ? 1 : 0;
    m_builder.writeNextFieldValueOrIgnore(FieldType::IsReflector, isReflector);
  }

  if (m_configuration.fields.enableHasBlooming)
  {
    std::uint8_t const hasBloomingInt8 = hasBlooming ? 1 : 0;
    m_builder.writeNextFieldValueOrIgnore(FieldType::HasBlooming, hasBloomingInt8);
  }
}

auto PointCloudCollector::isEchoInvalid(Beam const& beam, Echo const& echo, std::size_t echoIndex, bool echoIsTheLastValidEcho) const -> bool
{
  if (m_configuration.filters.selectedEchos.has_value() &&
      m_configuration.filters.selectedEchos->find(echoIndex) == m_configuration.filters.selectedEchos->end())
  {
    return true;
  }

  if (!m_configuration.filters.range.contains(echo.distance))
  {
    return true;
  }

  if (!m_configuration.filters.intensity.contains(echo.intensity))
  {
    return true;
  }

  // Filter reflectors, bit 0 = Reflector
  bool const thisEchoIsAReflector = echoIsTheLastValidEcho && (beam.properties & 0x01) != 0;
  if (m_configuration.filters.requiredReflectorFlag.has_value() && *m_configuration.filters.requiredReflectorFlag != thisEchoIsAReflector)
  {
    return true;
  }

  // Filter blooming
  bool const echoHasBlooming = (beam.properties & bloomingMask(echoIndex)) != 0;
  return m_configuration.filters.requiredBloomingFlag.has_value() && *m_configuration.filters.requiredBloomingFlag != echoHasBlooming;
}

void PointCloudCollector::validateTimestamps(ScanData const& scanData)
{
  auto const smallestTimestampInScanData = getSmallestTimestampInScanData(scanData);

  if (smallestTimestampInScanData < m_pointCloudTimestamp)
  {
    throw std::runtime_error("Encountered a smaller timestamp than the one in the point cloud.");
  }
}

void PointCloudCollector::reset()
{
  m_pointCloudTimestamp  = Timestamp::fromMicrosecondsSinceEpoch(0);
  m_builder              = createDefaultBuilder(m_desiredFields);
  m_hasCollectionStarted = false;
}

} // namespace sick::compact::scan_data
