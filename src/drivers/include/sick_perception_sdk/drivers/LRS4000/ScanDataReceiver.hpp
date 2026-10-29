/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudConfiguration.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloud.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/DataLossMonitor.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/PointCloudConverter.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanData.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanDataParser.hpp>
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
#include <utility>

namespace sick::LRS4000 {

class SDK_EXPORT ScanDataReceiverConfig
{
public:
  using ScanDataCallback              = std::function<void(compact::scan_data::ScanData const&)>;
  using DataLossCallback              = std::function<void(compact::LossCounts const&)>;
  using UnorganizedPointCloudCallback = std::function<void(point_cloud::UnorganizedPointCloud const&)>;

  static constexpr std::uint16_t kDefaultPort = 2115;

  static auto create(std::uint16_t sensorPort = kDefaultPort) -> ScanDataReceiverConfig;

  auto setSensorPort(std::uint16_t sensorPort) -> ScanDataReceiverConfig&;

  auto setOnNewFrameCallback(ScanDataCallback callback) -> ScanDataReceiverConfig&;
  auto setOnNewFrameCallback(
    UnorganizedPointCloudCallback callback,
    point_cloud::PointCloudConfiguration const& pointCloudConfiguration = point_cloud::PointCloudConfiguration()
  ) -> ScanDataReceiverConfig&;

  auto setDataLossMonitor(compact::scan_data::DataLossMonitor monitor, DataLossCallback callback) -> ScanDataReceiverConfig&;

  auto setTimeouts(std::chrono::milliseconds firstDataTimeout, std::chrono::milliseconds newDataTimeout) -> ScanDataReceiverConfig&;
  auto setReceiveBufferSize(std::size_t receiveBufferSize) -> ScanDataReceiverConfig&;

  auto setOnError(compact::ErrorCallback onError) -> ScanDataReceiverConfig&;
  auto setLoggerName(std::string loggerName) -> ScanDataReceiverConfig&;

  struct Callbacks
  {
    std::optional<std::pair<compact::scan_data::DataLossMonitor, DataLossCallback>> dataLoss;
    std::optional<ScanDataCallback> onNewData;
    std::optional<std::pair<compact::scan_data::PointCloudConverter, UnorganizedPointCloudCallback>> pointCloud;
  };

  [[nodiscard]] auto transport() const -> compact::ReceiverTransport const&;
  [[nodiscard]] auto callbacks() const -> Callbacks const&;
  [[nodiscard]] auto onError() const -> compact::ErrorCallback const&;
  [[nodiscard]] auto loggerName() const -> std::string const&;

private:
  ScanDataReceiverConfig() = default;

  compact::ReceiverTransport m_transport {
    kDefaultPort,
    compact::receiver_defaults::kFirstDataTimeout,
    compact::receiver_defaults::kNewDataTimeout,
    compact::receiver_defaults::kTcpReceiveBufferSize
  };
  Callbacks m_callbacks;
  compact::ErrorCallback m_onError = compact::receiver_defaults::kDefaultErrorCallback;
  std::string m_loggerName         = "ScanDataReceiver";
};

class SDK_EXPORT ScanDataReceiver
{
public:
  ScanDataReceiver(IpV4Address sensorAddress, ScanDataReceiverConfig config);

  ~ScanDataReceiver();

  ScanDataReceiver(ScanDataReceiver const&)                    = delete;
  auto operator=(ScanDataReceiver const&) -> ScanDataReceiver& = delete;
  ScanDataReceiver(ScanDataReceiver&&)                         = delete;
  auto operator=(ScanDataReceiver&&) -> ScanDataReceiver&      = delete;

  void start();
  void stop();
  void restart();

  [[nodiscard]] auto isRunning() const -> bool;

private:
  class Dispatcher
  {
  public:
    Dispatcher(ScanDataReceiverConfig::Callbacks callbacks, compact::ErrorCallback onError);

    void operator()(compact::scan_data::ScanData const& scanData);

  private:
    ScanDataReceiverConfig::Callbacks m_callbacks;
    compact::ErrorCallback m_onError;
  };

  using LoopT = compact::ReceiverLoop<compact::TelegramStreamDecoder<compact::scan_data::Parser>>;

  IpV4Address m_sensorAddress;
  ScanDataReceiverConfig m_config;
  std::unique_ptr<LoopT> m_loop;
};

} // namespace sick::LRS4000
