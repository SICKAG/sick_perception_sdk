/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/quantities/Angle.hpp>

#include <cmath>
#include <ostream>

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
