/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_2_imu_legacy/ImuData.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_2_imu_legacy/ImuLegacyParser.hpp>
#include <sick_perception_sdk/drivers/Receiver/DatagramDecoder.hpp>
#include <sick_perception_sdk/drivers/Receiver/ReceiverDefaults.hpp>
#include <sick_perception_sdk/drivers/Receiver/ReceiverLoop.hpp>
#include <sick_perception_sdk/drivers/Receiver/ReceiverSockets.hpp>

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <string>

namespace sick::compact {

class SDK_EXPORT UdpImuReceiverConfig
{
public:
  using DataCallback = std::function<void(imu::ImuData const&)>;

  static constexpr std::uint16_t kDefaultPort = 7503;

  static auto create(std::uint16_t receiverPort = kDefaultPort) -> UdpImuReceiverConfig;

  auto setReceiverPort(std::uint16_t receiverPort) -> UdpImuReceiverConfig&;

  auto setOnNewDataCallback(DataCallback callback) -> UdpImuReceiverConfig&;
  auto setMulticast(IpV4Address const& groupAddress, IpV4Address const& localInterfaceAddress) -> UdpImuReceiverConfig&;
  auto setTimeouts(std::chrono::milliseconds firstDataTimeout, std::chrono::milliseconds newDataTimeout) -> UdpImuReceiverConfig&;
  auto setReceiveBufferSize(std::size_t receiveBufferSize) -> UdpImuReceiverConfig&;
  //! \brief Defaults to rethrowing the exception. Set an empty-bodied callback to silence errors instead.
  auto setOnError(ErrorCallback onError) -> UdpImuReceiverConfig&;
  auto setLoggerName(std::string loggerName) -> UdpImuReceiverConfig&;

  [[nodiscard]] auto transport() const -> ReceiverTransport const&;
  [[nodiscard]] auto multicast() const -> std::optional<MulticastGroup> const&;
  [[nodiscard]] auto dataCallback() const -> DataCallback const&;
  [[nodiscard]] auto onError() const -> ErrorCallback const&;
  [[nodiscard]] auto loggerName() const -> std::string const&;

private:
  UdpImuReceiverConfig() = default;

  ReceiverTransport
    m_transport {kDefaultPort, receiver_defaults::kFirstDataTimeout, receiver_defaults::kNewDataTimeout, receiver_defaults::kUdpReceiveBufferSize};
  std::optional<MulticastGroup> m_multicast;
  DataCallback m_dataCallback;
  ErrorCallback m_onError  = receiver_defaults::kDefaultErrorCallback;
  std::string m_loggerName = "ImuReceiver";
};

//! \brief Receives Compact IMU telegrams from a UDP port.
class SDK_EXPORT UdpImuReceiver
{
public:
  explicit UdpImuReceiver(UdpImuReceiverConfig config);

  ~UdpImuReceiver();

  UdpImuReceiver(UdpImuReceiver const&)                    = delete;
  auto operator=(UdpImuReceiver const&) -> UdpImuReceiver& = delete;
  UdpImuReceiver(UdpImuReceiver&&)                         = delete;
  auto operator=(UdpImuReceiver&&) -> UdpImuReceiver&      = delete;

  void start();
  void stop();
  void restart();

  [[nodiscard]] auto isRunning() const -> bool;

private:
  using LoopT = ReceiverLoop<DatagramDecoder<imu_legacy::Parser>>;

  UdpImuReceiverConfig m_config;
  std::unique_ptr<LoopT> m_loop;
};

} // namespace sick::compact
