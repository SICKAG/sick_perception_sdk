/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file TSCTCupdatetime.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::multiScan200::v1_1_0::api::rest {

/**
 * @brief Payloads for endpoint /TSCTCupdatetime.
*/
struct TSCTCupdatetime
{

  constexpr static const char* variableName = "TSCTCupdatetime";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the update time of the client.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(NumericRange<int, 1, 3600, 600> TSCTCupdatetime)
        : _TSCTCupdatetime(TSCTCupdatetime)
      {}

      NumericRange<int, 1, 3600, 600> _TSCTCupdatetime;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the update time of the client.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(NumericRange<int, 1, 3600, 600> TSCTCupdatetime)
        : _TSCTCupdatetime(TSCTCupdatetime)
      {}

      NumericRange<int, 1, 3600, 600> _TSCTCupdatetime;
    };

  }; // struct Post

}; // struct TSCTCupdatetime

} // namespace sick::multiScan200::v1_1_0::api::rest
