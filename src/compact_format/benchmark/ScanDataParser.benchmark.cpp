/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanDataParser.hpp>

#include "../test/utils/TestParams.hpp"
#include "benchmark_tools.hpp"

#include <benchmark/benchmark.h>

static std::vector<std::string> const deviceNames = {
  "LRS4000",      //
  "multiScan100", //
  "picoScan100",  //
};

static std::vector<std::string> const testFiles = {
  "LRS4581_scan-frame_0.bin",              //
  "multiScan136_scan-frame_0.bin",         //
  "picoScan150_profile1_scan-frame_0.bin", //
};

class ScanDataParserBenchmark : public ::benchmark::Fixture
{
protected:
  ScanDataParserBenchmark()
  { }
};

BENCHMARK_DEFINE_F(ScanDataParserBenchmark, validateAndParse)(benchmark::State& state)
{
  auto const file_idx  = state.range(0);
  auto const& fileName = testFiles[file_idx];

  constexpr bool validateChecksum = true;
  auto const data                 = sick::benchmark::readBinary("data/" + fileName);

  // Set the label to show the device name
  state.SetLabel(deviceNames[file_idx]);

  for (auto _ : state)
  {
    benchmark::DoNotOptimize(sick::compact::scan_data::Parser::validateAndParse(data, validateChecksum));
  }
}

// Register the benchmark with one argument per device file
static void RegisterBenchmarks(benchmark::internal::Benchmark* b)
{
  for (size_t i = 0; i < testFiles.size(); ++i)
  {
    b->Args({static_cast<int64_t>(i)});
  }
}

BENCHMARK_REGISTER_F(ScanDataParserBenchmark, validateAndParse)->Apply(RegisterBenchmarks);
