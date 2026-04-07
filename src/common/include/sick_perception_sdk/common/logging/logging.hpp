/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/logging/LogLevel.hpp>

#include <ostream>
#include <sstream>
#include <string>
#include <utility> // added for std::move

namespace sick {

class SDK_EXPORT LogMessage
{
public:
  LogMessage(std::string const& prefix, LogLevel level, std::string fileName, int lineNumber);
  ~LogMessage();

  // Disable copy (std::stringstream is not copyable)
  LogMessage(LogMessage const&)                    = delete;
  auto operator=(LogMessage const&) -> LogMessage& = delete;

  // Allow move
  LogMessage(LogMessage&& other) noexcept;
  auto operator=(LogMessage&& other) noexcept -> LogMessage&;

  // Generic stream operator for any type that can be streamed into std::stringstream.
  template <typename T>
  auto operator<<(T const& value) -> LogMessage&
  {
    m_stream << value;
    return *this;
  }

  // Overload for ostream manipulators like std::endl, std::flush, etc.
  auto operator<<(std::ostream& (*manip)(std::ostream&)) -> LogMessage&
  {
    if (manip == nullptr)
    {
      // Silently ignore invalid manipulators
      return *this;
    }
    manip(m_stream);
    return *this;
  }

private:
  LogLevel m_level;
  std::stringstream m_stream;
  std::string m_fileName;
  int m_lineNumber;
};

class SDK_EXPORT Log
{
public:
  /**
 * @brief Initialize the logging system with the given minimum log level.
 * 
 * @param minimumLogLevel The minimum log level to log. Messages with a lower level will be ignored.
 */
  static void init(LogLevel minimumLogLevel);

  static auto error(std::string const& prefix, std::string fileName, int lineNumber) -> LogMessage;
  static auto fastLoopInfo(std::string const& prefix, std::string fileName, int lineNumber) -> LogMessage;
  static auto fastLoopWarning(std::string const& prefix, std::string fileName, int lineNumber) -> LogMessage;
  static auto info(std::string const& prefix, std::string fileName, int lineNumber) -> LogMessage;
  static auto warning(std::string const& prefix, std::string fileName, int lineNumber) -> LogMessage;
};

// NOLINTBEGIN(cppcoreguidelines-macro-usage): macros are the only solution for __LINE__ to work unless we update to C++20.
#define LOG_ERROR(prefix) ::sick::Log::error((prefix), __FILE__, __LINE__)
#define LOG_FAST_LOOP_INFO(prefix) ::sick::Log::fastLoopInfo((prefix), __FILE__, __LINE__)
#define LOG_FAST_LOOP_WARNING(prefix) ::sick::Log::fastLoopWarning((prefix), __FILE__, __LINE__)
#define LOG_INFO(prefix) ::sick::Log::info((prefix), __FILE__, __LINE__)
#define LOG_WARNING(prefix) ::sick::Log::warning((prefix), __FILE__, __LINE__)
// NOLINTEND(cppcoreguidelines-macro-usage)

} // namespace sick
