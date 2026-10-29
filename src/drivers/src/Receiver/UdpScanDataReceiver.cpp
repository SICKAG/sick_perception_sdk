/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/drivers/Receiver/UdpScanDataReceiver.hpp>

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/logging/logging.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudConfiguration.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/DataLossMonitor.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/PointCloudCollector.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/PointCloudConverter.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanData.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanDataParser.hpp>
#include <sick_perception_sdk/drivers/Receiver/DatagramDecoder.hpp>
#include <sick_perception_sdk/drivers/Receiver/ReceiverDefaults.hpp>
#include <sick_perception_sdk/drivers/Receiver/ReceiverSockets.hpp>

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <memory>
#include <optional>
#include <string>
#include <utility>

namespace sick::compact {

auto UdpScanDataReceiverConfig::create(std::uint16_t receiverPort) -> UdpScanDataReceiverConfig
{
  UdpScanDataReceiverConfig config;
  config.m_transport.port = receiverPort;
  return config;
}

auto UdpScanDataReceiverConfig::setReceiverPort(std::uint16_t receiverPort) -> UdpScanDataReceiverConfig&
{
  m_transport.port = receiverPort;
  return *this;
}

auto UdpScanDataReceiverConfig::setOnNewSegmentCallback(ScanDataCallback callback) -> UdpScanDataReceiverConfig&
{
  m_callbacks.onNewSegment = std::move(callback);
  return *this;
}

auto UdpScanDataReceiverConfig::setOnNewSegmentCallback(
  UnorganizedPointCloudCallback callback,
  point_cloud::PointCloudConfiguration const& pointCloudConfiguration
) -> UdpScanDataReceiverConfig&
{
  m_callbacks.segmentPointCloud = std::make_pair(compact::scan_data::PointCloudConverter(pointCloudConfiguration), std::move(callback));
  return *this;
}

auto UdpScanDataReceiverConfig::setOnNewFrameCallback(
  UnorganizedPointCloudCallback callback,
  point_cloud::PointCloudConfiguration const& pointCloudConfiguration
) -> UdpScanDataReceiverConfig&
{
  m_callbacks.framePointCloud = std::make_pair(compact::scan_data::PointCloudCollector(pointCloudConfiguration), std::move(callback));
  return *this;
}

auto UdpScanDataReceiverConfig::setDataLossMonitor(compact::scan_data::DataLossMonitor monitor, DataLossCallback callback) -> UdpScanDataReceiverConfig&
{
  m_callbacks.dataLoss = std::make_pair(std::move(monitor), std::move(callback));
  return *this;
}

auto UdpScanDataReceiverConfig::setMulticast(IpV4Address const& groupAddress, IpV4Address const& localInterfaceAddress) -> UdpScanDataReceiverConfig&
{
  m_multicast = MulticastGroup {groupAddress, localInterfaceAddress};
  return *this;
}

auto UdpScanDataReceiverConfig::setTimeouts(std::chrono::milliseconds firstDataTimeout, std::chrono::milliseconds newDataTimeout) -> UdpScanDataReceiverConfig&
{
  m_transport.firstDataTimeout = firstDataTimeout;
  m_transport.newDataTimeout   = newDataTimeout;
  return *this;
}

auto UdpScanDataReceiverConfig::setReceiveBufferSize(std::size_t receiveBufferSize) -> UdpScanDataReceiverConfig&
{
  m_transport.receiveBufferSize = receiveBufferSize;
  return *this;
}

auto UdpScanDataReceiverConfig::setOnError(ErrorCallback onError) -> UdpScanDataReceiverConfig&
{
  m_onError = std::move(onError);
  return *this;
}

auto UdpScanDataReceiverConfig::setLoggerName(std::string loggerName) -> UdpScanDataReceiverConfig&
{
  m_loggerName = std::move(loggerName);
  return *this;
}

auto UdpScanDataReceiverConfig::transport() const -> ReceiverTransport const&
{
  return m_transport;
}

auto UdpScanDataReceiverConfig::multicast() const -> std::optional<MulticastGroup> const&
{
  return m_multicast;
}

auto UdpScanDataReceiverConfig::callbacks() const -> Callbacks const&
{
  return m_callbacks;
}

auto UdpScanDataReceiverConfig::onError() const -> ErrorCallback const&
{
  return m_onError;
}

auto UdpScanDataReceiverConfig::loggerName() const -> std::string const&
{
  return m_loggerName;
}

UdpScanDataReceiver::Dispatcher::Dispatcher(UdpScanDataReceiverConfig::Callbacks callbacks, ErrorCallback onError, std::string loggerName)
  : m_callbacks(std::move(callbacks))
  , m_onError(std::move(onError))
  , m_loggerName(std::move(loggerName))
{ }

void UdpScanDataReceiver::Dispatcher::operator()(compact::scan_data::ScanData const& scanData)
{
  if (m_callbacks.dataLoss)
  {
    try
    {
      auto& [monitor, callback] = *m_callbacks.dataLoss;
      auto const lossCounts     = monitor.check(scanData);
      if ((lossCounts.numberOfLostFrames != 0) || (lossCounts.numberOfLostTelegrams != 0) || (lossCounts.numberOfLostSegments != 0))
      {
        callback(lossCounts);
      }
    }
    catch (std::exception_ptr const& exception)
    {
      m_onError(exception);
    }
  }
  if (m_callbacks.onNewSegment)
  {
    (*m_callbacks.onNewSegment)(scanData);
  }
  if (m_callbacks.segmentPointCloud)
  {
    auto& [converter, callback] = *m_callbacks.segmentPointCloud;
    callback(converter.convert(scanData));
  }
  if (m_callbacks.framePointCloud)
  {
    if (!m_lastFrameSequenceNumber)
    {
      m_lastFrameSequenceNumber = scanData.frameSequenceNumber;
      return;
    }

    auto& collector = m_callbacks.framePointCloud->first;  // No structured bindings because captured in lambda below.
    auto& callback  = m_callbacks.framePointCloud->second; // No structured bindings because captured in lambda below.

    auto collectScanData = [&]() -> void {
      LOG_FAST_LOOP_INFO(m_loggerName) << "Collecting segment with number " << scanData.segmentIndex << " from frame " << scanData.frameSequenceNumber << ".";
      collector.collect(scanData);
    };

    bool const frameChanged   = (*m_lastFrameSequenceNumber != scanData.frameSequenceNumber);
    m_lastFrameSequenceNumber = scanData.frameSequenceNumber;

    if (!m_firstFrameChangeDetected && frameChanged)
    {
      m_firstFrameChangeDetected = true;
      LOG_INFO(m_loggerName) << "First frame change detected. Starting to collect segments.";
      collectScanData();
      return;
    }

    if (frameChanged)
    {
      LOG_FAST_LOOP_INFO(m_loggerName) << "Frame changed. Calling the frame callback with the frame point cloud.";
      callback(collector.getPointCloud());
      collector.reset();
    }

    collectScanData();
  }
}

UdpScanDataReceiver::UdpScanDataReceiver(UdpScanDataReceiverConfig config)
  : m_config(std::move(config))
{ }

UdpScanDataReceiver::~UdpScanDataReceiver()
{
  stop();
}

void UdpScanDataReceiver::start()
{
  if (m_loop)
  {
    LOG_WARNING(m_config.loggerName()) << "Start called, but is already started. Doing nothing.";
    return;
  }

  auto const& transport = m_config.transport();
  m_loop                = std::make_unique<LoopT>(
    makeUdpSocket(transport.port, m_config.multicast()),
    transport.receiveBufferSize,
    DatagramDecoder<scan_data::Parser>(Dispatcher(m_config.callbacks(), m_config.onError(), m_config.loggerName())),
    m_config.onError(),
    transport.firstDataTimeout,
    transport.newDataTimeout,
    m_config.loggerName() + " on port " + std::to_string(transport.port)
  );
  m_loop->start();
}

void UdpScanDataReceiver::stop()
{
  m_loop = nullptr;
}

void UdpScanDataReceiver::restart()
{
  stop();
  start();
}

auto UdpScanDataReceiver::isRunning() const -> bool
{
  return m_loop != nullptr;
}

} // namespace sick::compact
