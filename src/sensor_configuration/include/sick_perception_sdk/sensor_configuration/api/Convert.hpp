/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/common/quantities/Timestamp.hpp>

#include <array>
#include <chrono>
#include <cstdint>
#include <ctime>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

namespace sick::convert {

constexpr Timestamp::value_type microSecondsPerSecond = 1'000'000;

/**
 * @brief Convert a broken-down device date/time payload to a Timestamp.
 *
 * Works with any generated date/time struct (e.g. `DateTime` or `LSPdatetime`), as they all expose
 * the same `_uiYear`, `_usiMonth`, `_usiDay`, `_usiHour`, `_usiMinute`, `_usiSec`, `_udiUSec` fields.
 */
template <typename DateTimeT>
auto toTimestamp(DateTimeT const& dateTime) -> Timestamp
{
  std::tm timeStruct {};
  // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  timeStruct.tm_year = static_cast<int>(dateTime._uiYear.value()) - 1900;
  timeStruct.tm_mon  = static_cast<int>(dateTime._usiMonth.value()) - 1;
  timeStruct.tm_mday = static_cast<int>(dateTime._usiDay.value());
  timeStruct.tm_hour = static_cast<int>(dateTime._usiHour.value());
  timeStruct.tm_min  = static_cast<int>(dateTime._usiMinute.value());
  timeStruct.tm_sec  = static_cast<int>(dateTime._usiSec.value());

#ifdef _WIN32
  auto const secondsSinceEpoch = static_cast<Timestamp::value_type>(_mkgmtime(&timeStruct));
#else
  auto const secondsSinceEpoch = static_cast<Timestamp::value_type>(timegm(&timeStruct));
#endif

  return Timestamp::fromMicrosecondsSinceEpoch(secondsSinceEpoch * microSecondsPerSecond + static_cast<Timestamp::value_type>(dateTime._udiUSec.value()));
}

/**
 * @brief Convert a Timestamp to a broken-down device date/time payload.
 *
 * @tparam DateTimeT The generated date/time struct to produce (e.g. `DateTime` or `LSPdatetime`).
 * @throws std::runtime_error if the time cannot be represented in UTC.
 */
template <typename DateTimeT>
auto toSopasPayload(Timestamp const& timestamp) -> DateTimeT
{
  auto const totalMicroseconds = timestamp.microsecondsSinceEpoch();
  auto const seconds           = totalMicroseconds / microSecondsPerSecond;
  auto const microseconds      = totalMicroseconds % microSecondsPerSecond;

  auto const timeT = static_cast<std::time_t>(seconds);
  std::tm timeStruct {};

#ifdef _WIN32
  if (gmtime_s(&timeStruct, &timeT) != 0)
#else
  if (gmtime_r(&timeT, &timeStruct) == nullptr)
#endif
  {
    throw std::runtime_error("Failed to convert time to UTC");
  }

  DateTimeT dateTime {};
  // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  dateTime._uiYear    = static_cast<decltype(dateTime._uiYear.value())>(timeStruct.tm_year + 1900);
  dateTime._usiMonth  = static_cast<decltype(dateTime._usiMonth.value())>(timeStruct.tm_mon + 1);
  dateTime._usiDay    = static_cast<decltype(dateTime._usiDay.value())>(timeStruct.tm_mday);
  dateTime._usiHour   = static_cast<decltype(dateTime._usiHour.value())>(timeStruct.tm_hour);
  dateTime._usiMinute = static_cast<decltype(dateTime._usiMinute.value())>(timeStruct.tm_min);
  dateTime._usiSec    = static_cast<decltype(dateTime._usiSec.value())>(timeStruct.tm_sec);
  dateTime._udiUSec   = static_cast<decltype(dateTime._udiUSec.value())>(microseconds);
  return dateTime;
}

} // namespace sick::convert
