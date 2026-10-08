/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/
#include <sick_perception_sdk/compact_format/telegram_type_3_ambient_light/AmbientLightParser.hpp>

#include "../CompactParserContext.hpp"
#include "../CompactTelegram.hpp"
#include "../WireInfo.hpp"
#include "CompactTelegram.hpp"
#include <sick_perception_sdk/common/ByteView.hpp>
#include <sick_perception_sdk/common/CheckedMath.hpp>
#include <sick_perception_sdk/compact_format/CompactData.hpp>
#include <sick_perception_sdk/compact_format/CompactParser.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_3_ambient_light/AmbientLightData.hpp>

#include <cstddef>
#include <cstring> // for std::memcpy
#include <limits>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

namespace sick::compact::ambient_light {

namespace {

std::set<int> const kSupportedTelegramVersions = {1};

auto readPixels(CompactParserContext& context, MetaData const& metaData) -> std::vector<Column>
{
  auto const numberOfBytesToRead = checkedMultiply(metaData.numberOfColumns, metaData.numberOfLayers, telegram::kPixels.sizeInBytes);
  if (numberOfBytesToRead > static_cast<std::size_t>(std::numeric_limits<std::ptrdiff_t>::max()))
  {
    throw std::invalid_argument("Number of pixels is too large, causing overflow.");
  }

  if (context.numberOfBytesRemaining() < numberOfBytesToRead)
  {
    throw std::invalid_argument("Not enough data to read the pixel data.");
  }

  std::size_t readPosition = 0;
  auto pixels              = std::vector<Column> {};
  pixels.resize(metaData.numberOfColumns);
  for (auto& column : pixels)
  {
    column.resize(metaData.numberOfLayers);
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic) Pointer arithmetic is necessary here for efficient reading of the pixel data.
    std::memcpy(column.data(), context.data().data() + readPosition, column.size() * telegram::kPixels.sizeInBytes);
    readPosition += column.size() * telegram::kPixels.sizeInBytes;
  }
  context.skipBytes(numberOfBytesToRead);
  return pixels;
}

auto readPayload(CompactParserContext& context) -> Payload
{
  if (context.numberOfBytesRemaining() <
      telegram::kFrameSequenceNumber.sizeInBytes + telegram::kStartTimestamp.sizeInBytes + telegram::kStopTimestamp.sizeInBytes +
        telegram::kNumberOfLayers.sizeInBytes + telegram::kNumberOfColumns.sizeInBytes + telegram::kStartAzimuth.sizeInBytes +
        telegram::kStopAzimuth.sizeInBytes + telegram::kStartElevation.sizeInBytes + telegram::kStopElevation.sizeInBytes + telegram::kEncoding.sizeInBytes)
  {
    throw std::invalid_argument("Not enough data to read the payload metadata.");
  }

  Payload payload;
  payload.metaData.frameSequenceNumber = context.readValueUnsafe(telegram::kFrameSequenceNumber);
  payload.metaData.startTimestamp      = Timestamp::fromMicrosecondsSinceEpoch(context.readValueUnsafe(telegram::kStartTimestamp));
  payload.metaData.stopTimestamp       = Timestamp::fromMicrosecondsSinceEpoch(context.readValueUnsafe(telegram::kStopTimestamp));
  payload.metaData.numberOfLayers      = context.readValueUnsafe(telegram::kNumberOfLayers);
  payload.metaData.numberOfColumns     = context.readValueUnsafe(telegram::kNumberOfColumns);
  payload.metaData.startAzimuth        = Angle::fromRadians(context.readValueUnsafe(telegram::kStartAzimuth));
  payload.metaData.stopAzimuth         = Angle::fromRadians(context.readValueUnsafe(telegram::kStopAzimuth));
  payload.metaData.startElevation      = Angle::fromRadians(context.readValueUnsafe(telegram::kStartElevation));
  payload.metaData.stopElevation       = Angle::fromRadians(context.readValueUnsafe(telegram::kStopElevation));
  payload.metaData.encoding            = context.readValueUnsafe<PixelEncoding>(telegram::kEncoding);

  payload.pixels = readPixels(context, payload.metaData);
  return payload;
}

} // namespace

auto Parser::validateAndParse(ByteView data, bool validateChecksum) -> AmbientLightData
{
  if (validateChecksum)
  {
    CompactParser::validateChecksum(data);
  }

  CompactParserContext context {data};

  AmbientLightData ambientLightData;
  TelegramHeaderWireInfo telegramHeaderWireInfo;
  if (readAndValidateTelegramHeaderCommon(
        context,
        TelegramType::AmbientLight,
        kSupportedTelegramVersions,
        ambientLightData.telegramHeader,
        telegramHeaderWireInfo
      ) == HeaderReadResult::InsufficientData)
  {
    throw std::invalid_argument("Not enough data to read the telegram header.");
  }
  ambientLightData.telegramHeader.senderSerialNumber = context.readValue(compact::telegram::header::kSenderSerialNumber);

  ambientLightData.payload = readPayload(context);

  if (context.numberOfBytesRemaining() != compact::telegram::kChecksum.sizeInBytes)
  {
    throw std::invalid_argument(
      "Expected exactly " + std::to_string(compact::telegram::kChecksum.sizeInBytes) + " bytes for the checksum at the end of the telegram, but found " +
      std::to_string(context.numberOfBytesRemaining()) + " bytes."
    );
  }

  return ambientLightData;
}

auto Parser::getSize(ByteView data) const -> std::optional<std::size_t>
{
  CompactParserContext context {data};

  AmbientLightData ambientLightData;
  TelegramHeaderWireInfo telegramHeaderWireInfo;
  if (readAndValidateTelegramHeaderCommon(
        context,
        TelegramType::AmbientLight,
        kSupportedTelegramVersions,
        ambientLightData.telegramHeader,
        telegramHeaderWireInfo
      ) == HeaderReadResult::InsufficientData)
  {
    return std::nullopt;
  }

  return compact::telegram::header::sizeInBytes + telegramHeaderWireInfo.payloadLength + compact::telegram::kChecksum.sizeInBytes;
}

} // namespace sick::compact::ambient_light
