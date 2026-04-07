/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/quantities/Speed.hpp>

#include <ostream>
#include <string>

namespace sick {

auto operator<<(std::ostream& stream, sick::Speed const& speed) -> std::ostream&
{
  return stream << speed.metersPerSecond() << " m/s";
}

} // namespace sick

namespace std {

auto to_string(sick::Speed const& speed) -> std::string
{
  return std::to_string(speed.metersPerSecond()) + " m/s";
}

} // namespace std
