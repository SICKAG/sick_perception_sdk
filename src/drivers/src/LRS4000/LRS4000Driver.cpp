/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/drivers/LRS4000/LRS4000Driver.hpp>

#include <sick_perception_sdk/compact_format/PointCloud/PointCloudConfiguration.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/DataLossMonitor.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/PointCloudConverter.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanData.hpp>

#include <exception>
#include <functional>
#include <utility>

namespace sick::LRS4000 {

Driver::Driver(IpV4Address deviceAddress, std::function<void(std::exception_ptr)> const& onError)
  : m_scanDataReceiver(deviceAddress, onError, "ScanDataReceiver")
{ }

Driver::~Driver()
{
  stop();
}

void Driver::run()
{
  m_scanDataReceiver.start();
}

void Driver::stop()
{
  m_scanDataReceiver.stop();
}

// --------------------------------------------------------------
// ScanDataReceiver
// --------------------------------------------------------------
Driver::ScanDataReceiver::ScanDataReceiver(IpV4Address deviceAddress, BaseT::ErrorCallback onError, std::string loggerName)
  : BaseT(onError, loggerName)
  , m_deviceAddress(std::move(deviceAddress))
{ }

auto Driver::ScanDataReceiver::setup(
  std::uint16_t sensorPort,
  std::chrono::milliseconds firstDataTimeout,
  std::chrono::milliseconds newDataTimeout,
  std::size_t receiveBufferSize
) -> ScanDataReceiver&
{
  BaseT::setup(
    [this](compact::scan_data::ScanData const& data) {
      this->multiplexScanData(data);
    },
    m_deviceAddress,
    sensorPort,
    firstDataTimeout,
    newDataTimeout,
    receiveBufferSize
  );

  return *this;
}

void Driver::ScanDataReceiver::multiplexScanData(compact::scan_data::ScanData const& scanData)
{
  if (m_dataLoss)
  {
    try
    {
      auto& [monitor, callback] = *m_dataLoss;
      auto const lossCounts     = monitor.check(scanData);
      if ((lossCounts.numberOfLostFrames != 0) || (lossCounts.numberOfLostTelegrams != 0) || (lossCounts.numberOfLostSegments != 0))
      {
        callback(lossCounts);
      }
    }
    catch (std::exception_ptr exception)
    {
      m_onError(exception);
    }
  }
  if (m_onNewData)
  {
    (*m_onNewData)(scanData);
  }
  if (m_pointCloud)
  {
    auto& [converter, callback] = *m_pointCloud;
    callback(converter.convert(scanData));
  }
}

auto Driver::ScanDataReceiver::setDataLossMonitor(compact::scan_data::DataLossMonitor monitor, DataLossCallback callback) -> ScanDataReceiver&
{
  m_dataLoss = std::make_pair(std::move(monitor), std::move(callback));
  return *this;
}

auto Driver::ScanDataReceiver::setOnNewFrameCallback(ScanDataCallback callback) -> ScanDataReceiver&
{
  m_onNewData = std::move(callback);
  return *this;
}

auto Driver::ScanDataReceiver::setOnNewFrameCallback(
  UnorganizedPointCloudCallback callback,
  point_cloud::PointCloudConfiguration const& pointCloudConfiguration
) -> ScanDataReceiver&
{
  m_pointCloud = std::make_pair(compact::scan_data::PointCloudConverter(pointCloudConfiguration), std::move(callback));
  return *this;
}

} // namespace sick::LRS4000
