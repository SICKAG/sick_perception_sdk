/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/drivers/LRS4000/ScanDataReceiver.hpp>

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/logging/logging.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudConfiguration.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/DataLossMonitor.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/PointCloudConverter.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanData.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanDataParser.hpp>
#include <sick_perception_sdk/drivers/Receiver/ReceiverDefaults.hpp>
#include <sick_perception_sdk/drivers/Receiver/ReceiverSockets.hpp>
#include <sick_perception_sdk/drivers/Receiver/TelegramStreamDecoder.hpp>

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <memory>
#include <optional>
#include <string>
#include <utility>

namespace sick::LRS4000 {

auto ScanDataReceiverConfig::create(std::uint16_t sensorPort) -> ScanDataReceiverConfig
{
  ScanDataReceiverConfig config;
  config.m_transport.port = sensorPort;
  return config;
}

auto ScanDataReceiverConfig::setSensorPort(std::uint16_t sensorPort) -> ScanDataReceiverConfig&
{
  m_transport.port = sensorPort;
  return *this;
}

auto ScanDataReceiverConfig::setOnNewFrameCallback(ScanDataCallback callback) -> ScanDataReceiverConfig&
{
  m_callbacks.onNewData = std::move(callback);
  return *this;
}

auto ScanDataReceiverConfig::setOnNewFrameCallback(UnorganizedPointCloudCallback callback, point_cloud::PointCloudConfiguration const& pointCloudConfiguration)
  -> ScanDataReceiverConfig&
{
  m_callbacks.pointCloud = std::make_pair(compact::scan_data::PointCloudConverter(pointCloudConfiguration), std::move(callback));
  return *this;
}

auto ScanDataReceiverConfig::setDataLossMonitor(compact::scan_data::DataLossMonitor monitor, DataLossCallback callback) -> ScanDataReceiverConfig&
{
  m_callbacks.dataLoss = std::make_pair(std::move(monitor), std::move(callback));
  return *this;
}

auto ScanDataReceiverConfig::setTimeouts(std::chrono::milliseconds firstDataTimeout, std::chrono::milliseconds newDataTimeout) -> ScanDataReceiverConfig&
{
  m_transport.firstDataTimeout = firstDataTimeout;
  m_transport.newDataTimeout   = newDataTimeout;
  return *this;
}

auto ScanDataReceiverConfig::setReceiveBufferSize(std::size_t receiveBufferSize) -> ScanDataReceiverConfig&
{
  m_transport.receiveBufferSize = receiveBufferSize;
  return *this;
}

auto ScanDataReceiverConfig::setOnError(compact::ErrorCallback onError) -> ScanDataReceiverConfig&
{
  m_onError = std::move(onError);
  return *this;
}

auto ScanDataReceiverConfig::setLoggerName(std::string loggerName) -> ScanDataReceiverConfig&
{
  m_loggerName = std::move(loggerName);
  return *this;
}

auto ScanDataReceiverConfig::transport() const -> compact::ReceiverTransport const&
{
  return m_transport;
}

auto ScanDataReceiverConfig::callbacks() const -> Callbacks const&
{
  return m_callbacks;
}

auto ScanDataReceiverConfig::onError() const -> compact::ErrorCallback const&
{
  return m_onError;
}

auto ScanDataReceiverConfig::loggerName() const -> std::string const&
{
  return m_loggerName;
}

ScanDataReceiver::Dispatcher::Dispatcher(ScanDataReceiverConfig::Callbacks callbacks, compact::ErrorCallback onError)
  : m_callbacks(std::move(callbacks))
  , m_onError(std::move(onError))
{ }

void ScanDataReceiver::Dispatcher::operator()(compact::scan_data::ScanData const& scanData)
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
  if (m_callbacks.onNewData)
  {
    (*m_callbacks.onNewData)(scanData);
  }
  if (m_callbacks.pointCloud)
  {
    auto& [converter, callback] = *m_callbacks.pointCloud;
    callback(converter.convert(scanData));
  }
}

ScanDataReceiver::ScanDataReceiver(IpV4Address sensorAddress, ScanDataReceiverConfig config)
  : m_sensorAddress(sensorAddress)
  , m_config(std::move(config))
{ }

ScanDataReceiver::~ScanDataReceiver()
{
  stop();
}

void ScanDataReceiver::start()
{
  if (m_loop)
  {
    LOG_WARNING(m_config.loggerName()) << "Start called, but is already started. Doing nothing.";
    return;
  }

  auto const& transport  = m_config.transport();
  std::string streamName = m_config.loggerName() + " " + m_sensorAddress.toString() + ":" + std::to_string(transport.port);

  m_loop = std::make_unique<LoopT>(
    compact::makeTcpSocket(m_sensorAddress, transport.port),
    transport.receiveBufferSize,
    compact::TelegramStreamDecoder<compact::scan_data::Parser>(Dispatcher(m_config.callbacks(), m_config.onError()), streamName),
    m_config.onError(),
    transport.firstDataTimeout,
    transport.newDataTimeout,
    std::move(streamName)
  );
  m_loop->start();
}

void ScanDataReceiver::stop()
{
  m_loop = nullptr;
}

void ScanDataReceiver::restart()
{
  stop();
  start();
}

auto ScanDataReceiver::isRunning() const -> bool
{
  return m_loop != nullptr;
}

} // namespace sick::LRS4000
