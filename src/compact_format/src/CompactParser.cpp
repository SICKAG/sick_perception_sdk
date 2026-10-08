/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/CompactParser.hpp>

#include "CompactParserContext.hpp"
#include "CompactTelegram.hpp"
#include <sick_perception_sdk/common/ByteView.hpp>
#include <sick_perception_sdk/compact_format/Crc32Utils.hpp>

#include <cstdint>
#include <stdexcept>

namespace sick::compact {

void CompactParser::validateChecksum(ByteView data)
{
  if (data.size() < telegram::kChecksum.sizeInBytes)
  {
    throw std::invalid_argument("Data is too short to contain a checksum");
  }

  CompactParserContext context(data.last(telegram::kChecksum.sizeInBytes));
  auto const crcFromTelegram = context.readValueUnsafe(telegram::kChecksum);

  std::uint32_t const computedCrc = crc32(data.first(data.size() - telegram::kChecksum.sizeInBytes));
  if (crcFromTelegram != computedCrc)
  {
    throw std::invalid_argument("Invalid checksum");
  }
}

} // namespace sick::compact
