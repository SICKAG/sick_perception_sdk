/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/telegram_type_6_multiScan200/MultiScan200Parser.hpp>

#include "../CompactParserContext.hpp"
#include "../CompactTelegram.hpp"
#include "../WireInfo.hpp"
#include "CompactTelegram.hpp"
#include <sick_perception_sdk/common/BitField.hpp>
#include <sick_perception_sdk/common/ByteView.hpp>
#include <sick_perception_sdk/common/CheckedMath.hpp>
#include <sick_perception_sdk/common/SubByteArrayConverter.hpp>
#include <sick_perception_sdk/common/logging/logging.hpp>
#include <sick_perception_sdk/common/quantities/Angle.hpp>
#include <sick_perception_sdk/common/quantities/Distance.hpp>
#include <sick_perception_sdk/common/quantities/Duration.hpp>
#include <sick_perception_sdk/compact_format/CompactData.hpp>
#include <sick_perception_sdk/compact_format/CompactParser.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_6_multiScan200/MultiScan200Data.hpp>

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

namespace sick::compact::multiscan200 {

namespace {

// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic): Pointer arithmetic is necessary here for efficient reading of the compact data.

std::set<int> const kSupportedTelegramVersions = {1};
constexpr std::size_t kSizeOfIntensityInBits   = 12;
constexpr auto maxIntensityValue               = static_cast<float>((1 << kSizeOfIntensityInBits) - 1);

enum class EchoDataContent
{
  None       = 0x00,
  Intensity  = 0x01,
  Properties = 0x04,
  All        = Intensity | Properties,
};

void readSegmentMetaData(CompactParserContext& context, SegmentMetaData& metaData, BitField<EchoDataContent>& echoDataContent, float& distanceScalingFactor)
{
  if (context.numberOfBytesRemaining() < telegram::segment_meta_data::sizeInBytes)
  {
    throw std::invalid_argument("Not enough data to read the segment meta data.");
  }

  // Caution! The order of the following readValueUnsafe calls is important and defined by the protocol!

  metaData.frameSequenceNumber         = context.readValueUnsafe(telegram::segment_meta_data::kFrameSequenceNumber);
  metaData.frameTimestamp              = Timestamp::fromMicrosecondsSinceEpoch(context.readValueUnsafe(telegram::segment_meta_data::kFrameTimestamp));
  metaData.segmentIndex                = context.readValueUnsafe(telegram::segment_meta_data::kSegmentIndex);
  metaData.numberOfSegmentsPerFrame    = context.readValueUnsafe(telegram::segment_meta_data::kNumberOfSegmentsPerFrame);
  metaData.numberOfColumnsInSegment    = context.readValueUnsafe(telegram::segment_meta_data::kNumberOfColumnsInSegment);
  metaData.numberOfColumnsInFrame      = context.readValueUnsafe(telegram::segment_meta_data::kNumberOfColumnsInFrame);
  metaData.numberOfRows                = context.readValueUnsafe(telegram::segment_meta_data::kNumberOfRows);
  metaData.numberOfEchoes              = context.readValueUnsafe(telegram::segment_meta_data::kNumberOfEchoes);
  metaData.numberOfAmbientLightRows    = context.readValueUnsafe(telegram::segment_meta_data::kNumberOfAmbientLightRows);
  metaData.numberOfInterlaceSteps      = context.readValueUnsafe(telegram::segment_meta_data::kNumberOfInterlaceSteps);
  metaData.interlaceIndex              = context.readValueUnsafe(telegram::segment_meta_data::kInterlaceIndex);
  metaData.scanConfigurationIdentifier = context.readValueUnsafe(telegram::segment_meta_data::kScanConfigurationIdentifier);
  distanceScalingFactor                = context.readValueUnsafe(telegram::segment_meta_data::kDistanceScalingFactor);
  echoDataContent                      = context.readValueUnsafe<BitField<EchoDataContent>>(telegram::segment_meta_data::kEchoDataContent);

  context.skipBytes(telegram::segment_meta_data::reservedSize);
}

auto readAmbientLightPixels(CompactParserContext& context, SegmentMetaData const& metaData) -> std::vector<std::uint16_t>
{
  auto const numberOfColumns            = metaData.numberOfColumnsInSegment;
  auto const numberOfRows               = metaData.numberOfAmbientLightRows;
  auto const numberOfAmbientLightValues = checkedMultiply(numberOfColumns, numberOfRows);
  auto const numberOfBytesToRead        = checkedMultiply(numberOfAmbientLightValues, telegram::kAmbientLightData.sizeInBytes);
  if (context.numberOfBytesRemaining() < numberOfBytesToRead)
  {
    throw std::invalid_argument("Not enough data to read the pixel data.");
  }

  std::vector<std::uint16_t> pixelValues;
  pixelValues.resize(numberOfAmbientLightValues);
  context.copyMemoryUnsafe(pixelValues.data(), numberOfBytesToRead);
  return pixelValues;
}

auto readGeometry(CompactParserContext& context, SegmentMetaData const& metaData) -> Geometry
{
  auto const sizeOfElevationData          = checkedMultiply(metaData.numberOfRows, telegram::geometry::kElevationAngles.sizeInBytes);
  auto const sizeOfAzimuthData            = checkedMultiply(metaData.numberOfColumnsInSegment, telegram::geometry::kAzimuthAngles.sizeInBytes);
  auto const sizeOfRelativeTimeStampsData = checkedMultiply(metaData.numberOfColumnsInSegment, telegram::geometry::kRelativeTimeStamps.sizeInBytes);
  auto const sizeOfReservedGeometryData   = checkedMultiply(metaData.numberOfColumnsInSegment, telegram::geometry::kReservedGeometry.sizeInBytes);
  auto const sizeOfGeometry               = checkedAdd(sizeOfElevationData, sizeOfAzimuthData, sizeOfRelativeTimeStampsData, sizeOfReservedGeometryData);
  ;
  if (context.numberOfBytesRemaining() < sizeOfGeometry)
  {
    throw std::invalid_argument("Not enough data to read the geometry.");
  }

  Geometry geometry;
  geometry.elevations.reserve(metaData.numberOfRows);
  geometry.azimuths.reserve(metaData.numberOfColumnsInSegment);
  geometry.relativeTimeStamps.reserve(metaData.numberOfColumnsInSegment);

  // Caution! The order of the readValueUnsafe calls is important and defined by the protocol!
  for (std::size_t rowIndex = 0; rowIndex < metaData.numberOfRows; ++rowIndex)
  {
    Angle const elevationAngle = Angle::fromRadians(context.readValueUnsafe(telegram::geometry::kElevationAngles));
    geometry.elevations.push_back(elevationAngle);
  }

  // Separate loops are necessary because the telegram layout stores all azimuths first, then all relative timestamps, etc.
  for (std::size_t columnIndex = 0; columnIndex < metaData.numberOfColumnsInSegment; ++columnIndex)
  {
    Angle const azimuthAngle = Angle::fromRadians(context.readValueUnsafe(telegram::geometry::kAzimuthAngles));
    geometry.azimuths.push_back(azimuthAngle);
  }

  for (std::size_t columnIndex = 0; columnIndex < metaData.numberOfColumnsInSegment; ++columnIndex)
  {
    // Caution! Contrary to most other timestamp related values this is a 32 bit value!
    Duration const relativeTimestamp = Duration::fromMicroseconds(context.readValueUnsafe(telegram::geometry::kRelativeTimeStamps));
    geometry.relativeTimeStamps.push_back(relativeTimestamp);
  }

  // Skip reserved geometry data
  context.skipBytes(sizeOfReservedGeometryData);

  return geometry;
}

auto readScanData(
  CompactParserContext& context,
  SegmentMetaData const& metaData,
  BitField<EchoDataContent> echoDataContent,
  float distanceScalingFactor,
  MultiScan200Data& multiScan200Data
)
{
  auto const numberOfBeams   = checkedMultiply(metaData.numberOfRows, metaData.numberOfColumnsInSegment);
  auto const numberOfSamples = checkedMultiply(metaData.numberOfEchoes, numberOfBeams);

  auto const sizeOfDistancesData   = checkedMultiply(numberOfSamples, telegram::kDistances.sizeInBytes);
  auto const sizeOfIntensitiesData = (echoDataContent.isSet(EchoDataContent::Intensity)) ? sizeOfSubByteArray<kSizeOfIntensityInBits>(numberOfSamples) : 0;
  auto const sizeOfEchoPropertiesData =
    (echoDataContent.isSet(EchoDataContent::Properties)) ? checkedMultiply(numberOfSamples, telegram::kEchoProperties.sizeInBytes) : 0;
  auto const totalSizeOfScanData = checkedAdd(sizeOfDistancesData, sizeOfIntensitiesData, sizeOfEchoPropertiesData);
  if (context.numberOfBytesRemaining() < totalSizeOfScanData)
  {
    throw std::invalid_argument("Not enough data to read the scan data.");
  }

  // Read raw distances without assuming alignment.
  std::uint8_t const* rawDistanceBytes = context.nextByte();
  multiScan200Data.distances           = std::vector<Distance>(numberOfSamples);
  for (std::size_t i = 0; i < numberOfSamples; ++i)
  {
    std::uint16_t rawDistance = 0;
    std::memcpy(&rawDistance, rawDistanceBytes + i * telegram::kDistances.sizeInBytes, sizeof(rawDistance));
    multiScan200Data.distances[i] = Distance::fromMillimeters(static_cast<Distance::value_type>(rawDistance) * distanceScalingFactor);
  }
  context.skipBytes(sizeOfDistancesData);

  // Intensities
  if ((echoDataContent.isSet(EchoDataContent::Intensity)))
  {
    std::vector<std::uint16_t> rawIntensities;
    auto const numberOfBytesRead = convertSubByteArray<std::uint16_t, kSizeOfIntensityInBits>(context.remainingBytes(), numberOfSamples, rawIntensities);
    context.skipBytes(numberOfBytesRead);

    multiScan200Data.intensities.resize(numberOfSamples);
    // AXIVION Next Construct CertC++-MEM30 CertC++-MEM50 : rawIntensities is accessed by fresh index after convertSubByteArray returns, no stale pointers exist.
    for (std::size_t i = 0; i < numberOfSamples; ++i)
    {
      multiScan200Data.intensities[i] = static_cast<float>(rawIntensities[i]) / maxIntensityValue;
    }
  }

  // Echo properties - bulk read directly into target
  if ((echoDataContent.isSet(EchoDataContent::Properties)))
  {
    multiScan200Data.echoProperties.resize(numberOfSamples);
    context.copyMemory(multiScan200Data.echoProperties.data(), sizeOfEchoPropertiesData);
  }
}

} // namespace

auto Parser::validateAndParse(ByteView data, bool validateChecksum) -> MultiScan200Data
{
  LOG_FAST_LOOP_INFO("MultiScan200Parser") << "Validating and parsing " << data.size() << " bytes of data.";

  if (validateChecksum)
  {
    CompactParser::validateChecksum(data);
  }

  CompactParserContext context {data};

  MultiScan200Data multiScan200Data;
  TelegramHeaderWireInfo telegramHeaderWireInfo;
  if (readAndValidateTelegramHeaderCommon(
        context,
        TelegramType::MultiScan200,
        kSupportedTelegramVersions,
        multiScan200Data.telegramHeader,
        telegramHeaderWireInfo
      ) == HeaderReadResult::InsufficientData)
  {
    throw std::invalid_argument("Not enough data to read the telegram header.");
  }
  multiScan200Data.telegramHeader.senderSerialNumber = context.readValue(compact::telegram::header::kSenderSerialNumber);

  BitField<EchoDataContent> echoDataContent;
  float distanceScalingFactor = 0.0f;
  // Read and parse the segment meta data
  readSegmentMetaData(context, multiScan200Data.segmentMetaData, echoDataContent, distanceScalingFactor);

  // Read and parse the ambient light pixels
  multiScan200Data.ambientLightData = readAmbientLightPixels(context, multiScan200Data.segmentMetaData);

  // Intermediate step: read the geometry information. This will later be used to fill the beams.
  multiScan200Data.geometry = readGeometry(context, multiScan200Data.segmentMetaData);

  // Read the scan data. The resulting data is quite different from the protocol layout so it needs the
  // geometry information to assemble the beams correctly.
  readScanData(context, multiScan200Data.segmentMetaData, echoDataContent, distanceScalingFactor, multiScan200Data);

  if (context.numberOfBytesRemaining() != compact::telegram::kChecksum.sizeInBytes)
  {
    throw std::invalid_argument(
      "Expected exactly " + std::to_string(compact::telegram::kChecksum.sizeInBytes) + " bytes for the checksum at the end of the telegram, but found " +
      std::to_string(context.numberOfBytesRemaining()) + " bytes."
    );
  }

  return multiScan200Data;
}

auto Parser::getSize(ByteView data) const -> std::optional<std::size_t>
{
  CompactParserContext context {data};

  TelegramHeader telegramHeader;
  TelegramHeaderWireInfo telegramHeaderWireInfo;
  if (readAndValidateTelegramHeaderCommon(context, TelegramType::MultiScan200, kSupportedTelegramVersions, telegramHeader, telegramHeaderWireInfo) ==
      HeaderReadResult::InsufficientData)
  {
    return std::nullopt;
  }

  return compact::telegram::header::sizeInBytes + telegramHeaderWireInfo.payloadLength + compact::telegram::kChecksum.sizeInBytes;
}

// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)

} // namespace sick::compact::multiscan200
