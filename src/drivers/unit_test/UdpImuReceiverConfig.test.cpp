/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/drivers/Receiver/UdpImuReceiver.hpp>

#include <gtest/gtest.h>

#include <chrono>
#include <exception>
#include <stdexcept>

using namespace std::chrono_literals;
using sick::compact::UdpImuReceiverConfig;

TEST(UdpImuReceiverConfigTest, create_uses_the_default_values)
{
  auto const config = UdpImuReceiverConfig::create();

  EXPECT_EQ(config.transport().port, UdpImuReceiverConfig::kDefaultPort);
  EXPECT_EQ(config.transport().firstDataTimeout, sick::compact::receiver_defaults::kFirstDataTimeout);
  EXPECT_EQ(config.transport().newDataTimeout, sick::compact::receiver_defaults::kNewDataTimeout);
  EXPECT_EQ(config.transport().receiveBufferSize, sick::compact::receiver_defaults::kUdpReceiveBufferSize);
  EXPECT_FALSE(config.multicast().has_value());
  EXPECT_FALSE(config.dataCallback());
  EXPECT_TRUE(config.onError());
  EXPECT_EQ(config.loggerName(), "ImuReceiver");
}

TEST(UdpImuReceiverConfigTest, default_on_error_rethrows_the_exception)
{
  auto const config = UdpImuReceiverConfig::create();

  EXPECT_THROW(config.onError()(std::make_exception_ptr(std::runtime_error("boom"))), std::runtime_error);
}

TEST(UdpImuReceiverConfigTest, create_sets_the_port)
{
  EXPECT_EQ(UdpImuReceiverConfig::create(4711).transport().port, 4711);
}

TEST(UdpImuReceiverConfigTest, set_receiver_port_changes_only_the_port)
{
  auto config = UdpImuReceiverConfig::create(4711).setTimeouts(5s, 2s).setLoggerName("logger");

  config.setReceiverPort(4712);

  EXPECT_EQ(config.transport().port, 4712);
  EXPECT_EQ(config.transport().firstDataTimeout, 5s);
  EXPECT_EQ(config.transport().newDataTimeout, 2s);
  EXPECT_EQ(config.loggerName(), "logger");
}

TEST(UdpImuReceiverConfigTest, set_timeouts_changes_only_the_timeouts)
{
  auto config = UdpImuReceiverConfig::create(4711);

  config.setTimeouts(5s, 2s);

  EXPECT_EQ(config.transport().port, 4711);
  EXPECT_EQ(config.transport().firstDataTimeout, 5s);
  EXPECT_EQ(config.transport().newDataTimeout, 2s);
}

TEST(UdpImuReceiverConfigTest, set_receive_buffer_size_stores_the_size)
{
  auto config = UdpImuReceiverConfig::create();

  config.setReceiveBufferSize(1234);

  EXPECT_EQ(config.transport().receiveBufferSize, 1234U);
}

TEST(UdpImuReceiverConfigTest, set_multicast_stores_both_addresses)
{
  auto config = UdpImuReceiverConfig::create();

  config.setMulticast(sick::IpV4Address {"239.1.2.3"}, sick::IpV4Address {"192.168.0.100"});

  ASSERT_TRUE(config.multicast().has_value());
  EXPECT_EQ(config.multicast()->groupAddress.toString(), "239.1.2.3");
  EXPECT_EQ(config.multicast()->localInterfaceAddress.toString(), "192.168.0.100");
}

TEST(UdpImuReceiverConfigTest, set_on_new_data_callback_stores_the_callback)
{
  auto config = UdpImuReceiverConfig::create();

  config.setOnNewDataCallback([](sick::compact::imu::ImuData const& /*unused*/) { });

  EXPECT_TRUE(config.dataCallback());
}

TEST(UdpImuReceiverConfigTest, set_on_error_stores_the_callback)
{
  auto config = UdpImuReceiverConfig::create();

  config.setOnError([](std::exception_ptr const& /*unused*/) { });

  EXPECT_TRUE(config.onError());
}
