/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

#pragma once

namespace sick {

/**
 * @brief Definitions of known log levels.
 * 
 * @note The order of the log levels in the enum matters for filtering log messages
 * and is from highest severity to lowest severity.
 */
enum class LogLevel
{
  //! @brief An error occurred that causes the driver to abort. For example: "The connection timed out."
  Error,

  //! @brief A warning occurred that might cause problems. For example: "An empty segment was received."
  Warning,

  //! @brief Use this to log nominal behaviour of the driver. Do not use this to log messages with high frequency. For
  //! example: "Successfully connected to the sensor."
  Info,

  //! @brief Use this log level for unexpected situations which may occur at high frequency. For example: "Unsupported
  //! telegram type. Discarding STX."
  FastLoopWarning,

  //! @brief Use this log level for expected situations which may occur at high frequency. For example: "STX found at
  //! position 42."
  FastLoopInfo,
};

} // namespace sick
