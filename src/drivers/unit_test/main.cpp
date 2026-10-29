/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/logging/logging.hpp>

#include <gtest/gtest.h>

auto main(int argc, char** argv) -> int
{
  sick::Log::init(sick::LogLevel::Warning);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
