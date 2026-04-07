/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#include <sick_perception_sdk/compact_format/StreamExtractor.hpp>

#include <sick_perception_sdk/common/ByteView.hpp>
#include <sick_perception_sdk/common/logging/logging.hpp>
#include <sick_perception_sdk/compact_format/CompactData.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_1_scan_data/ScanDataParser.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_2_imu/ImuParser.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_4_encoder/EncoderParser.hpp>

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring> // for std::memcpy
#include <exception>
#include <iterator>
#include <limits>
#include <memory>
#include <optional>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

// NOLINTBEGIN(misc-no-recursion): recursion is necessary for resolution of multiple data packages

namespace sick::compact {

constexpr std::array<std::uint8_t, 4> kStxBytes = {0x02, 0x02, 0x02, 0x02};

StreamExtractor::StreamExtractor()
  : m_buffer()
  , m_state(State::WaitingForStx)
  , m_stxPositionInBuffer {0}
  , m_parser(nullptr)
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
      case State::WaitingForTelegramType:
        readTelegramType();
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
  if (m_buffer.size() >= kStxBytes.size())
  {
    // AXIVION Next Construct CertC++-CTR55: iterator increment is safe because of the size check above.
    m_buffer.erase(m_buffer.begin(), m_buffer.begin() + kStxBytes.size());
  }
}

void StreamExtractor::findStx()
{
  LOG_FAST_LOOP_INFO("StreamExtractor") << "Searching for STX.";
  m_state = State::WaitingForStx;
  ByteView const view(m_buffer);
  auto const* const it  = std::search(view.begin(), view.end(), kStxBytes.begin(), kStxBytes.end());
  m_stxPositionInBuffer = static_cast<std::size_t>(std::distance(view.begin(), it));
  if (m_stxPositionInBuffer == m_buffer.size())
  {
    LOG_FAST_LOOP_INFO("StreamExtractor") << "STX not found. Waiting for more data.";
    return;
  }
  LOG_FAST_LOOP_INFO("StreamExtractor") << "STX found at position " << m_stxPositionInBuffer << ".";

  m_state = State::WaitingForTelegramType;
}

void StreamExtractor::readTelegramType()
{
  LOG_FAST_LOOP_INFO("StreamExtractor") << "Reading telegram type.";
  m_state                   = State::WaitingForTelegramType;
  ByteView const view       = getBufferFromStx();
  TelegramType telegramType = TelegramType::Invalid;
  if (view.size() < kStxBytes.size() + sizeof(telegramType))
  {
    LOG_FAST_LOOP_INFO("StreamExtractor") << "Not enough data for telegram type. Waiting for more data.";
    return;
  }

  // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic): memcpy with pointer arithmetic is necessary here for efficient reading of the telegram type from the buffer.
  std::memcpy(&telegramType, view.data() + kStxBytes.size(), sizeof(telegramType));

  LOG_FAST_LOOP_INFO("StreamExtractor") << "Telegram type: " << static_cast<std::underlying_type_t<TelegramType>>(telegramType);

  if (telegramType == TelegramType::ScanData)
  {
    m_parser = std::make_unique<sick::compact::scan_data::Parser>();
  }
  else if (telegramType == TelegramType::Imu)
  {
    m_parser = std::make_unique<sick::compact::imu::Parser>();
  }
  else if (telegramType == TelegramType::Encoder)
  {
    m_parser = std::make_unique<sick::compact::encoder::Parser>();
  }
  else
  {
    LOG_FAST_LOOP_WARNING("StreamExtractor") << "Unsupported telegram type. Discarding STX.";
    discardStx();
    m_state = State::WaitingForStx;
    return;
  }

  m_state = State::WaitingForChecksum;
}

auto StreamExtractor::extractPacket() -> std::optional<std::vector<std::uint8_t>>
{
  if (m_parser == nullptr)
  {
    throw std::runtime_error("No valid Compact telegram received yet.");
  }

  LOG_FAST_LOOP_INFO("StreamExtractor") << "Validating and extracting packet.";
  m_state                         = State::WaitingForChecksum;
  ByteView const view             = getBufferFromStx();
  std::optional<std::size_t> size = m_parser->getSize(view);
  if (!size.has_value())
  {
    LOG_FAST_LOOP_INFO("StreamExtractor") << "Not enough data to compute the size of the data package. Waiting for more data.";
    return std::nullopt;
  }

  if (size.value() > static_cast<std::size_t>(std::numeric_limits<std::ptrdiff_t>::max()))
  {
    LOG_FAST_LOOP_WARNING("StreamExtractor") << "Data package size is too large, causing overflow. Discarding STX.";
    discardStx();
    m_state = State::WaitingForStx;
    return std::nullopt;
  }
  if (view.size() < size.value())
  {
    LOG_FAST_LOOP_INFO("StreamExtractor") << "Not enough data for the whole data package. Waiting for more data.";
    return std::nullopt;
  }

  ByteView const telegramView = view.first(size.value());

  if (!CompactParser::isChecksumValid(telegramView))
  {
    LOG_FAST_LOOP_WARNING("StreamExtractor") << "CRC check failed. Not synchronized. Discarding STX.";
    discardStx();
    m_state = State::WaitingForStx;
    return std::nullopt;
  }

  std::vector<std::uint8_t> dataPackage = telegramView.toVector();

  m_buffer.erase(m_buffer.begin(), m_buffer.begin() + static_cast<std::ptrdiff_t>(m_stxPositionInBuffer + size.value()));
  m_stxPositionInBuffer = 0;
  m_state               = State::WaitingForStx;
  return dataPackage;
}

} // namespace sick::compact

// NOLINTEND(misc-no-recursion)
