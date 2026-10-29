/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/ByteView.hpp>
#include <sick_perception_sdk/common/logging/logging.hpp>
#include <sick_perception_sdk/compact_format/StreamExtractor.hpp>

#include <functional>
#include <string>
#include <utility>

namespace sick::compact {

/**
 * @brief Decodes byte-oriented streams, where telegram boundaries have to be recovered first.
 */
template <typename ParserT>
class TelegramStreamDecoder
{
public:
  using DataHandler = std::function<void(typename ParserT::DataT const&)>;

  TelegramStreamDecoder(DataHandler onNewData, std::string streamName)
    : m_onNewData(std::move(onNewData))
    , m_streamName(std::move(streamName))
  { }

  void operator()(ByteView bytes)
  {
    // Skip the parse entirely when the application registered no callback.
    if (!m_onNewData)
    {
      return;
    }

    auto const telegrams = m_extractor.extractTelegrams(bytes);
    LOG_FAST_LOOP_INFO(m_streamName) << "Extracted " << telegrams.size() << " packages.";
    for (auto const& telegram : telegrams)
    {
      // Don't check CRC32 here, because it has already been checked in the StreamExtractor.
      bool const checkCrc32 = false;
      m_onNewData(ParserT::validateAndParse(telegram, checkCrc32));
    }
  }

private:
  StreamExtractor m_extractor;
  DataHandler m_onNewData;
  std::string m_streamName;
};

} // namespace sick::compact
