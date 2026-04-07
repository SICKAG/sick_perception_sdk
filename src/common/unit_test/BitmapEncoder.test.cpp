/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/common/BitmapEncoder.hpp>

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <vector>

namespace sick::common { namespace {

// BMP header constants for validation
constexpr std::size_t kBmpFileHeaderSize = 14;
constexpr std::size_t kBmpDibHeaderSize  = 40;
constexpr std::size_t kBmpColorTableSize = 256 * 4;
constexpr std::size_t kBmpHeaderSize     = kBmpFileHeaderSize + kBmpDibHeaderSize + kBmpColorTableSize;

auto readUint16(std::vector<std::uint8_t> const& buffer, std::size_t offset) -> std::uint16_t
{
  return static_cast<std::uint16_t>(buffer[offset]) | (static_cast<std::uint16_t>(buffer[offset + 1]) << 8);
}

auto readUint32(std::vector<std::uint8_t> const& buffer, std::size_t offset) -> std::uint32_t
{
  return static_cast<std::uint32_t>(buffer[offset]) | (static_cast<std::uint32_t>(buffer[offset + 1]) << 8) |
         (static_cast<std::uint32_t>(buffer[offset + 2]) << 16) | (static_cast<std::uint32_t>(buffer[offset + 3]) << 24);
}

auto readInt32(std::vector<std::uint8_t> const& buffer, std::size_t offset) -> std::int32_t
{
  return static_cast<std::int32_t>(readUint32(buffer, offset));
}

TEST(BitmapEncoder, encodeGrayscaleBmp_1D_creates_valid_bmp_header)
{
  std::size_t width  = 10;
  std::size_t height = 5;
  std::vector<std::uint8_t> data(width * height, 128);
  auto const result = encodeGrayscaleBmp(data, width, height, {{0, 255}});

  // Verify BMP signature
  EXPECT_EQ(readUint16(result, 0), 0x4D42); // "BM"

  // Verify DIB header values
  EXPECT_EQ(readUint32(result, 14), 40u); // DIB header size
  EXPECT_EQ(readInt32(result, 18), width);
  EXPECT_EQ(readInt32(result, 22), height);
  EXPECT_EQ(readUint16(result, 26), 1u); // Planes
  EXPECT_EQ(readUint16(result, 28), 8u); // Bits per pixel
  EXPECT_EQ(readUint32(result, 30), 0u); // Compression (none)
}

TEST(BitmapEncoder, encodeGrayscaleBmp_1D_creates_correct_file_size)
{
  constexpr std::size_t width  = 10;
  constexpr std::size_t height = 5;
  std::vector<std::uint8_t> data(width * height, 128);
  auto const result = encodeGrayscaleBmp(data, width, height, {{0, 255}});

  // Width 10 requires padding to 12 bytes per row (next multiple of 4)
  std::size_t const paddedRowSize = 12;
  std::size_t const expectedSize  = kBmpHeaderSize + paddedRowSize * height;

  EXPECT_EQ(result.size(), expectedSize);
  EXPECT_EQ(readUint32(result, 2), static_cast<std::uint32_t>(expectedSize)); // File size in header
}

TEST(BitmapEncoder, encodeGrayscaleBmp_1D_scales_values_correctly)
{
  // Create 2x2 image with values at min, max, and middle
  std::size_t width               = 2;
  std::size_t height              = 2;
  std::vector<std::uint16_t> data = {0, 32768, 65535, 16384};
  auto const result               = encodeGrayscaleBmp(data, width, height, {{0, 65'535}});

  // Pixel data starts after header, BMP stores bottom row first
  // Row 1 (bottom in image, first in file): values 65535, 16384 -> 255, 64
  // Row 0 (top in image, second in file): values 0, 32768 -> 0, 128
  EXPECT_EQ(result[kBmpHeaderSize + 0], 255); // 65535 -> 255
  EXPECT_EQ(result[kBmpHeaderSize + 1], 64);  // 16384 -> ~64
  // Second row (after 4-byte padding)
  EXPECT_EQ(result[kBmpHeaderSize + 4], 0);   // 0 -> 0
  EXPECT_EQ(result[kBmpHeaderSize + 5], 128); // 32768 -> 128
}

TEST(BitmapEncoder, encodeGrayscaleBmp_1D_clamps_out_of_range_values)
{
  std::vector<std::int16_t> data = {-100, 50, 200, 300};
  auto const result              = encodeGrayscaleBmp(data, 2, 2, {{0, 100}});

  // -100 should clamp to 0, 300 should clamp to 255
  EXPECT_EQ(result[kBmpHeaderSize + 0], 255); // 200 clamped -> 255 (bottom-left)
  EXPECT_EQ(result[kBmpHeaderSize + 1], 255); // 300 clamped -> 255 (bottom-right)
  EXPECT_EQ(result[kBmpHeaderSize + 4], 0);   // -100 clamped -> 0 (top-left)
  EXPECT_EQ(result[kBmpHeaderSize + 5], 128); // 50 -> 128 (top-right)
}

TEST(BitmapEncoder, encodeGrayscaleBmp_1D_throws_on_zero_dimensions)
{
  std::vector<std::uint8_t> data(10, 0);

  EXPECT_THROW(encodeGrayscaleBmp(data, 0, 5, {{0, 255}}), std::invalid_argument);
  EXPECT_THROW(encodeGrayscaleBmp(data, 5, 0, {{0, 255}}), std::invalid_argument);
}

TEST(BitmapEncoder, encodeGrayscaleBmp_1D_throws_on_size_mismatch)
{
  std::vector<std::uint8_t> data(10, 0);

  EXPECT_THROW(encodeGrayscaleBmp(data, 5, 5, {{0, 255}}), std::invalid_argument);
}

TEST(BitmapEncoder, encodeGrayscaleBmp_1D_throws_on_invalid_range)
{
  std::vector<std::uint8_t> data(10, 0);

  // min = max
  EXPECT_THROW(encodeGrayscaleBmp(data, 5, 2, {{100, 100}}), std::invalid_argument);
  // min > max
  EXPECT_THROW(encodeGrayscaleBmp(data, 5, 2, {{100, 50}}), std::invalid_argument);
}

TEST(BitmapEncoder, encodeGrayscaleBmp_2D_creates_valid_bmp)
{
  // 3 columns, 2 rows (column-major)
  std::vector<std::vector<std::uint8_t>> data = {{10, 20}, {30, 40}, {50, 60}};
  auto const result                           = encodeGrayscaleBmp(data, {{0, 255}});

  EXPECT_EQ(readUint16(result, 0), 0x4D42); // "BM"
  EXPECT_EQ(readInt32(result, 18), 3);      // Width = 3 columns
  EXPECT_EQ(readInt32(result, 22), 2);      // Height = 2 rows
}

TEST(BitmapEncoder, encodeGrayscaleBmp_2D_converts_column_major_to_row_major)
{
  // Column-major: data[col][row]
  // col0: {10, 20}, col1: {30, 40}, col2: {50, 60}
  // Row-major equivalent:
  //   row0: 10, 30, 50
  //   row1: 20, 40, 60
  // BMP stores bottom-to-top:
  //   file row0 (image row1): 20, 40, 60
  //   file row1 (image row0): 10, 30, 50
  std::vector<std::vector<std::uint8_t>> data = {{10, 20}, {30, 40}, {50, 60}};
  auto const result                           = encodeGrayscaleBmp(data, {{0, 255}});

  // First row in file (image row 1): 20, 40, 60, padding
  EXPECT_EQ(result[kBmpHeaderSize + 0], 20);
  EXPECT_EQ(result[kBmpHeaderSize + 1], 40);
  EXPECT_EQ(result[kBmpHeaderSize + 2], 60);

  // Second row in file (image row 0): 10, 30, 50, padding
  EXPECT_EQ(result[kBmpHeaderSize + 4], 10);
  EXPECT_EQ(result[kBmpHeaderSize + 5], 30);
  EXPECT_EQ(result[kBmpHeaderSize + 6], 50);
}

TEST(BitmapEncoder, encodeGrayscaleBmp_2dd_throws_on_empty_data)
{
  std::vector<std::vector<std::uint8_t>> emptyOuter;
  std::vector<std::vector<std::uint8_t>> emptyInner = {{}};

  EXPECT_THROW(encodeGrayscaleBmp(emptyOuter, {{0, 255}}), std::invalid_argument);
  EXPECT_THROW(encodeGrayscaleBmp(emptyInner, {{0, 255}}), std::invalid_argument);
}

TEST(BitmapEncoder, encodeGrayscaleBmp_2D_throws_on_non_uniform_columns)
{
  std::vector<std::vector<std::uint8_t>> data = {{10, 20}, {30, 40, 50}}; // Different column heights

  EXPECT_THROW(encodeGrayscaleBmp(data, {{0, 255}}), std::invalid_argument);
}

TEST(BitmapEncoder, encodeGrayscaleBmp_creates_valid_grayscale_color_table)
{
  std::vector<std::uint8_t> data(4, 0);
  auto const result = encodeGrayscaleBmp(data, 2, 2, {{0, 255}});

  // Verify first few color table entries (starts at offset 54)
  std::size_t const colorTableOffset = kBmpFileHeaderSize + kBmpDibHeaderSize;

  // Entry 0: black (0, 0, 0, 0)
  EXPECT_EQ(result[colorTableOffset + 0], 0);
  EXPECT_EQ(result[colorTableOffset + 1], 0);
  EXPECT_EQ(result[colorTableOffset + 2], 0);
  EXPECT_EQ(result[colorTableOffset + 3], 0);

  // Entry 255: white (255, 255, 255, 0)
  EXPECT_EQ(result[colorTableOffset + 255 * 4 + 0], 255);
  EXPECT_EQ(result[colorTableOffset + 255 * 4 + 1], 255);
  EXPECT_EQ(result[colorTableOffset + 255 * 4 + 2], 255);
  EXPECT_EQ(result[colorTableOffset + 255 * 4 + 3], 0);
}

TEST(BitmapEncoder, encodeGrayscaleBmp_works_with_float_data)
{
  std::vector<float> data = {0.0f, 0.5f, 1.0f, 0.25f};
  auto const result       = encodeGrayscaleBmp(data, 2, 2, {{0.0f, 1.0f}});

  // Bottom row in file (row 1 in image): 1.0 -> 255, 0.25 -> 64
  EXPECT_EQ(result[kBmpHeaderSize + 0], 255);
  EXPECT_EQ(result[kBmpHeaderSize + 1], 64);

  // Top row in file (row 0 in image): 0.0 -> 0, 0.5 -> 128
  EXPECT_EQ(result[kBmpHeaderSize + 4], 0);
  EXPECT_EQ(result[kBmpHeaderSize + 5], 128);
}
}} // namespace sick::common
