/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_3_ambient_light/AmbientLightData.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_3_ambient_light/AmbientLightParser.hpp>
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

class SDK_EXPORT AmbientLightReceiverConfig
{
public:
  using DataCallback = std::function<void(compact::ambient_light::AmbientLightData const&)>;

  static constexpr std::uint16_t kDefaultPort = 2116;

  static auto create(std::uint16_t sensorPort = kDefaultPort) -> AmbientLightReceiverConfig;

  auto setSensorPort(std::uint16_t sensorPort) -> AmbientLightReceiverConfig&;
  auto setOnNewDataCallback(DataCallback callback) -> AmbientLightReceiverConfig&;
  auto setTimeouts(std::chrono::milliseconds firstDataTimeout, std::chrono::milliseconds newDataTimeout) -> AmbientLightReceiverConfig&;
  auto setReceiveBufferSize(std::size_t receiveBufferSize) -> AmbientLightReceiverConfig&;
  //! \brief Defaults to rethrowing the exception. Set an empty-bodied callback to silence errors instead.
  auto setOnError(compact::ErrorCallback onError) -> AmbientLightReceiverConfig&;
  auto setLoggerName(std::string loggerName) -> AmbientLightReceiverConfig&;

  [[nodiscard]] auto transport() const -> compact::ReceiverTransport const&;
  [[nodiscard]] auto dataCallback() const -> DataCallback const&;
  [[nodiscard]] auto onError() const -> compact::ErrorCallback const&;
  [[nodiscard]] auto loggerName() const -> std::string const&;

private:
  AmbientLightReceiverConfig() = default;

  compact::ReceiverTransport m_transport {
    kDefaultPort,
    compact::receiver_defaults::kFirstDataTimeout,
    compact::receiver_defaults::kNewDataTimeout,
    compact::receiver_defaults::kTcpReceiveBufferSize
  };
  DataCallback m_dataCallback;
  compact::ErrorCallback m_onError = compact::receiver_defaults::kDefaultErrorCallback;
  std::string m_loggerName         = "AmbientLightReceiver";
};

//! \brief Receives Compact ambient light telegrams over a TCP connection to the sensor.
class SDK_EXPORT AmbientLightReceiver
{
public:
  AmbientLightReceiver(IpV4Address sensorAddress, AmbientLightReceiverConfig config);

  ~AmbientLightReceiver();

  AmbientLightReceiver(AmbientLightReceiver const&)                    = delete;
  auto operator=(AmbientLightReceiver const&) -> AmbientLightReceiver& = delete;
  AmbientLightReceiver(AmbientLightReceiver&&)                         = delete;
  auto operator=(AmbientLightReceiver&&) -> AmbientLightReceiver&      = delete;

  void start();
  void stop();
  void restart();

  [[nodiscard]] auto isRunning() const -> bool;

private:
  using LoopT = compact::ReceiverLoop<compact::TelegramStreamDecoder<compact::ambient_light::Parser>>;

  IpV4Address m_sensorAddress;
  AmbientLightReceiverConfig m_config;
  std::unique_ptr<LoopT> m_loop;
};

} // namespace sick::multiScan200
