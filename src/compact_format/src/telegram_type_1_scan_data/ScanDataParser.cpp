/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanDataParser.hpp>

#include "../CompactParserContext.hpp"
#include "../CompactTelegram.hpp"
#include "../WireInfo.hpp"
#include "CompactTelegram.hpp"
#include <sick_perception_sdk/common/BitField.hpp>
#include <sick_perception_sdk/common/ByteView.hpp>
#include <sick_perception_sdk/common/CheckedMath.hpp>
#include <sick_perception_sdk/common/logging/logging.hpp>
#include <sick_perception_sdk/common/quantities/Angle.hpp>
#include <sick_perception_sdk/common/quantities/Distance.hpp>
#include <sick_perception_sdk/common/quantities/Timestamp.hpp>
#include <sick_perception_sdk/compact_format/CompactData.hpp>
#include <sick_perception_sdk/compact_format/CompactParser.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanData.hpp>

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <limits>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace sick::compact::scan_data {

namespace {

std::set<int> const kSupportedTelegramVersions = {3, 4};

struct ModuleWireInfo
{
  std::uint64_t segmentIndex {0};
  std::uint64_t frameSequenceNumber {0};
  std::uint32_t senderSerialNumber {0};
  float distanceScalingFactor {1.0f};
  std::size_t numberOfBytesOfNextModule {0};
  BitField<EchoContent> echoContent;
  BitField<BeamContent> beamContent;
};

// In the binary data the intensity value is between 0 and 65,535, in the data structure it is between 0.0 and 1.0.
constexpr float kIntensityScalingFactor = 65'535.0f;

// The offset from the start of the module meta data of the numberOfRows field.
constexpr std::size_t kNumberOfRowsOffset =
  telegram::module_meta_data::kSegmentIndex.sizeInBytes + telegram::module_meta_data::kFrameSequenceNumber.sizeInBytes +
  telegram::module_meta_data::kSenderSerialNumber.sizeInBytes;

// The number of bytes by which the module meta data grows per row in the module.
constexpr std::size_t kModuleMetaDataSizePerRow =
  telegram::module_meta_data::kStartTimestamp.sizeInBytes + telegram::module_meta_data::kEndTimestamp.sizeInBytes +
  telegram::module_meta_data::kElevations.sizeInBytes + telegram::module_meta_data::kFirstBeamAzimuths.sizeInBytes +
  telegram::module_meta_data::kLastBeamAzimuths.sizeInBytes;

template <typename ValueT, typename CompactValueT, typename AccessorT>
void readRowMetaDataArray(
  CompactParserContext& context,
  std::size_t numberOfRows,
  telegram::CompactField<CompactValueT> const& field,
  std::vector<Module::RowMetaData>& rowMetaData,
  AccessorT memberAccessor
)
{
  for (std::size_t i = 0; i < numberOfRows; ++i)
  {
    memberAccessor(rowMetaData[i]) = context.readValueUnsafe<ValueT, CompactValueT>(field);
  }
}

auto readModuleMetaData(CompactParserContext& context, std::uint32_t telegramVersion, ModuleWireInfo& telegramModuleWireInfo, Module& module)
{
  auto const initialNumberOfBytesRemaining = context.numberOfBytesRemaining();
  std::size_t metaDataFixedSize =
    telegram::module_meta_data::kSegmentIndex.sizeInBytes            //
    + telegram::module_meta_data::kFrameSequenceNumber.sizeInBytes   //
    + telegram::module_meta_data::kSenderSerialNumber.sizeInBytes    //
    + telegram::module_meta_data::kNumberOfRows.sizeInBytes          //
    + telegram::module_meta_data::kNumberOfColumns.sizeInBytes       //
    + telegram::module_meta_data::kNumberOfEchoesPerBeam.sizeInBytes //
    + telegram::module_meta_data::kNextModulePayloadSize.sizeInBytes //
    + telegram::module_meta_data::kAvailability.sizeInBytes          //
    + telegram::module_meta_data::kEchoContent.sizeInBytes           //
    + telegram::module_meta_data::kBeamContent.sizeInBytes           //
    + telegram::module_meta_data::kReserved.sizeInBytes;

  if (telegramVersion == 4)
  {
    metaDataFixedSize += telegram::module_meta_data::kDistanceScalingFactor.sizeInBytes; // Only available in version 4
  }

  if (initialNumberOfBytesRemaining < metaDataFixedSize)
  {
    throw std::invalid_argument("Not enough data to read module meta data.");
  }

  telegramModuleWireInfo.segmentIndex        = context.readValueUnsafe(telegram::module_meta_data::kSegmentIndex);
  telegramModuleWireInfo.frameSequenceNumber = context.readValueUnsafe(telegram::module_meta_data::kFrameSequenceNumber);
  telegramModuleWireInfo.senderSerialNumber  = context.readValueUnsafe(telegram::module_meta_data::kSenderSerialNumber);
  auto const numberOfRows                    = context.readValueUnsafe<std::size_t>(telegram::module_meta_data::kNumberOfRows);
  if (initialNumberOfBytesRemaining < checkedAdd(checkedMultiply(numberOfRows, kModuleMetaDataSizePerRow), metaDataFixedSize))
  {
    throw std::invalid_argument("Not enough data to read module meta data.");
  }

  module.numberOfColumns       = context.readValueUnsafe<std::size_t>(telegram::module_meta_data::kNumberOfColumns);
  module.numberOfEchoesPerBeam = context.readValueUnsafe<std::size_t>(telegram::module_meta_data::kNumberOfEchoesPerBeam);

  // Row meta data
  module.rowMetaData = std::vector<Module::RowMetaData>(numberOfRows);
  readRowMetaDataArray<Timestamp::value_type>(
    context,
    numberOfRows,
    telegram::module_meta_data::kStartTimestamp,
    module.rowMetaData,
    [](Module::RowMetaData& metaData) -> Timestamp::value_type& {
      return metaData.firstBeamTimestamp.rawValueMutable();
    }
  );
  readRowMetaDataArray<Timestamp::value_type>(
    context,
    numberOfRows,
    telegram::module_meta_data::kEndTimestamp,
    module.rowMetaData,
    [](Module::RowMetaData& metaData) -> Timestamp::value_type& {
      return metaData.lastBeamTimestamp.rawValueMutable();
    }
  );
  readRowMetaDataArray<Angle::value_type>(
    context,
    numberOfRows,
    telegram::module_meta_data::kElevations,
    module.rowMetaData,
    [](Module::RowMetaData& metaData) -> Angle::value_type& {
      return metaData.elevation.rawValueMutable();
    }
  );
  readRowMetaDataArray<Angle::value_type>(
    context,
    numberOfRows,
    telegram::module_meta_data::kFirstBeamAzimuths,
    module.rowMetaData,
    [](Module::RowMetaData& metaData) -> Angle::value_type& {
      return metaData.firstBeamAzimuth.rawValueMutable();
    }
  );
  readRowMetaDataArray<Angle::value_type>(
    context,
    numberOfRows,
    telegram::module_meta_data::kLastBeamAzimuths,
    module.rowMetaData,
    [](Module::RowMetaData& metaData) -> Angle::value_type& {
      return metaData.lastBeamAzimuth.rawValueMutable();
    }
  );

  telegramModuleWireInfo.distanceScalingFactor = 1.0f;

  if (telegramVersion == 4)
  {
    telegramModuleWireInfo.distanceScalingFactor = context.readValueUnsafe<float, float32>(telegram::module_meta_data::kDistanceScalingFactor);
  }

  telegramModuleWireInfo.numberOfBytesOfNextModule = context.readValueUnsafe<size_t>(telegram::module_meta_data::kNextModulePayloadSize);
  context.skipValue(telegram::module_meta_data::kAvailability);
  telegramModuleWireInfo.echoContent = context.readValueUnsafe<BitField<EchoContent>>(telegram::module_meta_data::kEchoContent);
  telegramModuleWireInfo.beamContent = context.readValueUnsafe<BitField<BeamContent>>(telegram::module_meta_data::kBeamContent);
  context.skipValue(telegram::module_meta_data::kReserved);

  return telegramModuleWireInfo;
}

void readModuleBeamData(CompactParserContext& context, ModuleWireInfo const& telegramModuleWireInfo, Module& module)
{
  std::size_t sizeOfEchoData = 0;
  if ((telegramModuleWireInfo.echoContent.isSet(EchoContent::Distance)))
  {
    sizeOfEchoData += telegram::beam_data::kDistance.sizeInBytes;
  }
  if ((telegramModuleWireInfo.echoContent.isSet(EchoContent::Intensity)))
  {
    sizeOfEchoData += telegram::beam_data::kIntensity.sizeInBytes;
  }

  std::size_t sizeOfBeamData = 0;
  if ((telegramModuleWireInfo.beamContent.isSet(BeamContent::Properties)))
  {
    sizeOfBeamData += telegram::beam_data::kProperties.sizeInBytes;
  }
  if ((telegramModuleWireInfo.beamContent.isSet(BeamContent::Azimuth)))
  {
    sizeOfBeamData += telegram::beam_data::kAngle.sizeInBytes;
  }

  auto const numberOfBeamsInModule = checkedMultiply(module.numberOfColumns, module.rowMetaData.size());
  auto const numberOfSamples       = checkedMultiply(numberOfBeamsInModule, module.numberOfEchoesPerBeam);
  auto const sizeOfBeamsData =
    checkedMultiply(numberOfBeamsInModule, checkedAdd(sizeOfBeamData, checkedMultiply(module.numberOfEchoesPerBeam, sizeOfEchoData)));

  if (sizeOfBeamsData > static_cast<std::size_t>(std::numeric_limits<std::ptrdiff_t>::max()))
  {
    throw std::invalid_argument("Number of beams is too large, causing overflow.");
  }
  if (context.numberOfBytesRemaining() < sizeOfBeamsData)
  {
    throw std::invalid_argument("Not enough data to read the beams.");
  }

  bool const hasDistance   = telegramModuleWireInfo.echoContent.isSet(EchoContent::Distance);
  bool const hasIntensity  = telegramModuleWireInfo.echoContent.isSet(EchoContent::Intensity);
  bool const hasProperties = telegramModuleWireInfo.beamContent.isSet(BeamContent::Properties);
  bool const hasAzimuth    = telegramModuleWireInfo.beamContent.isSet(BeamContent::Azimuth);

  auto const numberOfEchoes  = module.numberOfEchoesPerBeam;
  auto const numberOfRows    = module.rowMetaData.size();
  auto const numberOfColumns = module.numberOfColumns;

  // Pre-allocate flat arrays
  if (hasDistance)
  {
    module.distances.resize(numberOfSamples);
  }
  if (hasIntensity)
  {
    module.intensities.resize(numberOfSamples, std::numeric_limits<float>::quiet_NaN());
  }
  if (hasProperties)
  {
    module.beamProperties.resize(numberOfBeamsInModule);
  }
  if (hasAzimuth)
  {
    module.beamAzimuths.resize(numberOfBeamsInModule);
  }

  for (std::size_t columnIndex = 0; columnIndex < numberOfColumns; ++columnIndex)
  {
    for (std::size_t rowIndex = 0; rowIndex < numberOfRows; ++rowIndex)
    {
      auto const flatBeamIndex = computeBeamIndex(module, columnIndex, rowIndex);

      for (std::size_t echoIndex = 0; echoIndex < numberOfEchoes; ++echoIndex)
      {
        auto const flatSampleIndex = computeSampleIndex(module, columnIndex, rowIndex, echoIndex);

        if (hasDistance)
        {
          auto const echoDistanceRaw        = context.readValueUnsafe<float>(telegram::beam_data::kDistance);
          module.distances[flatSampleIndex] = Distance::fromMillimeters(echoDistanceRaw * telegramModuleWireInfo.distanceScalingFactor);
        }
        if (hasIntensity)
        {
          auto const intensity                = context.readValueUnsafe<float>(telegram::beam_data::kIntensity) / kIntensityScalingFactor;
          module.intensities[flatSampleIndex] = intensity;
        }
      }

      // AXIVION Next Construct CertC++-MEM30 CertC++-MEM50 : Module vectors are pre-allocated with resize(), not modified during iteration.
      if (hasProperties)
      {
        module.beamProperties[flatBeamIndex] = BitField<BeamProperties>(context.readValueUnsafe<std::uint8_t, std::uint8_t>(telegram::beam_data::kProperties));
      }
      // AXIVION Next Construct CertC++-MEM30 CertC++-MEM50 : Module vectors are pre-allocated with resize(), not modified during iteration.
      if (hasAzimuth)
      {
        auto const azimuthRaw = context.readValueUnsafe<float>(telegram::beam_data::kAngle);

        // See SICK Compact format description (document number 8028132 on www.sick.com):
        // angleUint = angleRad * 5215 + 16384
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers): see documentation
        module.beamAzimuths[flatBeamIndex] = Angle::fromRadians((azimuthRaw - 16384.0f) / 5215.0f);
      }
    }
  }
}

void readModule(CompactParserContext& context, std::uint32_t telegramVersion, ModuleWireInfo& moduleWireInfo, Module& module)
{
  readModuleMetaData(context, telegramVersion, moduleWireInfo, module);
  readModuleBeamData(context, moduleWireInfo, module);
}

auto getNumberOfBytesOfNextModule(ByteView data, std::uint32_t telegramVersion) -> std::optional<std::size_t>
{
  if (data.size() < kNumberOfRowsOffset + telegram::module_meta_data::kNumberOfRows.sizeInBytes)
  {
    return std::nullopt;
  }

  CompactParserContext context {data.subview(kNumberOfRowsOffset)};

  auto numberOfRows = context.readValueUnsafe<std::size_t>(telegram::module_meta_data::kNumberOfRows);

  std::size_t nextModuleSizeOffset = checkedAdd(
    telegram::module_meta_data::kSegmentIndex.sizeInBytes + telegram::module_meta_data::kFrameSequenceNumber.sizeInBytes +
      telegram::module_meta_data::kSenderSerialNumber.sizeInBytes + telegram::module_meta_data::kNumberOfRows.sizeInBytes +
      telegram::module_meta_data::kNumberOfColumns.sizeInBytes + telegram::module_meta_data::kNumberOfEchoesPerBeam.sizeInBytes,
    checkedMultiply(numberOfRows, kModuleMetaDataSizePerRow)
  );
  if (telegramVersion == 4)
  {
    nextModuleSizeOffset += telegram::module_meta_data::kDistanceScalingFactor.sizeInBytes; // Only available in version 4
  }
  if (nextModuleSizeOffset > static_cast<std::size_t>(std::numeric_limits<std::ptrdiff_t>::max()))
  {
    throw std::invalid_argument("Next module size is too large, causing overflow.");
  }
  if (data.size() < checkedAdd(nextModuleSizeOffset, telegram::module_meta_data::kNextModulePayloadSize.sizeInBytes))
  {
    return std::nullopt;
  }

  context = CompactParserContext(data.subview(nextModuleSizeOffset));
  return context.readValueUnsafe<std::size_t>(telegram::module_meta_data::kNextModulePayloadSize);
}

} // namespace

auto Parser::validateAndParse(ByteView data, bool validateChecksum) -> ScanData
{
  LOG_FAST_LOOP_INFO("ScanDataParser") << "Validating and parsing " << data.size() << " bytes of scan data.";

  if (validateChecksum)
  {
    CompactParser::validateChecksum(data);
  }

  CompactParserContext context {data};

  TelegramHeader telegramHeader;
  TelegramHeaderWireInfo telegramHeaderWireInfo;
  if (readAndValidateTelegramHeaderCommon(context, TelegramType::ScanData, kSupportedTelegramVersions, telegramHeader, telegramHeaderWireInfo) ==
      HeaderReadResult::InsufficientData)
  {
    throw std::invalid_argument("Not enough data to read the telegram header.");
  }

  // We must parse and validate the checksum *after* reading all the modules because for telegram type 1
  // the field `payloadLength` is just the size of the first module, not the whole payload.
  // That is not really the purpose of a checksum but the format leaves us no choice.

  std::vector<Module> modules;
  std::vector<ModuleWireInfo> moduleWireInfos;

  std::size_t numberOfBytesOfNextModule = telegramHeaderWireInfo.payloadLength;
  // AXIVION Disable CertC++-MEM30: moduleWireInfos[0] is accessed only after loop completes and emptiness is checked.
  // AXIVION Disable CertC++-MEM50: moduleWireInfos[0] is accessed only after loop completes and emptiness is checked.
  while (numberOfBytesOfNextModule > 0)
  {
    ModuleWireInfo moduleWireInfo;
    Module module;
    readModule(context, telegramHeaderWireInfo.telegramVersion, moduleWireInfo, module);
    modules.push_back(std::move(module));
    moduleWireInfos.push_back(moduleWireInfo);
    numberOfBytesOfNextModule = moduleWireInfo.numberOfBytesOfNextModule;
  }

  if (context.numberOfBytesRemaining() != compact::telegram::kChecksum.sizeInBytes)
  {
    throw std::invalid_argument(
      "Expected exactly " + std::to_string(compact::telegram::kChecksum.sizeInBytes) + " bytes for the checksum at the end of the telegram, but found " +
      std::to_string(context.numberOfBytesRemaining()) + " bytes."
    );
  }

  if (moduleWireInfos.empty())
  {
    throw std::invalid_argument("Scan data telegram must contain at least one module");
  }

  telegramHeader.senderSerialNumber = moduleWireInfos[0].senderSerialNumber;
  // AXIVION Enable CertC++-MEM30
  // AXIVION Enable CertC++-MEM50

  return {telegramHeader, moduleWireInfos[0].frameSequenceNumber, moduleWireInfos[0].segmentIndex, std::move(modules)};
}

auto Parser::getSize(ByteView data) const -> std::optional<std::size_t>
{
  CompactParserContext context {data};

  TelegramHeader telegramHeader;
  TelegramHeaderWireInfo telegramHeaderWireInfo;
  if (readAndValidateTelegramHeaderCommon(context, TelegramType::ScanData, kSupportedTelegramVersions, telegramHeader, telegramHeaderWireInfo) ==
      HeaderReadResult::InsufficientData)
  {
    return std::nullopt;
  }
  std::size_t readPosition = context.readPosition();

  std::size_t numberOfBytesOfCurrentModule = telegramHeaderWireInfo.payloadLength;
  while (numberOfBytesOfCurrentModule > 0)
  {
    LOG_FAST_LOOP_INFO("ScanDataParser") << "Position " << readPosition << ": Next module size: " << numberOfBytesOfCurrentModule;

    if (data.size() < readPosition)
    {
      return std::nullopt;
    }

    auto numberOfBytesOfNextModule = getNumberOfBytesOfNextModule(data.subview(readPosition), telegramHeaderWireInfo.telegramVersion);
    if (!numberOfBytesOfNextModule.has_value())
    {
      return std::nullopt;
    }

    readPosition                 = checkedAdd(readPosition, numberOfBytesOfCurrentModule);
    numberOfBytesOfCurrentModule = *numberOfBytesOfNextModule;
  }

  return checkedAdd(readPosition, compact::telegram::kChecksum.sizeInBytes);
}

} // namespace sick::compact::scan_data
