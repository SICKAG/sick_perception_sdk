/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_2_imu_legacy/ImuData.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_7_imu/ImuParser.hpp>
#include <sick_perception_sdk/drivers/Receiver/ReceiverDefaults.hpp>
#include <sick_perception_sdk/drivers/Receiver/ReceiverLoop.hpp>
#include <sick_perception_sdk/drivers/Receiver/ReceiverSockets.hpp>
#include <sick_perception_sdk/drivers/Receiver/TelegramStreamDecoder.hpp>

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <string>

namespace sick::multiScan200 {

class SDK_EXPORT ImuReceiverConfig
{
public:
  using DataCallback = std::function<void(compact::imu::ImuData const&)>;

  static constexpr std::uint16_t kDefaultPort = 2117;

  static auto create(std::uint16_t sensorPort = kDefaultPort) -> ImuReceiverConfig;

  auto setSensorPort(std::uint16_t sensorPort) -> ImuReceiverConfig&;
  auto setOnNewDataCallback(DataCallback callback) -> ImuReceiverConfig&;
  auto setTimeouts(std::chrono::milliseconds firstDataTimeout, std::chrono::milliseconds newDataTimeout) -> ImuReceiverConfig&;
  auto setReceiveBufferSize(std::size_t receiveBufferSize) -> ImuReceiverConfig&;
  //! \brief Defaults to rethrowing the exception. Set an empty-bodied callback to silence errors instead.
  auto setOnError(compact::ErrorCallback onError) -> ImuReceiverConfig&;
  auto setLoggerName(std::string loggerName) -> ImuReceiverConfig&;

  [[nodiscard]] auto transport() const -> compact::ReceiverTransport const&;
  [[nodiscard]] auto dataCallback() const -> DataCallback const&;
  [[nodiscard]] auto onError() const -> compact::ErrorCallback const&;
  [[nodiscard]] auto loggerName() const -> std::string const&;

private:
  ImuReceiverConfig() = default;

  compact::ReceiverTransport m_transport {
    kDefaultPort,
    compact::receiver_defaults::kFirstDataTimeout,
    compact::receiver_defaults::kNewDataTimeout,
    compact::receiver_defaults::kTcpReceiveBufferSize
  };
  DataCallback m_dataCallback;
  compact::ErrorCallback m_onError = compact::receiver_defaults::kDefaultErrorCallback;
  std::string m_loggerName         = "ImuReceiver";
};

//! \brief Receives Compact IMU telegrams over a TCP connection to the sensor.
class SDK_EXPORT ImuReceiver
{
public:
  ImuReceiver(IpV4Address sensorAddress, ImuReceiverConfig config);

  ~ImuReceiver();

  ImuReceiver(ImuReceiver const&)                    = delete;
  auto operator=(ImuReceiver const&) -> ImuReceiver& = delete;
  ImuReceiver(ImuReceiver&&)                         = delete;
  auto operator=(ImuReceiver&&) -> ImuReceiver&      = delete;

  void start();
  void stop();
  void restart();

  [[nodiscard]] auto isRunning() const -> bool;

private:
  using LoopT = compact::ReceiverLoop<compact::TelegramStreamDecoder<compact::imu::Parser>>;

  IpV4Address m_sensorAddress;
  ImuReceiverConfig m_config;
  std::unique_ptr<LoopT> m_loop;
};

} // namespace sick::multiScan200
