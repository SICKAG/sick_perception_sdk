/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/SubByteArrayConverter.hpp>

#include <sick_perception_sdk/common/ByteView.hpp>

#include <gtest/gtest.h>
#include <stdexcept>

using namespace sick;

TEST(SubByteArrayConverterTest, converts_4bit_values)
{
  // Two 4-bit values: 0b1010 (10) and 0b0101 (5)
  // Packed as: 0b0101'1010 = 0x5A
  std::vector<std::uint8_t> const data {0x5A};
  std::vector<std::uint16_t> result;

  auto bytesRead = convertSubByteArray<std::uint16_t, 4>(ByteView {data}, 2, result);

  EXPECT_EQ(1, bytesRead);
  ASSERT_EQ(2, result.size());
  EXPECT_EQ(10, result[0]);
  EXPECT_EQ(5, result[1]);
}

TEST(SubByteArrayConverterTest, converts_4bit_values_spanning_multiple_bytes)
{
  // Four 4-bit values: 3, 7, 15, 1
  // Packed as: 0b0111'0011'0001'1111 (0x731F)
  std::vector<std::uint8_t> const data {0x73, 0x1F};
  std::vector<std::uint32_t> result;

  auto bytesRead = convertSubByteArray<std::uint32_t, 4>(ByteView {data}, 4, result);

  EXPECT_EQ(2, bytesRead);
  ASSERT_EQ(4, result.size());
  EXPECT_EQ(3, result[0]);
  EXPECT_EQ(7, result[1]);
  EXPECT_EQ(15, result[2]);
  EXPECT_EQ(1, result[3]);
}

TEST(SubByteArrayConverterTest, converts_6bit_values)
{
  // Two 6-bit values: 0b10'1010 (42) and 0b11'1111 (63)
  // Packed as: 0b1110'1010'0000'1111 (0xEA0F)
  std::vector<std::uint8_t> const data {0xEA, 0x0F};
  std::vector<std::uint16_t> result;

  auto bytesRead = convertSubByteArray<std::uint16_t, 6>(ByteView {data}, 2, result);

  EXPECT_EQ(2, bytesRead);
  ASSERT_EQ(2, result.size());
  EXPECT_EQ(42, result[0]);
  EXPECT_EQ(63, result[1]);
}

TEST(SubByteArrayConverterTest, converts_3bit_values)
{
  // Three 3-bit values: 0b101 (5), 0b011 (3), 0b111 (7)
  // Packed LSB-first: bits[0:2]=101, bits[3:5]=011, bits[6:8]=111
  // Byte 0: 0b11011101 (0xDD), Byte 1: 0b00000001 (0x01)
  std::vector<std::uint8_t> const data {0xDD, 0x01};
  std::vector<std::uint8_t> result;

  auto bytesRead = convertSubByteArray<std::uint8_t, 3>(ByteView {data}, 3, result);

  EXPECT_EQ(2, bytesRead);
  ASSERT_EQ(3, result.size());
  EXPECT_EQ(5, result[0]);
  EXPECT_EQ(3, result[1]);
  EXPECT_EQ(7, result[2]);
}

TEST(SubByteArrayConverterTest, converts_12bit_values)
{
  // Two 12-bit values: 0xABC (2748) and 0x123 (291)
  // Packed LSB-first: 0xABC in bits[0:11], 0x123 in bits[12:23]
  std::vector<std::uint8_t> const data {0xBC, 0x3A, 0x12};
  std::vector<std::uint16_t> result;

  auto bytesRead = convertSubByteArray<std::uint16_t, 12>(ByteView {data}, 2, result);

  EXPECT_EQ(3, bytesRead);
  ASSERT_EQ(2, result.size());
  EXPECT_EQ(0xABC, result[0]);
  EXPECT_EQ(0x123, result[1]);
}

TEST(SubByteArrayConverterTest, converts_8bit_values)
{
  // Three 8-bit values: 0x12 (18), 0x34 (52), 0x56 (86)
  std::vector<std::uint8_t> const data {0x12, 0x34, 0x56};
  std::vector<std::uint16_t> result;

  auto bytesRead = convertSubByteArray<std::uint16_t, 8>(ByteView {data}, 3, result);

  EXPECT_EQ(3, bytesRead);
  ASSERT_EQ(3, result.size());
  EXPECT_EQ(0x12, result[0]);
  EXPECT_EQ(0x34, result[1]);
  EXPECT_EQ(0x56, result[2]);
}

TEST(SubByteArrayConverterTest, converts_16bit_values)
{
  // Two 16-bit values: 0x1234 (4660) and 0xABCD (43981)
  std::vector<std::uint8_t> const data {0x34, 0x12, 0xCD, 0xAB}; // Little-endian
  std::vector<std::uint16_t> result;

  auto bytesRead = convertSubByteArray<std::uint16_t, 16>(ByteView {data}, 2, result);

  EXPECT_EQ(4, bytesRead);
  ASSERT_EQ(2, result.size());
  EXPECT_EQ(0x1234, result[0]);
  EXPECT_EQ(0xABCD, result[1]);
}

TEST(SubByteArrayConverterTest, handles_single_value)
{
  // Single 5-bit value: 0b10101 (21)
  std::vector<std::uint8_t> const data {0x15}; // 0b00010101
  std::vector<std::uint32_t> result;

  auto bytesRead = convertSubByteArray<std::uint32_t, 5>(ByteView {data}, 1, result);

  EXPECT_EQ(1, bytesRead);
  ASSERT_EQ(1, result.size());
  EXPECT_EQ(21, result[0]);
}

TEST(SubByteArrayConverterTest, handles_empty_input)
{
  std::vector<std::uint8_t> const data;
  std::vector<std::uint16_t> result;

  auto bytesRead = convertSubByteArray<std::uint16_t, 4>(ByteView {data}, 0, result);

  EXPECT_EQ(0, bytesRead);
  EXPECT_EQ(0, result.size());
}

TEST(SubByteArrayConverterTest, clears_result_vector)
{
  std::vector<std::uint8_t> const data {0x5A};
  std::vector<std::uint16_t> result {999, 888, 777};

  convertSubByteArray<std::uint16_t, 4>(ByteView {data}, 2, result);

  ASSERT_EQ(2, result.size());
  EXPECT_EQ(10, result[0]);
  EXPECT_EQ(5, result[1]);
}

TEST(SubByteArrayConverterTest, throws_when_not_enough_data)
{
  std::vector<std::uint8_t> const data {0x5A};
  std::vector<std::uint16_t> result;

  EXPECT_THROW((convertSubByteArray<std::uint16_t, 4>(ByteView {data}, 3, result)), std::invalid_argument);
}

TEST(SubByteArrayConverterTest, calculates_correct_byte_count_with_padding)
{
  // Three 5-bit values = 15 bits total, requires 2 bytes (with 1 bit padding)
  std::vector<std::uint8_t> const data {0xFF, 0xFF};
  std::vector<std::uint16_t> result;

  auto bytesRead = convertSubByteArray<std::uint16_t, 5>(ByteView {data}, 3, result);

  EXPECT_EQ(2, bytesRead);
  ASSERT_EQ(3, result.size());
}

TEST(SubByteArrayConverterTest, converts_7bit_values)
{
  // Two 7-bit values: 0b1010101 (85) and 0b0101010 (42)
  // Packed LSB-first: bits[0:6]=1010101, bits[7:13]=0101010
  std::vector<std::uint8_t> const data {0x55, 0x15};
  std::vector<std::uint16_t> result;

  auto bytesRead = convertSubByteArray<std::uint16_t, 7>(ByteView {data}, 2, result);

  EXPECT_EQ(2, bytesRead);
  ASSERT_EQ(2, result.size());
  EXPECT_EQ(85, result[0]);
  EXPECT_EQ(42, result[1]);
}
