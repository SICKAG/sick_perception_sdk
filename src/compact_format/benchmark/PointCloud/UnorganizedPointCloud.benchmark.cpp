/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/telegram_type_6_multiScan200/PointCloudConverter.hpp>

#include "../../test/utils/TestParams.hpp"
#include "../benchmark_tools.hpp"
#include <sick_perception_sdk/compact_format/PointCloud/UnorganizedPointCloud.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_6_multiScan200/MultiScan200Parser.hpp>

#include <benchmark/benchmark.h>
#include <memory>

using namespace sick::compact;
using namespace sick::compact::multiscan200;

class UnorganizedPointCloudBenchmark : public ::benchmark::Fixture
{
protected:
  std::unique_ptr<sick::point_cloud::UnorganizedPointCloud> m_pointCloud;

  void SetUp(benchmark::State const& state) override
  {
    std::string const fileName = "telegram_type_6_multiScan270_profile_12_full-frame_0.bin";
    auto const rawData         = sick::benchmark::readBinary("data/" + fileName);
    auto const rawDataView     = sick::ByteView(rawData);

    constexpr bool validateChecksum = true;
    auto const data                 = sick::compact::multiscan200::Parser::validateAndParse(rawDataView, validateChecksum);

    sick::point_cloud::PointCloudConfiguration config;
    config.fields.enableCartesian   = true;
    config.fields.enableSpherical   = true;
    config.fields.enableIntensity   = true;
    config.fields.enableTimeOffset  = true;
    config.fields.enableRing        = true;
    config.fields.enableLayerIndex  = true;
    config.fields.enableColumnIndex = true;
    config.fields.enableEchoIndex   = true;
    config.fields.enableProperties  = true;
    config.fields.enablePulseWidth  = false;

    sick::compact::multiscan200::PointCloudConverter converter {config};
    m_pointCloud = std::make_unique<sick::point_cloud::UnorganizedPointCloud>(converter.convertToUnorganized(data));
  }
};

BENCHMARK_DEFINE_F(UnorganizedPointCloudBenchmark, getCartesian_first_point)(benchmark::State& state)
{
  constexpr std::size_t pointIndex = 0;
  auto const& pointCloud           = *m_pointCloud;
  for (auto _ : state)
  {
    benchmark::DoNotOptimize(pointCloud.getCartesian(pointIndex));
  }
}

BENCHMARK_DEFINE_F(UnorganizedPointCloudBenchmark, getCartesian_last_point)(benchmark::State& state)
{
  std::size_t const pointIndex = m_pointCloud->numberOfPoints() - 1;
  auto const& pointCloud       = *m_pointCloud;
  for (auto _ : state)
  {
    benchmark::DoNotOptimize(pointCloud.getCartesian(pointIndex));
  }
}

BENCHMARK_DEFINE_F(UnorganizedPointCloudBenchmark, getCartesian)(benchmark::State& state)
{
  state.SetLabel(std::to_string(m_pointCloud->numberOfPoints()) + " points");
  auto const& pointCloud = *m_pointCloud;
  for (auto _ : state)
  {
    for (std::size_t i = 0; i < pointCloud.numberOfPoints(); ++i)
    {
      benchmark::DoNotOptimize(pointCloud.getCartesian(i));
    }
  }
}

BENCHMARK_DEFINE_F(UnorganizedPointCloudBenchmark, getAllFields)(benchmark::State& state)
{
  state.SetLabel(std::to_string(m_pointCloud->numberOfPoints()) + " points");
  auto const& pointCloud = *m_pointCloud;
  for (auto _ : state)
  {
    for (std::size_t i = 0; i < pointCloud.numberOfPoints(); ++i)
    {
      benchmark::DoNotOptimize(pointCloud.getCartesian(i));
      benchmark::DoNotOptimize(pointCloud.getSpherical(i));
      benchmark::DoNotOptimize(pointCloud.getIntensity(i));
      benchmark::DoNotOptimize(pointCloud.getTimeOffset(i));
      benchmark::DoNotOptimize(pointCloud.getRing(i));
      benchmark::DoNotOptimize(pointCloud.getLayerIndex(i));
      benchmark::DoNotOptimize(pointCloud.getEchoIndex(i));
      benchmark::DoNotOptimize(pointCloud.getColumnIndex(i));
      benchmark::DoNotOptimize(pointCloud.getProperties(i));
    }
  }
}

BENCHMARK_REGISTER_F(UnorganizedPointCloudBenchmark, getCartesian_first_point);
BENCHMARK_REGISTER_F(UnorganizedPointCloudBenchmark, getCartesian_last_point);
BENCHMARK_REGISTER_F(UnorganizedPointCloudBenchmark, getCartesian);
BENCHMARK_REGISTER_F(UnorganizedPointCloudBenchmark, getAllFields);
