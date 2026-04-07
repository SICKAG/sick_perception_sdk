/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file FieldEvaluationGroupState.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan150::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /FieldEvaluationGroupState.
*/
struct FieldEvaluationGroupState
{

  constexpr static const char* variableName = "FieldEvaluationGroupState";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the activation condition for all existing evaluation groups (not configured, active, or inactive).
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::array<int, 48> FieldEvaluationGroupState)
        : _FieldEvaluationGroupState(FieldEvaluationGroupState)
      {}

      std::array<int, 48> _FieldEvaluationGroupState;
    };

  }; // struct Get

}; // struct FieldEvaluationGroupState

} // namespace sick::picoScan150::v2_2_1_0R::api::rest
