/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include "Crc32UtilsImpl.hpp"

#include <sick_perception_sdk/common/ByteView.hpp>

#include <cstdint>

namespace sick::compact {

auto crc32Impl(ByteView data) -> std::uint32_t
{
  constexpr std::uint32_t startValue = 0xffffffffu;
  constexpr std::uint32_t polynomial = 0xedb88320u;
  constexpr int bitsPerByte          = 8;

  std::uint32_t crc = startValue;
  for (std::uint8_t const byte : data)
  {
    crc ^= byte;
    for (int i = 0; i < bitsPerByte; i++)
    {
      crc = static_cast<bool>(crc & 1) ? (crc >> 1) ^ polynomial : crc >> 1;
    }
  }
  return ~crc;
}

} // namespace sick::compact
