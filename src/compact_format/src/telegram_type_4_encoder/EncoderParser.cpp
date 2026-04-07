/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/telegram_type_4_encoder/EncoderParser.hpp>

#include <sick_perception_sdk/common/ByteView.hpp>
#include <sick_perception_sdk/compact_format/CompactData.hpp>
#include <sick_perception_sdk/compact_format/CompactParser.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_4_encoder/EncoderData.hpp>

#include <cstddef>
#include <cstdint>
#include <optional>
#include <set>

namespace sick::compact::encoder {

namespace {

std::set<std::uint32_t> const kSupportedTelegramVersions = {1};

}

auto Parser::validateAndParse(ByteView data, bool validateChecksum) -> EncoderData
{
  EncoderData encoderData {};
  CompactParser::readValue(data, encoderData);

  CompactParser::validateTelegramHeader(encoderData.telegramHeader, TelegramType::Encoder, {1});

  if (validateChecksum)
  {
    CompactParser::validateChecksum(encoderData.telegramHeader, data);
  }

  return encoderData;
}

auto Parser::getSize(ByteView data) const -> std::optional<std::size_t>
{
  if (data.size() < sizeof(TelegramHeader))
  {
    return std::nullopt;
  }

  TelegramHeader header;
  readValue(data, header);
  validateTelegramHeader(header, TelegramType::Encoder, kSupportedTelegramVersions);

  return sizeof(TelegramHeader) + header.payloadLength + sizeof(std::uint32_t);
}

} // namespace sick::compact::encoder
