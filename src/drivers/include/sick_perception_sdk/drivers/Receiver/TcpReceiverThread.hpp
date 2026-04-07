/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/ByteView.hpp>
#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/logging/logging.hpp>
#include <sick_perception_sdk/common/socket/TcpClientSocket.hpp>
#include <sick_perception_sdk/compact_format/StreamExtractor.hpp>
#include <sick_perception_sdk/drivers/Exceptions/Timeout.hpp>
#include <sick_perception_sdk/drivers/Receiver/ReceiverThread.hpp>

#include <chrono>
#include <optional>

namespace sick::compact {

template <typename ParserT>
class TcpReceiverThread : public ReceiverThread<typename ParserT::DataT>
{
public:
  //! \param deviceAddress The IP address of the device to connect to
  //! \param sensorPort The port on the device to which to connect
  //! \param receiveBufferSize The size of the buffer used to receive data from the socket
  //! \param onNewData Callback function that is called when new data is received and parsed
  //! \param onError Callback function that is called when an unhandled exception is thrown
  //! \param firstDataTimeout If more time has passed than specified since the stream was started without receiving
  //! any data, an exception is raised. A value of 0 means no timeout.
  //! \param newDataTimeout If more time has passed than specified without receiving any data after the first data was
  //! received, an exception is raised. A value of 0 means no timeout.
  //! \param streamName The name of the stream, used to identify the stream in logs
  TcpReceiverThread(
    IpV4Address const& deviceAddress,
    std::uint16_t sensorPort,
    std::size_t receiveBufferSize,
    std::function<void(typename ParserT::DataT)> onNewData,
    std::function<void(std::exception_ptr)> onError,
    std::chrono::milliseconds firstDataTimeout = std::chrono::milliseconds(0),
    std::chrono::milliseconds newDataTimeout   = std::chrono::milliseconds(0),
    std::string streamName                     = "TcpReceiverThread"
  )
    : ReceiverThread<typename ParserT::DataT>(
        std::make_unique<TcpClientSocket>(deviceAddress, sensorPort),
        receiveBufferSize,
        std::move(onNewData),
        std::move(onError),
        firstDataTimeout,
        newDataTimeout,
        std::move(streamName)
      )
  { }

  ~TcpReceiverThread() override
  {
    // This dtor will be called before the base class dtor, so we must make sure to stop the receive thread
    // before destroying this instance. Otherwise the stream extractor instance will be destroyed while possibly
    // still being accessed by the receive thread.
    this->stop();
  }

private:
  void receive() override
  {
    std::size_t const numberOfBytesReceived = this->receiveWithTimeout();

    auto extractedPackages = this->m_streamExtractor.extractTelegrams(ByteView {this->m_receiveBuffer.data(), numberOfBytesReceived});
    LOG_FAST_LOOP_INFO(this->m_streamName) << "Extracted " << extractedPackages.size() << " packages.";
    for (auto& extractedPackage : extractedPackages)
    {
      // Don't check CRC32 here, because it has already been checked in the StreamExtractor
      bool const checkCrc32 = false;
      this->m_onNewData(ParserT::validateAndParse(extractedPackage, checkCrc32));
    }
  }

  StreamExtractor m_streamExtractor;
};

} // namespace sick::compact
