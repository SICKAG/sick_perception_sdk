/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EvaluationsToLog.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan150::v2_2_1_0R::api::rest {

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

 This function requires at least user level: Authorized Client.
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

} // namespace sick::picoScan150::v2_2_1_0R::api::rest
