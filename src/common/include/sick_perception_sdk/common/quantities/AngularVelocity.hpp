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
class SDK_EXPORT AngularVelocity
{
public:
  using value_type = float;

  constexpr AngularVelocity()
    : m_radiansPerSecond(std::numeric_limits<AngularVelocity::value_type>::quiet_NaN())
  { }

  constexpr static auto fromRadiansPerSecond(value_type radiansPerSecond) -> AngularVelocity
  {
    return AngularVelocity(radiansPerSecond);
  }

  constexpr auto radiansPerSecond() const -> value_type
  {
    return m_radiansPerSecond;
  }

private:
  value_type m_radiansPerSecond;

  constexpr explicit AngularVelocity(value_type radPerSecond)
    : m_radiansPerSecond {radPerSecond}
  { }
};

auto SDK_EXPORT operator<<(std::ostream& stream, AngularVelocity const& angularVelocity) -> std::ostream&;

} // namespace sick

namespace std {

// NOLINTNEXTLINE(readability-identifier-naming): to_string is standard library style
auto SDK_EXPORT to_string(sick::AngularVelocity const& angularVelocity) -> std::string;

} // namespace std
