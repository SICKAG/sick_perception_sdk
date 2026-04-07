/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/drivers/Receiver/StreamReceiver.hpp>
#include <sick_perception_sdk/drivers/Receiver/UdpReceiverThread.hpp>

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <string>

namespace sick::compact {

template <typename ParserT, typename DerivedT>
class UdpStreamReceiver : public StreamReceiver<UdpReceiverThread<ParserT>>
{
  using BaseT = StreamReceiver<UdpReceiverThread<ParserT>>;

public:
  using ThreadT      = UdpReceiverThread<ParserT>;
  using DataCallback = std::function<void(typename ParserT::DataT const&)>;

  static constexpr std::size_t kDefaultReceiveBufferSize = 65'507;

  explicit UdpStreamReceiver(typename BaseT::ErrorCallback onError, std::string loggerName)
    : BaseT(onError, loggerName)
  { }

  auto setup(
    DataCallback dataCallback,
    std::uint16_t receiverPort,
    std::chrono::milliseconds firstDataTimeout = BaseT::kDefaultFirstDataTimeout,
    std::chrono::milliseconds newDataTimeout   = BaseT::kDefaultNewDataTimeout,
    std::size_t receiveBufferSize              = kDefaultReceiveBufferSize
  ) -> DerivedT&
  {
    this->logSetupWhileRunning();

    std::string const streamName = this->m_loggerName + " on port " + std::to_string(receiverPort);
    auto const errorCallback     = this->m_onError;

    this->m_streamFactory = [=]() -> std::unique_ptr<ThreadT> {
      return std::make_unique<ThreadT>(receiverPort, receiveBufferSize, dataCallback, errorCallback, firstDataTimeout, newDataTimeout, streamName);
    };

    return derived();
  }

  auto setupMulticast(IpV4Address const& multicastGroupAddress, IpV4Address const& localInterfaceAddress) -> DerivedT&
  {
    m_multicastAddresses = std::make_pair(multicastGroupAddress, localInterfaceAddress);
    return derived();
  }

  void start()
  {
    bool const wasRunning = this->m_thread != nullptr;

    BaseT::start();

    // Join multicast group after starting the thread because the socket does not exist before the thread is started.
    // wasRunning prevents the receiver from joining the same multicast group multiple times.
    if (this->m_thread && m_multicastAddresses && !wasRunning)
    {
      this->m_thread->joinMulticastGroup(m_multicastAddresses->first, m_multicastAddresses->second);
    }
  }

protected:
  std::optional<std::pair<sick::IpV4Address, sick::IpV4Address>> m_multicastAddresses;

  auto derived() -> DerivedT&
  {
    return static_cast<DerivedT&>(*this);
  }
};

} // namespace sick::compact
