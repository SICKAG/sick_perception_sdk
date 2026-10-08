/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/drivers/multiScan200/MultiScan200Driver.hpp>

#include <sick_perception_sdk/common/IpV4Address.hpp>
#include <sick_perception_sdk/compact_format/PointCloud/PointCloudConfiguration.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_2_imu_legacy/ImuData.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_3_ambient_light/AmbientLightData.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_6_multiScan200/DataLossMonitor.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_6_multiScan200/MultiScan200Data.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_6_multiScan200/PointCloudConverter.hpp>

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <functional>
#include <utility>

namespace sick::multiScan200 {

Driver::Driver(IpV4Address sensorAddress, std::function<void(std::exception_ptr const&)> const& onError)
  : m_ambientLightReceiver(sensorAddress, onError, "AmbientLightReceiver")
  , m_imuReceiver(sensorAddress, onError, "ImuReceiver")
  , m_scanDataReceiver(sensorAddress, onError, "ScanDataReceiver")
{ }

Driver::~Driver()
{
  stop();
}

void Driver::run()
{
  m_ambientLightReceiver.start();
  m_imuReceiver.start();
  m_scanDataReceiver.start();
}

void Driver::stop()
{
  m_ambientLightReceiver.stop();
  m_imuReceiver.stop();
  m_scanDataReceiver.stop();
}

// --------------------------------------------------------------
// AmbientLightDataReceiver
// --------------------------------------------------------------

Driver::AmbientLightReceiver::AmbientLightReceiver(IpV4Address sensorAddress, BaseT::ErrorCallback onError, std::string loggerName)
  : BaseT(std::move(onError), std::move(loggerName))
  , m_sensorAddress(sensorAddress)
{ }

auto Driver::AmbientLightReceiver::setup(
  std::uint16_t sensorPort,
  std::chrono::milliseconds firstDataTimeout,
  std::chrono::milliseconds newDataTimeout,
  std::size_t receiveBufferSize
) -> AmbientLightReceiver&
{
  BaseT::setup(
    [this](compact::ambient_light::AmbientLightData const& data) -> void {
      if (m_callback.has_value())
      {
        (*m_callback)(data);
      }
    },
    m_sensorAddress,
    sensorPort,
    firstDataTimeout,
    newDataTimeout,
    receiveBufferSize
  );
  return *this;
}

auto Driver::AmbientLightReceiver::setOnNewDataCallback(DataCallback callback) -> AmbientLightReceiver&
{
  m_callback = std::move(callback);
  return *this;
}

// --------------------------------------------------------------
// ImuReceiver
// --------------------------------------------------------------

Driver::ImuReceiver::ImuReceiver(IpV4Address sensorAddress, BaseT::ErrorCallback onError, std::string loggerName)
  : BaseT(std::move(onError), std::move(loggerName))
  , m_sensorAddress(sensorAddress)
{ }

auto Driver::ImuReceiver::setup(
  std::uint16_t sensorPort,
  std::chrono::milliseconds firstDataTimeout,
  std::chrono::milliseconds newDataTimeout,
  std::size_t receiveBufferSize
) -> ImuReceiver&
{
  BaseT::setup(
    [this](compact::imu::ImuData const& data) -> void {
      if (m_callback.has_value())
      {
        (*m_callback)(data);
      }
    },
    m_sensorAddress,
    sensorPort,
    firstDataTimeout,
    newDataTimeout,
    receiveBufferSize
  );
  return *this;
}

auto Driver::ImuReceiver::setOnNewDataCallback(DataCallback callback) -> ImuReceiver&
{
  m_callback = std::move(callback);
  return *this;
}

// --------------------------------------------------------------
// ScanDataReceiver
// --------------------------------------------------------------

Driver::ScanDataReceiver::ScanDataReceiver(IpV4Address sensorAddress, BaseT::ErrorCallback onError, std::string loggerName)
  : BaseT(std::move(onError), std::move(loggerName))
  , m_sensorAddress(sensorAddress)
{ }

auto Driver::ScanDataReceiver::setup(
  std::uint16_t sensorPort,
  std::chrono::milliseconds firstDataTimeout,
  std::chrono::milliseconds newDataTimeout,
  std::size_t receiveBufferSize
) -> ScanDataReceiver&
{
  BaseT::setup(
    [this](compact::multiscan200::MultiScan200Data const& data) -> void {
      this->multiplexScanData(data);
    },
    m_sensorAddress,
    sensorPort,
    firstDataTimeout,
    newDataTimeout,
    receiveBufferSize
  );
  return *this;
}

void Driver::ScanDataReceiver::multiplexScanData(compact::multiscan200::MultiScan200Data const& data)
{
  if (m_dataLoss)
  {
    try
    {
      auto& [monitor, callback] = *m_dataLoss;
      auto const lossCounts     = monitor.check(data);
      if ((lossCounts.numberOfLostFrames != 0) || (lossCounts.numberOfLostTelegrams != 0) || (lossCounts.numberOfLostSegments != 0))
      {
        callback(lossCounts);
      }
    }
    catch (std::exception_ptr const& exception)
    {
      m_onError(exception);
    }
  }
  if (m_onNewData)
  {
    (*m_onNewData)(data);
  }
  if (m_organizedPointCloud)
  {
    auto& [converter, callback] = *m_organizedPointCloud;
    callback(converter.convertToOrganized(data));
  }
  if (m_unorganizedPointCloud)
  {
    auto& [converter, callback] = *m_unorganizedPointCloud;
    callback(converter.convertToUnorganized(data));
  }
}

auto Driver::ScanDataReceiver::setDataLossMonitor(compact::multiscan200::DataLossMonitor monitor, DataLossCallback callback) -> ScanDataReceiver&
{
  m_dataLoss = std::make_pair(std::move(monitor), std::move(callback));
  return *this;
}

auto Driver::ScanDataReceiver::setOnNewFrameCallback(ScanDataCallback callback) -> ScanDataReceiver&
{
  m_onNewData = std::move(callback);
  return *this;
}

auto Driver::ScanDataReceiver::setOnNewFrameCallback(OrganizedPointCloudCallback callback, point_cloud::PointCloudConfiguration const& pointCloudConfiguration)
  -> ScanDataReceiver&
{
  m_organizedPointCloud = std::make_pair(compact::multiscan200::PointCloudConverter(pointCloudConfiguration), std::move(callback));
  return *this;
}

auto Driver::ScanDataReceiver::setOnNewFrameCallback(
  UnorganizedPointCloudCallback callback,
  point_cloud::PointCloudConfiguration const& pointCloudConfiguration
) -> ScanDataReceiver&
{
  m_unorganizedPointCloud = std::make_pair(compact::multiscan200::PointCloudConverter(pointCloudConfiguration), std::move(callback));
  return *this;
}

} // namespace sick::multiScan200
