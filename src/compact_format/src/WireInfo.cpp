/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include "WireInfo.hpp"
#include "CompactParserContext.hpp"
#include "CompactTelegram.hpp"
#include <sick_perception_sdk/compact_format/CompactData.hpp>
#include <sick_perception_sdk/compact_format/CompactParser.hpp>

#include <set>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace sick::compact {

auto readAndValidateTelegramHeaderCommon(
  CompactParserContext& context,
  TelegramType expectedType,
  std::set<int> expectedVersions,
  TelegramHeader& telegramHeader,
  TelegramHeaderWireInfo& telegramHeaderWireInfo
) -> HeaderReadResult
{
  if (context.numberOfBytesRemaining() < compact::telegram::header::sizeInBytes)
  {
    // The header has not fully arrived yet. This might be a normal streaming condition or an error.
    // It's up to the caller to decide how to handle this situation appropriately.
    return HeaderReadResult::InsufficientData;
  }

  auto const startOfFrame = context.readValueUnsafe(telegram::header::kStartOfFrame);
  if (startOfFrame != CompactParser::kExpectedStartOfFrame)
  {
    throw std::invalid_argument("Invalid start of frame");
  }

  telegramHeaderWireInfo.telegramType = context.readValueUnsafe<TelegramType>(telegram::header::kTelegramType);
  if (telegramHeaderWireInfo.telegramType != expectedType)
  {
    throw std::invalid_argument(
      "Unsupported telegram type " + std::to_string(static_cast<std::underlying_type_t<TelegramType>>(telegramHeaderWireInfo.telegramType))
    );
  }

  telegramHeader.telegramSequenceNumber  = context.readValueUnsafe(telegram::header::kTelegramSequenceNumber);
  telegramHeader.transmitTimestamp       = Timestamp::fromMicrosecondsSinceEpoch(context.readValueUnsafe(telegram::header::kTransmitTimestamp));
  telegramHeaderWireInfo.telegramVersion = context.readValueUnsafe<int>(telegram::header::kTelegramVersion);

  if (expectedVersions.find(telegramHeaderWireInfo.telegramVersion) == expectedVersions.end())
  {
    throw std::invalid_argument(
      "Unsupported telegram version " + std::to_string(telegramHeaderWireInfo.telegramVersion) + " for telegram type " +
      std::to_string(static_cast<std::underlying_type_t<TelegramType>>(telegramHeaderWireInfo.telegramType))
    );
  }

  telegramHeaderWireInfo.payloadLength = context.readValueUnsafe(telegram::header::kPayloadLength);
  return HeaderReadResult::Ok;
}

} // namespace sick::compact
