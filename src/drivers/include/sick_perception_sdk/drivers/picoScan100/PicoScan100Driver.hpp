/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/logging/LogLevel.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudConfiguration.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloud.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/DataLossMonitor.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/PointCloudCollector.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/PointCloudConverter.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanData.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanDataParser.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_4_encoder/EncoderData.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_4_encoder/EncoderParser.hpp>
#include <sick_perception_sdk/drivers/Receiver/UdpImuReceiver.hpp>
#include <sick_perception_sdk/drivers/Receiver/UdpScanDataReceiver.hpp>

#include <functional>
#include <optional>
#include <string>
#include <utility>

namespace sick::picoScan100 {

/**
 * @ingroup Drivers
 * 
 * See drivers.hpp for an overview.
 */
class SDK_EXPORT Driver
{
public:
  class SDK_EXPORT EncoderReceiver : public compact::UdpStreamReceiver<compact::encoder::Parser, EncoderReceiver>
  {
    using BaseT = compact::UdpStreamReceiver<compact::encoder::Parser, EncoderReceiver>;

  public:
    using BaseT::BaseT;

    static constexpr std::uint16_t kDefaultPort = 7504;

    auto setup(
      std::uint16_t receiverPort                 = kDefaultPort,
      std::chrono::milliseconds firstDataTimeout = kDefaultFirstDataTimeout,
      std::chrono::milliseconds newDataTimeout   = kDefaultNewDataTimeout,
      std::size_t receiveBufferSize              = kDefaultReceiveBufferSize
    ) -> EncoderReceiver&;

    auto setOnNewDataCallback(DataCallback callback) -> EncoderReceiver&;

  private:
    std::optional<DataCallback> m_callback;
  };

  using ImuReceiver      = compact::UdpImuReceiver;
  using ScanDataReceiver = compact::UdpScanDataReceiver;

  /** @param onError Callback function that is called when an unhandled exception is thrown */
  explicit Driver(std::function<void(std::exception_ptr)> const& onError = [](std::exception_ptr) -> void {});

  Driver(Driver const&)                    = delete;
  auto operator=(Driver const&) -> Driver& = delete;
  Driver(Driver&&)                         = delete;
  auto operator=(Driver&&) -> Driver&      = delete;

  ~Driver();

  auto encoderReceiver() -> EncoderReceiver&
  {
    return m_encoderReceiver;
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
   * @brief Listens for incoming data packets.
   *        Forwards the received packets to the onNewData callbacks.
   */
  void run();

  /**
   * @brief Stops receiving data. Call @ref run() to start receiving data again.
   */
  void stop();

private:
  EncoderReceiver m_encoderReceiver;
  ImuReceiver m_imuReceiver;
  ScanDataReceiver m_scanDataReceiver;
};

} // namespace sick::picoScan100
