/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/drivers/LRS4000/LRS4000Driver.hpp>

#include <gtest/gtest.h>

#include <chrono>
#include <exception>
#include <stdexcept>

using namespace std::chrono_literals;
using sick::LRS4000::Config;
using sick::LRS4000::ScanDataReceiverConfig;

namespace {

void noScanData(sick::compact::scan_data::ScanData const& /*unused*/)
{ }

void noPointCloud(sick::point_cloud::UnorganizedPointCloud const& /*unused*/)
{ }

} // namespace

TEST(LRS4000ScanDataReceiverConfigTest, create_uses_the_default_values)
{
  auto const config = ScanDataReceiverConfig::create();

  EXPECT_EQ(config.transport().port, ScanDataReceiverConfig::kDefaultPort);
  EXPECT_EQ(config.transport().receiveBufferSize, sick::compact::receiver_defaults::kTcpReceiveBufferSize);
  EXPECT_FALSE(config.callbacks().onNewData.has_value());
  EXPECT_FALSE(config.callbacks().pointCloud.has_value());
  EXPECT_TRUE(config.onError());
}

TEST(LRS4000ScanDataReceiverConfigTest, default_on_error_rethrows_the_exception)
{
  auto const config = ScanDataReceiverConfig::create();

  EXPECT_THROW(config.onError()(std::make_exception_ptr(std::runtime_error("boom"))), std::runtime_error);
}

TEST(LRS4000ScanDataReceiverConfigTest, set_on_error_overrides_the_default_callback)
{
  auto config = ScanDataReceiverConfig::create();

  config.setOnError([](std::exception_ptr const& /*unused*/) { });

  EXPECT_NO_THROW(config.onError()(std::make_exception_ptr(std::runtime_error("boom"))));
}

TEST(LRS4000ScanDataReceiverConfigTest, create_with_port_stores_the_port)
{
  auto const config = ScanDataReceiverConfig::create(4711);

  EXPECT_EQ(config.transport().port, 4711);
}

TEST(LRS4000ScanDataReceiverConfigTest, set_sensor_port_changes_only_the_port)
{
  auto config = ScanDataReceiverConfig::create(4711).setTimeouts(5s, 2s);

  config.setSensorPort(4712);

  EXPECT_EQ(config.transport().port, 4712);
  EXPECT_EQ(config.transport().firstDataTimeout, 5s);
}

TEST(LRS4000ScanDataReceiverConfigTest, frame_callbacks_are_stored_independently)
{
  auto config = ScanDataReceiverConfig::create();

  config.setOnNewFrameCallback(noScanData);
  EXPECT_TRUE(config.callbacks().onNewData.has_value());
  EXPECT_FALSE(config.callbacks().pointCloud.has_value());

  config.setOnNewFrameCallback(noPointCloud);
  EXPECT_TRUE(config.callbacks().onNewData.has_value());
  EXPECT_TRUE(config.callbacks().pointCloud.has_value());
}

TEST(LRS4000ConfigTest, create_stores_the_sensor_address_and_configures_no_receiver)
{
  auto const config = Config::create(sick::IpV4Address {"192.168.0.1"});

  EXPECT_EQ(config.sensorAddress().toString(), "192.168.0.1");
  EXPECT_FALSE(config.scanData().has_value());
}

TEST(LRS4000ConfigTest, configure_scan_data_replaces_an_existing_configuration)
{
  auto config = Config::create(sick::IpV4Address {"192.168.0.1"});
  config.configureScanDataReceiver(ScanDataReceiverConfig::create(4711).setOnNewFrameCallback(noScanData));

  config.configureScanDataReceiver(ScanDataReceiverConfig::create(4712));

  EXPECT_EQ(config.scanData()->transport().port, 4712);
  EXPECT_FALSE(config.scanData()->callbacks().onNewData.has_value());
}

TEST(LRS4000ConfigTest, point_cloud_shortcut_creates_a_configuration)
{
  auto config = Config::create(sick::IpV4Address {"192.168.0.1"});

  config.configureScanDataReceiver(4711, noPointCloud);

  ASSERT_TRUE(config.scanData().has_value());
  EXPECT_EQ(config.scanData()->transport().port, 4711);
  EXPECT_TRUE(config.scanData()->callbacks().pointCloud.has_value());
  EXPECT_FALSE(config.scanData()->callbacks().onNewData.has_value());
}

TEST(LRS4000ConfigTest, scan_data_shortcut_creates_a_configuration)
{
  auto config = Config::create(sick::IpV4Address {"192.168.0.1"});

  config.configureScanDataReceiver(4711, noScanData);

  ASSERT_TRUE(config.scanData().has_value());
  EXPECT_EQ(config.scanData()->transport().port, 4711);
  EXPECT_TRUE(config.scanData()->callbacks().onNewData.has_value());
  EXPECT_FALSE(config.scanData()->callbacks().pointCloud.has_value());
}

TEST(LRS4000ConfigTest, scan_data_shortcuts_can_be_combined)
{
  auto config = Config::create(sick::IpV4Address {"192.168.0.1"});

  config.configureScanDataReceiver(4711, noPointCloud).configureScanDataReceiver(4711, noScanData);

  EXPECT_TRUE(config.scanData()->callbacks().pointCloud.has_value());
  EXPECT_TRUE(config.scanData()->callbacks().onNewData.has_value());
}

TEST(LRS4000ConfigTest, scan_data_shortcut_keeps_the_other_settings_of_an_existing_configuration)
{
  auto config = Config::create(sick::IpV4Address {"192.168.0.1"});
  config.configureScanDataReceiver(
    ScanDataReceiverConfig::create(4711).setTimeouts(5s, 2s).setReceiveBufferSize(1234).setLoggerName("logger").setOnNewFrameCallback(noScanData)
  );

  config.configureScanDataReceiver(4712, noPointCloud);

  auto const& scanData = *config.scanData();
  EXPECT_EQ(scanData.transport().port, 4712);
  EXPECT_EQ(scanData.transport().firstDataTimeout, 5s);
  EXPECT_EQ(scanData.transport().newDataTimeout, 2s);
  EXPECT_EQ(scanData.transport().receiveBufferSize, 1234U);
  EXPECT_EQ(scanData.loggerName(), "logger");
  EXPECT_TRUE(scanData.callbacks().onNewData.has_value());
  EXPECT_TRUE(scanData.callbacks().pointCloud.has_value());
}
