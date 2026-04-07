/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/IpV4Address.hpp>

#include <array>
#include <gtest/gtest.h>

TEST(IpV4AddressTest, constructor_throws_for_too_many_blocks)
{
  EXPECT_THROW((sick::IpV4Address("192.168.1.1.256")), std::invalid_argument);
}

TEST(IpV4AddressTest, constructor_throws_for_too_few_blocks)
{
  EXPECT_THROW((sick::IpV4Address("192.168.1")), std::invalid_argument);
}

TEST(IpV4AddressTest, constructor_throws_for_block_value_too_large)
{
  EXPECT_THROW((sick::IpV4Address("192.168.1.256")), std::invalid_argument);
}

TEST(IpV4AddressTest, constructor_throws_for_negative_block_value)
{
  EXPECT_THROW((sick::IpV4Address("192.168.-1.1")), std::invalid_argument);
}

TEST(IpV4AddressTest, constructor_throws_for_non_numeric_block)
{
  EXPECT_THROW((sick::IpV4Address("192.168.abc.1")), std::invalid_argument);
}

TEST(IpV4AddressTest, constructor_parses_valid_address_string)
{
  auto const address  = sick::IpV4Address("192.168.1.1");
  auto const expected = std::array<std::uint8_t, 4> {192, 168, 1, 1};
  EXPECT_EQ(address.bytes(), expected);
}

TEST(IpV4AddressTest, constructor_parses_minimum_address_values)
{
  auto const address  = sick::IpV4Address("0.0.0.0");
  auto const expected = std::array<std::uint8_t, 4> {0, 0, 0, 0};
  EXPECT_EQ(address.bytes(), expected);
}

TEST(IpV4AddressTest, constructor_parses_maximum_address_values)
{
  auto const address  = sick::IpV4Address("255.255.255.255");
  auto const expected = std::array<std::uint8_t, 4> {255, 255, 255, 255};
  EXPECT_EQ(address.bytes(), expected);
}

TEST(IpV4AddressTest, constructor_parses_localhost_address)
{
  auto const address  = sick::IpV4Address("127.0.0.1");
  auto const expected = std::array<std::uint8_t, 4> {127, 0, 0, 1};
  EXPECT_EQ(address.bytes(), expected);
}

TEST(IpV4AddressTest, constructor_accepts_uint8_array)
{
  auto const bytes   = std::array<std::uint8_t, 4> {192, 168, 1, 1};
  auto const address = sick::IpV4Address(bytes);
  EXPECT_EQ(address.bytes(), bytes);
}

TEST(IpV4AddressTest, constructor_accepts_minimum_uint8_array)
{
  auto const bytes   = std::array<std::uint8_t, 4> {0, 0, 0, 0};
  auto const address = sick::IpV4Address(bytes);
  EXPECT_EQ(address.bytes(), bytes);
}

TEST(IpV4AddressTest, constructor_accepts_maximum_uint8_array)
{
  auto const bytes   = std::array<std::uint8_t, 4> {255, 255, 255, 255};
  auto const address = sick::IpV4Address(bytes);
  EXPECT_EQ(address.bytes(), bytes);
}

TEST(IpV4AddressTest, to_string_returns_dotted_decimal_format)
{
  auto const address = sick::IpV4Address("192.168.1.1");
  EXPECT_EQ(address.toString(), "192.168.1.1");
}

TEST(IpV4AddressTest, to_string_returns_minimum_address_correctly)
{
  auto const address = sick::IpV4Address("0.0.0.0");
  EXPECT_EQ(address.toString(), "0.0.0.0");
}

TEST(IpV4AddressTest, to_string_returns_maximum_address_correctly)
{
  auto const address = sick::IpV4Address("255.255.255.255");
  EXPECT_EQ(address.toString(), "255.255.255.255");
}

TEST(IpV4AddressTest, constructor_accepts_char_pointer)
{
  auto const* const ipStr = "10.0.0.1";
  auto const address      = sick::IpV4Address(ipStr);
  auto const expected     = std::array<std::uint8_t, 4> {10, 0, 0, 1};
  EXPECT_EQ(address.bytes(), expected);
}
