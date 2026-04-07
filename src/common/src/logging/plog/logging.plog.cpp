/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/logging/logging.hpp>

#include "CustomFormatter.hpp"
#include <sick_perception_sdk/common/logging/LogLevel.hpp>
#include <sick_perception_sdk/common/version.hpp>

#include <memory>
#include <plog/Appenders/ConsoleAppender.h>
#include <plog/Initializers/ConsoleInitializer.h>
#include <plog/Logger.h>
#include <plog/Severity.h>
#include <utility>

namespace sick {

namespace {

auto toPlogSeverity(LogLevel level) -> plog::Severity
{
  switch (level)
  {
  case LogLevel::Error:
    return plog::error;
  case LogLevel::Warning:
    return plog::warning;
  case LogLevel::Info:
    return plog::info;
  case LogLevel::FastLoopWarning:
    return plog::debug;
  case LogLevel::FastLoopInfo:
    return plog::verbose;
  default:
    return plog::none;
  }
}

struct Impl
{
  explicit Impl(LogLevel minimumLogLevel)
  {
    if (plog::get<0>() == nullptr)
    {
      plog::init<CustomFormatter, 0>(toPlogSeverity(minimumLogLevel), plog::streamStdOut);
    }
  }
};

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables)
std::unique_ptr<Impl> g_impl = nullptr;

void ensureInstanceIsAvailable()
{
  if (g_impl == nullptr)
  {
    g_impl = std::make_unique<Impl>(LogLevel::Info);
  }
}

} // namespace

auto Log::init(LogLevel minimumLogLevel) -> void
{
  if (g_impl != nullptr)
  {
    Log::warning("Log", __FILE__, __LINE__) << "Logging is already initialized. Ignoring re-initialization.";
    return;
  }
  g_impl = std::make_unique<Impl>(minimumLogLevel);
  LOG_INFO("") << "SDK Version: " << sick::version();
}

auto Log::fastLoopInfo(std::string const& prefix, std::string fileName, int lineNumber) -> LogMessage
{
  ensureInstanceIsAvailable();
  return {prefix, LogLevel::FastLoopInfo, std::move(fileName), lineNumber};
}

auto Log::fastLoopWarning(std::string const& prefix, std::string fileName, int lineNumber) -> LogMessage
{
  ensureInstanceIsAvailable();
  return {prefix, LogLevel::FastLoopWarning, std::move(fileName), lineNumber};
}

auto Log::error(std::string const& prefix, std::string fileName, int lineNumber) -> LogMessage
{
  ensureInstanceIsAvailable();
  return {prefix, LogLevel::Error, std::move(fileName), lineNumber};
}

auto Log::info(std::string const& prefix, std::string fileName, int lineNumber) -> LogMessage
{
  ensureInstanceIsAvailable();
  return {prefix, LogLevel::Info, std::move(fileName), lineNumber};
}

auto Log::warning(std::string const& prefix, std::string fileName, int lineNumber) -> LogMessage
{
  ensureInstanceIsAvailable();
  return {prefix, LogLevel::Warning, std::move(fileName), lineNumber};
}

LogMessage::LogMessage(std::string const& prefix, LogLevel level, std::string fileName, int lineNumber)
  : m_level(level)
  , m_fileName(std::move(fileName))
  , m_lineNumber(lineNumber)
{
  if (prefix.empty())
  {
    return;
  }
  m_stream << "[" << prefix << "] ";
}

LogMessage::~LogMessage()
{
  if (plog::get<0>() == nullptr || !plog::get<0>()->checkSeverity(toPlogSeverity(m_level)))
  {
    return;
  }

  (*plog::get<0>()) += plog::Record(toPlogSeverity(m_level), "", m_lineNumber, m_fileName.c_str(), nullptr, 0).ref() << m_stream.str();
}

} // namespace sick
