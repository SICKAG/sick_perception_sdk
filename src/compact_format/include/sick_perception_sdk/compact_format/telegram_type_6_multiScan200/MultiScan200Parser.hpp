/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <sick_perception_sdk/common/ByteView.hpp>
#include <sick_perception_sdk/common/export.hpp>
#include <sick_perception_sdk/compact_format/CompactParser.hpp>
#include <sick_perception_sdk/compact_format/telegram_type_6_multiScan200/MultiScan200Data.hpp>

#include <vector>

namespace sick::compact::multiscan200 {

/**
 * @brief Parser from the Telegram Type 6 (MultiScan200) byte stream into the intermediate `MultiScan200Data` representation.
 *
 * This can be converted into the internal `PointCloud` representation using the `PointCloudConverter`.
 */
class SDK_EXPORT Parser : public CompactParser
{
public:
  using DataT = MultiScan200Data;

  /**
   * @throws std::invalid_argument if validation or parsing fails.
   */
  static auto validateAndParse(ByteView data, bool validateChecksum) -> DataT;

  auto getSize(ByteView data) const -> std::optional<std::size_t> override;
};

} // namespace sick::compact::multiscan200
