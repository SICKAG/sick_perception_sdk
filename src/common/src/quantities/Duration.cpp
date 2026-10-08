/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/quantities/Duration.hpp>

#include <ostream>

namespace sick {

auto operator<<(std::ostream& stream, sick::Duration const& duration) -> std::ostream&
{
  return stream << duration.microseconds() << " microseconds";
}

} // namespace sick
