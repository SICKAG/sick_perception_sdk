/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/ByteView.hpp>

#include <benchmark/benchmark.h>

#include <algorithm>
#include <cstdint>
#include <numeric>
#include <vector>

namespace {

// Test data sizes for benchmarking
constexpr std::size_t kSmallSize  = 64;
constexpr std::size_t kMediumSize = 1024;
constexpr std::size_t kLargeSize  = 64 * 1024;

auto createTestData(std::size_t size) -> std::vector<std::uint8_t>
{
  std::vector<std::uint8_t> data(size);
  std::iota(data.begin(), data.end(), static_cast<std::uint8_t>(0));
  return data;
}

static void BM_ByteView_At(benchmark::State& state)
{
  auto const data = createTestData(static_cast<std::size_t>(state.range(0)));
  sick::ByteView const view(data);
  std::size_t idx = 0;

  for (auto _ : state)
  {
    benchmark::DoNotOptimize(view.at(idx));
    idx = (idx + 1) % view.size();
  }
  state.SetBytesProcessed(static_cast<int64_t>(state.iterations()));
}

static void BM_ByteView_Subview(benchmark::State& state)
{
  auto const data = createTestData(static_cast<std::size_t>(state.range(0)));
  sick::ByteView const view(data);
  std::size_t const offset = view.size() / 4;
  std::size_t const count  = view.size() / 2;

  for (auto _ : state)
  {
    benchmark::DoNotOptimize(view.subview(offset, count));
  }
}

static void BM_ByteView_First(benchmark::State& state)
{
  auto const data = createTestData(static_cast<std::size_t>(state.range(0)));
  sick::ByteView const view(data);
  std::size_t const count = view.size() / 2;

  for (auto _ : state)
  {
    benchmark::DoNotOptimize(view.first(count));
  }
}

static void BM_ByteView_Last(benchmark::State& state)
{
  auto const data = createTestData(static_cast<std::size_t>(state.range(0)));
  sick::ByteView const view(data);
  std::size_t const count = view.size() / 2;

  for (auto _ : state)
  {
    benchmark::DoNotOptimize(view.last(count));
  }
}

static void BM_ByteView_ToVector(benchmark::State& state)
{
  auto const data = createTestData(static_cast<std::size_t>(state.range(0)));
  sick::ByteView const view(data);

  for (auto _ : state)
  {
    benchmark::DoNotOptimize(view.toVector());
  }
  state.SetBytesProcessed(static_cast<int64_t>(state.iterations()) * state.range(0));
}

static void BM_ByteView_Iterate(benchmark::State& state)
{
  auto const data = createTestData(static_cast<std::size_t>(state.range(0)));
  sick::ByteView const view(data);

  for (auto _ : state)
  {
    std::uint64_t sum = 0;
    for (auto const byte : view)
    {
      sum += byte;
    }
    benchmark::DoNotOptimize(sum);
  }
  state.SetBytesProcessed(static_cast<int64_t>(state.iterations()) * state.range(0));
}

static void BM_ByteView_ChainedSubviews(benchmark::State& state)
{
  auto const data = createTestData(static_cast<std::size_t>(state.range(0)));
  sick::ByteView const view(data);

  for (auto _ : state)
  {
    auto sub1 = view.subview(10);
    auto sub2 = sub1.first(sub1.size() - 20);
    auto sub3 = sub2.last(sub2.size() / 2);
    benchmark::DoNotOptimize(sub3);
  }
}

// Register ByteView (cpp) benchmarks
BENCHMARK(BM_ByteView_At)->Arg(kSmallSize)->Arg(kMediumSize)->Arg(kLargeSize);
BENCHMARK(BM_ByteView_Subview)->Arg(kSmallSize)->Arg(kMediumSize)->Arg(kLargeSize);
BENCHMARK(BM_ByteView_First)->Arg(kSmallSize)->Arg(kMediumSize)->Arg(kLargeSize);
BENCHMARK(BM_ByteView_Last)->Arg(kSmallSize)->Arg(kMediumSize)->Arg(kLargeSize);
BENCHMARK(BM_ByteView_ToVector)->Arg(kSmallSize)->Arg(kMediumSize)->Arg(kLargeSize);
BENCHMARK(BM_ByteView_Iterate)->Arg(kSmallSize)->Arg(kMediumSize)->Arg(kLargeSize);
BENCHMARK(BM_ByteView_ChainedSubviews)->Arg(kMediumSize)->Arg(kLargeSize);

} // namespace
