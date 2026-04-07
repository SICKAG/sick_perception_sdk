/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/telegram_type_2_imu/ImuParser.hpp>

#include <sick_perception_sdk/common/ByteView.hpp>
#include <sick_perception_sdk/compact_format/CompactData.hpp>
#include <sick_perception_sdk/compact_format/CompactParser.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_2_imu/ImuData.hpp>

#include <cstddef>
#include <optional>
#include <stdexcept>

namespace sick::compact::imu {

namespace {

void validateHeader(Header const& header)
{
  if (header.startOfFrame != CompactParser::kStartOfFrame)
  {
    throw std::invalid_argument("Invalid start of frame");
  }
  if (header.telegramType != TelegramType::Imu)
  {
    throw std::invalid_argument("Unsupported telegram type (command ID)");
  }

  if (header.telegramVersion != 1u)
  {
    throw std::invalid_argument("Unsupported telegram version. Supported version is 1.");
  }
}

} // namespace

auto Parser::validateAndParse(ByteView data, bool validateChecksum) -> ImuData
{
  ImuData compactImuData {};
  CompactParser::readValue(data, compactImuData);

  validateHeader(compactImuData.header);

  // Checksum validation cannot be done with validateChecksum here because the telegram does
  // not have the standard TelegramHeader with the payload length.
  if (validateChecksum && !CompactParser::isChecksumValid(data))
  {
    throw std::invalid_argument("Checksum verification failed");
  }

  return compactImuData;
}

auto Parser::getSize(ByteView /*data*/) const -> std::optional<std::size_t>
{
  return sizeof(ImuData);
}

} // namespace sick::compact::imu
