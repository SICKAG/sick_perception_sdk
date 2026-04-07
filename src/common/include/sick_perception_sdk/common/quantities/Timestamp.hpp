/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/common/quantities/Duration.hpp>

#include <chrono>
#include <cstdint>
#include <ostream>
#include <string>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

namespace sick {

/**
 * @ingroup Quantities
 * 
 * See quantities.hpp for an overview.
 */
class SDK_EXPORT Timestamp
{
public:
  using value_type = std::uint64_t;

  static Timestamp now()
  {
    auto const now = std::chrono::steady_clock::now().time_since_epoch();
    return Timestamp::fromMicrosecondsSinceEpoch(std::chrono::duration_cast<std::chrono::microseconds>(now).count());
  }

  constexpr Timestamp()
    : m_microsecondsSinceEpoch(0)
  { }

  constexpr static auto fromMicrosecondsSinceEpoch(value_type microseconds) -> Timestamp
  {
    return Timestamp(microseconds);
  }

  constexpr auto microsecondsSinceEpoch() const -> value_type
  {
    return m_microsecondsSinceEpoch;
  }

  /*
   * @brief Mutable access to the raw value.
   *
   * @warning Use this function with caution. It relies on convention what the internal representation is.
   * Therefore, this function should only be used for deserialization of Compact formats.
   */

  auto rawValueMutable() -> Timestamp::value_type&
  {
    return m_microsecondsSinceEpoch;
  }

private:
  /**
   * @brief The internal representation of the quantity's value.
   * 
   * @warning This member must be the same type and scaling as in the Compact format!
   */
  value_type m_microsecondsSinceEpoch;

  constexpr explicit Timestamp(value_type microseconds)
    : m_microsecondsSinceEpoch {microseconds}
  { }
};

// Comparison operators
constexpr auto operator<(Timestamp const& lhs, Timestamp const& rhs) -> bool
{
  return lhs.microsecondsSinceEpoch() < rhs.microsecondsSinceEpoch();
}

constexpr auto operator==(Timestamp const& lhs, Timestamp const& rhs) -> bool
{
  return lhs.microsecondsSinceEpoch() == rhs.microsecondsSinceEpoch();
}

constexpr auto operator!=(Timestamp const& lhs, Timestamp const& rhs) -> bool
{
  return !(lhs == rhs);
}

// Arithmetic operators
constexpr auto operator+(Timestamp const& lhs, Duration const& rhs) -> Timestamp
{
  return Timestamp::fromMicrosecondsSinceEpoch(lhs.microsecondsSinceEpoch() + static_cast<Timestamp::value_type>(rhs.microseconds()));
}

constexpr auto operator-(Timestamp const& lhs, Timestamp const& rhs) -> Duration
{
  return Duration::fromMicroseconds(
    static_cast<Duration::value_type>(lhs.microsecondsSinceEpoch()) - static_cast<Duration::value_type>(rhs.microsecondsSinceEpoch())
  );
}

// Stream operators
auto SDK_EXPORT operator<<(std::ostream& stream, Timestamp const& timestamp) -> std::ostream&;

constexpr auto max(Timestamp const& lhs, Timestamp const& rhs) -> Timestamp
{
  if (lhs.microsecondsSinceEpoch() > rhs.microsecondsSinceEpoch())
  {
    return lhs;
  }
  return rhs;
}

constexpr auto min(Timestamp const& lhs, Timestamp const& rhs) -> Timestamp
{
  if (lhs.microsecondsSinceEpoch() < rhs.microsecondsSinceEpoch())
  {
    return lhs;
  }
  return rhs;
}

} // namespace sick

namespace std {

// NOLINTNEXTLINE(readability-identifier-naming): to_string is standard library style
auto SDK_EXPORT to_string(sick::Timestamp const& timestamp) -> std::string;

} // namespace std

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
