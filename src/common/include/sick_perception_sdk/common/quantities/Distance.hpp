/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>

#include <limits>
#include <ostream>
#include <string>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

namespace sick {

/**
 * @ingroup Quantities
 * 
 * See quantities.hpp for an overview.
 */
class SDK_EXPORT Distance
{
public:
  using value_type = float;

  constexpr Distance()
    : m_meters(std::numeric_limits<Distance::value_type>::quiet_NaN())
  { }

  constexpr static auto fromMillimeters(value_type millimeters) -> Distance
  {
    return Distance(millimeters / 1'000.0f);
  }

  constexpr static auto fromMeters(value_type meters) -> Distance
  {
    return Distance(meters);
  }

  constexpr auto meters() const -> value_type
  {
    return m_meters;
  }

  constexpr auto millimeters() const -> value_type
  {
    return m_meters * 1'000.0f;
  }

private:
  value_type m_meters;

  constexpr explicit Distance(value_type meters)
    : m_meters {meters}
  { }
};

// Comparison operators
constexpr auto operator<(Distance const& lhs, Distance const& rhs) -> bool
{
  return lhs.meters() < rhs.meters();
}

constexpr auto operator<=(Distance const& lhs, Distance const& rhs) -> bool
{
  return lhs.meters() <= rhs.meters();
}

constexpr auto operator>(Distance const& lhs, Distance const& rhs) -> bool
{
  return lhs.meters() > rhs.meters();
}

constexpr auto operator>=(Distance const& lhs, Distance const& rhs) -> bool
{
  return lhs.meters() >= rhs.meters();
}

// Arithmetic operators
constexpr auto operator-(Distance const& distance) -> Distance
{
  return Distance::fromMeters(-distance.meters());
}

constexpr auto operator/(Distance const& lhs, int rhs) -> Distance
{
  return Distance::fromMeters(lhs.meters() / static_cast<float>(rhs));
}

// Stream operators
auto SDK_EXPORT operator<<(std::ostream& stream, Distance const& distance) -> std::ostream&;

namespace literals {

constexpr auto operator"" _m(long double value) -> Distance
{
  return Distance::fromMeters(static_cast<Distance::value_type>(value));
}

constexpr auto operator"" _m(unsigned long long value) -> Distance
{
  return Distance::fromMeters(static_cast<Distance::value_type>(value));
}

constexpr auto operator"" _mm(long double value) -> Distance
{
  return Distance::fromMillimeters(static_cast<Distance::value_type>(value));
}

constexpr auto operator"" _mm(unsigned long long value) -> Distance
{
  return Distance::fromMillimeters(static_cast<Distance::value_type>(value));
}

} // namespace literals

} // namespace sick

namespace std {

// NOLINTNEXTLINE(readability-identifier-naming): to_string is standard library style
auto SDK_EXPORT to_string(sick::Distance const& distance) -> std::string;

} // namespace std

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
