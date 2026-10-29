/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/drivers/LRS4000/LRS4000Driver.hpp>

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudConfiguration.hpp>
#include <sick_perception_sdk/drivers/LRS4000/ScanDataReceiver.hpp>

#include <cstdint>
#include <optional>
#include <utility>

namespace sick::LRS4000 {

auto Config::create(IpV4Address sensorAddress) -> Config
{
  return Config(sensorAddress);
}

Config::Config(IpV4Address sensorAddress)
  : m_sensorAddress(sensorAddress)
{ }

auto Config::configureScanDataReceiver(ScanDataReceiverConfig config) -> Config&
{
  m_scanData = std::move(config);
  return *this;
}

auto Config::configureScanDataReceiver(
  std::uint16_t sensorPort,
  ScanDataReceiverConfig::UnorganizedPointCloudCallback callback,
  point_cloud::PointCloudConfiguration const& pointCloudConfiguration
) -> Config&
{
  if (!m_scanData)
  {
    m_scanData = ScanDataReceiverConfig::create();
  }
  m_scanData->setSensorPort(sensorPort).setOnNewFrameCallback(std::move(callback), pointCloudConfiguration);
  return *this;
}

auto Config::configureScanDataReceiver(std::uint16_t sensorPort, ScanDataReceiverConfig::ScanDataCallback callback) -> Config&
{
  if (!m_scanData)
  {
    m_scanData = ScanDataReceiverConfig::create();
  }
  m_scanData->setSensorPort(sensorPort).setOnNewFrameCallback(std::move(callback));
  return *this;
}

auto Config::scanData() const -> std::optional<ScanDataReceiverConfig> const&
{
  return m_scanData;
}

auto Config::sensorAddress() const -> IpV4Address const&
{
  return m_sensorAddress;
}

Driver::Driver(Config const& config)
{
  if (config.scanData())
  {
    m_scanDataReceiver.emplace(config.sensorAddress(), *config.scanData());
  }
}

Driver::~Driver()
{
  stop();
}

void Driver::run()
{
  if (m_scanDataReceiver)
  {
    m_scanDataReceiver->start();
  }
}

void Driver::stop()
{
  if (m_scanDataReceiver)
  {
    m_scanDataReceiver->stop();
  }
}

} // namespace sick::LRS4000
