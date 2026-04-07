/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file SCdevicestate.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /SCdevicestate.
*/
struct SCdevicestate
{

  constexpr static const char* variableName = "SCdevicestate";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the device state (busy, ready, or ready).
   */
  struct Get
  {
    struct Response
    {
      enum class SCdevicestate
      {
        Busy = 0,
        Ready = 1,
        Error = 2,
      };

      Response() = default;

      explicit Response(SCdevicestate SCdevicestate)
        : _SCdevicestate(SCdevicestate)
      {}

      SCdevicestate _SCdevicestate;
    };

  }; // struct Get

}; // struct SCdevicestate

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
