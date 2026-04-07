/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/quantities/Temperature.hpp>

#include <ostream>
#include <string>

namespace sick {

auto operator<<(std::ostream& stream, sick::Temperature const& temperature) -> std::ostream&
{
  return stream << temperature.degreesCelsius() << " degC";
}

} // namespace sick

namespace std {

auto to_string(sick::Temperature const& temperature) -> std::string
{
  return std::to_string(temperature.degreesCelsius()) + " degC";
}

} // namespace std
