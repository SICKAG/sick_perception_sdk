/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/quantities/Acceleration.hpp>

#include <ostream>
#include <string>

namespace sick {

auto operator<<(std::ostream& stream, Acceleration const& acceleration) -> std::ostream&
{
  return stream << acceleration.metersPerSecondSquared() << " m/s²";
}

} // namespace sick

namespace std {

// NOLINTNEXTLINE(readability-identifier-naming): to_string is standard library style
auto to_string(sick::Acceleration const& acceleration) -> std::string
{
  return std::to_string(acceleration.metersPerSecondSquared()) + " m/s²";
}

} // namespace std
