/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ParticleFilter.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /ParticleFilter.
*/
struct ParticleFilter
{

  constexpr static const char* variableName = "ParticleFilter";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the particle filter settings. Filters out disturbances in the measurement data caused by particles such as dust, snowflakes, or similar. Configure the minimal threshold of the required distance step (mm) between the echo to be filtered and the echoes of surrounding beam angles.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool bEnable, NumericRange<std::uint16_t, 500, 5000, 1000> uiThreshold)
        : _bEnable(bEnable), _uiThreshold(std::move(uiThreshold))
      {}

      bool _bEnable;
      NumericRange<std::uint16_t, 500, 5000, 1000> _uiThreshold;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the particle filter settings. Filters out disturbances in the measurement data caused by particles such as dust, snowflakes, or similar. Configure the minimal threshold of the required distance step (mm) between the echo to be filtered and the echoes of surrounding beam angles.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool bEnable, NumericRange<std::uint16_t, 500, 5000, 1000> uiThreshold)
        : _bEnable(bEnable), _uiThreshold(std::move(uiThreshold))
      {}

      bool _bEnable;
      NumericRange<std::uint16_t, 500, 5000, 1000> _uiThreshold;
    };

  }; // struct Post

}; // struct ParticleFilter

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
