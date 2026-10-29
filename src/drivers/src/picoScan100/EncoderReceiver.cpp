/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/drivers/picoScan100/EncoderReceiver.hpp>

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/logging/logging.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_4_encoder/EncoderParser.hpp>
#include <sick_perception_sdk/drivers/Receiver/DatagramDecoder.hpp>
#include <sick_perception_sdk/drivers/Receiver/ReceiverDefaults.hpp>
#include <sick_perception_sdk/drivers/Receiver/ReceiverSockets.hpp>

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <utility>

namespace sick::picoScan100 {

auto EncoderReceiverConfig::create(std::uint16_t receiverPort) -> EncoderReceiverConfig
{
  EncoderReceiverConfig config;
  config.m_transport.port = receiverPort;
  return config;
}

auto EncoderReceiverConfig::setReceiverPort(std::uint16_t receiverPort) -> EncoderReceiverConfig&
{
  m_transport.port = receiverPort;
  return *this;
}

auto EncoderReceiverConfig::setOnNewDataCallback(DataCallback callback) -> EncoderReceiverConfig&
{
  m_dataCallback = std::move(callback);
  return *this;
}

auto EncoderReceiverConfig::setMulticast(IpV4Address const& groupAddress, IpV4Address const& localInterfaceAddress) -> EncoderReceiverConfig&
{
  m_multicast = compact::MulticastGroup {groupAddress, localInterfaceAddress};
  return *this;
}

auto EncoderReceiverConfig::setTimeouts(std::chrono::milliseconds firstDataTimeout, std::chrono::milliseconds newDataTimeout) -> EncoderReceiverConfig&
{
  m_transport.firstDataTimeout = firstDataTimeout;
  m_transport.newDataTimeout   = newDataTimeout;
  return *this;
}

auto EncoderReceiverConfig::setReceiveBufferSize(std::size_t receiveBufferSize) -> EncoderReceiverConfig&
{
  m_transport.receiveBufferSize = receiveBufferSize;
  return *this;
}

auto EncoderReceiverConfig::setOnError(compact::ErrorCallback onError) -> EncoderReceiverConfig&
{
  m_onError = std::move(onError);
  return *this;
}

auto EncoderReceiverConfig::setLoggerName(std::string loggerName) -> EncoderReceiverConfig&
{
  m_loggerName = std::move(loggerName);
  return *this;
}

auto EncoderReceiverConfig::transport() const -> compact::ReceiverTransport const&
{
  return m_transport;
}

auto EncoderReceiverConfig::multicast() const -> std::optional<compact::MulticastGroup> const&
{
  return m_multicast;
}

auto EncoderReceiverConfig::dataCallback() const -> DataCallback const&
{
  return m_dataCallback;
}

auto EncoderReceiverConfig::onError() const -> compact::ErrorCallback const&
{
  return m_onError;
}

auto EncoderReceiverConfig::loggerName() const -> std::string const&
{
  return m_loggerName;
}

EncoderReceiver::EncoderReceiver(EncoderReceiverConfig config)
  : m_config(std::move(config))
{ }

EncoderReceiver::~EncoderReceiver()
{
  stop();
}

void EncoderReceiver::start()
{
  if (m_loop)
  {
    LOG_WARNING(m_config.loggerName()) << "Start called, but is already started. Doing nothing.";
    return;
  }

  auto const& transport = m_config.transport();
  m_loop                = std::make_unique<LoopT>(
    compact::makeUdpSocket(transport.port, m_config.multicast()),
    transport.receiveBufferSize,
    compact::DatagramDecoder<compact::encoder::Parser>(m_config.dataCallback()),
    m_config.onError(),
    transport.firstDataTimeout,
    transport.newDataTimeout,
    m_config.loggerName() + " on port " + std::to_string(transport.port)
  );
  m_loop->start();
}

void EncoderReceiver::stop()
{
  m_loop = nullptr;
}

void EncoderReceiver::restart()
{
  stop();
  start();
}

auto EncoderReceiver::isRunning() const -> bool
{
  return m_loop != nullptr;
}

} // namespace sick::picoScan100
