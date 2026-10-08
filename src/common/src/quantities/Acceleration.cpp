/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/quantities/Acceleration.hpp>

#include <ostream>

namespace sick {

auto operator<<(std::ostream& stream, Acceleration const& acceleration) -> std::ostream&
{
  return stream << acceleration.metersPerSecondSquared() << " m/s²";
}

} // namespace sick

