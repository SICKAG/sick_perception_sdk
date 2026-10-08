/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

namespace sick::compact {

struct LossCounts
{
  int numberOfLostTelegrams = 0;
  int numberOfLostFrames    = 0;
  int numberOfLostSegments  = 0;

  auto operator+=(LossCounts const& other) -> LossCounts&
  {
    numberOfLostTelegrams += other.numberOfLostTelegrams;
    numberOfLostFrames += other.numberOfLostFrames;
    numberOfLostSegments += other.numberOfLostSegments;
    return *this;
  }
};

} // namespace sick::compact
