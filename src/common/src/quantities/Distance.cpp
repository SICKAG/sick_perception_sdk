/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/quantities/Distance.hpp>

#include <ostream>

namespace sick {

auto operator<<(std::ostream& stream, sick::Distance const& distance) -> std::ostream&
{
  return stream << distance.meters() << " meters";
}

} // namespace sick
