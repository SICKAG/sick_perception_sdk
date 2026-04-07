/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file TSCTCupdatetime.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::picoScan120::v2_2_1_0R::api::rest {

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

      explicit Response(NumericRange<std::uint32_t, 1, 3600, 600> TSCTCupdatetime)
        : _TSCTCupdatetime(std::move(TSCTCupdatetime))
      {}

      NumericRange<std::uint32_t, 1, 3600, 600> _TSCTCupdatetime;
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

      explicit Request(NumericRange<std::uint32_t, 1, 3600, 600> TSCTCupdatetime)
        : _TSCTCupdatetime(std::move(TSCTCupdatetime))
      {}

      NumericRange<std::uint32_t, 1, 3600, 600> _TSCTCupdatetime;
    };

  }; // struct Post

}; // struct TSCTCupdatetime

} // namespace sick::picoScan120::v2_2_1_0R::api::rest
