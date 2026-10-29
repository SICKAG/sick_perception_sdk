/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/drivers/Receiver/UdpScanDataReceiver.hpp>

#include <gtest/gtest.h>

#include <chrono>
#include <exception>
#include <stdexcept>

using namespace std::chrono_literals;
using sick::compact::UdpScanDataReceiverConfig;

namespace {

void noScanData(sick::compact::scan_data::ScanData const& /*unused*/)
{ }

void noPointCloud(sick::point_cloud::UnorganizedPointCloud const& /*unused*/)
{ }

void noDataLoss(sick::compact::LossCounts const& /*unused*/)
{ }

} // namespace

TEST(UdpScanDataReceiverConfigTest, create_uses_the_default_values)
{
  auto const config = UdpScanDataReceiverConfig::create();

  EXPECT_EQ(config.transport().port, UdpScanDataReceiverConfig::kDefaultPort);
  EXPECT_EQ(config.transport().firstDataTimeout, sick::compact::receiver_defaults::kFirstDataTimeout);
  EXPECT_EQ(config.transport().newDataTimeout, sick::compact::receiver_defaults::kNewDataTimeout);
  EXPECT_EQ(config.transport().receiveBufferSize, sick::compact::receiver_defaults::kUdpReceiveBufferSize);
  EXPECT_FALSE(config.multicast().has_value());
  EXPECT_TRUE(config.onError());
  EXPECT_EQ(config.loggerName(), "ScanDataReceiver");
}

TEST(UdpScanDataReceiverConfigTest, default_on_error_rethrows_the_exception)
{
  auto const config = UdpScanDataReceiverConfig::create();

  EXPECT_THROW(config.onError()(std::make_exception_ptr(std::runtime_error("boom"))), std::runtime_error);
}

TEST(UdpScanDataReceiverConfigTest, create_has_no_callbacks)
{
  auto const config = UdpScanDataReceiverConfig::create();

  EXPECT_FALSE(config.callbacks().dataLoss.has_value());
  EXPECT_FALSE(config.callbacks().onNewSegment.has_value());
  EXPECT_FALSE(config.callbacks().framePointCloud.has_value());
  EXPECT_FALSE(config.callbacks().segmentPointCloud.has_value());
}

TEST(UdpScanDataReceiverConfigTest, create_sets_the_port)
{
  EXPECT_EQ(UdpScanDataReceiverConfig::create(4711).transport().port, 4711);
}

TEST(UdpScanDataReceiverConfigTest, set_receiver_port_changes_only_the_port)
{
  auto config = UdpScanDataReceiverConfig::create(4711).setTimeouts(5s, 2s).setLoggerName("logger");

  config.setReceiverPort(4712);

  EXPECT_EQ(config.transport().port, 4712);
  EXPECT_EQ(config.transport().firstDataTimeout, 5s);
  EXPECT_EQ(config.transport().newDataTimeout, 2s);
  EXPECT_EQ(config.loggerName(), "logger");
}

TEST(UdpScanDataReceiverConfigTest, set_timeouts_changes_only_the_timeouts)
{
  auto config = UdpScanDataReceiverConfig::create(4711);

  config.setTimeouts(5s, 2s);

  EXPECT_EQ(config.transport().port, 4711);
  EXPECT_EQ(config.transport().firstDataTimeout, 5s);
  EXPECT_EQ(config.transport().newDataTimeout, 2s);
  EXPECT_EQ(config.transport().receiveBufferSize, sick::compact::receiver_defaults::kUdpReceiveBufferSize);
}

TEST(UdpScanDataReceiverConfigTest, set_receive_buffer_size_changes_only_the_buffer_size)
{
  auto config = UdpScanDataReceiverConfig::create(4711);

  config.setReceiveBufferSize(1234);

  EXPECT_EQ(config.transport().receiveBufferSize, 1234U);
  EXPECT_EQ(config.transport().port, 4711);
}

TEST(UdpScanDataReceiverConfigTest, set_multicast_stores_both_addresses)
{
  auto config = UdpScanDataReceiverConfig::create();

  config.setMulticast(sick::IpV4Address {"239.1.2.3"}, sick::IpV4Address {"192.168.0.100"});

  ASSERT_TRUE(config.multicast().has_value());
  EXPECT_EQ(config.multicast()->groupAddress.toString(), "239.1.2.3");
  EXPECT_EQ(config.multicast()->localInterfaceAddress.toString(), "192.168.0.100");
}

TEST(UdpScanDataReceiverConfigTest, set_on_error_stores_the_callback)
{
  auto config = UdpScanDataReceiverConfig::create();

  config.setOnError([](std::exception_ptr const& /*unused*/) { });

  EXPECT_TRUE(config.onError());
}

TEST(UdpScanDataReceiverConfigTest, set_logger_name_stores_the_name)
{
  auto config = UdpScanDataReceiverConfig::create();

  config.setLoggerName("my_logger");

  EXPECT_EQ(config.loggerName(), "my_logger");
}

TEST(UdpScanDataReceiverConfigTest, segment_scan_data_callback_sets_only_on_new_segment)
{
  auto config = UdpScanDataReceiverConfig::create();

  config.setOnNewSegmentCallback(noScanData);

  EXPECT_TRUE(config.callbacks().onNewSegment.has_value());
  EXPECT_FALSE(config.callbacks().segmentPointCloud.has_value());
  EXPECT_FALSE(config.callbacks().framePointCloud.has_value());
}

TEST(UdpScanDataReceiverConfigTest, segment_point_cloud_callback_sets_only_the_segment_point_cloud)
{
  auto config = UdpScanDataReceiverConfig::create();

  config.setOnNewSegmentCallback(noPointCloud);

  EXPECT_TRUE(config.callbacks().segmentPointCloud.has_value());
  EXPECT_FALSE(config.callbacks().onNewSegment.has_value());
  EXPECT_FALSE(config.callbacks().framePointCloud.has_value());
}

TEST(UdpScanDataReceiverConfigTest, frame_point_cloud_callback_sets_only_the_frame_point_cloud)
{
  auto config = UdpScanDataReceiverConfig::create();

  config.setOnNewFrameCallback(noPointCloud);

  EXPECT_TRUE(config.callbacks().framePointCloud.has_value());
  EXPECT_FALSE(config.callbacks().onNewSegment.has_value());
  EXPECT_FALSE(config.callbacks().segmentPointCloud.has_value());
}

TEST(UdpScanDataReceiverConfigTest, data_loss_monitor_sets_only_the_data_loss_callback)
{
  auto config = UdpScanDataReceiverConfig::create();

  config.setDataLossMonitor(sick::compact::scan_data::DataLossMonitor(1, 1), noDataLoss);

  EXPECT_TRUE(config.callbacks().dataLoss.has_value());
  EXPECT_FALSE(config.callbacks().onNewSegment.has_value());
  EXPECT_FALSE(config.callbacks().framePointCloud.has_value());
  EXPECT_FALSE(config.callbacks().segmentPointCloud.has_value());
}

TEST(UdpScanDataReceiverConfigTest, all_callbacks_can_be_set_at_the_same_time)
{
  auto config = UdpScanDataReceiverConfig::create();

  config.setOnNewSegmentCallback(noScanData)
    .setOnNewSegmentCallback(noPointCloud)
    .setOnNewFrameCallback(noPointCloud)
    .setDataLossMonitor(sick::compact::scan_data::DataLossMonitor(1, 1), noDataLoss);

  EXPECT_TRUE(config.callbacks().onNewSegment.has_value());
  EXPECT_TRUE(config.callbacks().segmentPointCloud.has_value());
  EXPECT_TRUE(config.callbacks().framePointCloud.has_value());
  EXPECT_TRUE(config.callbacks().dataLoss.has_value());
}
