/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/quantities/Timestamp.hpp>

#include <ostream>
#include <string>

namespace sick {

auto operator<<(std::ostream& stream, sick::Timestamp const& timestamp) -> std::ostream&
{
  return stream << timestamp.microsecondsSinceEpoch() << " microseconds since epoch";
}

} // namespace sick

namespace std {

// NOLINTNEXTLINE(readability-identifier-naming): to_string is standard library style
auto to_string(sick::Timestamp const& timestamp) -> std::string
{
  return std::to_string(timestamp.microsecondsSinceEpoch()) + " microseconds since epoch";
}

} // namespace std
