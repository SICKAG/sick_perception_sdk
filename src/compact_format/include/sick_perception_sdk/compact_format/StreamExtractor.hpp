/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/
#pragma once

#include <sick_perception_sdk/common/ByteView.hpp>
#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/compact_format/CompactParser.hpp>

#include <memory>
#include <vector>

namespace sick::compact {

class SDK_EXPORT StreamExtractor
{
public:
  /**
   * @brief Upper bound on a single Compact telegram.
   * 
   * A telegram or module size above this, or buffering this many bytes from a start-of-frame 
   * without being able to determine a size, is treated as a false start-of-frame and triggers a
   * resync. 
   *
   * Raise it via the constructor if a device emits larger telegrams.
   */
  static constexpr std::size_t kDefaultMaxTelegramSizeInBytes = 100'000'000;

  explicit StreamExtractor(std::size_t maxTelegramSizeInBytes = kDefaultMaxTelegramSizeInBytes);

  /**
   * @brief Extract all complete Compact telegrams from a stream of bytes.
   *
   * The data from @p newData is copied into the internal buffer. This function does not take
   * ownership of the input - the caller's data remains valid and unmodified.
   * The returned data is a copy of the internal buffer. Ownership is transferred to the caller.
   *
   * @param newData The new data to process.
   * @return A vector of complete telegrams extracted from the accumulated data.
   */
  auto extractTelegrams(ByteView newData) -> std::vector<std::vector<std::uint8_t>>;

private:
  enum class State
  {
    WaitingForStx      = 1,
    WaitingForChecksum = 2,
  };

  std::vector<std::uint8_t> m_buffer;
  State m_state;
  std::size_t m_stxPositionInBuffer;
  std::unique_ptr<CompactParser> m_parser;
  std::size_t m_maxTelegramSizeInBytes;

  auto getBufferFromStx() const -> ByteView;

  void discardStx();

  void findStx();

  auto extractPacket() -> std::optional<std::vector<std::uint8_t>>;
};

} // namespace sick::compact
