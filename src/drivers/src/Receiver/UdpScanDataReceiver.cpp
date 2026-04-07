/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/drivers/Receiver/UdpScanDataReceiver.hpp>

namespace sick::compact {

UdpScanDataReceiver::UdpScanDataReceiver(typename BaseT::ErrorCallback onError, std::string loggerName)
  : BaseT(std::move(onError), std::move(loggerName))
{ }

auto UdpScanDataReceiver::setup(
  std::uint16_t receiverPort,
  std::chrono::milliseconds firstDataTimeout,
  std::chrono::milliseconds newDataTimeout,
  std::size_t receiveBufferSize
) -> UdpScanDataReceiver&
{
  BaseT::setup(
    [this](compact::scan_data::ScanData const& data) {
      this->multiplexScanData(data);
    },
    receiverPort,
    firstDataTimeout,
    newDataTimeout,
    receiveBufferSize
  );

  return *this;
}

void UdpScanDataReceiver::multiplexScanData(compact::scan_data::ScanData const& scanData)
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
  if (m_onNewSegmentScanData)
  {
    (*m_onNewSegmentScanData)(scanData);
  }
  if (m_segmentPointCloud)
  {
    auto& [converter, callback] = *m_segmentPointCloud;
    callback(converter.convert(scanData));
  }
  if (m_framePointCloud)
  {
    if (scanData.modules.empty())
    {
      LOG_WARNING("picoScan100") << "Received segment with no modules. Cannot deduce the frame sequence number.";
      return;
    }

    if (!m_lastFrameSequenceNumber)
    {
      m_lastFrameSequenceNumber = scanData.modules.front().metaData.frameSequenceNumber;
      return;
    }

    auto& collector = m_framePointCloud->first;  // No structured bindings because captured in lambda below.
    auto& callback  = m_framePointCloud->second; // No structured bindings because captured in lambda below.

    auto collectScanData = [&]() -> void {
      LOG_FAST_LOOP_INFO("picoScan100") << "Collecting segment with number " << scanData.modules.front().metaData.segmentIndex << " from frame "
                                        << scanData.modules.front().metaData.frameSequenceNumber << ".";
      collector.collect(scanData);
    };

    bool const frameChanged   = (*m_lastFrameSequenceNumber != scanData.modules.front().metaData.frameSequenceNumber);
    m_lastFrameSequenceNumber = scanData.modules.front().metaData.frameSequenceNumber;

    if (!m_firstFrameChangeDetected && frameChanged)
    {
      m_firstFrameChangeDetected = true;
      LOG_INFO("picoScan100") << "First frame change detected. Starting to collect segments.";
      collectScanData();
      return;
    }

    if (frameChanged)
    {
      LOG_FAST_LOOP_INFO("picoScan100") << "Frame changed. Calling the frame callback with the frame point cloud.";
      callback(collector.getPointCloud());
      collector.reset();
    }

    collectScanData();
  }
}

auto UdpScanDataReceiver::setDataLossMonitor(compact::scan_data::DataLossMonitor monitor, DataLossCallback callback) -> UdpScanDataReceiver&
{
  m_dataLoss = std::make_pair(std::move(monitor), std::move(callback));
  return *this;
}

auto UdpScanDataReceiver::setOnNewFrameCallback(UnorganizedPointCloudCallback callback, point_cloud::PointCloudConfiguration const& pointCloudConfiguration)
  -> UdpScanDataReceiver&
{
  m_framePointCloud = std::make_pair(compact::scan_data::PointCloudCollector(pointCloudConfiguration), std::move(callback));
  return *this;
}

auto UdpScanDataReceiver::setOnNewSegmentCallback(ScanDataCallback callback) -> UdpScanDataReceiver&
{
  m_onNewSegmentScanData = std::move(callback);
  return *this;
}

auto UdpScanDataReceiver::setOnNewSegmentCallback(UnorganizedPointCloudCallback callback, point_cloud::PointCloudConfiguration const& pointCloudConfiguration)
  -> UdpScanDataReceiver&
{
  m_segmentPointCloud = std::make_pair(compact::scan_data::PointCloudConverter(pointCloudConfiguration), std::move(callback));
  return *this;
}

} // namespace sick::compact
