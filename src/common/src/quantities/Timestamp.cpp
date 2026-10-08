/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/quantities/Timestamp.hpp>

#include <ostream>

namespace sick {

auto operator<<(std::ostream& stream, sick::Timestamp const& timestamp) -> std::ostream&
{
  return stream << timestamp.microsecondsSinceEpoch() << " microseconds since epoch";
}

} // namespace sick
