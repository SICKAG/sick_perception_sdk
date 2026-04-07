/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

#include <plog/Record.h>

namespace sick {

/**
 * @brief Custom log formatter for plog.
 *
 * This implementation is similar to `plog::TxtFormatter`
 * but prints the file name instead of the function name to the log message.
 * 
 * Log messages will be formatted like this:
 * YYYY-MM-DD hh:mm:ss.ms INFO  [TID 1234] [file path@19] [prefix] message
 */
class CustomFormatter
{
public:
  static auto header() -> plog::util::nstring;
  static auto format(plog::Record const& record) -> plog::util::nstring;
};

} // namespace sick
