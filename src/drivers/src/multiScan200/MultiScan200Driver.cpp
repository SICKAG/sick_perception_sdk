/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/drivers/multiScan200/MultiScan200Driver.hpp>

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudConfiguration.hpp>
#include <sick_perception_sdk/drivers/multiScan200/AmbientLightReceiver.hpp>
#include <sick_perception_sdk/drivers/multiScan200/ImuReceiver.hpp>
#include <sick_perception_sdk/drivers/multiScan200/ScanDataReceiver.hpp>

#include <cstdint>
#include <optional>
#include <utility>

namespace sick::multiScan200 {

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

auto Config::configureScanDataReceiver(
  std::uint16_t sensorPort,
  ScanDataReceiverConfig::OrganizedPointCloudCallback callback,
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

auto Config::configureImuReceiver(ImuReceiverConfig config) -> Config&
{
  m_imu = std::move(config);
  return *this;
}

auto Config::configureImuReceiver(std::uint16_t sensorPort, ImuReceiverConfig::DataCallback callback) -> Config&
{
  if (!m_imu)
  {
    m_imu = ImuReceiverConfig::create();
  }
  m_imu->setSensorPort(sensorPort).setOnNewDataCallback(std::move(callback));
  return *this;
}

auto Config::configureAmbientLightReceiver(AmbientLightReceiverConfig config) -> Config&
{
  m_ambientLight = std::move(config);
  return *this;
}

auto Config::configureAmbientLightReceiver(std::uint16_t sensorPort, AmbientLightReceiverConfig::DataCallback callback) -> Config&
{
  if (!m_ambientLight)
  {
    m_ambientLight = AmbientLightReceiverConfig::create();
  }
  m_ambientLight->setSensorPort(sensorPort).setOnNewDataCallback(std::move(callback));
  return *this;
}

auto Config::scanData() const -> std::optional<ScanDataReceiverConfig> const&
{
  return m_scanData;
}

auto Config::imu() const -> std::optional<ImuReceiverConfig> const&
{
  return m_imu;
}

auto Config::ambientLight() const -> std::optional<AmbientLightReceiverConfig> const&
{
  return m_ambientLight;
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
  if (config.imu())
  {
    m_imuReceiver.emplace(config.sensorAddress(), *config.imu());
  }
  if (config.ambientLight())
  {
    m_ambientLightReceiver.emplace(config.sensorAddress(), *config.ambientLight());
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
  if (m_imuReceiver)
  {
    m_imuReceiver->start();
  }
  if (m_ambientLightReceiver)
  {
    m_ambientLightReceiver->start();
  }
}

void Driver::stop()
{
  if (m_scanDataReceiver)
  {
    m_scanDataReceiver->stop();
  }
  if (m_imuReceiver)
  {
    m_imuReceiver->stop();
  }
  if (m_ambientLightReceiver)
  {
    m_ambientLightReceiver->stop();
  }
}

} // namespace sick::multiScan200
