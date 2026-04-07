/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include "../src/Crc32UtilsImpl.hpp"

#include <sick_perception_sdk/common/ByteView.hpp>

#include <exception>
#include <gtest/gtest.h>

/**
 * This test suite explicitly tests only the internal CRC-32 implementation.
 * The actual implementation used in production code is selected at compile time
 * via the USE_ZLIB_CRC32 CMake option.
 */

TEST(Crc32UtilsTest, computes_correct_value)
{
  std::vector<std::uint8_t> const data {1, 2, 3, 4};
  auto const checksum = sick::compact::crc32Impl(sick::ByteView {data});
  EXPECT_EQ(0xB63CFBCD, checksum); // CRC-32/ISO-HDLC
}

TEST(Crc32UtilsTest, handles_empty_data)
{
  std::vector<std::uint8_t> const data {};
  auto const checksum = sick::compact::crc32Impl(sick::ByteView {data});
  EXPECT_NE(0xB63CFBCD, checksum);
}

