/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/Crc32Utils.hpp>

#include <sick_perception_sdk/common/ByteView.hpp>

#include <cstdint>

#ifdef USE_ZLIB_CRC32
#  include <zconf.h>
#  include <zlib.h>
#else
#  include "Crc32UtilsImpl.hpp"
#endif

namespace sick::compact {

auto crc32(ByteView data) -> std::uint32_t
{
#ifdef USE_ZLIB_CRC32
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
  return ::crc32(0, reinterpret_cast<Bytef const*>(data.data()), static_cast<uInt>(data.size()));
#else
  return crc32Impl(data);
#endif
}

} // namespace sick::compact
