/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file FieldEvaluationApplicationState.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once


namespace sick::multiScan200::v1_1_0::api::rest {

/**
 * @brief Payloads for endpoint /FieldEvaluationApplicationState.
*/
struct FieldEvaluationApplicationState
{

  constexpr static const char* variableName = "FieldEvaluationApplicationState";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the state (DEACTIVATED, ACTIVE, CONFIGURING, ERROR) of the field evaluation.
   */
  struct Get
  {
    struct Response
    {
      enum class FieldEvaluationApplicationState
      {
        Deactivated = 0,
        Active = 1,
        Configuring = 2,
        Error = 3,
      };

      Response() = default;

      explicit Response(FieldEvaluationApplicationState FieldEvaluationApplicationState)
        : _FieldEvaluationApplicationState(FieldEvaluationApplicationState)
      {}

      FieldEvaluationApplicationState _FieldEvaluationApplicationState;
    };

  }; // struct Get

}; // struct FieldEvaluationApplicationState

} // namespace sick::multiScan200::v1_1_0::api::rest
