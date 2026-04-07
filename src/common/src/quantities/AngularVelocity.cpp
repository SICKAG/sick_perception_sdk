/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/quantities/AngularVelocity.hpp>

#include <ostream>
#include <string>

namespace sick {

auto operator<<(std::ostream& stream, sick::AngularVelocity const& angularVelocity) -> std::ostream&
{
  return stream << angularVelocity.radiansPerSecond() << " rad/s";
}

} // namespace sick

namespace std {

// NOLINTNEXTLINE(readability-identifier-naming): to_string is standard library style
auto to_string(sick::AngularVelocity const& angularVelocity) -> std::string
{
  return std::to_string(angularVelocity.radiansPerSecond()) + " rad/s";
}

} // namespace std
