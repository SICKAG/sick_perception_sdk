/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/version.hpp>

#include <gtest/gtest.h>
#include <string>

TEST(VersionTest, built_executable_does_not_contain_default_version)
{
  std::string const ver = sick::version();
  EXPECT_NE("0.0.0-invalid", ver);
}
