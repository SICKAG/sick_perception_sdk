/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/drivers/multiScan200/MultiScan200Driver.hpp>

#include <gtest/gtest.h>

#include <chrono>
#include <exception>
#include <stdexcept>

using namespace std::chrono_literals;
using sick::multiScan200::AmbientLightReceiverConfig;
using sick::multiScan200::Config;
using sick::multiScan200::ImuReceiverConfig;
using sick::multiScan200::ScanDataReceiverConfig;

namespace {

void noScanData(sick::compact::multiscan200::MultiScan200Data const& /*unused*/)
{ }

void noOrganizedPointCloud(sick::point_cloud::OrganizedPointCloud const& /*unused*/)
{ }

void unorganizedPointCloudFunction(sick::point_cloud::UnorganizedPointCloud const& /*unused*/)
{ }

// A plain function would also convert to the organized callback type, which makes the overloads ambiguous.
auto const noUnorganizedPointCloud = ScanDataReceiverConfig::UnorganizedPointCloudCallback {unorganizedPointCloudFunction};

void noImuData(sick::compact::imu::ImuData const& /*unused*/)
{ }

void noAmbientLightData(sick::compact::ambient_light::AmbientLightData const& /*unused*/)
{ }

} // namespace

TEST(MultiScan200ScanDataReceiverConfigTest, create_uses_the_default_values)
{
  auto const config = ScanDataReceiverConfig::create();

  EXPECT_EQ(config.transport().port, ScanDataReceiverConfig::kDefaultPort);
  EXPECT_EQ(config.transport().receiveBufferSize, sick::compact::receiver_defaults::kTcpReceiveBufferSize);
  EXPECT_FALSE(config.callbacks().onNewData.has_value());
  EXPECT_FALSE(config.callbacks().organizedPointCloud.has_value());
  EXPECT_FALSE(config.callbacks().unorganizedPointCloud.has_value());
  EXPECT_TRUE(config.onError());
}

TEST(MultiScan200ScanDataReceiverConfigTest, default_on_error_rethrows_the_exception)
{
  auto const config = ScanDataReceiverConfig::create();

  EXPECT_THROW(config.onError()(std::make_exception_ptr(std::runtime_error("boom"))), std::runtime_error);
}

TEST(MultiScan200ScanDataReceiverConfigTest, set_sensor_port_changes_only_the_port)
{
  auto config = ScanDataReceiverConfig::create(4711).setTimeouts(5s, 2s);

  config.setSensorPort(4712);

  EXPECT_EQ(config.transport().port, 4712);
  EXPECT_EQ(config.transport().firstDataTimeout, 5s);
}

TEST(MultiScan200ScanDataReceiverConfigTest, frame_callbacks_are_stored_independently)
{
  auto config = ScanDataReceiverConfig::create();

  config.setOnNewFrameCallback(noScanData);
  EXPECT_TRUE(config.callbacks().onNewData.has_value());
  EXPECT_FALSE(config.callbacks().organizedPointCloud.has_value());
  EXPECT_FALSE(config.callbacks().unorganizedPointCloud.has_value());

  config.setOnNewFrameCallback(noOrganizedPointCloud);
  EXPECT_TRUE(config.callbacks().organizedPointCloud.has_value());
  EXPECT_FALSE(config.callbacks().unorganizedPointCloud.has_value());

  config.setOnNewFrameCallback(noUnorganizedPointCloud);
  EXPECT_TRUE(config.callbacks().unorganizedPointCloud.has_value());
}

TEST(MultiScan200ImuReceiverConfigTest, set_sensor_port_changes_only_the_port)
{
  auto config = ImuReceiverConfig::create(4711).setTimeouts(5s, 2s);

  config.setSensorPort(4712);

  EXPECT_EQ(config.transport().port, 4712);
  EXPECT_EQ(config.transport().firstDataTimeout, 5s);
}

TEST(MultiScan200ImuReceiverConfigTest, default_on_error_rethrows_the_exception)
{
  auto const config = ImuReceiverConfig::create();

  EXPECT_TRUE(config.onError());
  EXPECT_THROW(config.onError()(std::make_exception_ptr(std::runtime_error("boom"))), std::runtime_error);
}

TEST(MultiScan200AmbientLightReceiverConfigTest, set_sensor_port_changes_only_the_port)
{
  auto config = AmbientLightReceiverConfig::create(4711).setTimeouts(5s, 2s);

  config.setSensorPort(4712);

  EXPECT_EQ(config.transport().port, 4712);
  EXPECT_EQ(config.transport().firstDataTimeout, 5s);
}

TEST(MultiScan200AmbientLightReceiverConfigTest, default_on_error_rethrows_the_exception)
{
  auto const config = AmbientLightReceiverConfig::create();

  EXPECT_TRUE(config.onError());
  EXPECT_THROW(config.onError()(std::make_exception_ptr(std::runtime_error("boom"))), std::runtime_error);
}

TEST(MultiScan200ConfigTest, create_stores_the_sensor_address_and_configures_no_receiver)
{
  auto const config = Config::create(sick::IpV4Address {"192.168.0.1"});

  EXPECT_EQ(config.sensorAddress().toString(), "192.168.0.1");
  EXPECT_FALSE(config.scanData().has_value());
  EXPECT_FALSE(config.imu().has_value());
  EXPECT_FALSE(config.ambientLight().has_value());
}

TEST(MultiScan200ConfigTest, configure_scan_data_replaces_an_existing_configuration)
{
  auto config = Config::create(sick::IpV4Address {"192.168.0.1"});
  config.configureScanDataReceiver(ScanDataReceiverConfig::create(4711).setOnNewFrameCallback(noScanData));

  config.configureScanDataReceiver(ScanDataReceiverConfig::create(4712));

  EXPECT_EQ(config.scanData()->transport().port, 4712);
  EXPECT_FALSE(config.scanData()->callbacks().onNewData.has_value());
}

TEST(MultiScan200ConfigTest, unorganized_point_cloud_shortcut_creates_a_configuration)
{
  auto config = Config::create(sick::IpV4Address {"192.168.0.1"});

  config.configureScanDataReceiver(4711, noUnorganizedPointCloud);

  ASSERT_TRUE(config.scanData().has_value());
  EXPECT_EQ(config.scanData()->transport().port, 4711);
  EXPECT_TRUE(config.scanData()->callbacks().unorganizedPointCloud.has_value());
  EXPECT_FALSE(config.scanData()->callbacks().organizedPointCloud.has_value());
  EXPECT_FALSE(config.scanData()->callbacks().onNewData.has_value());
}

TEST(MultiScan200ConfigTest, organized_point_cloud_shortcut_creates_a_configuration)
{
  auto config = Config::create(sick::IpV4Address {"192.168.0.1"});

  config.configureScanDataReceiver(4711, noOrganizedPointCloud);

  ASSERT_TRUE(config.scanData().has_value());
  EXPECT_TRUE(config.scanData()->callbacks().organizedPointCloud.has_value());
  EXPECT_FALSE(config.scanData()->callbacks().unorganizedPointCloud.has_value());
  EXPECT_FALSE(config.scanData()->callbacks().onNewData.has_value());
}

TEST(MultiScan200ConfigTest, scan_data_shortcut_creates_a_configuration)
{
  auto config = Config::create(sick::IpV4Address {"192.168.0.1"});

  config.configureScanDataReceiver(4711, noScanData);

  ASSERT_TRUE(config.scanData().has_value());
  EXPECT_TRUE(config.scanData()->callbacks().onNewData.has_value());
  EXPECT_FALSE(config.scanData()->callbacks().organizedPointCloud.has_value());
  EXPECT_FALSE(config.scanData()->callbacks().unorganizedPointCloud.has_value());
}

TEST(MultiScan200ConfigTest, scan_data_shortcuts_can_be_combined)
{
  auto config = Config::create(sick::IpV4Address {"192.168.0.1"});

  config.configureScanDataReceiver(4711, noOrganizedPointCloud)
    .configureScanDataReceiver(4711, noUnorganizedPointCloud)
    .configureScanDataReceiver(4711, noScanData);

  EXPECT_EQ(config.scanData()->transport().port, 4711);
  EXPECT_TRUE(config.scanData()->callbacks().organizedPointCloud.has_value());
  EXPECT_TRUE(config.scanData()->callbacks().unorganizedPointCloud.has_value());
  EXPECT_TRUE(config.scanData()->callbacks().onNewData.has_value());
}

TEST(MultiScan200ConfigTest, scan_data_shortcut_keeps_the_other_settings_of_an_existing_configuration)
{
  auto config = Config::create(sick::IpV4Address {"192.168.0.1"});
  config.configureScanDataReceiver(
    ScanDataReceiverConfig::create(4711).setTimeouts(5s, 2s).setReceiveBufferSize(1234).setLoggerName("logger").setOnNewFrameCallback(noScanData)
  );

  config.configureScanDataReceiver(4712, noOrganizedPointCloud);

  auto const& scanData = *config.scanData();
  EXPECT_EQ(scanData.transport().port, 4712);
  EXPECT_EQ(scanData.transport().firstDataTimeout, 5s);
  EXPECT_EQ(scanData.transport().newDataTimeout, 2s);
  EXPECT_EQ(scanData.transport().receiveBufferSize, 1234U);
  EXPECT_EQ(scanData.loggerName(), "logger");
  EXPECT_TRUE(scanData.callbacks().onNewData.has_value());
  EXPECT_TRUE(scanData.callbacks().organizedPointCloud.has_value());
}

TEST(MultiScan200ConfigTest, scan_data_shortcut_does_not_touch_the_other_receivers)
{
  auto config = Config::create(sick::IpV4Address {"192.168.0.1"});
  config.configureImuReceiver(4712, noImuData).configureAmbientLightReceiver(4713, noAmbientLightData);

  config.configureScanDataReceiver(4711, noUnorganizedPointCloud);

  EXPECT_EQ(config.imu()->transport().port, 4712);
  EXPECT_EQ(config.ambientLight()->transport().port, 4713);
}

TEST(MultiScan200ConfigTest, imu_shortcut_keeps_the_other_settings_of_an_existing_configuration)
{
  auto config = Config::create(sick::IpV4Address {"192.168.0.1"});
  config.configureImuReceiver(ImuReceiverConfig::create(4712).setTimeouts(5s, 2s).setLoggerName("logger"));

  config.configureImuReceiver(4713, noImuData);

  EXPECT_EQ(config.imu()->transport().port, 4713);
  EXPECT_EQ(config.imu()->transport().firstDataTimeout, 5s);
  EXPECT_EQ(config.imu()->loggerName(), "logger");
  EXPECT_TRUE(config.imu()->dataCallback());
}

TEST(MultiScan200ConfigTest, ambient_light_shortcut_keeps_the_other_settings_of_an_existing_configuration)
{
  auto config = Config::create(sick::IpV4Address {"192.168.0.1"});
  config.configureAmbientLightReceiver(AmbientLightReceiverConfig::create(4712).setTimeouts(5s, 2s).setLoggerName("logger"));

  config.configureAmbientLightReceiver(4713, noAmbientLightData);

  EXPECT_EQ(config.ambientLight()->transport().port, 4713);
  EXPECT_EQ(config.ambientLight()->transport().firstDataTimeout, 5s);
  EXPECT_EQ(config.ambientLight()->loggerName(), "logger");
  EXPECT_TRUE(config.ambientLight()->dataCallback());
}
