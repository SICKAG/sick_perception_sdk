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
  StreamExtractor();

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
    WaitingForStx          = 1,
    WaitingForTelegramType = 2,
    WaitingForChecksum     = 3
  };

  std::vector<std::uint8_t> m_buffer;
  State m_state;
  std::size_t m_stxPositionInBuffer;
  std::unique_ptr<CompactParser> m_parser;

  auto getBufferFromStx() const -> ByteView;

  void discardStx();

  void findStx();

  void readTelegramType();

  auto extractPacket() -> std::optional<std::vector<std::uint8_t>>;
};

} // namespace sick::compact
