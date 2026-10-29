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
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/PointCloudCollector.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/PointCloudConverter.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanData.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanDataParser.hpp>
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
#include <utility>

namespace sick::compact {

class SDK_EXPORT UdpScanDataReceiverConfig
{
public:
  using ScanDataCallback              = std::function<void(compact::scan_data::ScanData const&)>;
  using DataLossCallback              = std::function<void(compact::LossCounts const&)>;
  using UnorganizedPointCloudCallback = std::function<void(point_cloud::UnorganizedPointCloud const&)>;

  static constexpr std::uint16_t kDefaultPort = 2115;

  static auto create(std::uint16_t receiverPort = kDefaultPort) -> UdpScanDataReceiverConfig;

  auto setReceiverPort(std::uint16_t receiverPort) -> UdpScanDataReceiverConfig&;

  //! \brief Receive every segment as the parsed telegram.
  auto setOnNewSegmentCallback(ScanDataCallback callback) -> UdpScanDataReceiverConfig&;
  //! \brief Receive every segment as a point cloud.
  auto setOnNewSegmentCallback(
    UnorganizedPointCloudCallback callback,
    point_cloud::PointCloudConfiguration const& pointCloudConfiguration = point_cloud::PointCloudConfiguration()
  ) -> UdpScanDataReceiverConfig&;
  //! \brief Receive a point cloud assembled from all segments of a frame.
  auto setOnNewFrameCallback(
    UnorganizedPointCloudCallback callback,
    point_cloud::PointCloudConfiguration const& pointCloudConfiguration = point_cloud::PointCloudConfiguration()
  ) -> UdpScanDataReceiverConfig&;
  auto setDataLossMonitor(compact::scan_data::DataLossMonitor monitor, DataLossCallback callback) -> UdpScanDataReceiverConfig&;

  auto setMulticast(IpV4Address const& groupAddress, IpV4Address const& localInterfaceAddress) -> UdpScanDataReceiverConfig&;
  auto setTimeouts(std::chrono::milliseconds firstDataTimeout, std::chrono::milliseconds newDataTimeout) -> UdpScanDataReceiverConfig&;
  auto setReceiveBufferSize(std::size_t receiveBufferSize) -> UdpScanDataReceiverConfig&;
  //! \brief Defaults to rethrowing the exception. Set an empty-bodied callback to silence errors instead.
  auto setOnError(ErrorCallback onError) -> UdpScanDataReceiverConfig&;
  auto setLoggerName(std::string loggerName) -> UdpScanDataReceiverConfig&;

  //! The callbacks a running receiver fans data out to.
  struct Callbacks
  {
    std::optional<std::pair<compact::scan_data::DataLossMonitor, DataLossCallback>> dataLoss;
    std::optional<ScanDataCallback> onNewSegment;
    std::optional<std::pair<compact::scan_data::PointCloudCollector, UnorganizedPointCloudCallback>> framePointCloud;
    std::optional<std::pair<compact::scan_data::PointCloudConverter, UnorganizedPointCloudCallback>> segmentPointCloud;
  };

  [[nodiscard]] auto transport() const -> ReceiverTransport const&;
  [[nodiscard]] auto multicast() const -> std::optional<MulticastGroup> const&;
  [[nodiscard]] auto callbacks() const -> Callbacks const&;
  [[nodiscard]] auto onError() const -> ErrorCallback const&;
  [[nodiscard]] auto loggerName() const -> std::string const&;

private:
  UdpScanDataReceiverConfig() = default;

  ReceiverTransport
    m_transport {kDefaultPort, receiver_defaults::kFirstDataTimeout, receiver_defaults::kNewDataTimeout, receiver_defaults::kUdpReceiveBufferSize};
  std::optional<MulticastGroup> m_multicast;
  Callbacks m_callbacks;
  ErrorCallback m_onError  = receiver_defaults::kDefaultErrorCallback;
  std::string m_loggerName = "ScanDataReceiver";
};

//! \brief Receives Compact scan data telegrams from a UDP port.
class SDK_EXPORT UdpScanDataReceiver
{
public:
  explicit UdpScanDataReceiver(UdpScanDataReceiverConfig config);

  ~UdpScanDataReceiver();

  UdpScanDataReceiver(UdpScanDataReceiver const&)                    = delete;
  auto operator=(UdpScanDataReceiver const&) -> UdpScanDataReceiver& = delete;
  UdpScanDataReceiver(UdpScanDataReceiver&&)                         = delete;
  auto operator=(UdpScanDataReceiver&&) -> UdpScanDataReceiver&      = delete;

  void start();
  void stop();
  void restart();

  [[nodiscard]] auto isRunning() const -> bool;

private:
  //! Fans one stream's scan data out to the configured callbacks.
  class Dispatcher
  {
  public:
    Dispatcher(UdpScanDataReceiverConfig::Callbacks callbacks, ErrorCallback onError, std::string loggerName);

    void operator()(compact::scan_data::ScanData const& scanData);

  private:
    UdpScanDataReceiverConfig::Callbacks m_callbacks;
    ErrorCallback m_onError;
    std::string m_loggerName;
    std::optional<std::uint64_t> m_lastFrameSequenceNumber;
    bool m_firstFrameChangeDetected = false;
  };

  using LoopT = ReceiverLoop<DatagramDecoder<scan_data::Parser>>;

  UdpScanDataReceiverConfig m_config;
  std::unique_ptr<LoopT> m_loop;
};

} // namespace sick::compact
