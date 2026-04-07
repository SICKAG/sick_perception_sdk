/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>

#include <cstdint>
#include <ostream>
#include <string>
#include <utility>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

namespace sick {

/**
 * @ingroup Quantities
 * 
 * See quantities.hpp for an overview.
 */
class SDK_EXPORT Duration
{
public:
  using value_type = double;

  constexpr Duration()
    : m_nanoseconds(0)
  { }

  constexpr static auto fromSeconds(value_type seconds) -> Duration
  {
    return Duration(seconds * static_cast<value_type>(1'000'000'000));
  }

  constexpr static auto fromMilliseconds(value_type milliseconds) -> Duration
  {
    return Duration(milliseconds * static_cast<value_type>(1'000'000));
  }

  constexpr static auto fromMicroseconds(value_type microseconds) -> Duration
  {
    return Duration(microseconds * static_cast<value_type>(1'000));
  }

  constexpr static auto fromNanoseconds(value_type nanoseconds) -> Duration
  {
    return Duration(nanoseconds);
  }

  constexpr auto microseconds() const -> value_type
  {
    return m_nanoseconds / static_cast<value_type>(1'000);
  }

  constexpr auto milliseconds() const -> value_type
  {
    return m_nanoseconds / static_cast<value_type>(1'000'000);
  }

  template <typename OutputT>
  constexpr auto milliseconds() const -> OutputT
  {
    return static_cast<OutputT>(m_nanoseconds / static_cast<value_type>(1'000'000));
  }

  constexpr auto nanoseconds() const -> value_type
  {
    return m_nanoseconds;
  }

  constexpr auto seconds() const -> value_type
  {
    return m_nanoseconds / static_cast<value_type>(1'000'000'000);
  }

  template <typename OutputT>
  constexpr auto seconds() const -> OutputT
  {
    return static_cast<OutputT>(m_nanoseconds / static_cast<value_type>(1'000'000'000));
  }

  /**
   * @brief Returns the duration as a pair of seconds and nanoseconds, where the nanoseconds part is always less than 1 second.
   * 
   * @return A pair of seconds (first element) and nanoseconds (second element).
   */
  constexpr auto secondsAndNanoseconds() const -> std::pair<std::uint32_t, std::uint32_t>
  {
    auto const secondsPart     = static_cast<std::uint32_t>(seconds());
    auto const nanosecondsPart = static_cast<std::uint32_t>(m_nanoseconds - static_cast<value_type>(secondsPart) * static_cast<value_type>(1'000'000'000));
    return {secondsPart, nanosecondsPart};
  }

private:
  value_type m_nanoseconds;

  constexpr explicit Duration(value_type nanoseconds)
    : m_nanoseconds {nanoseconds}
  { }
};

// Comparison operators
constexpr auto operator<(Duration const& lhs, Duration const& rhs) -> bool
{
  return lhs.nanoseconds() < rhs.nanoseconds();
}

// Arithmetic operators
constexpr auto operator+(Duration const& lhs, Duration const& rhs) -> Duration
{
  return Duration::fromNanoseconds(lhs.nanoseconds() + rhs.nanoseconds());
}

constexpr auto operator-(Duration const& lhs, Duration const& rhs) -> Duration
{
  return Duration::fromNanoseconds(lhs.nanoseconds() - rhs.nanoseconds());
}

/**
 * Multiplication with a non-Duration scalar is useful for forming multiples of a duration and are therefore only implemented for integers.
 */
constexpr auto operator*(Duration const& lhs, std::uint64_t rhs) -> Duration
{
  return Duration::fromNanoseconds(lhs.nanoseconds() * static_cast<Duration::value_type>(rhs));
}

/**
 * Division by a non-Duration scalar is useful for forming partial durations and are therefore only implemented for integers.
 */
constexpr auto operator/(Duration const& lhs, std::uint32_t rhs) -> Duration
{
  return Duration::fromNanoseconds(lhs.nanoseconds() / static_cast<Duration::value_type>(rhs));
}

// Stream operators
auto SDK_EXPORT operator<<(std::ostream& stream, Duration const& duration) -> std::ostream&;

namespace literals {

constexpr auto operator"" _s(unsigned long long value) -> Duration
{
  return Duration::fromSeconds(static_cast<Duration::value_type>(value));
}

constexpr auto operator"" _ms(unsigned long long value) -> Duration
{
  return Duration::fromMilliseconds(static_cast<Duration::value_type>(value));
}

constexpr auto operator"" _us(unsigned long long value) -> Duration
{
  return Duration::fromMicroseconds(static_cast<Duration::value_type>(value));
}

constexpr auto operator"" _ns(unsigned long long value) -> Duration
{
  return Duration::fromNanoseconds(static_cast<Duration::value_type>(value));
}

} // namespace literals

constexpr auto min(Duration const& lhs, Duration const& rhs) -> Duration
{
  if (lhs.nanoseconds() < rhs.nanoseconds())
  {
    return lhs;
  }
  return rhs;
}

} // namespace sick

namespace std {

// NOLINTNEXTLINE(readability-identifier-naming): to_string is standard library style
auto SDK_EXPORT to_string(sick::Duration const& duration) -> std::string;

} // namespace std

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
