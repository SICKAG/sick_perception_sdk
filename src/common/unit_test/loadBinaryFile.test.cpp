/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/loadBinaryFile.hpp>

#include <cstdint>
#include <filesystem>
#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>

// Set in main() from argv[0]; points at this very test executable.
extern char const* g_testExecutablePath;

TEST(LoadBinaryFileTest, loadBinary_file_with_existing_file_returns_its_bytes)
{
  ASSERT_NE(g_testExecutablePath, nullptr);

  auto const data = sick::loadBinaryFile(g_testExecutablePath);

  EXPECT_FALSE(data.empty());
  EXPECT_EQ(data.size(), std::filesystem::file_size(g_testExecutablePath));
}

TEST(LoadBinaryFileTest, loadBinary_file_with_missing_file_throws)
{
  EXPECT_THROW(sick::loadBinaryFile("does_not_exist_a1b2c3.bin"), std::runtime_error);
}
