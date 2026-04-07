/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/logging/logging.hpp>
#include <sick_perception_sdk/common/socket/ReceiveError.hpp>
#include <sick_perception_sdk/common/socket/Socket.hpp>
#include <sick_perception_sdk/drivers/Exceptions/Timeout.hpp>

#include <chrono>
#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <thread>
#include <vector>

namespace sick::compact {

template <typename DataT>
class ReceiverThread
{
public:
  ReceiverThread(
    std::unique_ptr<Socket> socket,
    std::size_t receiveBufferSize,
    std::function<void(DataT)> onNewData,
    std::function<void(std::exception_ptr)> onError,
    std::chrono::milliseconds firstDataTimeout = std::chrono::milliseconds(0),
    std::chrono::milliseconds newDataTimeout   = std::chrono::milliseconds(0),
    std::string streamName                     = "ReceiverThread"
  )
    : m_socket(std::move(socket))
    , m_onNewData(std::move(onNewData))
    , m_onError(std::move(onError))
    , m_receiveBuffer(receiveBufferSize)
    , m_receiveThread(nullptr)
    , m_runReceiveLoop(false)
    , m_firstDataTimeout(firstDataTimeout)
    , m_newDataTimeout(newDataTimeout)
    , m_streamName(std::move(streamName))
  {
    if (m_socket == nullptr)
    {
      throw std::invalid_argument("Socket cannot be null");
    }

    LOG_INFO(this->m_streamName) << "Setting socket timeout to " << firstDataTimeout.count() << " ms.";
    m_socket->setTimeout(firstDataTimeout);
    start();
  }

  ReceiverThread(ReceiverThread const&)                    = delete;
  auto operator=(ReceiverThread const&) -> ReceiverThread& = delete;
  ReceiverThread(ReceiverThread&&)                         = delete;
  auto operator=(ReceiverThread&&) -> ReceiverThread&      = delete;

  virtual ~ReceiverThread()
  {
    stop();
  }

  void stop()
  {
    if (m_receiveThread == nullptr)
    {
      return;
    }

    LOG_INFO(m_streamName) << "Stopping receive loop.";
    m_runReceiveLoop = false;
    if (m_receiveThread->joinable())
    {
      m_receiveThread->join();
    }

    m_receiveThread = nullptr;
  }

protected:
  virtual void receive() = 0;

  void start()
  {
    if (m_startTime.has_value())
    {
      LOG_INFO(m_streamName) << "Start called, but receive loop is already running.";
      return;
    }

    m_startTime = std::chrono::steady_clock::now();

    connectToSource();

    m_runReceiveLoop = true;
    m_receiveThread  = std::make_unique<std::thread>([this]() -> void {
      LOG_INFO(m_streamName) << "Starting receive loop.";

      while (m_runReceiveLoop)
      {
        try
        {
          receive();
        }
        catch (std::exception const& exception)
        {
          LOG_WARNING(m_streamName) << "Exception in receive loop: " << exception.what();
          m_onError(std::current_exception());
        }
      }
    });
  }

  void connectToSource()
  {
    // AXIVION Next Line CertC++-EXP34: false positive, m_socket is != nullptr.
    m_socket->connect();
    LOG_INFO(m_streamName) << "Connected.";
  }

  auto receiveWithTimeout() -> std::size_t
  {
    try
    {
      std::size_t const numberOfBytesReceived = m_socket->receive(this->m_receiveBuffer);
      LOG_FAST_LOOP_INFO(this->m_streamName) << "Received " << numberOfBytesReceived << " bytes.";
      if (numberOfBytesReceived == 0)
      {
        this->onNoDataReceived();
        return 0;
      }
      if (!this->m_lastReceiveTime.has_value())
      {
        LOG_INFO(this->m_streamName) << "First data received, setting socket timeout to " << this->m_newDataTimeout.count() << " ms.";
        m_socket->setTimeout(this->m_newDataTimeout);
      }
      this->m_lastReceiveTime = std::chrono::steady_clock::now();
      return numberOfBytesReceived;
    }
    catch (ReceiveError const& error)
    {
      if (Socket::errorCodeIsTimeoutError(error.getErrorCode()))
      {
        throw Timeout("Timeout while receiving data from socket.");
      }
      throw error;
    }
  }

  void onNoDataReceived()
  {
    if (m_lastReceiveTime && m_newDataTimeout.count() > 0)
    {
      auto const now                  = std::chrono::steady_clock::now();
      auto const timeSinceLastReceive = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_lastReceiveTime.value());
      if (timeSinceLastReceive > m_newDataTimeout)
      {
        std::string const msg = "No data received for more than " + std::to_string(m_newDataTimeout.count()) + " ms since the last data was received.";
        LOG_ERROR(m_streamName) << msg;
        m_onError(timeout(msg));
      }
      return;
    }

    // Check timeout until first data is received.
    if (!m_lastReceiveTime && m_startTime)
    {
      // We have not received any data yet.
      if (m_firstDataTimeout.count() > 0)
      {
        auto const now            = std::chrono::steady_clock::now();
        auto const timeSinceStart = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_startTime.value());
        if (timeSinceStart > m_firstDataTimeout)
        {
          std::string const msg = "No data received for more than " + std::to_string(m_firstDataTimeout.count()) + " ms since stream start.";
          LOG_ERROR(m_streamName) << msg;
          m_onError(timeout(msg));
        }
      }
      return;
    }
  };

  // We want to allow protected member variables
  // NOLINTBEGIN(misc-non-private-member-variables-in-classes, cppcoreguidelines-non-private-member-variables-in-classes)
  std::vector<std::uint8_t> m_receiveBuffer;
  std::function<void(DataT)> m_onNewData;
  std::function<void(std::exception_ptr)> m_onError;
  std::string m_streamName;
  std::unique_ptr<Socket> m_socket;
  // NOLINTEND(misc-non-private-member-variables-in-classes, cppcoreguidelines-non-private-member-variables-in-classes)

private:
  std::chrono::milliseconds m_firstDataTimeout;
  std::chrono::milliseconds m_newDataTimeout;
  std::optional<std::chrono::steady_clock::time_point> m_lastReceiveTime;

  std::unique_ptr<std::thread> m_receiveThread;
  bool m_runReceiveLoop;
  std::optional<std::chrono::steady_clock::time_point> m_startTime;

  static auto timeout(std::string const& message) -> std::exception_ptr
  {
    return std::make_exception_ptr(Timeout(message));
  }
};

} // namespace sick::compact
