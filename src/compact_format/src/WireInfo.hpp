/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include "CompactParserContext.hpp"
#include <sick_perception_sdk/compact_format/CompactData.hpp>

#include <set>

namespace sick::compact {

struct TelegramHeaderWireInfo
{
  TelegramType telegramType {TelegramType::Invalid};
  int telegramVersion {0};
  std::size_t payloadLength {0};
};

enum class HeaderReadResult
{
  Ok,
  InsufficientData
};

/**
 * @brief Reads and validates the common header of a Compact telegram.
 * 
 * This function attempts to read and validate the common header of a Compact telegram from the provided `CompactParserContext`. 
 * It checks for the expected telegram type and version, and fills in the provided `TelegramHeader` and `TelegramHeaderWireInfo` 
 * structures with the parsed information.
 * 
 * The error handling is designed to distinguish between normal streaming conditions (where the header has not fully arrived yet) and invalid headers.
 * In the case of insufficient data, the function returns `HeaderReadResult::InsufficientData`. If the header is invalid, an exception is thrown.
 * 
 * @note It depends on the caller context if `HeaderReadResult::InsufficientData` is a normal streaming condition or an error condition. 
 *       The caller should handle this appropriately.
 * 
 * @note This function only validates the start-of-frame (0x02020202), telegram type, and telegram version. It does **not** validate the telegram checksum.
 * 
 * @throws std::invalid_argument if the header is invalid (e.g., unsupported telegram type or version).
 */
[[nodiscard]] auto readAndValidateTelegramHeaderCommon(
  CompactParserContext& context,
  TelegramType expectedType,
  std::set<int> expectedVersions,
  TelegramHeader& telegramHeader,
  TelegramHeaderWireInfo& telegramHeaderWireInfo
) -> HeaderReadResult;

} // namespace sick::compact
