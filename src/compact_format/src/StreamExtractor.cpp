/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/StreamExtractor.hpp>

#include "CompactParserContext.hpp"
#include "CompactTelegram.hpp"
#include <sick_perception_sdk/common/ByteView.hpp>
#include <sick_perception_sdk/common/logging/logging.hpp>
#include <sick_perception_sdk/compact_format/CompactData.hpp>
#include <sick_perception_sdk/compact_format/CompactParser.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanDataParser.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_2_imu_legacy/ImuLegacyParser.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_3_ambient_light/AmbientLightParser.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_4_encoder/EncoderParser.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_6_multiScan200/MultiScan200Parser.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_7_imu/ImuParser.hpp>

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring> // for std::memcpy
#include <exception>
#include <iterator>
#include <memory>
#include <optional>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

// NOLINTBEGIN(misc-no-recursion): recursion is necessary for resolution of multiple data packages

namespace sick::compact {

constexpr std::array<std::uint8_t, 4> kStxBytes = {0x02, 0x02, 0x02, 0x02};

namespace {

// A telegram always starts with the STX sequence immediately followed by a 4-byte telegram type.
constexpr std::size_t kStartOfTelegramSize = kStxBytes.size() + telegram::header::kTelegramType.sizeInBytes;

// Creates the parser for the given telegram type, or nullptr if it is not a known telegram type.
auto makeParserForTelegramType(TelegramType telegramType) -> std::unique_ptr<CompactParser>
{
  switch (telegramType)
  {
  case TelegramType::ScanData:
    return std::make_unique<scan_data::Parser>();
  case TelegramType::ImuLegacy:
    return std::make_unique<imu_legacy::Parser>();
  case TelegramType::Encoder:
    return std::make_unique<encoder::Parser>();
  case TelegramType::AmbientLight:
    return std::make_unique<ambient_light::Parser>();
  case TelegramType::MultiScan200:
    return std::make_unique<multiscan200::Parser>();
  case TelegramType::Imu:
    return std::make_unique<imu::Parser>();
  default:
    return nullptr;
  }
}

} // namespace

StreamExtractor::StreamExtractor(std::size_t maxTelegramSizeInBytes)
  : m_buffer()
  , m_state(State::WaitingForStx)
  , m_stxPositionInBuffer {0}
  , m_parser(nullptr)
  , m_maxTelegramSizeInBytes(maxTelegramSizeInBytes)
{ }

auto StreamExtractor::getBufferFromStx() const -> ByteView
{
  return ByteView(m_buffer).subview(m_stxPositionInBuffer);
}

auto StreamExtractor::extractTelegrams(ByteView newData) -> std::vector<std::vector<std::uint8_t>>
{
  std::vector<std::vector<std::uint8_t>> result;

  try
  {
    m_buffer.insert(m_buffer.end(), newData.begin(), newData.end());

    // Use iteration instead of recursion to avoid stack overflow
    while (true)
    {
      auto const previousState = m_state;

      switch (m_state)
      {
      case State::WaitingForStx:
        findStx();
        break;
      case State::WaitingForChecksum:
      {
        auto packet = extractPacket();
        if (packet.has_value())
        {
          result.push_back(std::move(packet.value()));
          continue;
        }
        break;
      }
      default:
        throw std::logic_error("Unknown state in StreamExtractor state machine.");
      }

      // If state changed, we made progress - continue processing the buffer
      if (m_state != previousState)
      {
        continue;
      }

      // State didn't change - we're waiting for more data
      return result;
    }
  }
  catch (std::exception const& exception)
  {
    LOG_FAST_LOOP_WARNING("StreamExtractor") << "Data packet extraction from stream failed: " << exception.what();
    discardStx();
    m_state = State::WaitingForStx;
    return result;
  }
}

void StreamExtractor::discardStx()
{
  // Discard everything up to and including the detected STX so the next findStx() resumes after it.
  // If the STX is only partially present it sits at the buffer tail; discard that partial STX as well so its
  // remaining bytes cannot be re-detected as the same STX once the rest of it arrives.
  std::size_t const numberOfBytesToDiscard = std::min(m_stxPositionInBuffer + kStxBytes.size(), m_buffer.size());
  // AXIVION Next Construct CertC++-CTR55: iterator increment is safe because numberOfBytesToDiscard is clamped to the buffer size.
  m_buffer.erase(m_buffer.begin(), m_buffer.begin() + static_cast<std::ptrdiff_t>(numberOfBytesToDiscard));
  m_stxPositionInBuffer = 0;
}

void StreamExtractor::findStx()
{
  LOG_FAST_LOOP_INFO("StreamExtractor") << "Searching for start of telegram (STX + telegram type).";
  m_state = State::WaitingForStx;
  ByteView const view(m_buffer);

  // Searching for the STX sequence alone is not robust because 0x02 bytes occur frequently in telegram payloads.
  // A telegram start is therefore only accepted if the STX is immediately followed by a known telegram type.
  auto const* searchBegin = view.begin();
  while (true)
  {
    auto const* const stxIt = std::search(searchBegin, view.end(), kStxBytes.begin(), kStxBytes.end());
    if (stxIt == view.end())
    {
      break; // No STX candidate in the remaining buffer.
    }
    auto const stxOffset = static_cast<std::size_t>(std::distance(view.begin(), stxIt));
    if (stxOffset + kStartOfTelegramSize > view.size())
    {
      break; // STX found but the telegram type has not fully arrived yet.
    }

    CompactParserContext context {view.subview(stxOffset)};
    context.skipValue(telegram::header::kStartOfFrame);
    auto const telegramType = context.readValueUnsafe<TelegramType>(telegram::header::kTelegramType);
    if (auto parser = makeParserForTelegramType(telegramType))
    {
      m_stxPositionInBuffer = stxOffset;
      m_parser              = std::move(parser);
      m_state               = State::WaitingForChecksum;
      LOG_FAST_LOOP_INFO("StreamExtractor") << "Start of telegram found at position " << stxOffset << " with telegram type "
                                            << static_cast<std::underlying_type_t<TelegramType>>(telegramType) << " (buffer size " << m_buffer.size() << ").";
      return;
    }

    // STX not followed by a known telegram type: a telegram cannot start here. Continue searching after this STX byte.
    searchBegin = std::next(stxIt);
  }

  LOG_FAST_LOOP_INFO("StreamExtractor") << "No start of telegram found. Waiting for more data.";
  // Keep only the trailing bytes that could be the prefix of a start-of-telegram sequence split across chunks and
  // discard everything before to bound buffer growth.
  constexpr std::size_t maxStartOfTelegramFragmentSize = kStartOfTelegramSize - 1;
  if (m_buffer.size() > maxStartOfTelegramFragmentSize)
  {
    m_buffer.erase(m_buffer.begin(), m_buffer.end() - static_cast<std::ptrdiff_t>(maxStartOfTelegramFragmentSize));
  }
  m_stxPositionInBuffer = m_buffer.size();
}

auto StreamExtractor::extractPacket() -> std::optional<std::vector<std::uint8_t>>
{
  if (m_parser == nullptr)
  {
    throw std::runtime_error("No valid Compact telegram received yet.");
  }

  LOG_FAST_LOOP_INFO("StreamExtractor") << "Validating and extracting packet.";
  m_state         = State::WaitingForChecksum;
  auto const view = getBufferFromStx();
  auto const size = m_parser->getSize(view);
  if (!size.has_value())
  {
    if (view.size() >= m_maxTelegramSizeInBytes)
    {
      // We have buffered more than any valid telegram yet still cannot determine a size: a false start-of-frame
      // (e.g. a misaligned stream after data loss) whose garbage header demands an implausible amount of data. Resync.
      LOG_WARNING("StreamExtractor") << "Buffered " << view.size() << " bytes without a determinable telegram size (max " << m_maxTelegramSizeInBytes
                                     << " bytes). Discarding STX.";
      discardStx();
      m_state = State::WaitingForStx;
      return std::nullopt;
    }
    LOG_FAST_LOOP_INFO("StreamExtractor") << "Not enough data to compute the size of the data package. Waiting for more data.";
    return std::nullopt;
  }

  if (size.value() > m_maxTelegramSizeInBytes)
  {
    // A size beyond any plausible telegram means we locked onto a false start-of-frame; resync instead of waiting forever.
    LOG_FAST_LOOP_WARNING("StreamExtractor") << "Computed telegram size " << size.value() << " exceeds the maximum of " << m_maxTelegramSizeInBytes
                                             << " bytes. Discarding STX.";
    discardStx();
    m_state = State::WaitingForStx;
    return std::nullopt;
  }
  if (view.size() < size.value())
  {
    LOG_FAST_LOOP_INFO("StreamExtractor") << "Not enough data for the whole data package. Waiting for more data.";
    return std::nullopt;
  }

  auto const telegramView = view.first(size.value());

  try
  {
    CompactParser::validateChecksum(telegramView);
    // Invalid checksums are, in the truest sense of the word, an exception and not an expected part of regular control flow.
    // Therefore, we catch the exception here and handle it gracefully.
  }
  catch (std::invalid_argument const&)
  {
    LOG_WARNING("StreamExtractor") << "Checksum check failed. Not synchronized. Discarding STX.";
    discardStx();
    m_state = State::WaitingForStx;
    return std::nullopt;
  }

  // Don't make const to allow for automatic move.
  auto dataPackage = telegramView.toVector();

  m_buffer.erase(m_buffer.begin(), m_buffer.begin() + static_cast<std::ptrdiff_t>(m_stxPositionInBuffer + size.value()));
  m_stxPositionInBuffer = 0;
  m_state               = State::WaitingForStx;
  return dataPackage;
}

} // namespace sick::compact

// NOLINTEND(misc-no-recursion)
