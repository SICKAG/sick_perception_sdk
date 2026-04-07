/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include "utils/test_config.hpp"
#include <sick_perception_sdk/common/logging/logging.hpp>

#include <filesystem>
#include <gtest/gtest.h>

static std::filesystem::path gExecutablePath;

auto getExecutablePath() -> std::filesystem::path
{
  return gExecutablePath;
}

auto main(int argc, char** argv) -> int
{
  sick::Log::init(sick::LogLevel::Warning);
  gExecutablePath = std::filesystem::absolute(argv[0]).remove_filename();
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
