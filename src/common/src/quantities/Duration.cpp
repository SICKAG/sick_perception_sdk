/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/quantities/Duration.hpp>

#include <ostream>
#include <string>

namespace sick {

auto operator<<(std::ostream& stream, sick::Duration const& duration) -> std::ostream&
{
  return stream << duration.microseconds() << " microseconds";
}

} // namespace sick

namespace std {

// NOLINTNEXTLINE(readability-identifier-naming): to_string is standard library style
auto to_string(sick::Duration const& duration) -> std::string
{
  return std::to_string(duration.microseconds()) + " microseconds";
}

} // namespace std
