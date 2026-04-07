/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file MCSenseLevel.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /MCSenseLevel.
*/
struct MCSenseLevel
{

  constexpr static const char* variableName = "MCSenseLevel";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the fog filter settings.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(NumericRange<std::uint8_t, 0, 1, 0> MCSenseLevel)
        : _MCSenseLevel(std::move(MCSenseLevel))
      {}

      NumericRange<std::uint8_t, 0, 1, 0> _MCSenseLevel;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the fog filter settings.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(NumericRange<std::uint8_t, 0, 1, 0> MCSenseLevel)
        : _MCSenseLevel(std::move(MCSenseLevel))
      {}

      NumericRange<std::uint8_t, 0, 1, 0> _MCSenseLevel;
    };

  }; // struct Post

}; // struct MCSenseLevel

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
