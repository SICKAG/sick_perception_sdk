/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LFPparticle.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /LFPparticle.
*/
struct LFPparticle
{

  constexpr static const char* variableName = "LFPparticle";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the particle filter settings. Filters out disturbances in the measurement data caused by particles such as dust, snowflakes, or similar. Configure the minimal threshold of the required distance step (mm) between the echo to be filtered and the echoes of surrounding beam angles.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool bEnable, NumericRange<std::uint16_t, 20, 5000, 500> uiThreshold)
        : _bEnable(bEnable), _uiThreshold(std::move(uiThreshold))
      {}

      bool _bEnable;
      NumericRange<std::uint16_t, 20, 5000, 500> _uiThreshold;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the particle filter settings. Filters out disturbances in the measurement data caused by particles such as dust, snowflakes, or similar. Configure the minimal threshold of the required distance step (mm) between the echo to be filtered and the echoes of surrounding beam angles.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool bEnable, NumericRange<std::uint16_t, 20, 5000, 500> uiThreshold)
        : _bEnable(bEnable), _uiThreshold(std::move(uiThreshold))
      {}

      bool _bEnable;
      NumericRange<std::uint16_t, 20, 5000, 500> _uiThreshold;
    };

  }; // struct Post

}; // struct LFPparticle

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
