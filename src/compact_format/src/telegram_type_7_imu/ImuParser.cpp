/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/telegram_type_7_imu/ImuParser.hpp>

#include "../CompactParserContext.hpp"
#include "../CompactTelegram.hpp"
#include "../WireInfo.hpp"
#include "CompactTelegram.hpp"
#include <sick_perception_sdk/common/ByteView.hpp>
#include <sick_perception_sdk/compact_format/CompactData.hpp>
#include <sick_perception_sdk/compact_format/CompactParser.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_2_imu_legacy/ImuData.hpp>

#include <cstddef>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>

namespace sick::compact::imu {

namespace {

std::set<int> const kSupportedTelegramVersions = {1};

}

auto Parser::validateAndParse(ByteView data, bool validateChecksum) -> imu::ImuData
{
  if (validateChecksum)
  {
    CompactParser::validateChecksum(data);
  }

  CompactParserContext context {data};

  TelegramHeader telegramHeader;
  TelegramHeaderWireInfo telegramHeaderWireInfo;
  if (readAndValidateTelegramHeaderCommon(context, TelegramType::Imu, kSupportedTelegramVersions, telegramHeader, telegramHeaderWireInfo) ==
      HeaderReadResult::InsufficientData)
  {
    throw std::invalid_argument("Not enough data to read the telegram header.");
  }
  telegramHeader.senderSerialNumber = context.readValue(compact::telegram::header::kSenderSerialNumber);

  imu::ImuData imuData;

  imuData.sensorTimestamp = Timestamp::fromMicrosecondsSinceEpoch(context.readValueUnsafe(telegram::kSensorTimestamp));

  imuData.acceleration.x = Acceleration::fromMetersPerSecondSquared(context.readValueUnsafe(telegram::kAccelerationX));
  imuData.acceleration.y = Acceleration::fromMetersPerSecondSquared(context.readValueUnsafe(telegram::kAccelerationY));
  imuData.acceleration.z = Acceleration::fromMetersPerSecondSquared(context.readValueUnsafe(telegram::kAccelerationZ));

  imuData.angularVelocity.x = AngularVelocity::fromRadiansPerSecond(context.readValueUnsafe(telegram::kAngularVelocityX));
  imuData.angularVelocity.y = AngularVelocity::fromRadiansPerSecond(context.readValueUnsafe(telegram::kAngularVelocityY));
  imuData.angularVelocity.z = AngularVelocity::fromRadiansPerSecond(context.readValueUnsafe(telegram::kAngularVelocityZ));

  imuData.orientation.w = context.readValueUnsafe(telegram::kOrientationW);
  imuData.orientation.x = context.readValueUnsafe(telegram::kOrientationX);
  imuData.orientation.y = context.readValueUnsafe(telegram::kOrientationY);
  imuData.orientation.z = context.readValueUnsafe(telegram::kOrientationZ);

  if (context.numberOfBytesRemaining() != compact::telegram::kChecksum.sizeInBytes)
  {
    throw std::invalid_argument(
      "Expected exactly " + std::to_string(compact::telegram::kChecksum.sizeInBytes) + " bytes for the checksum at the end of the telegram, but found " +
      std::to_string(context.numberOfBytesRemaining()) + " bytes."
    );
  }

  return imuData;
}

auto Parser::getSize(ByteView /*data*/) const -> std::optional<std::size_t>
{
  return telegram::sizeInBytes;
}

} // namespace sick::compact::imu
