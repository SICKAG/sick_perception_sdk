/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/ByteView.hpp>
#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/compact_format/CompactData.hpp>

#include <cstdint>
#include <cstring> // for std::memcpy
#include <limits>
#include <optional>
#include <set>
#include <stdexcept>
#include <vector>

namespace sick::compact {

class SDK_EXPORT CompactParser
{
public:
  static constexpr std::uint32_t kStartOfFrame = 0x02020202u;

  CompactParser()                                        = default;
  virtual ~CompactParser()                               = default;
  CompactParser(CompactParser const&)                    = default;
  auto operator=(CompactParser const&) -> CompactParser& = default;
  CompactParser(CompactParser&&)                         = default;
  auto operator=(CompactParser&&) -> CompactParser&      = default;

  /**
   * @brief Get the size of the complete telegram (header + payload + checksum) if enough data is available to determine the size, 
   *        otherwise std::nullopt.
   */
  virtual auto getSize(ByteView data) const -> std::optional<std::size_t> = 0;

  /**
   * @brief Checks if the checksum of the data is valid.
   *
   * Assumes that the CRC32 is the last four bytes of the data,
   * i.e. starts at data.size() - 4.
   */
  static auto isChecksumValid(ByteView data) -> bool;

  /**
   * @brief Reads a value of type T from the data without bounds check.
   * @tparam T The type of value to read.
   * @param data The input data view.
   * @param value The variable to store the read value.
   * @return The number of bytes read.
   */
  template <typename T>
  static auto readValueUnsafe(ByteView data, T& value) -> std::size_t
  {
#ifdef UNSAFE_MEMCPY_ALLOWED
    std::memcpy(reinterpret_cast<void*>(&value), data.data(), sizeof(T));
    return sizeof(T);
#else
    return readValue(data, value);
#endif
  }

  /**
   * @brief Reads a value of type T from the data with bounds check.
   * @tparam T The type of value to read.
   * @param data The input data view.
   * @param value The variable to store the read value.
   * @return The number of bytes read.
   * @throws std::invalid_argument if there is not enough data.
   */
  template <typename T>
  static auto readValue(ByteView data, T& value) -> std::size_t
  {
    if (data.size() < sizeof(T))
    {
      throw std::invalid_argument("Not enough data to read the value");
    }
    std::memcpy(&value, data.data(), sizeof(T));
    return sizeof(T);
  }

  /**
   * @brief Reads an array of elements from the data.
   * @tparam T The type of elements.
   * @param data The input data view.
   * @param numberOfElements The number of elements to read.
   * @param destination The vector to fill with read elements.
   * @return The number of bytes read.
   * @throws std::invalid_argument if there is not enough data.
   */
  template <typename T>
  static auto readArray(ByteView data, std::size_t numberOfElements, std::vector<T>& destination) -> std::size_t
  {
    std::size_t const bytesToRead = numberOfElements * sizeof(T);
    if (bytesToRead > static_cast<std::size_t>(std::numeric_limits<std::ptrdiff_t>::max()))
    {
      throw std::invalid_argument("Number of elements is too large, causing overflow.");
    }

    if (data.size() < bytesToRead)
    {
      throw std::invalid_argument("Not enough data to read the array.");
    }
    destination.resize(numberOfElements);
    std::memcpy(destination.data(), data.data(), bytesToRead);
    return bytesToRead;
  }

  /**
   * @brief Checks if the checksum of the given telegram is valid.
   *
   * The position of the assumed checksum is derived from the telegram header (header size + payloadLength).
   */
  template <class HeaderT>
  static void validateChecksum(HeaderT const& header, ByteView data)
  {
    auto const requiredSize = sizeof(HeaderT) + header.payloadLength + sizeof(std::uint32_t);
    if (!isChecksumValid(data.first(requiredSize)))
    {
      throw std::invalid_argument("Invalid checksum");
    }
  }

  static void validateTelegramHeader(TelegramHeader const& header, TelegramType expectedType, std::set<std::uint32_t> expectedVersions);
};

} // namespace sick::compact
