/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_2_imu_legacy/ImuData.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_2_imu_legacy/ImuLegacyParser.hpp>
#include <sick_perception_sdk/drivers/Receiver/UdpStreamReceiver.hpp>

#include <chrono>
#include <cstdint>
#include <functional>
#include <optional>
#include <string>
#include <utility>

namespace sick::compact {

class SDK_EXPORT UdpImuReceiver : public UdpStreamReceiver<imu_legacy::Parser, UdpImuReceiver>
{
public:
  using BaseT = UdpStreamReceiver<imu_legacy::Parser, UdpImuReceiver>;

  explicit UdpImuReceiver(typename BaseT::ErrorCallback onError, std::string loggerName)
    : BaseT(std::move(onError), std::move(loggerName))
  { }

  static constexpr std::uint16_t kDefaultPort = 7503;

  auto setup(
    std::uint16_t receiverPort                 = kDefaultPort,
    std::chrono::milliseconds firstDataTimeout = BaseT::kDefaultFirstDataTimeout,
    std::chrono::milliseconds newDataTimeout   = BaseT::kDefaultNewDataTimeout,
    std::size_t receiveBufferSize              = kDefaultReceiveBufferSize
  ) -> UdpImuReceiver&;

  auto setOnNewDataCallback(DataCallback callback) -> UdpImuReceiver&;

private:
  std::optional<DataCallback> m_callback;
};

} // namespace sick::compact
