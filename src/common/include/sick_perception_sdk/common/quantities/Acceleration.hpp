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
class SDK_EXPORT Acceleration
{
public:
  using value_type = float;

  constexpr Acceleration()
    : m_metersPerSecondSquared(std::numeric_limits<value_type>::quiet_NaN())
  { }

  constexpr static auto fromMetersPerSecondSquared(float metersPerSecondSquared) -> Acceleration
  {
    return Acceleration(metersPerSecondSquared);
  }

  constexpr auto metersPerSecondSquared() const -> float
  {
    return m_metersPerSecondSquared;
  }

private:
  float m_metersPerSecondSquared;

  constexpr explicit Acceleration(float metersPerSecondSquared)
    : m_metersPerSecondSquared(metersPerSecondSquared)
  { }
};

auto SDK_EXPORT operator<<(std::ostream& stream, Acceleration const& acceleration) -> std::ostream&;

} // namespace sick

namespace std {

// NOLINTNEXTLINE(readability-identifier-naming): to_string is standard library style
auto SDK_EXPORT to_string(sick::Acceleration const& acceleration) -> std::string;

} // namespace std
