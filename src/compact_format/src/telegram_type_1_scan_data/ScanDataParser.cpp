/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanDataParser.hpp>

#include <sick_perception_sdk/common/ByteView.hpp>
#include <sick_perception_sdk/common/logging/logging.hpp>
#include <sick_perception_sdk/common/quantities/Angle.hpp>
#include <sick_perception_sdk/common/quantities/Timestamp.hpp>
#include <sick_perception_sdk/compact_format/CompactData.hpp>
#include <sick_perception_sdk/compact_format/CompactParser.hpp>
#include <sick_perception_sdk/compact_format/Crc32Utils.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanData.hpp>

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <limits>
#include <optional>
#include <stdexcept>
#include <vector>

namespace sick::compact::scan_data {

auto Parser::readModuleMetaData(ByteView data, std::uint32_t version, Module::MetaData& metaData) -> std::size_t
{
  std::uint8_t reserved = 0;

  std::size_t metaDataFixedSize =
    sizeof(metaData.segmentIndex)                //
    + sizeof(metaData.frameSequenceNumber)       //
    + sizeof(metaData.senderSerialNumber)        //
    + sizeof(metaData.numberOfRows)              //
    + sizeof(metaData.numberOfColumns)           //
    + sizeof(metaData.numberOfEchoesPerBeam)     //
    + sizeof(metaData.numberOfBytesOfNextModule) //
    + sizeof(std::uint8_t)                       // availability, not stored in meta data
    + sizeof(metaData.echoContent)               //
    + sizeof(metaData.beamContent)               //
    + sizeof(reserved);

  if (version == 4)
  {
    metaDataFixedSize += sizeof(metaData.distanceScalingFactor); // Only available in version 4
  }

  assert(metaDataFixedSize <= static_cast<std::size_t>(std::numeric_limits<std::ptrdiff_t>::max()));
  if (data.size() < metaDataFixedSize)
  {
    throw std::invalid_argument("Not enough data to read the module meta data.");
  }

  std::size_t readPosition = 0;

  // FIXME Potential for optimization: Read all of those variables at once with a single
  // memcpy(&metaData.segmentIndex, data.data() + readPosition, sizeOfFirstFixedSizePortionOfMetaData)
  readPosition += CompactParser::readValueUnsafe(data.subview(readPosition), metaData.segmentIndex);
  readPosition += CompactParser::readValueUnsafe(data.subview(readPosition), metaData.frameSequenceNumber);
  readPosition += CompactParser::readValueUnsafe(data.subview(readPosition), metaData.senderSerialNumber);
  readPosition += CompactParser::readValueUnsafe(data.subview(readPosition), metaData.numberOfRows);
  readPosition += CompactParser::readValueUnsafe(data.subview(readPosition), metaData.numberOfColumns);
  readPosition += CompactParser::readValueUnsafe(data.subview(readPosition), metaData.numberOfEchoesPerBeam);

  auto const metaDataVariableSize = metaData.numberOfRows * sizeof(Module::RowMetaData);
  if (metaDataFixedSize + metaDataVariableSize > static_cast<std::size_t>(std::numeric_limits<std::ptrdiff_t>::max()))
  {
    throw std::invalid_argument("Number of layers is too large, causing overflow.");
  }
  if (data.size() < metaDataFixedSize + metaDataVariableSize)
  {
    throw std::invalid_argument("Not enough data to read the module meta data.");
  }

  // Row meta data
  auto const numberOfRows = static_cast<std::size_t>(metaData.numberOfRows);
  metaData.rowMetaData    = std::vector<Module::RowMetaData>(numberOfRows);
  readPosition += readRowMetaDataArray<Timestamp::value_type>(
    data.subview(readPosition),
    numberOfRows,
    metaData.rowMetaData,
    [](Module::RowMetaData& metaData) -> Timestamp::value_type& {
      return metaData.firstBeamTimestamp.rawValueMutable();
    }
  );
  readPosition += readRowMetaDataArray<Timestamp::value_type>(
    data.subview(readPosition),
    numberOfRows,
    metaData.rowMetaData,
    [](Module::RowMetaData& metaData) -> Timestamp::value_type& {
      return metaData.lastBeamTimestamp.rawValueMutable();
    }
  );
  readPosition += readRowMetaDataArray<Angle::value_type>(
    data.subview(readPosition),
    numberOfRows,
    metaData.rowMetaData,
    [](Module::RowMetaData& metaData) -> Angle::value_type& {
      return metaData.elevation.rawValueMutable();
    }
  );
  readPosition += readRowMetaDataArray<Angle::value_type>(
    data.subview(readPosition),
    numberOfRows,
    metaData.rowMetaData,
    [](Module::RowMetaData& metaData) -> Angle::value_type& {
      return metaData.firstBeamAzimuth.rawValueMutable();
    }
  );
  readPosition += readRowMetaDataArray<Angle::value_type>(
    data.subview(readPosition),
    numberOfRows,
    metaData.rowMetaData,
    [](Module::RowMetaData& metaData) -> Angle::value_type& {
      return metaData.lastBeamAzimuth.rawValueMutable();
    }
  );

  if (version == 4)
  {
    readPosition += CompactParser::readValueUnsafe(data.subview(readPosition), metaData.distanceScalingFactor);
  }
  else
  {
    metaData.distanceScalingFactor = 1.0f;
  }

  // FIXME Potential for optimization: Read all of those variables at once with a single
  // memcpy(&metaData.numberOfBytesOfNextModule, data.data() + readPosition, sizeOfSecondFixedSizePortionOfMetaData)
  readPosition += CompactParser::readValueUnsafe(data.subview(readPosition), metaData.numberOfBytesOfNextModule);
  readPosition += sizeof(std::uint8_t); // availability, not stored in meta data
  readPosition += CompactParser::readValueUnsafe(data.subview(readPosition), metaData.echoContent);
  readPosition += CompactParser::readValueUnsafe(data.subview(readPosition), metaData.beamContent);
  readPosition += CompactParser::readValueUnsafe(data.subview(readPosition), reserved);

  return readPosition;
}

auto Parser::readModuleBeamData(ByteView data, Module::MetaData const& metaData, std::vector<Column>& columns) -> std::size_t
{
  std::size_t sizeOfEchoData = 0;
  if ((metaData.echoContent.isSet(EchoContent::Distance)))
  {
    sizeOfEchoData += kSizeOfBinaryDistance;
  }
  if ((metaData.echoContent.isSet(EchoContent::Intensity)))
  {
    sizeOfEchoData += kSizeOfBinaryIntensity;
  }

  std::size_t sizeOfBeamData = 0;
  if ((metaData.beamContent.isSet(BeamContent::Properties)))
  {
    sizeOfBeamData += sizeof(Beam::properties);
  }
  if ((metaData.beamContent.isSet(BeamContent::Azimuth)))
  {
    sizeOfBeamData += kSizeOfBinaryAzimuth;
  }

  auto const numberOfBeamsInModule = static_cast<std::size_t>(metaData.numberOfColumns) * static_cast<std::size_t>(metaData.numberOfRows);
  auto const sizeOfBeamsData       = static_cast<std::size_t>(numberOfBeamsInModule * (sizeOfBeamData + metaData.numberOfEchoesPerBeam * sizeOfEchoData));

  if (sizeOfBeamsData > static_cast<std::size_t>(std::numeric_limits<std::ptrdiff_t>::max()))
  {
    throw std::invalid_argument("Number of beams is too large, causing overflow.");
  }
  if (data.size() < sizeOfBeamsData)
  {
    throw std::invalid_argument("Not enough data to read the beams.");
  }

  std::size_t readPosition = 0;
  columns.resize(metaData.numberOfColumns);
  for (auto& column : columns)
  {
    column.resize(metaData.numberOfRows);
    for (auto& beam : column)
    {
      beam.echoes.resize(metaData.numberOfEchoesPerBeam);
      for (auto& echo : beam.echoes)
      {
        if (metaData.echoContent.isSet(EchoContent::Distance))
        {
          // echoDistance is not necessarily given in millimeters.
          // It needs to be scaled by metaData.distanceScalingFactor to obtain the measured distance in millimeters.
          std::uint16_t echoDistanceRaw = 0;
          readPosition += CompactParser::readValueUnsafe(data.subview(readPosition), echoDistanceRaw);
          echo.distance = Distance::fromMillimeters(static_cast<float>(echoDistanceRaw) * metaData.distanceScalingFactor);
        }
        if (metaData.echoContent.isSet(EchoContent::Intensity))
        {
          std::uint16_t intensity = 0;
          readPosition += CompactParser::readValueUnsafe(data.subview(readPosition), intensity);
          echo.intensity = static_cast<float>(intensity) / kIntensityScalingFactor;
        }
      }
      if (metaData.beamContent.isSet(BeamContent::Properties))
      {
        beam.properties = 0;
        readPosition += CompactParser::readValueUnsafe(data.subview(readPosition), beam.properties);
      }
      if (metaData.beamContent.isSet(BeamContent::Azimuth))
      {
        std::uint16_t angleUint16 = 0;
        readPosition += CompactParser::readValueUnsafe(data.subview(readPosition), angleUint16);

        // See SICK Compact format description (document number 8028132 on www.sick.com):
        // angleUint = angleRad * 5215 + 16384
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers): see documentation
        beam.azimuth = Angle::fromRadians((static_cast<float>(angleUint16) - 16384.0f) / 5215.0f);
      }
    }
  }
  return readPosition;
}

auto Parser::readModule(ByteView data, std::uint32_t version, Module& module) -> std::size_t
{
  std::size_t readPosition = readModuleMetaData(data, version, module.metaData);
  readPosition += readModuleBeamData(data.subview(readPosition), module.metaData, module.columns);
  return readPosition;
}

auto Parser::validateAndParse(ByteView data, bool validateChecksum) -> ScanData
{
  LOG_FAST_LOOP_INFO("ScanDataParser") << "Validating and parsing " << data.size() << " bytes of scan data.";
  TelegramHeader telegramHeader;
  std::size_t readPosition = CompactParser::readValue(data, telegramHeader);
  CompactParser::validateTelegramHeader(telegramHeader, TelegramType::ScanData, {3, 4});

  // We must parse and validate the checksum *after* reading all the modules because the for telegram type 1
  // the field `payloadLength` is just the size of the first module, not the whole payload.
  // That is not really the purpose of a checksum but the format leaves us no choice.

  std::vector<Module> modules;

  std::uint32_t numberOfBytesOfNextModule = telegramHeader.payloadLength;
  while (numberOfBytesOfNextModule > 0)
  {
    Module module;
    readPosition += readModule(data.subview(readPosition), telegramHeader.telegramVersion, module);
    modules.push_back(module);
    numberOfBytesOfNextModule = module.metaData.numberOfBytesOfNextModule;
  }

  // read checksum
  std::uint32_t receivedChecksum = 0;
  readPosition += CompactParser::readValue(data.subview(readPosition), receivedChecksum);

  // Verify checksum
  std::uint32_t const computedChecksum = sick::compact::crc32(data.first(readPosition - 4));
  if (validateChecksum && receivedChecksum != computedChecksum)
  {
    throw std::invalid_argument("Checksum verification failed");
  }

  return {telegramHeader, modules, receivedChecksum};
}

auto Parser::getSize(ByteView data) const -> std::optional<std::size_t>
{
  if (data.size() < sizeof(TelegramHeader))
  {
    return std::nullopt;
  }

  TelegramHeader telegramHeader;
  std::size_t readPosition = readValue(data, telegramHeader);
  CompactParser::validateTelegramHeader(telegramHeader, TelegramType::ScanData, {3, 4});

  std::uint32_t numberOfBytesOfCurrentModule = telegramHeader.payloadLength;
  while (numberOfBytesOfCurrentModule > 0)
  {
    LOG_FAST_LOOP_INFO("ScanDataParser") << "Position " << readPosition << ": Next module size: " << numberOfBytesOfCurrentModule;

    if (data.size() < readPosition)
    {
      return std::nullopt;
    }

    auto numberOfBytesOfNextModule = getNumberOfBytesOfNextModule(data.subview(readPosition), telegramHeader.telegramVersion);
    if (!numberOfBytesOfNextModule.has_value())
    {
      return std::nullopt;
    }

    readPosition += numberOfBytesOfCurrentModule;
    numberOfBytesOfCurrentModule = *numberOfBytesOfNextModule;
  }

  return readPosition + sizeof(ScanData::checksum);
}

auto Parser::getNumberOfBytesOfNextModule(ByteView data, std::uint32_t version) -> std::optional<std::uint32_t>
{
  if (data.size() < kNumberOfRowsOffset + sizeof(Module::MetaData::numberOfRows))
  {
    return std::nullopt;
  }
  std::uint32_t numberOfRows = 0;
  CompactParser::readValueUnsafe(data.subview(kNumberOfRowsOffset), numberOfRows);

  auto nextModuleSizeOffset = static_cast<std::size_t>(
    sizeof(Module::MetaData::segmentIndex) + sizeof(Module::MetaData::frameSequenceNumber) + sizeof(Module::MetaData::senderSerialNumber) +
    sizeof(Module::MetaData::numberOfRows) + sizeof(Module::MetaData::numberOfColumns) + sizeof(Module::MetaData::numberOfEchoesPerBeam) +
    numberOfRows * kModuleMetaDataSizePerRow
  );
  if (version == 4)
  {
    nextModuleSizeOffset += sizeof(Module::MetaData::distanceScalingFactor); // Only available in version 4
  }
  if (nextModuleSizeOffset > static_cast<std::size_t>(std::numeric_limits<std::ptrdiff_t>::max()))
  {
    throw std::invalid_argument("Next module size is too large, causing overflow.");
  }
  if (data.size() < nextModuleSizeOffset + sizeof(Module::MetaData::numberOfBytesOfNextModule))
  {
    return std::nullopt;
  }

  std::uint32_t numberOfBytesOfNextModule = 0;
  CompactParser::readValueUnsafe(data.subview(nextModuleSizeOffset), numberOfBytesOfNextModule);
  return numberOfBytesOfNextModule;
}

} // namespace sick::compact::scan_data
