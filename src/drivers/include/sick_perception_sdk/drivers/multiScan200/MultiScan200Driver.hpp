/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/logging/LogLevel.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/OrganizedPointCloud.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudConfiguration.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloud.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_2_imu_legacy/ImuData.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_3_ambient_light/AmbientLightData.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_3_ambient_light/AmbientLightParser.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_6_multiScan200/DataLossMonitor.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_6_multiScan200/MultiScan200Data.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_6_multiScan200/MultiScan200Parser.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_6_multiScan200/PointCloudConverter.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_7_imu/ImuParser.hpp>
#include <sick_perception_sdk/drivers/Receiver/TcpStreamReceiver.hpp>

#include <chrono>
#include <cstdint>
#include <functional>
#include <optional>
#include <string>
#include <utility>

namespace sick::multiScan200 {

/**
 * @ingroup Drivers
 * 
 * See drivers.hpp for an overview.
 */
class SDK_EXPORT Driver
{
public:
  class SDK_EXPORT AmbientLightReceiver : public compact::TcpStreamReceiver<compact::ambient_light::Parser>
  {
    using BaseT = compact::TcpStreamReceiver<compact::ambient_light::Parser>;

  public:
    explicit AmbientLightReceiver(IpV4Address sensorAddress, BaseT::ErrorCallback onError, std::string loggerName);

    static constexpr std::uint16_t kDefaultPort = 2116;

    auto setup(
      std::uint16_t sensorPort                   = kDefaultPort,
      std::chrono::milliseconds firstDataTimeout = kDefaultFirstDataTimeout,
      std::chrono::milliseconds newDataTimeout   = kDefaultNewDataTimeout,
      std::size_t receiveBufferSize              = kDefaultReceiveBufferSize
    ) -> AmbientLightReceiver&;

    auto setOnNewDataCallback(DataCallback callback) -> AmbientLightReceiver&;

  private:
    IpV4Address m_sensorAddress;
    std::optional<DataCallback> m_callback;
  };

  class SDK_EXPORT ImuReceiver : public compact::TcpStreamReceiver<compact::imu::Parser>
  {
    using BaseT = compact::TcpStreamReceiver<compact::imu::Parser>;

  public:
    ImuReceiver(IpV4Address sensorAddress, BaseT::ErrorCallback onError, std::string loggerName);

    static constexpr std::uint16_t kDefaultPort = 2117;

    auto setup(
      std::uint16_t sensorPort                   = kDefaultPort,
      std::chrono::milliseconds firstDataTimeout = kDefaultFirstDataTimeout,
      std::chrono::milliseconds newDataTimeout   = kDefaultNewDataTimeout,
      std::size_t receiveBufferSize              = kDefaultReceiveBufferSize
    ) -> ImuReceiver&;

    auto setOnNewDataCallback(DataCallback callback) -> ImuReceiver&;

  private:
    IpV4Address m_sensorAddress;
    std::optional<DataCallback> m_callback;
  };

  class SDK_EXPORT ScanDataReceiver : public compact::TcpStreamReceiver<compact::multiscan200::Parser>
  {
    using BaseT = compact::TcpStreamReceiver<compact::multiscan200::Parser>;

  public:
    ScanDataReceiver(IpV4Address sensorAddress, BaseT::ErrorCallback onError, std::string loggerName);

    static constexpr std::uint16_t kDefaultPort = 2115;
    using DataLossCallback                      = std::function<void(compact::LossCounts const&)>;
    using OrganizedPointCloudCallback           = std::function<void(point_cloud::OrganizedPointCloud const&)>;
    using UnorganizedPointCloudCallback         = std::function<void(point_cloud::UnorganizedPointCloud const&)>;
    using ScanDataCallback                      = std::function<void(compact::multiscan200::MultiScan200Data const&)>;

    auto setup(
      std::uint16_t sensorPort                   = kDefaultPort,
      std::chrono::milliseconds firstDataTimeout = kDefaultFirstDataTimeout,
      std::chrono::milliseconds newDataTimeout   = kDefaultNewDataTimeout,
      std::size_t receiveBufferSize              = kDefaultReceiveBufferSize
    ) -> ScanDataReceiver&;

    auto setDataLossMonitor(compact::multiscan200::DataLossMonitor monitor, DataLossCallback callback) -> ScanDataReceiver&;
    auto setOnNewFrameCallback(ScanDataCallback callback) -> ScanDataReceiver&;
    auto setOnNewFrameCallback(
      OrganizedPointCloudCallback callback,
      point_cloud::PointCloudConfiguration const& pointCloudConfiguration = point_cloud::PointCloudConfiguration()
    ) -> ScanDataReceiver&;
    auto setOnNewFrameCallback(
      UnorganizedPointCloudCallback callback,
      point_cloud::PointCloudConfiguration const& pointCloudConfiguration = point_cloud::PointCloudConfiguration()
    ) -> ScanDataReceiver&;

  private:
    IpV4Address m_sensorAddress;

    std::optional<std::pair<compact::multiscan200::DataLossMonitor, DataLossCallback>> m_dataLoss;
    std::optional<ScanDataCallback> m_onNewData;
    std::optional<std::pair<compact::multiscan200::PointCloudConverter, OrganizedPointCloudCallback>> m_organizedPointCloud;
    std::optional<std::pair<compact::multiscan200::PointCloudConverter, UnorganizedPointCloudCallback>> m_unorganizedPointCloud;

    void multiplexScanData(compact::multiscan200::MultiScan200Data const& data);
  };

  /**
   * @param sensorAddress The IP address of the MultiScan200 device to connect to
   * @param onError Callback function that is called when an unhandled exception is thrown
   */
  explicit Driver(IpV4Address sensorAddress, std::function<void(std::exception_ptr const&)> const& onError = [](auto) -> void { });

  Driver(Driver const&)                    = delete;
  auto operator=(Driver const&) -> Driver& = delete;
  Driver(Driver&&)                         = delete;
  auto operator=(Driver&&) -> Driver&      = delete;

  ~Driver();

  auto ambientLightReceiver() -> AmbientLightReceiver&
  {
    return m_ambientLightReceiver;
  }

  auto imuReceiver() -> ImuReceiver&
  {
    return m_imuReceiver;
  }

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
  AmbientLightReceiver m_ambientLightReceiver;
  ImuReceiver m_imuReceiver;
  ScanDataReceiver m_scanDataReceiver;
};

} // namespace sick::multiScan200
