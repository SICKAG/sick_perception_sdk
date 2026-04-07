/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/ByteView.hpp>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <vector>

namespace sick {

/**
 * @brief Converts an array of sub-byte sized integers to a vector of larger integers.
 *
 * This function extracts integers with a size not necessarily a multiple of 8 bits from
 * a byte array and converts them to a target integer type. The input data is assumed
 * to be byte-aligned, with padding bits set to 0 if the last element doesn't end on
 * a byte boundary.
 *
 * @tparam TargetT The target integer type (must be larger than SourceTypeSizeInBits)
 * @tparam SourceTypeSizeInBits The size of each source integer in bits
 *
 * @param data View of the byte array to read from
 * @param numberOfSourceElements Number of source elements to extract
 * @param result Output vector that will contain the converted values (cleared before use)
 *
 * @return The number of bytes read from the input array (including padding)
 *
 * @throws std::invalid_argument If there is not enough data to read all source elements
 */
template <typename TargetT, std::size_t SourceTypeSizeInBits>
auto convertSubByteArray(ByteView data, std::size_t numberOfSourceElements, std::vector<TargetT>& result) -> std::size_t
{
  constexpr std::size_t bitsPerByte = 8;
  static_assert(SourceTypeSizeInBits <= sizeof(TargetT) * bitsPerByte, "Source type must be smaller than target type");

  if (numberOfSourceElements == 0 || data.empty())
  {
    result.clear();
    return 0;
  }

  if constexpr (sizeof(TargetT) == SourceTypeSizeInBits / bitsPerByte)
  {
    // If the source type size in bits corresponds to a whole number of bytes, we can directly copy the data
    std::size_t totalBytes = sizeof(TargetT) * numberOfSourceElements;
    result.resize(numberOfSourceElements);
    std::memcpy(result.data(), data.data(), totalBytes);
    return totalBytes;
  }
  else if constexpr (SourceTypeSizeInBits == 12)
  {
    // Specialized fast path for 12-bit values
    // Pattern: every 3 bytes contain 2x 12-bit values
    // byte0 byte1 byte2 → value0 = byte0 | (byte1 & 0x0F) << 8
    //                     value1 = (byte1 >> 4) | byte2 << 4
    std::size_t const totalNumberOfBits         = numberOfSourceElements * 12;
    std::size_t const totalNumberOfBytes        = (totalNumberOfBits + bitsPerByte - 1) / bitsPerByte;
    std::size_t const numberOfInputElementPairs = numberOfSourceElements / 2;
    bool const hasOddElement                    = (numberOfSourceElements % 2) != 0;

    result.resize(numberOfSourceElements);
    auto* outputPtr      = result.data();
    auto const* inputPtr = data.data();

    // AXIVION Single Disable CertC++-EXP34 : inputPtr is checked above, outputPtr is != nullptr after resize with numberOfSourceElements > 0.

    // Process pairs of 12-bit values (3 bytes → 2 values)
    for (std::size_t i = 0; i < numberOfInputElementPairs; ++i)
    {
      auto const byte0 = static_cast<std::uint16_t>(inputPtr[0]);
      auto const byte1 = static_cast<std::uint16_t>(inputPtr[1]);
      auto const byte2 = static_cast<std::uint16_t>(inputPtr[2]);

      outputPtr[0] = static_cast<TargetT>(byte0 | ((byte1 & 0x0Fu) << 8u));
      outputPtr[1] = static_cast<TargetT>((byte1 >> 4u) | (byte2 << 4u));

      inputPtr += 3;
      outputPtr += 2;
    }

    // Handle odd element if present
    if (hasOddElement)
    {
      auto const byte0 = static_cast<std::uint16_t>(inputPtr[0]);
      auto const byte1 = static_cast<std::uint16_t>(inputPtr[1]);
      outputPtr[0]     = static_cast<TargetT>(byte0 | ((byte1 & 0x0Fu) << 8u));
    }

    // AXIVION Single Enable CertC++-EXP34

    return totalNumberOfBytes;
  }

  result.clear();
  result.reserve(numberOfSourceElements);

  std::size_t bitOffset = 0;
  for (std::size_t i = 0; i < numberOfSourceElements; ++i)
  {
    TargetT value = 0;

    // Calculate byte position and bit position within that byte
    std::size_t byteIndex = bitOffset / bitsPerByte;
    std::size_t bitInByte = bitOffset % bitsPerByte;

    // Extract bits that may span multiple bytes
    std::size_t bitsRemaining     = SourceTypeSizeInBits;
    std::size_t targetBitPosition = 0;

    while (bitsRemaining > 0)
    {
      if (byteIndex >= data.size())
      {
        throw std::invalid_argument("Not enough data to read all source elements");
      }

      auto const currentByte          = data[byteIndex];
      std::size_t const bitsToExtract = std::min(bitsRemaining, bitsPerByte - bitInByte);

      // Extract bits from current byte
      auto const mask          = static_cast<std::uint8_t>(((1u << bitsToExtract) - 1u) << bitInByte);
      auto const extractedBits = static_cast<std::uint8_t>((currentByte & mask) >> bitInByte);

      // Place extracted bits in target value
      value |= static_cast<TargetT>(extractedBits) << targetBitPosition;

      bitsRemaining -= bitsToExtract;
      targetBitPosition += bitsToExtract;
      byteIndex++;
      bitInByte = 0;
    }

    result.push_back(value);
    bitOffset += SourceTypeSizeInBits;
  }

  // Calculate total bytes read (rounded up since data is byte-aligned)
  std::size_t const totalNumberOfBits  = numberOfSourceElements * SourceTypeSizeInBits;
  std::size_t const totalNumberOfBytes = (totalNumberOfBits + bitsPerByte - 1) / bitsPerByte; // Round up to next byte

  return totalNumberOfBytes;
}

} // namespace sick
