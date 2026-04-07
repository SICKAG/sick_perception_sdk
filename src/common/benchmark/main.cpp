/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <benchmark/benchmark.h>
#include <filesystem>
#include <iostream>

int main(int argc, char** argv)
{
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
