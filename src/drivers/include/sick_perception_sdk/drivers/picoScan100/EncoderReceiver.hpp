/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_4_encoder/EncoderData.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_4_encoder/EncoderParser.hpp>
#include <sick_perception_sdk/drivers/Receiver/DatagramDecoder.hpp>
#include <sick_perception_sdk/drivers/Receiver/ReceiverDefaults.hpp>
#include <sick_perception_sdk/drivers/Receiver/ReceiverLoop.hpp>
#include <sick_perception_sdk/drivers/Receiver/ReceiverSockets.hpp>

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <string>

namespace sick::picoScan100 {

class SDK_EXPORT EncoderReceiverConfig
{
public:
  using DataCallback = std::function<void(compact::encoder::EncoderData const&)>;

  static constexpr std::uint16_t kDefaultPort = 7504;

  static auto create(std::uint16_t receiverPort = kDefaultPort) -> EncoderReceiverConfig;

  auto setReceiverPort(std::uint16_t receiverPort) -> EncoderReceiverConfig&;

  auto setOnNewDataCallback(DataCallback callback) -> EncoderReceiverConfig&;
  auto setMulticast(IpV4Address const& groupAddress, IpV4Address const& localInterfaceAddress) -> EncoderReceiverConfig&;
  auto setTimeouts(std::chrono::milliseconds firstDataTimeout, std::chrono::milliseconds newDataTimeout) -> EncoderReceiverConfig&;
  auto setReceiveBufferSize(std::size_t receiveBufferSize) -> EncoderReceiverConfig&;
  //! \brief Defaults to rethrowing the exception. Set an empty-bodied callback to silence errors instead.
  auto setOnError(compact::ErrorCallback onError) -> EncoderReceiverConfig&;
  auto setLoggerName(std::string loggerName) -> EncoderReceiverConfig&;

  [[nodiscard]] auto transport() const -> compact::ReceiverTransport const&;
  [[nodiscard]] auto multicast() const -> std::optional<compact::MulticastGroup> const&;
  [[nodiscard]] auto dataCallback() const -> DataCallback const&;
  [[nodiscard]] auto onError() const -> compact::ErrorCallback const&;
  [[nodiscard]] auto loggerName() const -> std::string const&;

private:
  EncoderReceiverConfig() = default;

  compact::ReceiverTransport m_transport {
    kDefaultPort,
    compact::receiver_defaults::kFirstDataTimeout,
    compact::receiver_defaults::kNewDataTimeout,
    compact::receiver_defaults::kUdpReceiveBufferSize
  };
  std::optional<compact::MulticastGroup> m_multicast;
  DataCallback m_dataCallback;
  compact::ErrorCallback m_onError = compact::receiver_defaults::kDefaultErrorCallback;
  std::string m_loggerName         = "EncoderReceiver";
};

//! \brief Receives Compact encoder telegrams from a UDP port.
class SDK_EXPORT EncoderReceiver
{
public:
  explicit EncoderReceiver(EncoderReceiverConfig config);

  ~EncoderReceiver();

  EncoderReceiver(EncoderReceiver const&)                    = delete;
  auto operator=(EncoderReceiver const&) -> EncoderReceiver& = delete;
  EncoderReceiver(EncoderReceiver&&)                         = delete;
  auto operator=(EncoderReceiver&&) -> EncoderReceiver&      = delete;

  void start();
  void stop();
  void restart();

  [[nodiscard]] auto isRunning() const -> bool;

private:
  using LoopT = compact::ReceiverLoop<compact::DatagramDecoder<compact::encoder::Parser>>;

  EncoderReceiverConfig m_config;
  std::unique_ptr<LoopT> m_loop;
};

} // namespace sick::picoScan100
