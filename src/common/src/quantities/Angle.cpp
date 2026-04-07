/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/quantities/Angle.hpp>

#include <cmath>
#include <ostream>
#include <string>

namespace sick {

auto operator<<(std::ostream& stream, sick::Angle const& angle) -> std::ostream&
{
  return stream << angle.radians() << " rad";
}

auto sin(Angle const& angle) -> float
{
  return std::sin(angle.radians());
}

auto cos(Angle const& angle) -> float
{
  return std::cos(angle.radians());
}

} // namespace sick

namespace std {

// NOLINTNEXTLINE(readability-identifier-naming): to_string is standard library style
auto to_string(sick::Angle const& angle) -> std::string
{
  return std::to_string(angle.radians()) + " rad";
}

} // namespace std
