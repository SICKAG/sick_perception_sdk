/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/quantities/Speed.hpp>

#include <ostream>

namespace sick {

auto operator<<(std::ostream& stream, sick::Speed const& speed) -> std::ostream&
{
  return stream << speed.metersPerSecond() << " m/s";
}

} // namespace sick
