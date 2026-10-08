/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <gtest/gtest.h>

// Path to this test executable, captured from argv[0] so tests can read a file that is
// guaranteed to exist without creating temporary files.
char const* g_testExecutablePath = nullptr;

auto main(int argc, char** argv) -> int
{
  g_testExecutablePath = argv[0];
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
