/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/drivers/Receiver/StreamReceiver.hpp>
#include <sick_perception_sdk/drivers/Receiver/TcpReceiverThread.hpp>

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <string>

namespace sick::compact {

template <typename ParserT>
class TcpStreamReceiver : public StreamReceiver<TcpReceiverThread<ParserT>>
{
  using BaseT = StreamReceiver<TcpReceiverThread<ParserT>>;

public:
  using ThreadT      = TcpReceiverThread<ParserT>;
  using DataCallback = std::function<void(typename ParserT::DataT const&)>;

  static constexpr std::size_t kDefaultReceiveBufferSize = 4'000'000;
  static constexpr std::chrono::milliseconds kDefaultFirstDataTimeout {3000};
  static constexpr std::chrono::milliseconds kDefaultNewDataTimeout {1000};

  explicit TcpStreamReceiver(typename BaseT::ErrorCallback onError, std::string loggerName)
    : BaseT(onError, loggerName)
  { }

  auto setup(
    DataCallback dataCallback,
    IpV4Address const& deviceAddress,
    std::uint16_t sensorPort,
    std::chrono::milliseconds firstDataTimeout = BaseT::kDefaultFirstDataTimeout,
    std::chrono::milliseconds newDataTimeout   = BaseT::kDefaultNewDataTimeout,
    std::size_t receiveBufferSize              = kDefaultReceiveBufferSize
  ) -> TcpStreamReceiver&
  {
    this->logSetupWhileRunning();

    std::string const streamName = this->m_loggerName + " " + deviceAddress.toString() + ":" + std::to_string(sensorPort);
    auto const errorCallback     = this->m_onError;

    this->m_streamFactory = [=]() -> std::unique_ptr<ThreadT> {
      return std::make_unique<ThreadT>(deviceAddress, sensorPort, receiveBufferSize, dataCallback, errorCallback, firstDataTimeout, newDataTimeout, streamName);
    };

    return *this;
  }
};

} // namespace sick::compact
