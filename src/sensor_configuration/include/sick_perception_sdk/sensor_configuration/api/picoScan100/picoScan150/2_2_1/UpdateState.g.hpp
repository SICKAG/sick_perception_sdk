/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file UpdateState.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan150::v2_2_1::api::rest {

/**
 * @brief Payloads for endpoint /UpdateState.
*/
struct UpdateState
{

  constexpr static const char* variableName = "UpdateState";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the state of the update process.
   */
  struct Get
  {
    struct Response
    {
      enum class UpdateState
      {
        Initial = 0,
        Started = 1,
        Finished = 2,
        Error = 3,
      };

      Response() = default;

      explicit Response(UpdateState UpdateState)
        : _UpdateState(UpdateState)
      {}

      UpdateState _UpdateState;
    };

  }; // struct Get

}; // struct UpdateState

} // namespace sick::picoScan150::v2_2_1::api::rest
