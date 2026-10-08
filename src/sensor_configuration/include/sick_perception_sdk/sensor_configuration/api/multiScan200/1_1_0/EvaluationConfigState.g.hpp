/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EvaluationConfigState.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <vector>

namespace sick::multiScan200::v1_1_0::api::rest {

/**
 * @brief Payloads for endpoint /EvaluationConfigState.
*/
struct EvaluationConfigState
{

  constexpr static const char* variableName = "EvaluationConfigState";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the performance state (OK, WWANING, EXEEDED) of an evaluation config.
   */
  struct Get
  {
    struct Response
    {
      enum class ActiveBeamsLimit
      {
        Ok = 0,
        Warning = 1,
        Exceeded = 2,
      };

      enum class ActiveEvaluationsLimit
      {
        Ok = 0,
        Warning = 1,
        Exceeded = 2,
      };

      enum class ActiveBeamsPerEvaluationLimit
      {
        Ok = 0,
        Warning = 1,
        Exceeded = 2,
      };

      Response() = default;

      explicit Response(ActiveBeamsLimit ActiveBeamsLimit, ActiveEvaluationsLimit ActiveEvaluationsLimit, ActiveBeamsPerEvaluationLimit ActiveBeamsPerEvaluationLimit, std::vector<int> NumberOfIntersectingBeams, std::vector<int> InputIsOutputErrorList)
        : _ActiveBeamsLimit(ActiveBeamsLimit), _ActiveEvaluationsLimit(ActiveEvaluationsLimit), _ActiveBeamsPerEvaluationLimit(ActiveBeamsPerEvaluationLimit), _NumberOfIntersectingBeams(NumberOfIntersectingBeams), _InputIsOutputErrorList(InputIsOutputErrorList)
      {}

      ActiveBeamsLimit _ActiveBeamsLimit;
      ActiveEvaluationsLimit _ActiveEvaluationsLimit;
      ActiveBeamsPerEvaluationLimit _ActiveBeamsPerEvaluationLimit;
      std::vector<int> _NumberOfIntersectingBeams;
      std::vector<int> _InputIsOutputErrorList;
    };

  }; // struct Get

}; // struct EvaluationConfigState

} // namespace sick::multiScan200::v1_1_0::api::rest
