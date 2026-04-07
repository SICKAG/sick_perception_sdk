/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include "CustomFormatter.hpp"

#include <ctime>
#include <iomanip>
#include <ios>
#include <plog/Record.h>
#include <plog/Severity.h>
#include <plog/Util.h>

namespace sick {

auto CustomFormatter::header() -> plog::util::nstring
{
  return {};
}

auto CustomFormatter::format(plog::Record const& record) -> plog::util::nstring
{
  // This formatter always uses UTC time
  tm timeStruct {};
  plog::util::gmtime_s(&timeStruct, &record.getTime().time);

  plog::util::nostringstream stream;
  // Add the date in the format YYYY-MM-DD
  // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  stream << timeStruct.tm_year + 1900 << "-" << std::setfill(PLOG_NSTR('0')) << std::setw(2) << timeStruct.tm_mon + 1 << PLOG_NSTR("-")
         << std::setfill(PLOG_NSTR('0')) << std::setw(2) << timeStruct.tm_mday << PLOG_NSTR(" ");
  // Add the time in the format HH:MM:SS.mmm
  stream << std::setfill(PLOG_NSTR('0')) << std::setw(2) << timeStruct.tm_hour << PLOG_NSTR(":") << std::setfill(PLOG_NSTR('0')) << std::setw(2)
         << timeStruct.tm_min << PLOG_NSTR(":") << std::setfill(PLOG_NSTR('0')) << std::setw(2) << timeStruct.tm_sec << PLOG_NSTR(".")
         << std::setfill(PLOG_NSTR('0')) << std::setw(3) << static_cast<int>(record.getTime().millitm) << PLOG_NSTR(" ");
  // Add the log level
  // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  stream << std::setfill(PLOG_NSTR(' ')) << std::setw(5) << std::left << severityToString(record.getSeverity()) << PLOG_NSTR(" ");
  // Add the thread ID
  stream << PLOG_NSTR("[TID ") << record.getTid() << PLOG_NSTR("] ");
  // Add the file name and line number
  stream << PLOG_NSTR("[") << record.getFile() << PLOG_NSTR("@") << record.getLine() << PLOG_NSTR("] ");
  // Add the log message
  stream << record.getMessage() << PLOG_NSTR("\n");

  return stream.str();
}

} // namespace sick
