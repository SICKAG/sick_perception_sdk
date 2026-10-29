/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/drivers/picoScan100/PicoScan100Driver.hpp>

#include <gtest/gtest.h>

#include <chrono>
#include <exception>
#include <stdexcept>

using namespace std::chrono_literals;
using sick::picoScan100::Config;
using sick::picoScan100::EncoderReceiverConfig;
using sick::picoScan100::ImuReceiverConfig;
using sick::picoScan100::ScanDataReceiverConfig;

namespace {

void noScanData(sick::compact::scan_data::ScanData const& /*unused*/)
{ }

void noPointCloud(sick::point_cloud::UnorganizedPointCloud const& /*unused*/)
{ }

void noImuData(sick::compact::imu::ImuData const& /*unused*/)
{ }

void noEncoderData(sick::compact::encoder::EncoderData const& /*unused*/)
{ }

} // namespace

TEST(PicoScan100EncoderReceiverConfigTest, create_uses_the_default_values)
{
  auto const config = EncoderReceiverConfig::create();

  EXPECT_EQ(config.transport().port, EncoderReceiverConfig::kDefaultPort);
  EXPECT_TRUE(config.onError());
}

TEST(PicoScan100EncoderReceiverConfigTest, default_on_error_rethrows_the_exception)
{
  auto const config = EncoderReceiverConfig::create();

  EXPECT_THROW(config.onError()(std::make_exception_ptr(std::runtime_error("boom"))), std::runtime_error);
}

TEST(PicoScan100ConfigTest, create_configures_no_receiver)
{
  auto const config = Config::create();

  EXPECT_FALSE(config.scanData().has_value());
  EXPECT_FALSE(config.imu().has_value());
  EXPECT_FALSE(config.encoder().has_value());
}

TEST(PicoScan100ConfigTest, configure_scan_data_replaces_an_existing_configuration)
{
  auto config = Config::create();
  config.configureScanDataReceiver(ScanDataReceiverConfig::create(4711).setOnNewSegmentCallback(noScanData));

  config.configureScanDataReceiver(ScanDataReceiverConfig::create(4712));

  EXPECT_EQ(config.scanData()->transport().port, 4712);
  EXPECT_FALSE(config.scanData()->callbacks().onNewSegment.has_value());
}

TEST(PicoScan100ConfigTest, frame_point_cloud_shortcut_creates_a_configuration)
{
  auto config = Config::create();

  config.configureScanDataReceiver(4711, noPointCloud);

  ASSERT_TRUE(config.scanData().has_value());
  EXPECT_EQ(config.scanData()->transport().port, 4711);
  EXPECT_TRUE(config.scanData()->callbacks().framePointCloud.has_value());
  EXPECT_FALSE(config.scanData()->callbacks().segmentPointCloud.has_value());
  EXPECT_FALSE(config.scanData()->callbacks().onNewSegment.has_value());
}

TEST(PicoScan100ConfigTest, segment_scan_data_shortcut_creates_a_configuration)
{
  auto config = Config::create();

  config.configureScanDataReceiver(4711, noScanData);

  ASSERT_TRUE(config.scanData().has_value());
  EXPECT_EQ(config.scanData()->transport().port, 4711);
  EXPECT_TRUE(config.scanData()->callbacks().onNewSegment.has_value());
  EXPECT_FALSE(config.scanData()->callbacks().framePointCloud.has_value());
  EXPECT_FALSE(config.scanData()->callbacks().segmentPointCloud.has_value());
}

TEST(PicoScan100ConfigTest, scan_data_shortcuts_can_be_combined)
{
  auto config = Config::create();

  config.configureScanDataReceiver(4711, noPointCloud).configureScanDataReceiver(4711, noScanData);

  EXPECT_EQ(config.scanData()->transport().port, 4711);
  EXPECT_TRUE(config.scanData()->callbacks().framePointCloud.has_value());
  EXPECT_TRUE(config.scanData()->callbacks().onNewSegment.has_value());
}

TEST(PicoScan100ConfigTest, scan_data_shortcut_keeps_the_other_settings_of_an_existing_configuration)
{
  auto config = Config::create();
  config.configureScanDataReceiver(
    ScanDataReceiverConfig::create(4711)
      .setTimeouts(5s, 2s)
      .setReceiveBufferSize(1234)
      .setMulticast(sick::IpV4Address {"239.1.2.3"}, sick::IpV4Address {"192.168.0.100"})
      .setLoggerName("logger")
      .setOnNewSegmentCallback(noScanData)
  );

  config.configureScanDataReceiver(4712, noPointCloud);

  auto const& scanData = *config.scanData();
  EXPECT_EQ(scanData.transport().port, 4712);
  EXPECT_EQ(scanData.transport().firstDataTimeout, 5s);
  EXPECT_EQ(scanData.transport().newDataTimeout, 2s);
  EXPECT_EQ(scanData.transport().receiveBufferSize, 1234U);
  ASSERT_TRUE(scanData.multicast().has_value());
  EXPECT_EQ(scanData.loggerName(), "logger");
  EXPECT_TRUE(scanData.callbacks().onNewSegment.has_value());
  EXPECT_TRUE(scanData.callbacks().framePointCloud.has_value());
}

TEST(PicoScan100ConfigTest, scan_data_shortcut_does_not_touch_the_other_receivers)
{
  auto config = Config::create();
  config.configureImuReceiver(4712, noImuData).configureEncoderReceiver(4713, noEncoderData);

  config.configureScanDataReceiver(4711, noPointCloud);

  EXPECT_EQ(config.imu()->transport().port, 4712);
  EXPECT_EQ(config.encoder()->transport().port, 4713);
}

TEST(PicoScan100ConfigTest, imu_shortcut_keeps_the_other_settings_of_an_existing_configuration)
{
  auto config = Config::create();
  config.configureImuReceiver(ImuReceiverConfig::create(4712).setTimeouts(5s, 2s).setLoggerName("logger"));

  config.configureImuReceiver(4713, noImuData);

  EXPECT_EQ(config.imu()->transport().port, 4713);
  EXPECT_EQ(config.imu()->transport().firstDataTimeout, 5s);
  EXPECT_EQ(config.imu()->loggerName(), "logger");
  EXPECT_TRUE(config.imu()->dataCallback());
}

TEST(PicoScan100ConfigTest, encoder_shortcut_creates_a_configuration)
{
  auto config = Config::create();

  config.configureEncoderReceiver(4713, noEncoderData);

  ASSERT_TRUE(config.encoder().has_value());
  EXPECT_EQ(config.encoder()->transport().port, 4713);
  EXPECT_TRUE(config.encoder()->dataCallback());
}

TEST(PicoScan100ConfigTest, encoder_shortcut_keeps_the_other_settings_of_an_existing_configuration)
{
  auto config = Config::create();
  config.configureEncoderReceiver(EncoderReceiverConfig::create(4713).setTimeouts(5s, 2s).setLoggerName("logger"));

  config.configureEncoderReceiver(4714, noEncoderData);

  EXPECT_EQ(config.encoder()->transport().port, 4714);
  EXPECT_EQ(config.encoder()->transport().firstDataTimeout, 5s);
  EXPECT_EQ(config.encoder()->loggerName(), "logger");
  EXPECT_TRUE(config.encoder()->dataCallback());
}
