/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file FieldEvaluationResult.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /FieldEvaluationResult.
*/
struct FieldEvaluationResult
{

  constexpr static const char* variableName = "FieldEvaluationResult";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the state of all possible fields.
   */
  struct Get
  {
    struct Response
    {
      struct FieldEvaluationResult
      {
        struct EvaluationResultListItem
        {
          enum class State
          {
            NotConfigured = 0,
            Inactive = 1,
            Free = 2,
            DetectingInfringed = 3,
            Infringed = 4,
            DetectingFree = 5,
          };

          EvaluationResultListItem() = default;

          explicit EvaluationResultListItem(State State)
            : _State(State)
          {}

          State _State;
        };

        FieldEvaluationResult() = default;

        explicit FieldEvaluationResult(std::uint16_t Version, std::uint64_t Timestamp, std::vector<EvaluationResultListItem> EvaluationResultList)
          : _Version(Version), _Timestamp(Timestamp), _EvaluationResultList(EvaluationResultList)
        {}

        std::uint16_t _Version;
        std::uint64_t _Timestamp;
        std::vector<EvaluationResultListItem> _EvaluationResultList;
      };

      Response() = default;

      explicit Response(FieldEvaluationResult FieldEvaluationResult)
        : _FieldEvaluationResult(FieldEvaluationResult)
      {}

      FieldEvaluationResult _FieldEvaluationResult;
    };

  }; // struct Get

}; // struct FieldEvaluationResult

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
