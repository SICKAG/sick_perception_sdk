/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file FieldEvaluationGroupState.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.10.0'.
 * Do not edit manually!
 */
#pragma once

#include <array>
#include <cstdint>

namespace sick::LRS4000::v1_10_0::api::rest {

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

      explicit Response(std::array<std::uint8_t, 48> FieldEvaluationGroupState)
        : _FieldEvaluationGroupState(FieldEvaluationGroupState)
      {}

      std::array<std::uint8_t, 48> _FieldEvaluationGroupState;
    };

  }; // struct Get

}; // struct FieldEvaluationGroupState

} // namespace sick::LRS4000::v1_10_0::api::rest
