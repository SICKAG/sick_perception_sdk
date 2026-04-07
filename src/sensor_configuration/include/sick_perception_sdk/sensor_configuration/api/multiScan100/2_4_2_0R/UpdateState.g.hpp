/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file UpdateState.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::multiScan100::v2_4_2_0R::api::rest {

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

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
