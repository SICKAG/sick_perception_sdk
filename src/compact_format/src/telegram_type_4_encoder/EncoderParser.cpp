/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/telegram_type_4_encoder/EncoderParser.hpp>

#include "../CompactParserContext.hpp"
#include "../CompactTelegram.hpp"
#include "../WireInfo.hpp"
#include "CompactTelegram.hpp"
#include <sick_perception_sdk/common/ByteView.hpp>
#include <sick_perception_sdk/compact_format/CompactData.hpp>
#include <sick_perception_sdk/compact_format/CompactParser.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_4_encoder/EncoderData.hpp>

#include <cstddef>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>

namespace sick::compact::encoder {

namespace {

std::set<int> const kSupportedTelegramVersions = {1};

}

auto Parser::validateAndParse(ByteView data, bool validateChecksum) -> EncoderData
{
  if (validateChecksum)
  {
    CompactParser::validateChecksum(data);
  }

  if (data.size() < telegram::sizeInBytes)
  {
    throw std::out_of_range("Not enough data to parse the encoder telegram.");
  }

  CompactParserContext context {data};

  EncoderData encoderData;
  TelegramHeaderWireInfo telegramHeaderWireInfo;
  if (readAndValidateTelegramHeaderCommon(context, TelegramType::Encoder, kSupportedTelegramVersions, encoderData.telegramHeader, telegramHeaderWireInfo) ==
      HeaderReadResult::InsufficientData)
  {
    throw std::invalid_argument("Not enough data to read the telegram header.");
  }
  encoderData.telegramHeader.senderSerialNumber = context.readValueUnsafe(telegram::kSenderSerialNumber);

  encoderData.frameSequenceNumber         = context.readValueUnsafe(telegram::kFrameSequenceNumber);
  encoderData.tickCount                   = context.readValueUnsafe(telegram::kTickCount);
  encoderData.tickCountAtReferenceSignal1 = context.readValueUnsafe(telegram::kTickCountAtReferenceSignal1);
  encoderData.tickCountAtReferenceSignal2 = context.readValueUnsafe(telegram::kTickCountAtReferenceSignal2);
  encoderData.speed                       = Speed::fromMetersPerSecond(context.readValueUnsafe(telegram::kSpeed));
  encoderData.timestampOfTickCount        = Timestamp::fromMicrosecondsSinceEpoch(context.readValueUnsafe(telegram::kTimestampOfTickCount));
  encoderData.timestampOfReferenceSignal1 = Timestamp::fromMicrosecondsSinceEpoch(context.readValueUnsafe(telegram::kTimestampOfReferenceSignal1));
  encoderData.timestampOfReferenceSignal2 = Timestamp::fromMicrosecondsSinceEpoch(context.readValueUnsafe(telegram::kTimestampOfReferenceSignal2));

  if (context.numberOfBytesRemaining() != compact::telegram::kChecksum.sizeInBytes)
  {
    throw std::invalid_argument(
      "Expected exactly " + std::to_string(compact::telegram::kChecksum.sizeInBytes) + " bytes for the checksum at the end of the telegram, but found " +
      std::to_string(context.numberOfBytesRemaining()) + " bytes."
    );
  }

  return encoderData;
}

auto Parser::getSize(ByteView /*data*/) const -> std::optional<std::size_t>
{
  return telegram::sizeInBytes;
}

} // namespace sick::compact::encoder
