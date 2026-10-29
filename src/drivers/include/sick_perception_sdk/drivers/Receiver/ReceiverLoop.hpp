/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/ByteView.hpp>
#include <sick_perception_sdk/common/logging/logging.hpp>
#include <sick_perception_sdk/common/socket/ReceiveError.hpp>
#include <sick_perception_sdk/common/socket/Socket.hpp>
#include <sick_perception_sdk/drivers/Exceptions/Timeout.hpp>

#include <atomic>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <functional>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <thread>
#include <utility>
#include <vector>

namespace sick::compact {

/**
 * @brief Receives bytes from a socket on a dedicated thread and feeds them to a decoder.
 */
template <typename DecoderT>
class ReceiverLoop final
{
public:
  using ErrorHandler = std::function<void(std::exception_ptr const&)>;

  /**
   * @param socket The socket to receive from. The socket is expected to be fully configured (bound, multicast groups joined) when it is handed over.
   */
  ReceiverLoop(
    std::unique_ptr<Socket> socket,
    std::size_t receiveBufferSize,
    DecoderT decoder,
    ErrorHandler onError,
    std::chrono::milliseconds firstDataTimeout,
    std::chrono::milliseconds newDataTimeout,
    std::string streamName
  )
    : m_receiveBuffer(receiveBufferSize)
    , m_decoder(std::move(decoder))
    , m_onError(std::move(onError))
    , m_streamName(std::move(streamName))
    , m_socket(std::move(socket))
    , m_firstDataTimeout(firstDataTimeout)
    , m_newDataTimeout(newDataTimeout)
    , m_receiveThread(nullptr)
    , m_runReceiveLoop(false)
  {
    if (m_socket == nullptr)
    {
      throw std::invalid_argument("Socket cannot be null");
    }
    if (m_onError == nullptr)
    {
      throw std::invalid_argument("Error handler cannot be null");
    }

    LOG_INFO(m_streamName) << "Setting socket timeout to " << firstDataTimeout.count() << " ms.";
    m_socket->setTimeout(firstDataTimeout);
  }

  ~ReceiverLoop()
  {
    stop();
  }

  ReceiverLoop(ReceiverLoop const&)                    = delete;
  auto operator=(ReceiverLoop const&) -> ReceiverLoop& = delete;
  ReceiverLoop(ReceiverLoop&&)                         = delete;
  auto operator=(ReceiverLoop&&) -> ReceiverLoop&      = delete;

  void start()
  {
    if (isRunning())
    {
      LOG_INFO(m_streamName) << "Start called, but receive loop is already running.";
      return;
    }

    m_startTime = std::chrono::steady_clock::now();

    m_socket->connect();
    LOG_INFO(m_streamName) << "Connected.";

    m_runReceiveLoop = true;
    m_receiveThread  = std::make_unique<std::thread>([this]() -> void {
      runReceiveLoop();
    });
  }

  void stop()
  {
    if (!isRunning())
    {
      return;
    }

    LOG_INFO(m_streamName) << "Stopping receive loop.";
    m_runReceiveLoop = false;

    // Close the socket to abort any blocking recv() call immediately.
    m_socket->closeConnection();

    m_startTime = std::nullopt;

    if (m_receiveThread->joinable())
    {
      m_receiveThread->join();
    }

    m_receiveThread = nullptr;
  }

  [[nodiscard]] auto isRunning() const -> bool
  {
    return m_receiveThread != nullptr;
  }

private:
  std::vector<std::uint8_t> m_receiveBuffer;
  DecoderT m_decoder;
  ErrorHandler m_onError;
  std::string m_streamName;
  std::unique_ptr<Socket> m_socket;
  std::chrono::milliseconds m_firstDataTimeout;
  std::chrono::milliseconds m_newDataTimeout;
  std::optional<std::chrono::steady_clock::time_point> m_startTime;
  std::optional<std::chrono::steady_clock::time_point> m_lastReceiveTime;
  std::unique_ptr<std::thread> m_receiveThread;
  std::atomic<bool> m_runReceiveLoop;

  void runReceiveLoop()
  {
    LOG_INFO(m_streamName) << "Starting receive loop.";

    while (m_runReceiveLoop)
    {
      try
      {
        std::size_t const numberOfBytesReceived = receiveWithTimeout();
        if (numberOfBytesReceived != 0)
        {
          m_decoder(ByteView {m_receiveBuffer.data(), numberOfBytesReceived});
        }
      }
      catch (std::exception const& exception)
      {
        if (!m_runReceiveLoop)
        {
          // Socket was closed by stop() to abort recv() — expected, not an error.
          break;
        }
        LOG_WARNING(m_streamName) << "Exception in receive loop: " << exception.what();
        m_onError(std::current_exception());
      }
    }
  }

  auto receiveWithTimeout() -> std::size_t
  {
    try
    {
      std::size_t const numberOfBytesReceived = m_socket->receive(m_receiveBuffer);
      LOG_FAST_LOOP_INFO(m_streamName) << "Received " << numberOfBytesReceived << " bytes.";
      if (numberOfBytesReceived == 0)
      {
        onNoDataReceived();
        return 0;
      }
      if (!m_lastReceiveTime.has_value())
      {
        LOG_INFO(m_streamName) << "First data received, setting socket timeout to " << m_newDataTimeout.count() << " ms.";
        m_socket->setTimeout(m_newDataTimeout);
      }
      m_lastReceiveTime = std::chrono::steady_clock::now();
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
        m_onError(std::make_exception_ptr(Timeout(msg)));
      }
      return;
    }

    // Check timeout until first data is received.
    if (!m_lastReceiveTime && m_startTime && m_firstDataTimeout.count() > 0)
    {
      auto const now            = std::chrono::steady_clock::now();
      auto const timeSinceStart = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_startTime.value());
      if (timeSinceStart > m_firstDataTimeout)
      {
        std::string const msg = "No data received for more than " + std::to_string(m_firstDataTimeout.count()) + " ms since stream start.";
        LOG_ERROR(m_streamName) << msg;
        m_onError(std::make_exception_ptr(Timeout(msg)));
      }
    }
  }
};

} // namespace sick::compact
