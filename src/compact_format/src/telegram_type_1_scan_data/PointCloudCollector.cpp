/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/PointCloudCollector.hpp>

#include <sick_perception_sdk/common/BitField.hpp>
#include <sick_perception_sdk/common/logging/logging.hpp>
#include <sick_perception_sdk/common/quantities/Angle.hpp>
#include <sick_perception_sdk/common/quantities/Distance.hpp>
#include <sick_perception_sdk/common/quantities/Duration.hpp>
#include <sick_perception_sdk/common/quantities/Timestamp.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudAttributes.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudConfiguration.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloud.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanData.hpp>

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring> // for std::memcpy
#include <functional>
#include <iterator>
#include <limits>
#include <map>
#include <set>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

namespace sick::compact::scan_data {

namespace {

struct LayerInfo
{
  std::uint8_t id {0};
  bool isInPointCloud {false};
  float sinElevation {std::numeric_limits<float>::quiet_NaN()};
  float cosElevation {std::numeric_limits<float>::quiet_NaN()};
  Duration firstBeamTimestampOffset;
  Duration timestampIncrementPerBeam;
  Angle azimuthIncrementPerBeam;
};

/**
 * @brief Validates that the module meta data contains the required beam content.
 * @throws std::runtime_error if the module does not contain the required beam content.
 */
void validateBeamContent(Module const& module, BitField<BeamContent> requiredBeamContent)
{
  if (requiredBeamContent.isSet(BeamContent::Properties) && module.beamProperties.empty())
  {
    throw std::runtime_error("Module does not contain the required beam content. The module does not provide beam properties.");
  }
}

/**
 * @brief Validates that the module meta data contains the required echo content.
 * @throws std::runtime_error if the module does not contain the required echo content.
 */
void validateEchoContent(Module const& module, BitField<EchoContent> requiredEchoContent)
{
  if (requiredEchoContent.isSet(EchoContent::Distance) && module.distances.empty())
  {
    throw std::runtime_error("Module does not contain the required echo content. The module does not provide distance samples.");
  }
  if (requiredEchoContent.isSet(EchoContent::Intensity) && module.intensities.empty())
  {
    throw std::runtime_error("Module does not contain the required echo content. The module does not provide intensity samples.");
  }
}

void validateScanData(ScanData const& scanData, BitField<BeamContent> requiredBeamContent, BitField<EchoContent> requiredEchoContent)
{
  for (auto const& module : scanData.modules)
  {
    validateBeamContent(module, requiredBeamContent);
    validateEchoContent(module, requiredEchoContent);
  }
}

/**
 * @brief Computes the layer id from the elevation angles.
 * 
 * @details The compact format does not contain layer ids. However, layer ids are used in filtering and can be added as
 * an additional field to the point cloud. 
 * 
 * @warning LayerIds computed here might not correspond to the layers in the
 * sensor GUI if some layers are deactivated. This is because layer which are deactivated in the GUI are not sent in the
 * scan data at all. Layer IDs are descending with ascending elevation angle. LayerIds start at 1.
 */
auto getElevationToLayerIdMapping(ScanData const& scanData) -> std::map<Angle, std::uint8_t>
{
  std::vector<Angle> allElevations;
  for (auto const& module : scanData.modules)
  {
    std::transform(
      module.rowMetaData.cbegin(),
      module.rowMetaData.cend(),
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
    maximumNumberOfNewPoints += module.rowMetaData.size() * module.numberOfColumns * module.numberOfEchoesPerBeam;
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
    FieldType::LayerIndex,
    // ColumnIndex is not supported for telegram type 1.
    FieldType::EchoIndex,
    // Properties is optional
    // PulseWidth is not available
  };
  for (auto const& module : scanData.modules)
  {
    if (!module.beamProperties.empty())
    {
      availableFields.insert(point_cloud::PointField::FieldType::Properties);
    }
    if (!module.intensities.empty())
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
  Module const& module,
  std::size_t beamFlatIndex,
  std::size_t layerIndex,
  std::size_t columnIndex,
  bool useAzimuthFromMetaData,
  LayerInfo const& layerInfo
) -> Angle
{
  return useAzimuthFromMetaData ? module.rowMetaData[layerIndex].firstBeamAzimuth + layerInfo.azimuthIncrementPerBeam * columnIndex
                                : module.beamAzimuths[beamFlatIndex];
}

auto getSmallestTimestampInScanData(ScanData const& scanData) -> Timestamp
{
  auto smallestTimestampInScanData = Timestamp::fromMicrosecondsSinceEpoch(std::numeric_limits<std::uint64_t>::max());
  for (auto const& module : scanData.modules)
  {
    for (auto const& row : module.rowMetaData)
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
    totalNumberOfPoints += module.rowMetaData.size() * module.numberOfColumns * module.numberOfEchoesPerBeam;
  }
  return totalNumberOfPoints;
}

auto createDefaultBuilder(std::set<point_cloud::PointField::FieldType> const& desiredFields) -> point_cloud::UnorganizedPointCloudBuilder
{
  return point_cloud::UnorganizedPointCloudBuilder({desiredFields, desiredFields}, Timestamp(), 0);
}

auto convertToPointCloudProperties(BitField<BeamProperties> beamProperties, std::size_t echoIndex, bool echoIsTheLastValidEcho)
  -> BitField<point_cloud::Properties>
{
  BitField<point_cloud::Properties> properties;
  bool const thisEchoIsAReflector = echoIsTheLastValidEcho && beamProperties.isSet(BeamProperties::Reflector);
  properties.set(point_cloud::Properties::Reflector, thisEchoIsAReflector);

  auto const bloomingMask    = static_cast<BeamProperties>(static_cast<std::underlying_type_t<BeamProperties>>(BeamProperties::BloomingEcho0) << echoIndex);
  bool const echoHasBlooming = beamProperties.isSet(bloomingMask);
  properties.set(point_cloud::Properties::Blooming, echoHasBlooming);

  return properties;
}

auto calculateLayerInfo(
  point_cloud::PointCloudConfiguration const& configuration,
  Timestamp pointCloudTimestamp,
  Module const& module,
  std::map<Angle, std::uint8_t> const& elevationToLayerIdMapping,
  bool useAzimuthFromMetaData
) -> std::vector<LayerInfo>
{
  using namespace sick::literals; // NOLINT(google-build-using-namespace)
  auto const numberOfRows = module.rowMetaData.size();
  std::vector<LayerInfo> layerInfos(numberOfRows, {0, false, 0.0f, 0.0f, 0_ms, 0_ms, 0_rad});

  for (std::size_t layerIndex = 0; layerIndex < numberOfRows; layerIndex++)
  {
    auto const elevation = module.rowMetaData[layerIndex].elevation;
    auto const layerIdIt = elevationToLayerIdMapping.find(elevation);
    assert(layerIdIt != elevationToLayerIdMapping.end());

    std::uint8_t const layerId = layerIdIt->second;

    layerInfos[layerIndex].id = layerId;
  }

  for (std::size_t layerIndex = 0; layerIndex < numberOfRows; layerIndex++)
  {
    if (configuration.filters.selectedLayers.has_value() &&
        configuration.filters.selectedLayers->find(static_cast<std::uint32_t>(layerInfos[layerIndex].id)) == configuration.filters.selectedLayers->end())
    {
      continue;
    }

    if (!configuration.filters.elevation.contains(module.rowMetaData[layerIndex].elevation))
    {
      continue;
    }

    layerInfos[layerIndex].isInPointCloud = true;
  }

  if (configuration.fields.enableCartesian)
  {
    for (std::size_t layerIndex = 0; layerIndex < numberOfRows; layerIndex++)
    {
      layerInfos[layerIndex].sinElevation = sin(module.rowMetaData[layerIndex].elevation);
      layerInfos[layerIndex].cosElevation = cos(module.rowMetaData[layerIndex].elevation);
    }
  }

  if (configuration.fields.enableTimeOffset)
  {
    for (std::size_t layerIndex = 0; layerIndex < numberOfRows; layerIndex++)
    {
      auto const firstBeamTimestampOffset              = module.rowMetaData[layerIndex].firstBeamTimestamp - pointCloudTimestamp;
      layerInfos[layerIndex].firstBeamTimestampOffset  = firstBeamTimestampOffset;
      auto const layerStopOffset                       = module.rowMetaData[layerIndex].lastBeamTimestamp - pointCloudTimestamp;
      layerInfos[layerIndex].timestampIncrementPerBeam = (layerStopOffset - firstBeamTimestampOffset) / std::max(std::size_t {1}, module.numberOfColumns - 1);
    }
  }

  if (useAzimuthFromMetaData)
  {
    for (std::size_t layerIndex = 0; layerIndex < numberOfRows; layerIndex++)
    {
      layerInfos[layerIndex].azimuthIncrementPerBeam =
        (module.rowMetaData[layerIndex].lastBeamAzimuth - module.rowMetaData[layerIndex].firstBeamAzimuth) /
        std::max(std::size_t {1}, module.numberOfColumns - 1);
    }
  }

  return layerInfos;
}

void writeEcho(
  point_cloud::UnorganizedPointCloudBuilder& builder,
  point_cloud::PointCloudConfiguration const& configuration,
  Distance const& echoDistance,
  float echoIntensity,
  BitField<point_cloud::Properties> pointProperties,
  float cosAzimuth,
  float sinAzimuth,
  Angle elevation,
  Angle azimuth,
  LayerInfo const& layerInfo,
  std::uint32_t beamTimestampOffsetNanoseconds,
  std::uint32_t beamTimestampOffsetSeconds,
  std::size_t echoIndex
)
{
  using FieldType = point_cloud::PointField::FieldType;

  if (echoDistance.meters() < 0.0f)
  {
    return;
  }

  builder.beginPoint();

  float const distanceScaled = echoDistance.meters() * configuration.distanceScalingFactor;
  if (configuration.fields.enableCartesian)
  {
    float const x = layerInfo.cosElevation * cosAzimuth * distanceScaled; // NOLINT(readability-identifier-length)
    float const y = layerInfo.cosElevation * sinAzimuth * distanceScaled; // NOLINT(readability-identifier-length)
    float const z = -layerInfo.sinElevation * distanceScaled;             // NOLINT(readability-identifier-length)

    builder.writeNextFieldValueOrIgnore(FieldType::X, x);
    builder.writeNextFieldValueOrIgnore(FieldType::Y, y);
    builder.writeNextFieldValueOrIgnore(FieldType::Z, z);
  }

  if (configuration.fields.enableSpherical)
  {
    builder.writeNextFieldValueOrIgnore(FieldType::Range, distanceScaled);
    builder.writeNextFieldValueOrIgnore(FieldType::Azimuth, azimuth);
    builder.writeNextFieldValueOrIgnore(FieldType::Elevation, elevation);
  }

  if (configuration.fields.enableIntensity)
  {
    builder.writeNextFieldValueOrIgnore(FieldType::Intensity, echoIntensity);
  }

  if (configuration.fields.enableTimeOffset)
  {
    builder.writeNextFieldValueOrIgnore(FieldType::TimeOffsetNanoseconds, beamTimestampOffsetNanoseconds);
    builder.writeNextFieldValueOrIgnore(FieldType::TimeOffsetSeconds, beamTimestampOffsetSeconds);
  }

  if (configuration.fields.enableRing)
  {
    builder.writeNextFieldValueOrIgnore(FieldType::Ring, layerInfo.id);
  }

  if (configuration.fields.enableLayerIndex)
  {
    builder.writeNextFieldValueOrIgnore(FieldType::LayerIndex, layerInfo.id);
  }

  if (configuration.fields.enableEchoIndex)
  {
    auto const echoId = static_cast<std::uint8_t>(echoIndex);
    builder.writeNextFieldValueOrIgnore(FieldType::EchoIndex, echoId);
  }

  if (configuration.fields.enableProperties)
  {
    builder.writeNextFieldValueOrIgnore(FieldType::Properties, pointProperties.underlyingValue());
  }
}

auto isEchoInvalid(
  point_cloud::PointCloudConfiguration const& configuration,
  Distance const& echoDistance,
  float echoIntensity,
  BitField<point_cloud::Properties> pointProperties,
  std::size_t echoIndex
) -> bool
{
  if (echoDistance.meters() <= 0.0f)
  {
    return true;
  }

  if (configuration.filters.selectedEchos.has_value() && configuration.filters.selectedEchos->find(echoIndex) == configuration.filters.selectedEchos->end())
  {
    return true;
  }

  if (!configuration.filters.range.contains(echoDistance))
  {
    return true;
  }

  if (!configuration.filters.intensity.contains(echoIntensity))
  {
    return true;
  }

  if (configuration.filters.requiredProperties.has_value() && (*configuration.filters.requiredProperties != pointProperties))
  {
    return true;
  }

  return false;
}

void validateTimestamps(ScanData const& scanData, Timestamp pointCloudTimestamp)
{
  auto const smallestTimestampInScanData = getSmallestTimestampInScanData(scanData);

  if (smallestTimestampInScanData < pointCloudTimestamp)
  {
    throw std::runtime_error("Encountered a smaller timestamp than the one in the point cloud.");
  }
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

  if (m_configuration.fields.enableProperties || m_configuration.filters.requiredProperties.has_value())
  {
    m_requiredBeamContent.set(BeamContent::Properties);
  }

  if (m_configuration.fields.enableCartesian || m_configuration.fields.enableSpherical)
  {
    m_requiredBeamContent.set(BeamContent::Azimuth);
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
    point_cloud::UnorganizedPointCloudBuilder::FieldConfig const fieldConfig {m_desiredFields, getAvailableFields(scanData)};

    m_pointCloudTimestamp  = getSmallestTimestampInScanData(scanData);
    m_builder              = point_cloud::UnorganizedPointCloudBuilder(fieldConfig, m_pointCloudTimestamp, getTotalNumberOfPoints(scanData));
    m_hasCollectionStarted = true;
  }
  validateScanData(scanData, m_requiredBeamContent, m_requiredEchoContent);
  validateTimestamps(scanData, m_pointCloudTimestamp);

  // Make sure there's enough space for the new segment in the builder's point cloud.
  m_builder.growBy(getMaximumNumberOfPoints(scanData));

  auto const elevationToLayerIdMapping = getElevationToLayerIdMapping(scanData);

  for (auto const& module : scanData.modules)
  {
    // True if the azimuth angles are required but not provided as part of the beam data.
    bool const useAzimuthFromMetaData = module.beamAzimuths.empty() && m_requiredBeamContent.isSet(BeamContent::Azimuth);

    auto const layerInfos = calculateLayerInfo(m_configuration, m_pointCloudTimestamp, module, elevationToLayerIdMapping, useAzimuthFromMetaData);

    auto const numberOfLayers = module.rowMetaData.size();

    bool const hasIntensity  = !module.intensities.empty();
    bool const hasProperties = !module.beamProperties.empty();

    // Iterate in column-major order to match flat array layout: column first, then layer (row)
    // AXIVION Disable CertC++-MEM30: layerInfos vector is not modified during iteration, no stale pointers exist.
    // AXIVION Disable CertC++-MEM50: layerInfos vector is not modified during iteration, no stale pointers exist.
    std::size_t beamFlatIndex = 0;
    for (std::size_t columnIndex = 0; columnIndex < module.numberOfColumns; ++columnIndex)
    {
      for (std::size_t layerIndex = 0; layerIndex < numberOfLayers; ++layerIndex, ++beamFlatIndex)
      {
        auto const& layerInfo = layerInfos[layerIndex];
        if (!layerInfo.isInPointCloud)
        {
          continue;
        }

        auto const beamAzimuth = getBeamAzimuth(module, beamFlatIndex, layerIndex, columnIndex, useAzimuthFromMetaData, layerInfo);

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

        auto const beamProperties = hasProperties ? module.beamProperties[beamFlatIndex] : BitField<BeamProperties>();

        bool foundValidEcho = false;
        // Iterate echoes in reverse order to find the last valid echo first
        for (std::size_t echoReverseIndex = 0; echoReverseIndex < module.numberOfEchoesPerBeam; ++echoReverseIndex)
        {
          std::size_t const echoIndex     = module.numberOfEchoesPerBeam - 1 - echoReverseIndex;
          std::size_t const flatEchoIndex = computeSampleIndex(module, columnIndex, layerIndex, echoIndex);

          auto const& echoDistance  = module.distances[flatEchoIndex];
          float const echoIntensity = hasIntensity ? module.intensities[flatEchoIndex] : std::numeric_limits<float>::quiet_NaN();

          bool echoIsTheLastValidEcho = false;
          if (!foundValidEcho && echoDistance.meters() > 0.0f)
          {
            foundValidEcho         = true;
            echoIsTheLastValidEcho = true;
          }

          auto const pointProperties = convertToPointCloudProperties(beamProperties, echoIndex, echoIsTheLastValidEcho);

          if (isEchoInvalid(m_configuration, echoDistance, echoIntensity, pointProperties, echoIndex))
          {
            continue;
          }

          writeEcho(
            m_builder,
            m_configuration,
            echoDistance,
            echoIntensity,
            pointProperties,
            cosAzimuth,
            sinAzimuth,
            module.rowMetaData[layerIndex].elevation,
            beamAzimuth,
            layerInfo,
            beamTimestampOffsetNanoseconds,
            beamTimestampOffsetSeconds,
            echoIndex
          );
        }
      }
    }
    // AXIVION Enable CertC++-MEM30
    // AXIVION Enable CertC++-MEM50
  }
}

auto PointCloudCollector::getPointCloud() -> point_cloud::UnorganizedPointCloud
{
  return m_builder.build();
}

void PointCloudCollector::reset()
{
  m_pointCloudTimestamp  = Timestamp::fromMicrosecondsSinceEpoch(0);
  m_builder              = createDefaultBuilder(m_desiredFields);
  m_hasCollectionStarted = false;
}

} // namespace sick::compact::scan_data
