/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file FieldEvaluationApplicationState.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /FieldEvaluationApplicationState.
*/
struct FieldEvaluationApplicationState
{

  constexpr static const char* variableName = "FieldEvaluationApplicationState";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Get the field evaluation application state. It returns the information whether the field evaluation application is active, configuring or deactivated. 0 - Deactivated - no evaluation is set up. 1 - Activated - at least one active evaluation (group activation has no influence on that). 2 - Configuring - new calculation of the e.g. field geometries.
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

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
