/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EvaluationsToLog.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.10.0'.
 * Do not edit manually!
 */
#pragma once

#include <array>

namespace sick::LRS4000::v1_10_0::api::rest {

/**
 * @brief Payloads for endpoint /EvaluationsToLog.
*/
struct EvaluationsToLog
{

  constexpr static const char* variableName = "EvaluationsToLog";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the evaluations which are logged (if they are in use).
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::array<bool, 48> EvaluationsToLog)
        : _EvaluationsToLog(EvaluationsToLog)
      {}

      std::array<bool, 48> _EvaluationsToLog;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the evaluations which are logged (if they are in use).
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(std::array<bool, 48> EvaluationsToLog)
        : _EvaluationsToLog(EvaluationsToLog)
      {}

      std::array<bool, 48> _EvaluationsToLog;
    };

  }; // struct Post

}; // struct EvaluationsToLog

} // namespace sick::LRS4000::v1_10_0::api::rest
