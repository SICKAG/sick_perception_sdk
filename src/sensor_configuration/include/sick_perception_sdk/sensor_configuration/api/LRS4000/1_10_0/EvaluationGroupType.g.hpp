/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EvaluationGroupType.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.10.0'.
 * Do not edit manually!
 */
#pragma once

#include <array>
#include <cstdint>

namespace sick::LRS4000::v1_10_0::api::rest {

/**
 * @brief Payloads for endpoint /EvaluationGroupType.
*/
struct EvaluationGroupType
{

  constexpr static const char* variableName = "EvaluationGroupType";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Reads the evaluation group type weather it`s a field evaluation or perpendicular distance.
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

  /**
   * @brief Reads the evaluation group type weather it`s a field evaluation or perpendicular distance.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(std::array<std::uint8_t, 48> EvaluationGroupType)
        : _EvaluationGroupType(EvaluationGroupType)
      {}

      std::array<std::uint8_t, 48> _EvaluationGroupType;
    };

  }; // struct Post

}; // struct EvaluationGroupType

} // namespace sick::LRS4000::v1_10_0::api::rest
