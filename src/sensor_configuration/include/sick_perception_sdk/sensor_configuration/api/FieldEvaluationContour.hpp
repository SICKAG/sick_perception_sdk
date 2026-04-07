/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/quantities/Distance.hpp>

#include <vector>

namespace sick {

struct FieldEvaluationContour
{
  struct Point
  {
    Distance x = Distance::fromMeters(0.0f);
    Distance y = Distance::fromMeters(0.0f);
  };

  int evaluationId     = -1;
  Distance lowerZLimit = Distance::fromMeters(0.0f);
  Distance upperZLimit = Distance::fromMeters(0.0f);
  std::vector<Point> points;
};

} // namespace sick
