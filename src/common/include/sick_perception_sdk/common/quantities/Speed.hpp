/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>

#include <limits>
#include <ostream>
#include <string>

namespace sick {

/**
 * @ingroup Quantities
 * 
 * See quantities.hpp for an overview.
 */
class SDK_EXPORT Speed
{
public:
  using value_type = float;

  constexpr Speed()
    : m_metersPerSecond(std::numeric_limits<value_type>::quiet_NaN())
  { }

  constexpr static auto fromMetersPerSecond(value_type metersPerSecond) -> Speed
  {
    return Speed(metersPerSecond);
  }

  constexpr auto metersPerSecond() const -> value_type
  {
    return m_metersPerSecond;
  }

private:
  value_type m_metersPerSecond;

  constexpr explicit Speed(value_type metersPerSecond)
    : m_metersPerSecond {metersPerSecond}
  { }
};

auto SDK_EXPORT operator<<(std::ostream& stream, Speed const& speed) -> std::ostream&;

} // namespace sick

namespace std {

// NOLINTNEXTLINE(readability-identifier-naming): to_string is standard library style
auto SDK_EXPORT to_string(sick::Speed const& speed) -> std::string;

} // namespace std
