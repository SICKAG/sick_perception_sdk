/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/drivers/multiScan200/ImuReceiver.hpp>

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/logging/logging.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_7_imu/ImuParser.hpp>
#include <sick_perception_sdk/drivers/Receiver/ReceiverDefaults.hpp>
#include <sick_perception_sdk/drivers/Receiver/ReceiverSockets.hpp>
#include <sick_perception_sdk/drivers/Receiver/TelegramStreamDecoder.hpp>

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <utility>

namespace sick::multiScan200 {

auto ImuReceiverConfig::create(std::uint16_t sensorPort) -> ImuReceiverConfig
{
  ImuReceiverConfig config;
  config.m_transport.port = sensorPort;
  return config;
}

auto ImuReceiverConfig::setSensorPort(std::uint16_t sensorPort) -> ImuReceiverConfig&
{
  m_transport.port = sensorPort;
  return *this;
}

auto ImuReceiverConfig::setOnNewDataCallback(DataCallback callback) -> ImuReceiverConfig&
{
  m_dataCallback = std::move(callback);
  return *this;
}

auto ImuReceiverConfig::setTimeouts(std::chrono::milliseconds firstDataTimeout, std::chrono::milliseconds newDataTimeout) -> ImuReceiverConfig&
{
  m_transport.firstDataTimeout = firstDataTimeout;
  m_transport.newDataTimeout   = newDataTimeout;
  return *this;
}

auto ImuReceiverConfig::setReceiveBufferSize(std::size_t receiveBufferSize) -> ImuReceiverConfig&
{
  m_transport.receiveBufferSize = receiveBufferSize;
  return *this;
}

auto ImuReceiverConfig::setOnError(compact::ErrorCallback onError) -> ImuReceiverConfig&
{
  m_onError = std::move(onError);
  return *this;
}

auto ImuReceiverConfig::setLoggerName(std::string loggerName) -> ImuReceiverConfig&
{
  m_loggerName = std::move(loggerName);
  return *this;
}

auto ImuReceiverConfig::transport() const -> compact::ReceiverTransport const&
{
  return m_transport;
}

auto ImuReceiverConfig::dataCallback() const -> DataCallback const&
{
  return m_dataCallback;
}

auto ImuReceiverConfig::onError() const -> compact::ErrorCallback const&
{
  return m_onError;
}

auto ImuReceiverConfig::loggerName() const -> std::string const&
{
  return m_loggerName;
}

ImuReceiver::ImuReceiver(IpV4Address sensorAddress, ImuReceiverConfig config)
  : m_sensorAddress(sensorAddress)
  , m_config(std::move(config))
{ }

ImuReceiver::~ImuReceiver()
{
  stop();
}

void ImuReceiver::start()
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
    compact::TelegramStreamDecoder<compact::imu::Parser>(m_config.dataCallback(), streamName),
    m_config.onError(),
    transport.firstDataTimeout,
    transport.newDataTimeout,
    std::move(streamName)
  );
  m_loop->start();
}

void ImuReceiver::stop()
{
  m_loop = nullptr;
}

void ImuReceiver::restart()
{
  stop();
  start();
}

auto ImuReceiver::isRunning() const -> bool
{
  return m_loop != nullptr;
}

} // namespace sick::multiScan200
