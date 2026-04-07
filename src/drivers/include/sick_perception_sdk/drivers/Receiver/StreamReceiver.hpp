/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/logging/logging.hpp>

#include <chrono>
#include <functional>
#include <memory>
#include <string>

namespace sick::compact {

template <typename ThreadT>
class StreamReceiver
{
public:
  static constexpr std::chrono::milliseconds kDefaultFirstDataTimeout {3000};
  static constexpr std::chrono::milliseconds kDefaultNewDataTimeout {1000};
  using ErrorCallback = std::function<void(std::exception_ptr)>;

  explicit StreamReceiver(ErrorCallback onError, std::string loggerName)
    : m_onError(std::move(onError))
    , m_loggerName(std::move(loggerName))
  { }

  StreamReceiver(StreamReceiver const&)                    = delete;
  auto operator=(StreamReceiver const&) -> StreamReceiver& = delete;
  StreamReceiver(StreamReceiver&&)                         = default;
  auto operator=(StreamReceiver&&) -> StreamReceiver&      = default;

  virtual ~StreamReceiver() = default;

  void start()
  {
    if (m_thread)
    {
      LOG_WARNING(m_loggerName) << "Start called, but is already started. Doing nothing.";
      return;
    }
    if (!m_streamFactory)
    {
      return;
    }
    m_thread = (*m_streamFactory)();
  }

  void stop()
  {
    m_thread = nullptr;
  }

  void restart()
  {
    stop();
    start();
  }

protected:
  void logSetupWhileRunning() const
  {
    if (m_thread)
    {
      LOG_INFO(m_loggerName) << "Setup called, but stream is already started. Setup will be applied on next restart.";
    }
  }

  // NOLINTBEGIN(misc-non-private-member-variables-in-classes, cppcoreguidelines-non-private-member-variables-in-classes)
  ErrorCallback m_onError;
  std::string m_loggerName;
  std::optional<std::function<std::unique_ptr<ThreadT>()>> m_streamFactory;
  std::unique_ptr<ThreadT> m_thread;
  // NOLINTEND(misc-non-private-member-variables-in-classes, cppcoreguidelines-non-private-member-variables-in-classes)
};

} // namespace sick::compact
