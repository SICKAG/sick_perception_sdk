/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudConfiguration.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloud.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/DataLossMonitor.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/PointCloudCollector.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/PointCloudConverter.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanData.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanDataParser.hpp>
#include <sick_perception_sdk/drivers/Receiver/UdpStreamReceiver.hpp>

#include <chrono>
#include <cstdint>
#include <functional>
#include <optional>
#include <string>
#include <utility>

namespace sick::compact {

class SDK_EXPORT UdpScanDataReceiver : public compact::UdpStreamReceiver<scan_data::Parser, UdpScanDataReceiver>
{
  using BaseT = compact::UdpStreamReceiver<scan_data::Parser, UdpScanDataReceiver>;

public:
  // Fixme: Rename to UdpScanDataReceiver
  explicit UdpScanDataReceiver(typename BaseT::ErrorCallback onError, std::string loggerName);

  static constexpr std::uint16_t kDefaultPort = 2115;
  using DataLossCallback                      = std::function<void(compact::scan_data::DataLossMonitor::LossCounts const&)>;
  using UnorganizedPointCloudCallback         = std::function<void(point_cloud::UnorganizedPointCloud const&)>;
  using ScanDataCallback                      = std::function<void(compact::scan_data::ScanData const&)>;

  auto setup(
    std::uint16_t receiverPort                 = kDefaultPort,
    std::chrono::milliseconds firstDataTimeout = BaseT::kDefaultFirstDataTimeout,
    std::chrono::milliseconds newDataTimeout   = BaseT::kDefaultNewDataTimeout,
    std::size_t receiveBufferSize              = kDefaultReceiveBufferSize
  ) -> UdpScanDataReceiver&;

  auto setDataLossMonitor(compact::scan_data::DataLossMonitor monitor, DataLossCallback callback) -> UdpScanDataReceiver&;
  auto setOnNewFrameCallback(
    UnorganizedPointCloudCallback callback,
    point_cloud::PointCloudConfiguration const& pointCloudConfiguration = point_cloud::PointCloudConfiguration()
  ) -> UdpScanDataReceiver&;
  auto setOnNewSegmentCallback(
    UnorganizedPointCloudCallback callback,
    point_cloud::PointCloudConfiguration const& pointCloudConfiguration = point_cloud::PointCloudConfiguration()
  ) -> UdpScanDataReceiver&;
  auto setOnNewSegmentCallback(ScanDataCallback callback) -> UdpScanDataReceiver&;

private:
  std::optional<std::pair<compact::scan_data::DataLossMonitor, DataLossCallback>> m_dataLoss;
  std::optional<ScanDataCallback> m_onNewSegmentScanData;
  std::optional<std::pair<compact::scan_data::PointCloudCollector, UnorganizedPointCloudCallback>> m_framePointCloud;
  std::optional<std::pair<compact::scan_data::PointCloudConverter, UnorganizedPointCloudCallback>> m_segmentPointCloud;
  std::optional<std::uint64_t> m_lastFrameSequenceNumber;
  bool m_firstFrameChangeDetected = false;

  void multiplexScanData(compact::scan_data::ScanData const& data);
};

} // namespace sick::compact
