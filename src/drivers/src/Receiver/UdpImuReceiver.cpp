/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/drivers/Receiver/UdpImuReceiver.hpp>

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/logging/logging.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_2_imu_legacy/ImuLegacyParser.hpp>
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

namespace sick::compact {

auto UdpImuReceiverConfig::create(std::uint16_t receiverPort) -> UdpImuReceiverConfig
{
  UdpImuReceiverConfig config;
  config.m_transport.port = receiverPort;
  return config;
}

auto UdpImuReceiverConfig::setReceiverPort(std::uint16_t receiverPort) -> UdpImuReceiverConfig&
{
  m_transport.port = receiverPort;
  return *this;
}

auto UdpImuReceiverConfig::setOnNewDataCallback(DataCallback callback) -> UdpImuReceiverConfig&
{
  m_dataCallback = std::move(callback);
  return *this;
}

auto UdpImuReceiverConfig::setMulticast(IpV4Address const& groupAddress, IpV4Address const& localInterfaceAddress) -> UdpImuReceiverConfig&
{
  m_multicast = MulticastGroup {groupAddress, localInterfaceAddress};
  return *this;
}

auto UdpImuReceiverConfig::setTimeouts(std::chrono::milliseconds firstDataTimeout, std::chrono::milliseconds newDataTimeout) -> UdpImuReceiverConfig&
{
  m_transport.firstDataTimeout = firstDataTimeout;
  m_transport.newDataTimeout   = newDataTimeout;
  return *this;
}

auto UdpImuReceiverConfig::setReceiveBufferSize(std::size_t receiveBufferSize) -> UdpImuReceiverConfig&
{
  m_transport.receiveBufferSize = receiveBufferSize;
  return *this;
}

auto UdpImuReceiverConfig::setOnError(ErrorCallback onError) -> UdpImuReceiverConfig&
{
  m_onError = std::move(onError);
  return *this;
}

auto UdpImuReceiverConfig::setLoggerName(std::string loggerName) -> UdpImuReceiverConfig&
{
  m_loggerName = std::move(loggerName);
  return *this;
}

auto UdpImuReceiverConfig::transport() const -> ReceiverTransport const&
{
  return m_transport;
}

auto UdpImuReceiverConfig::multicast() const -> std::optional<MulticastGroup> const&
{
  return m_multicast;
}

auto UdpImuReceiverConfig::dataCallback() const -> DataCallback const&
{
  return m_dataCallback;
}

auto UdpImuReceiverConfig::onError() const -> ErrorCallback const&
{
  return m_onError;
}

auto UdpImuReceiverConfig::loggerName() const -> std::string const&
{
  return m_loggerName;
}

UdpImuReceiver::UdpImuReceiver(UdpImuReceiverConfig config)
  : m_config(std::move(config))
{ }

UdpImuReceiver::~UdpImuReceiver()
{
  stop();
}

void UdpImuReceiver::start()
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
    DatagramDecoder<imu_legacy::Parser>(m_config.dataCallback()),
    m_config.onError(),
    transport.firstDataTimeout,
    transport.newDataTimeout,
    m_config.loggerName() + " on port " + std::to_string(transport.port)
  );
  m_loop->start();
}

void UdpImuReceiver::stop()
{
  m_loop = nullptr;
}

void UdpImuReceiver::restart()
{
  stop();
  start();
}

auto UdpImuReceiver::isRunning() const -> bool
{
  return m_loop != nullptr;
}

} // namespace sick::compact
