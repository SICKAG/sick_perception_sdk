/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>
#include <optional>
#include <stdexcept>
#include <vector>

namespace sick {

namespace {

constexpr std::size_t kBmpFileHeaderSize    = 14;
constexpr std::size_t kBmpDibHeaderSize     = 40;
constexpr std::size_t kBmpColorTableSize    = 256 * 4;
constexpr std::size_t kBmpHeaderSize        = kBmpFileHeaderSize + kBmpDibHeaderSize + kBmpColorTableSize;
constexpr std::size_t kBmpPixelDataOffset   = kBmpHeaderSize;
constexpr std::uint16_t kBmpSignature       = 0x4D42; // "BM" in little-endian
constexpr std::uint16_t kBmpPlanes          = 1;
constexpr std::uint16_t kBmpBitsPerPixel    = 8;
constexpr std::uint32_t kBmpCompressionNone = 0;
constexpr std::int32_t kBmpPixelsPerMeter   = 2835; // ~72 DPI

inline auto calculateRowPadding(std::size_t width) -> std::size_t
{
  return (4 - (width % 4)) % 4;
}

inline auto calculatePaddedRowSize(std::size_t width) -> std::size_t
{
  return width + calculateRowPadding(width);
}

template <typename T>
inline void writeToBuffer(std::vector<std::uint8_t>& buffer, std::size_t offset, T value)
{
  for (std::size_t i = 0; i < sizeof(T); ++i)
  {
    buffer[offset + i] = static_cast<std::uint8_t>((value >> (i * 8)) & 0xFF);
  }
}

inline void writeBmpHeaders(std::vector<std::uint8_t>& buffer, std::size_t width, std::size_t height)
{
  std::size_t const paddedRowSize = calculatePaddedRowSize(width);
  std::size_t const pixelDataSize = paddedRowSize * height;
  std::uint32_t const fileSize    = static_cast<std::uint32_t>(kBmpHeaderSize + pixelDataSize);
  std::int32_t const signedWidth  = static_cast<std::int32_t>(width);
  std::int32_t const signedHeight = static_cast<std::int32_t>(height);
  std::uint32_t const imageSize   = static_cast<std::uint32_t>(pixelDataSize);

  // File header (14 bytes)
  writeToBuffer(buffer, 0, kBmpSignature);                                    // Signature "BM"
  writeToBuffer(buffer, 2, fileSize);                                         // File size
  writeToBuffer(buffer, 6, std::uint32_t {0});                                // Reserved
  writeToBuffer(buffer, 10, static_cast<std::uint32_t>(kBmpPixelDataOffset)); // Pixel data offset

  // DIB header (BITMAPINFOHEADER - 40 bytes)
  writeToBuffer(buffer, 14, static_cast<std::uint32_t>(kBmpDibHeaderSize)); // Header size
  writeToBuffer(buffer, 18, signedWidth);                                   // Width
  writeToBuffer(buffer, 22, signedHeight);                                  // Height (positive = bottom-up)
  writeToBuffer(buffer, 26, kBmpPlanes);                                    // Planes
  writeToBuffer(buffer, 28, kBmpBitsPerPixel);                              // Bits per pixel
  writeToBuffer(buffer, 30, kBmpCompressionNone);                           // Compression
  writeToBuffer(buffer, 34, imageSize);                                     // Image size
  writeToBuffer(buffer, 38, kBmpPixelsPerMeter);                            // X pixels per meter
  writeToBuffer(buffer, 42, kBmpPixelsPerMeter);                            // Y pixels per meter
  writeToBuffer(buffer, 46, std::uint32_t {256});                           // Colors in color table
  writeToBuffer(buffer, 50, std::uint32_t {0});                             // Important colors

  // Color table (256 grayscale entries, 4 bytes each: B, G, R, Reserved)
  for (std::size_t i = 0; i < 256; ++i)
  {
    std::size_t const offset = kBmpFileHeaderSize + kBmpDibHeaderSize + i * 4;
    auto const grayValue     = static_cast<std::uint8_t>(i);
    buffer[offset]           = grayValue; // Blue
    buffer[offset + 1]       = grayValue; // Green
    buffer[offset + 2]       = grayValue; // Red
    buffer[offset + 3]       = 0;         // Reserved
  }
}

template <typename InputValueT>
auto estimateMinMax(InputValueT const* data, std::size_t size, std::optional<std::pair<InputValueT, InputValueT>> minMaxValue)
  -> std::pair<InputValueT, InputValueT>
{
  if (minMaxValue.has_value())
  {
    return minMaxValue.value();
  }

  InputValueT min = std::numeric_limits<InputValueT>::max();
  InputValueT max = std::numeric_limits<InputValueT>::lowest();

  for (std::size_t i = 0; i < size; ++i)
  {
    if (data[i] < min)
    {
      min = data[i];
    }
    if (data[i] > max)
    {
      max = data[i];
    }
  }
  return {min, max};
}

} // namespace

/**
 * @brief Encodes 1D grayscale data into BMP format.
 * @tparam InputValueT The numeric type of the input data
 * @param data Pixel values in row-major order (size must equal width * height)
 * @param width Image width in pixels
 * @param height Image height in pixels
 * @param minMaxValue Optional pair of minimum and maximum values of input range (maps to black and white). If not provided, the range will be estimated from the data.
 * @return BMP file content as byte sequence
 */
template <typename InputValueT>
auto encodeGrayscaleBmp(
  std::vector<InputValueT> const& data,
  std::size_t width,
  std::size_t height,
  std::optional<std::pair<InputValueT, InputValueT>> minMaxValue = std::nullopt
) -> std::vector<std::uint8_t>
{
  if (width == 0 || height == 0)
  {
    throw std::invalid_argument("Width and height must be greater than zero");
  }
  if (data.size() != width * height)
  {
    throw std::invalid_argument("Data size must equal width * height");
  }
  if (minMaxValue.has_value() && minMaxValue->second <= minMaxValue->first)
  {
    throw std::invalid_argument("maxValue must be greater than minValue");
  }

  auto const [min, max] = estimateMinMax(data.data(), data.size(), minMaxValue);

  std::size_t const paddedRowSize = calculatePaddedRowSize(width);
  std::size_t const pixelDataSize = paddedRowSize * height;
  std::vector<std::uint8_t> buffer(kBmpHeaderSize + pixelDataSize, 0);

  writeBmpHeaders(buffer, width, height);

  // Write pixel data (BMP stores rows bottom-to-top)
  double const range = static_cast<double>(max) - static_cast<double>(min);
  for (std::size_t row = 0; row < height; ++row)
  {
    std::size_t const srcRowIndex = height - 1 - row; // Flip vertically
    std::size_t const dstOffset   = kBmpPixelDataOffset + row * paddedRowSize;

    for (std::size_t col = 0; col < width; ++col)
    {
      auto const value        = data[srcRowIndex * width + col];
      double const normalized = (static_cast<double>(value) - static_cast<double>(min)) / range;
      double const clamped    = std::clamp(normalized, 0.0, 1.0);
      buffer[dstOffset + col] = static_cast<std::uint8_t>(clamped * 255.0 + 0.5);
    }
    // Padding bytes are already zero-initialized
  }

  return buffer;
}

/**
 * @brief Encodes 2D column-major grayscale data into BMP format.
 * @tparam InputValueT The numeric type of the input data
 * @param data 2D vector of pixel values (outer: columns, inner: rows)
 * @param minMaxValue Optional pair of minimum and maximum values of input range (maps to black and white). If not provided, the range will be estimated from the data.
 * @return BMP file content as byte sequence
 */
template <typename InputValueT>
auto encodeGrayscaleBmp(std::vector<std::vector<InputValueT>> const& data, std::optional<std::pair<InputValueT, InputValueT>> minMaxValue = std::nullopt)
  -> std::vector<std::uint8_t>
{
  if (data.empty() || data[0].empty())
  {
    throw std::invalid_argument("Data must not be empty");
  }

  auto const width  = data.size();
  auto const height = data[0].size();

  // Validate uniform column heights
  for (auto const& column : data)
  {
    if (column.size() != height)
    {
      throw std::invalid_argument("All columns must have the same height");
    }
  }

  // Convert column-major to row-major
  std::vector<InputValueT> flatData(width * height);
  for (std::size_t col = 0; col < width; ++col)
  {
    for (std::size_t row = 0; row < height; ++row)
    {
      flatData[row * width + col] = data[col][row];
    }
  }

  return encodeGrayscaleBmp(flatData, width, height, minMaxValue);
}

} // namespace sick
