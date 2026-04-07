/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/logging/LogLevel.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudConfiguration.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloud.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/DataLossMonitor.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/PointCloudConverter.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanData.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanDataParser.hpp>
#include <sick_perception_sdk/drivers/Receiver/TcpStreamReceiver.hpp>

#include <chrono>
#include <cstdint>
#include <functional>
#include <string>
#include <utility>

namespace sick::LRS4000 {

/**
 * @ingroup Drivers
 * 
 * See drivers.hpp for an overview.
 */
class SDK_EXPORT Driver
{
public:
  class SDK_EXPORT ScanDataReceiver : public compact::TcpStreamReceiver<compact::scan_data::Parser>
  {
    using BaseT = compact::TcpStreamReceiver<compact::scan_data::Parser>;

  public:
    explicit ScanDataReceiver(IpV4Address deviceAddress, BaseT::ErrorCallback onError, std::string loggerName);

    static constexpr std::uint16_t kDefaultPort = 2115;
    using DataLossCallback                      = std::function<void(compact::scan_data::DataLossMonitor::LossCounts const&)>;
    using UnorganizedPointCloudCallback         = std::function<void(point_cloud::UnorganizedPointCloud const&)>;
    using ScanDataCallback                      = std::function<void(compact::scan_data::ScanData const&)>;

    auto setup(
      std::uint16_t sensorPort                   = kDefaultPort,
      std::chrono::milliseconds firstDataTimeout = kDefaultFirstDataTimeout,
      std::chrono::milliseconds newDataTimeout   = kDefaultNewDataTimeout,
      std::size_t receiveBufferSize              = kDefaultReceiveBufferSize
    ) -> ScanDataReceiver&;

    auto setDataLossMonitor(compact::scan_data::DataLossMonitor monitor, DataLossCallback callback) -> ScanDataReceiver&;
    auto setOnNewFrameCallback(ScanDataCallback callback) -> ScanDataReceiver&;
    auto setOnNewFrameCallback(
      UnorganizedPointCloudCallback callback,
      point_cloud::PointCloudConfiguration const& pointCloudConfiguration = point_cloud::PointCloudConfiguration()
    ) -> ScanDataReceiver&;

  private:
    IpV4Address m_deviceAddress;

    std::optional<std::pair<compact::scan_data::DataLossMonitor, DataLossCallback>> m_dataLoss;
    std::optional<ScanDataCallback> m_onNewData;
    std::optional<std::pair<compact::scan_data::PointCloudConverter, UnorganizedPointCloudCallback>> m_pointCloud;

    void multiplexScanData(compact::scan_data::ScanData const& scanData);
  };

  /**
   * @param deviceAddress The IP address of the LRS4000 device to connect to
   * @param onError Callback function that is called when an unhandled exception is thrown
   */
  explicit Driver(IpV4Address deviceAddress, std::function<void(std::exception_ptr)> const& onError = [](std::exception_ptr) -> void {});

  Driver(Driver const&)                    = delete;
  auto operator=(Driver const&) -> Driver& = delete;
  Driver(Driver&&)                         = delete;
  auto operator=(Driver&&) -> Driver&      = delete;

  ~Driver();

  auto scanDataReceiver() -> ScanDataReceiver&
  {
    return m_scanDataReceiver;
  }

  /**
   * @brief Connects to the TCP server and listens for incoming data packets.
   *        Forwards the received packets to the onNewData callbacks.
   */
  void run();

  /**
   * @brief Stops receiving data. Call @ref run() to start receiving data again.
   */
  void stop();

private:
  ScanDataReceiver m_scanDataReceiver;
};

} // namespace sick::LRS4000
