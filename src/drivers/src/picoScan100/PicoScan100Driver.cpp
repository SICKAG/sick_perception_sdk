/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/drivers/picoScan100/PicoScan100Driver.hpp>

#include <sick_perception_sdk/compact_format/PointCloud/PointCloudConfiguration.hpp>
#include <sick_perception_sdk/drivers/picoScan100/EncoderReceiver.hpp>
#include <sick_perception_sdk/drivers/picoScan100/ImuReceiver.hpp>
#include <sick_perception_sdk/drivers/picoScan100/ScanDataReceiver.hpp>

#include <cstdint>
#include <optional>
#include <utility>

namespace sick::picoScan100 {

auto Config::create() -> Config
{
  return {};
}

auto Config::configureScanDataReceiver(ScanDataReceiverConfig config) -> Config&
{
  m_scanData = std::move(config);
  return *this;
}

auto Config::configureScanDataReceiver(
  std::uint16_t receiverPort,
  ScanDataReceiverConfig::UnorganizedPointCloudCallback callback,
  point_cloud::PointCloudConfiguration const& pointCloudConfiguration
) -> Config&
{
  if (!m_scanData)
  {
    m_scanData = ScanDataReceiverConfig::create();
  }
  m_scanData->setReceiverPort(receiverPort).setOnNewFrameCallback(std::move(callback), pointCloudConfiguration);
  return *this;
}

auto Config::configureScanDataReceiver(std::uint16_t receiverPort, ScanDataReceiverConfig::ScanDataCallback callback) -> Config&
{
  if (!m_scanData)
  {
    m_scanData = ScanDataReceiverConfig::create();
  }
  m_scanData->setReceiverPort(receiverPort).setOnNewSegmentCallback(std::move(callback));
  return *this;
}

auto Config::configureImuReceiver(ImuReceiverConfig config) -> Config&
{
  m_imu = std::move(config);
  return *this;
}

auto Config::configureImuReceiver(std::uint16_t receiverPort, ImuReceiverConfig::DataCallback callback) -> Config&
{
  if (!m_imu)
  {
    m_imu = ImuReceiverConfig::create();
  }
  m_imu->setReceiverPort(receiverPort).setOnNewDataCallback(std::move(callback));
  return *this;
}

auto Config::configureEncoderReceiver(EncoderReceiverConfig config) -> Config&
{
  m_encoder = std::move(config);
  return *this;
}

auto Config::configureEncoderReceiver(std::uint16_t receiverPort, EncoderReceiverConfig::DataCallback callback) -> Config&
{
  if (!m_encoder)
  {
    m_encoder = EncoderReceiverConfig::create();
  }
  m_encoder->setReceiverPort(receiverPort).setOnNewDataCallback(std::move(callback));
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

auto Config::encoder() const -> std::optional<EncoderReceiverConfig> const&
{
  return m_encoder;
}

Driver::Driver(Config const& config)
{
  if (config.scanData())
  {
    m_scanDataReceiver.emplace(*config.scanData());
  }
  if (config.imu())
  {
    m_imuReceiver.emplace(*config.imu());
  }
  if (config.encoder())
  {
    m_encoderReceiver.emplace(*config.encoder());
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
  if (m_encoderReceiver)
  {
    m_encoderReceiver->start();
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
  if (m_encoderReceiver)
  {
    m_encoderReceiver->stop();
  }
}

} // namespace sick::picoScan100
