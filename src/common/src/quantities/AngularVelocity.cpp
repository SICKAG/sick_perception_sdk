/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/quantities/AngularVelocity.hpp>

#include <ostream>

namespace sick {

auto operator<<(std::ostream& stream, sick::AngularVelocity const& angularVelocity) -> std::ostream&
{
  return stream << angularVelocity.radiansPerSecond() << " rad/s";
}

} // namespace sick
