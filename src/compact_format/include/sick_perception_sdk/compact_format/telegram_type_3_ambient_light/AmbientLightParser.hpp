/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/ByteView.hpp>
#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/compact_format/CompactParser.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_3_ambient_light/AmbientLightData.hpp>

#include <vector>

namespace sick::compact::ambient_light {

class SDK_EXPORT Parser : public CompactParser
{
public:
  using DataT = AmbientLightData;

  /**
   * @throws std::invalid_argument if validation or parsing fails.
   */
  static auto validateAndParse(ByteView data, bool validateChecksum) -> DataT;

  auto getSize(ByteView data) const -> std::optional<std::size_t> override;
};

} // namespace sick::compact::ambient_light
