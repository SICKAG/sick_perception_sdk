/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/export.hpp>

#include <array>
#include <cstdint>
#include <string>

namespace sick {

class SDK_EXPORT IpV4Address
{
public:
  /**
   * @brief Constructs an IpV4Address from a string in the format "x.x.x.x", where x is a number between 0 and 255.
   *
   * @warning The behavior of the ctor is undefined if the input string is not null-terminated.
   * @warning This ctor is not safe if `str` is nullptr.
   * 
   * For exceptions see the ctor with std::string argument.
   */
  // NOLINTNEXTLINE(google-explicit-constructor): ctors are not explicit so it can be used for implicit conversions from string literals
  IpV4Address(char const* str);

  /**
   * @brief Constructs an IpV4Address from a string in the format "x.x.x.x", where x is a number between 0 and 255.
   * 
   * @throws std::invalid_argument if the input string is empty.
   * @throws std::out_of_range if the input string does not contain exactly 4 segments, or if any segment is not a number between 0 and 255.
   */
  // NOLINTNEXTLINE(google-explicit-constructor): ctors are not explicit so it can be used for implicit conversions from string literals
  IpV4Address(std::string const& str);

  explicit IpV4Address(std::array<std::uint8_t, 4> bytes);

  auto toString() const -> std::string;

  auto bytes() const -> std::array<std::uint8_t, 4> const&
  {
    return m_bytes;
  }

private:
  std::array<std::uint8_t, 4> m_bytes;
};

} // namespace sick
