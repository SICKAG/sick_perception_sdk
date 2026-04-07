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
class SDK_EXPORT Temperature
{
public:
  using value_type = float;

  constexpr Temperature()
    : m_degreesCelsius(std::numeric_limits<value_type>::quiet_NaN())
  { }

  constexpr static auto fromDegreesCelsius(value_type degreesCelsius) -> Temperature
  {
    return Temperature(degreesCelsius);
  }

  constexpr auto degreesCelsius() const -> value_type
  {
    return m_degreesCelsius;
  }

private:
  value_type m_degreesCelsius;

  constexpr explicit Temperature(value_type degreesCelsius)
    : m_degreesCelsius {degreesCelsius}
  { }
};

// Stream operators
auto SDK_EXPORT operator<<(std::ostream& stream, Temperature const& temperature) -> std::ostream&;

namespace literals {

constexpr auto operator"" _degC(long double value) -> Temperature
{
  return Temperature::fromDegreesCelsius(static_cast<Temperature::value_type>(value));
}

constexpr auto operator"" _degC(unsigned long long value) -> Temperature
{
  return Temperature::fromDegreesCelsius(static_cast<Temperature::value_type>(value));
}

} // namespace literals

} // namespace sick

namespace std {

// NOLINTNEXTLINE(readability-identifier-naming): to_string is standard library style
auto SDK_EXPORT to_string(sick::Temperature const& temperature) -> std::string;

} // namespace std

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
