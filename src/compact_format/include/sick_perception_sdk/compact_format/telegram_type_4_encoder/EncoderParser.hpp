/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/ByteView.hpp>
#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/compact_format/CompactParser.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_4_encoder/EncoderData.hpp>

#include <optional>
#include <vector>

namespace sick::compact::encoder {

class SDK_EXPORT Parser : public CompactParser
{
public:
  using DataT = EncoderData;

  static auto validateAndParse(ByteView data, bool validateChecksum) -> DataT;

  auto getSize(ByteView data) const -> std::optional<size_t> override;
};

} // namespace sick::compact::encoder
