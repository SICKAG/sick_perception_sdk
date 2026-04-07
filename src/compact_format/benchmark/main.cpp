/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include "benchmark_tools.hpp"

#include <benchmark/benchmark.h>
#include <filesystem>
#include <iostream>

static std::filesystem::path gBenchmarkExecutablePath;

auto getBenchmarkExecutablePath() -> std::filesystem::path
{
  return gBenchmarkExecutablePath;
}

int main(int argc, char** argv)
{
  // Store the executable path for use in benchmarks
  gBenchmarkExecutablePath = std::filesystem::absolute(argv[0]).remove_filename();

  // Initialize and run benchmarks
  ::benchmark::Initialize(&argc, argv);
  if (::benchmark::ReportUnrecognizedArguments(argc, argv))
  {
    return 1;
  }
  ::benchmark::RunSpecifiedBenchmarks();
  ::benchmark::Shutdown();
  return 0;
}
