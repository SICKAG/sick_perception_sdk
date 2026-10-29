/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/drivers/multiScan200/AmbientLightReceiver.hpp>

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/logging/logging.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_3_ambient_light/AmbientLightParser.hpp>
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

auto AmbientLightReceiverConfig::create(std::uint16_t sensorPort) -> AmbientLightReceiverConfig
{
  AmbientLightReceiverConfig config;
  config.m_transport.port = sensorPort;
  return config;
}

auto AmbientLightReceiverConfig::setSensorPort(std::uint16_t sensorPort) -> AmbientLightReceiverConfig&
{
  m_transport.port = sensorPort;
  return *this;
}

auto AmbientLightReceiverConfig::setOnNewDataCallback(DataCallback callback) -> AmbientLightReceiverConfig&
{
  m_dataCallback = std::move(callback);
  return *this;
}

auto AmbientLightReceiverConfig::setTimeouts(std::chrono::milliseconds firstDataTimeout, std::chrono::milliseconds newDataTimeout)
  -> AmbientLightReceiverConfig&
{
  m_transport.firstDataTimeout = firstDataTimeout;
  m_transport.newDataTimeout   = newDataTimeout;
  return *this;
}

auto AmbientLightReceiverConfig::setReceiveBufferSize(std::size_t receiveBufferSize) -> AmbientLightReceiverConfig&
{
  m_transport.receiveBufferSize = receiveBufferSize;
  return *this;
}

auto AmbientLightReceiverConfig::setOnError(compact::ErrorCallback onError) -> AmbientLightReceiverConfig&
{
  m_onError = std::move(onError);
  return *this;
}

auto AmbientLightReceiverConfig::setLoggerName(std::string loggerName) -> AmbientLightReceiverConfig&
{
  m_loggerName = std::move(loggerName);
  return *this;
}

auto AmbientLightReceiverConfig::transport() const -> compact::ReceiverTransport const&
{
  return m_transport;
}

auto AmbientLightReceiverConfig::dataCallback() const -> DataCallback const&
{
  return m_dataCallback;
}

auto AmbientLightReceiverConfig::onError() const -> compact::ErrorCallback const&
{
  return m_onError;
}

auto AmbientLightReceiverConfig::loggerName() const -> std::string const&
{
  return m_loggerName;
}

AmbientLightReceiver::AmbientLightReceiver(IpV4Address sensorAddress, AmbientLightReceiverConfig config)
  : m_sensorAddress(sensorAddress)
  , m_config(std::move(config))
{ }

AmbientLightReceiver::~AmbientLightReceiver()
{
  stop();
}

void AmbientLightReceiver::start()
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
    compact::TelegramStreamDecoder<compact::ambient_light::Parser>(m_config.dataCallback(), streamName),
    m_config.onError(),
    transport.firstDataTimeout,
    transport.newDataTimeout,
    std::move(streamName)
  );
  m_loop->start();
}

void AmbientLightReceiver::stop()
{
  m_loop = nullptr;
}

void AmbientLightReceiver::restart()
{
  stop();
  start();
}

auto AmbientLightReceiver::isRunning() const -> bool
{
  return m_loop != nullptr;
}

} // namespace sick::multiScan200
