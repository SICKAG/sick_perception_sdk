/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

// NOLINTBEGIN(misc-non-private-member-variables-in-classes)

#pragma once

#include <sick_perception_sdk/common/quantities/Angle.hpp>
#include <sick_perception_sdk/common/quantities/Distance.hpp>

#include <string>

namespace sick {

struct SensorPosition
{
  Distance x  = Distance::fromMeters(0.0f);
  Distance y  = Distance::fromMeters(0.0f);
  Distance z  = Distance::fromMeters(0.0f);
  Angle yaw   = Angle::fromDegrees(0.0f);
  Angle pitch = Angle::fromDegrees(0.0f);
  Angle roll  = Angle::fromDegrees(0.0f);

  auto toString() const -> std::string
  {
    return "x: " + std::to_string(x) + ", y: " + std::to_string(y) + ", z: " + std::to_string(z) + ", yaw: " + std::to_string(yaw) +
           ", pitch: " + std::to_string(pitch) + ", roll: " + std::to_string(roll);
  }
};

} // namespace sick

// NOLINTEND(misc-non-private-member-variables-in-classes)
