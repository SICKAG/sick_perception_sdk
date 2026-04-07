/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EvaluationConfigState.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

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

      Response() = default;

      explicit Response(ActiveBeamsLimit ActiveBeamsLimit, ActiveEvaluationsLimit ActiveEvaluationsLimit, std::vector<std::uint16_t> NumberOfIntersectingBeams, std::vector<std::uint16_t> InputIsOutputErrorList)
        : _ActiveBeamsLimit(ActiveBeamsLimit), _ActiveEvaluationsLimit(ActiveEvaluationsLimit), _NumberOfIntersectingBeams(NumberOfIntersectingBeams), _InputIsOutputErrorList(InputIsOutputErrorList)
      {}

      ActiveBeamsLimit _ActiveBeamsLimit;
      ActiveEvaluationsLimit _ActiveEvaluationsLimit;
      std::vector<std::uint16_t> _NumberOfIntersectingBeams;
      std::vector<std::uint16_t> _InputIsOutputErrorList;
    };

  }; // struct Get

}; // struct EvaluationConfigState

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
