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
  static constexpr std::uint32_t kExpectedStartOfFrame = 0x02020202u;

  CompactParser()                                        = default;
  virtual ~CompactParser()                               = default;
  CompactParser(CompactParser const&)                    = default;
  auto operator=(CompactParser const&) -> CompactParser& = default;
  CompactParser(CompactParser&&)                         = default;
  auto operator=(CompactParser&&) -> CompactParser&      = default;

  /**
   * @brief Get the size of the complete telegram (header + payload + checksum) if enough data is available to determine the size,
   *        otherwise std::nullopt.
   * 
   * @note Implementations that depend on the data **do not validate the checksum**, i.e. the size returned by this function my be invalid
   *       and should be validated by the caller.
   */
  virtual auto getSize(ByteView data) const -> std::optional<std::size_t> = 0;

  /**
   * @brief Checks if the checksum of the data is valid.
   *
   * Assumes that the CRC32 is the last four bytes of the data,
   * i.e. starts at data.size() - 4.
   * 
   * @throws std::invalid_argument if the data is too short to contain a checksum or if the checksum is invalid.
   */
  static void validateChecksum(ByteView data);
};

} // namespace sick::compact
