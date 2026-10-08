/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/telegram_type_2_imu_legacy/ImuLegacyParser.hpp>

#include "../CompactParserContext.hpp"
#include "../CompactTelegram.hpp"
#include "CompactTelegram.hpp"
#include <sick_perception_sdk/common/ByteView.hpp>
#include <sick_perception_sdk/compact_format/CompactData.hpp>
#include <sick_perception_sdk/compact_format/CompactParser.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_2_imu_legacy/ImuData.hpp>

#include <cstddef>
#include <cstdint>
#include <optional>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace sick::compact::imu_legacy {

namespace {

struct ImuDataWireInfo
{
  std::uint32_t startOfFrame {0};
  TelegramType telegramType {TelegramType::Invalid};
  std::uint32_t telegramVersion {0};
};

void validateWireInfo(ImuDataWireInfo const& wireInfo)
{
  if (wireInfo.startOfFrame != CompactParser::kExpectedStartOfFrame)
  {
    throw std::invalid_argument("Invalid start of frame");
  }
  if (wireInfo.telegramType != TelegramType::ImuLegacy)
  {
    throw std::invalid_argument("Unsupported telegram type " + std::to_string(static_cast<std::underlying_type_t<TelegramType>>(wireInfo.telegramType)));
  }

  if (wireInfo.telegramVersion != 1u)
  {
    throw std::invalid_argument("Unsupported telegram version " + std::to_string(wireInfo.telegramVersion));
  }
}

} // namespace

auto Parser::validateAndParse(ByteView data, bool validateChecksum) -> imu::ImuData
{
  if (validateChecksum)
  {
    CompactParser::validateChecksum(data);
  }

  if (data.size() < telegram::sizeInBytes)
  {
    throw std::out_of_range("Not enough data to parse the imu telegram.");
  }

  CompactParserContext context {data};

  ImuDataWireInfo wireInfo {};
  wireInfo.startOfFrame    = context.readValueUnsafe(compact::telegram::header::kStartOfFrame);
  wireInfo.telegramType    = context.readValueUnsafe<TelegramType>(compact::telegram::header::kTelegramType);
  wireInfo.telegramVersion = context.readValueUnsafe(compact::telegram::header::kTelegramVersion);

  validateWireInfo(wireInfo);

  imu::ImuData imuData;

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

  imuData.sensorTimestamp = Timestamp::fromMicrosecondsSinceEpoch(context.readValueUnsafe(telegram::kSensorTimestamp));

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

} // namespace sick::compact::imu_legacy
