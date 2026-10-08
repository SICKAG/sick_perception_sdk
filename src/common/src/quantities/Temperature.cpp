/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/quantities/Temperature.hpp>

#include <ostream>

namespace sick {

auto operator<<(std::ostream& stream, sick::Temperature const& temperature) -> std::ostream&
{
  return stream << temperature.degreesCelsius() << " degC";
}

} // namespace sick
