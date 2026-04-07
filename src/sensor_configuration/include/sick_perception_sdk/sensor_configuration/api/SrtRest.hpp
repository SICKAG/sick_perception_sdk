/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/quantities/Angle.hpp>

namespace sick {

constexpr auto angleToSopas(Angle const& angle)
{
  return static_cast<std::int32_t>(angle.degrees() * 10'000.0f); // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
}

constexpr auto sopasToAngle(std::int32_t sopas)
{
  return Angle::fromDegrees(static_cast<float>(sopas) / 10'000.0f); // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
}

} // namespace sick
