/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include "CompactTelegram.hpp"

#include <sick_perception_sdk/common/ByteView.hpp>
#include <sick_perception_sdk/common/CheckedMath.hpp>
#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/compact_format/CompactData.hpp>

#include <cstddef>
#include <cstdint>
#include <cstring> // for std::memcpy
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace sick::compact {

// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic): Pointer arithmetic is necessary here for efficient reading of the compact data.

class SDK_EXPORT CompactParserContext
{
public:
  explicit CompactParserContext(ByteView data)
    : m_data(data)
    , m_readPosition {0}
  { }

  virtual ~CompactParserContext()                                      = default;
  CompactParserContext(CompactParserContext const&)                    = default;
  auto operator=(CompactParserContext const&) -> CompactParserContext& = default;
  CompactParserContext(CompactParserContext&&)                         = default;
  auto operator=(CompactParserContext&&) -> CompactParserContext&      = default;

  auto data() const -> ByteView const&
  {
    return m_data;
  }

  template <typename OutputValueT, typename CompactValueT, std::enable_if_t<std::is_trivially_copyable_v<OutputValueT>, int> = 0>
  auto readValueUnsafe(telegram::CompactField<CompactValueT> const& field) -> OutputValueT
  {
#ifdef UNSAFE_MEMCPY_ALLOWED
    CompactValueT compactValue;
    copyMemoryUnsafe(&compactValue, field.sizeInBytes);
    return static_cast<OutputValueT>(compactValue);
#else
    return readValue<OutputValueT, CompactValueT>(field);
#endif
  }

  template <typename CompactValueT, typename std::enable_if_t<std::is_trivially_copyable_v<CompactValueT>, int> = 0>
  auto readValueUnsafe(telegram::CompactField<CompactValueT> const& field) -> CompactValueT
  {
    return readValueUnsafe<CompactValueT, CompactValueT>(field);
  }

  template <typename CompactValueT, typename std::enable_if_t<std::is_trivially_copyable_v<CompactValueT>, int> = 0>
  auto readValue(telegram::CompactField<CompactValueT> const& field) -> CompactValueT
  {
    return readValue<CompactValueT, CompactValueT>(field);
  }

  template <typename OutputValueT, typename CompactValueT = OutputValueT, typename std::enable_if_t<std::is_trivially_copyable_v<OutputValueT>, int> = 0>
  auto readValue(telegram::CompactField<CompactValueT> const& field) -> OutputValueT
  {
    static_assert(sizeof(CompactValueT) <= sizeof(OutputValueT), "CompactValueT must not be larger than OutputValueT");
    if (field.sizeInBytes > numberOfBytesRemaining())
    {
      throw std::invalid_argument("Not enough data to read the value");
    }
    CompactValueT compactValue;
    copyMemoryUnsafe(&compactValue, field.sizeInBytes);
    return static_cast<OutputValueT>(compactValue);
  }

  template <typename OutputValueT, typename CompactValueT = OutputValueT, typename std::enable_if_t<std::is_trivially_copyable_v<OutputValueT>, int> = 0>
  auto readArray(telegram::CompactField<CompactValueT> const& field, std::size_t numberOfElements) -> std::vector<OutputValueT>
  {
    static_assert(sizeof(CompactValueT) <= sizeof(OutputValueT), "CompactValueT must not be larger than OutputValueT");
    std::size_t const numberOfBytesToRead = checkedMultiply(numberOfElements, field.sizeInBytes);
    if (numberOfBytesToRead > numberOfBytesRemaining())
    {
      throw std::invalid_argument("Number of elements is too large, causing overflow.");
    }

    std::vector<OutputValueT> destination;
    for (std::size_t i = 0; i < numberOfElements; ++i)
    {
      CompactValueT compactValue;
      copyMemoryUnsafe(&compactValue, field.sizeInBytes);
      destination.push_back(static_cast<OutputValueT>(compactValue));
    }
    return destination;
  }

  template <typename CompactValueT>
  void skipValue(telegram::CompactField<CompactValueT> const& field)
  {
    skipBytes(field.sizeInBytes);
  }

  void skipBytes(size_t numberOfBytes)
  {
    if (numberOfBytes > numberOfBytesRemaining())
    {
      throw std::invalid_argument("Not enough data to skip the bytes");
    }
    m_readPosition += numberOfBytes;
  }

  auto readPosition() const -> std::size_t
  {
    return m_readPosition;
  }

  auto remainingBytes() const -> ByteView
  {
    return m_data.subview(m_readPosition);
  }

  auto numberOfBytesRemaining() const -> std::size_t
  {
    return m_data.size() - m_readPosition;
  }

  auto nextByte() const -> ByteView::pointer
  {
    return m_data.data() + m_readPosition;
  }

  void copyMemory(void* destination, std::size_t numberOfBytes)
  {
    if (numberOfBytes > numberOfBytesRemaining())
    {
      throw std::invalid_argument("Not enough data to read the bytes");
    }
    copyMemoryUnsafe(destination, numberOfBytes);
  }

  void copyMemoryUnsafe(void* destination, std::size_t numberOfBytes)
  {
    std::memcpy(destination, m_data.data() + m_readPosition, numberOfBytes);
    m_readPosition += numberOfBytes;
  }

protected:
  ByteView m_data;
  std::size_t m_readPosition;
};

// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic)

} // namespace sick::compact
