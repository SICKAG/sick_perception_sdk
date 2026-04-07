/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/CompactParser.hpp>

#include <sick_perception_sdk/common/ByteView.hpp>
#include <sick_perception_sdk/compact_format/CompactData.hpp>
#include <sick_perception_sdk/compact_format/Crc32Utils.hpp>

#include <cstdint>
#include <cstring> // for std::memcpy
#include <set>
#include <stdexcept>

static_assert(sizeof(float) == 4);

namespace sick::compact {

auto CompactParser::isChecksumValid(ByteView data) -> bool
{
  if (data.size() < sizeof(std::uint32_t))
  {
    return false;
  }

  std::uint32_t expectedCRC = 0;
  readValueUnsafe(data.last(sizeof(std::uint32_t)), expectedCRC);

  std::uint32_t const computedCRC = crc32(data.first(data.size() - sizeof(std::uint32_t)));
  return expectedCRC == computedCRC;
}

void CompactParser::validateTelegramHeader(TelegramHeader const& header, TelegramType expectedType, std::set<std::uint32_t> expectedVersions)
{
  if (header.startOfFrame != kStartOfFrame)
  {
    throw std::invalid_argument("Invalid start of frame");
  }
  if (header.telegramType != expectedType)
  {
    throw std::invalid_argument("Unsupported telegram type (command ID)");
  }

  if (expectedVersions.find(header.telegramVersion) == expectedVersions.end())
  {
    throw std::invalid_argument("Unsupported telegram version.");
  }
}

} // namespace sick::compact
