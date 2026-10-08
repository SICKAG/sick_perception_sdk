/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EvaluationGroupType.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once

#include <array>
#include <cstdint>

namespace sick::picoScan150::v2_2_1::api::rest {

/**
 * @brief Payloads for endpoint /EvaluationGroupType.
*/
struct EvaluationGroupType
{

  constexpr static const char* variableName = "EvaluationGroupType";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the evaluation group type, whether it is a field evaluation or a perpendicular distance field.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::array<std::uint8_t, 48> EvaluationGroupType)
        : _EvaluationGroupType(EvaluationGroupType)
      {}

      std::array<std::uint8_t, 48> _EvaluationGroupType;
    };

  }; // struct Get

}; // struct EvaluationGroupType

} // namespace sick::picoScan150::v2_2_1::api::rest
