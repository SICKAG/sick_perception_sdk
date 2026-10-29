/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/ByteView.hpp>

#include <functional>
#include <utility>

namespace sick::compact {

/**
 * @brief Decodes datagram-oriented streams, where every received chunk is exactly one telegram.
*/
template <typename ParserT>
class DatagramDecoder
{
public:
  using DataHandler = std::function<void(typename ParserT::DataT const&)>;

  explicit DatagramDecoder(DataHandler onNewData)
    : m_onNewData(std::move(onNewData))
  { }

  void operator()(ByteView bytes) const
  {
    if (m_onNewData)
    {
      m_onNewData(ParserT::validateAndParse(bytes, true));
    }
  }

private:
  DataHandler m_onNewData;
};

} // namespace sick::compact
