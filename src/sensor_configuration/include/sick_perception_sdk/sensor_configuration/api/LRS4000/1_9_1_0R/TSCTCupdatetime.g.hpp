/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file TSCTCupdatetime.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /TSCTCupdatetime.
*/
struct TSCTCupdatetime
{

  constexpr static const char* variableName = "TSCTCupdatetime";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the NTP update time.
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
   * @brief Returns/sets the NTP update time.
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

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
