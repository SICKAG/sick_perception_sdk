/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file SyncPhase.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /SyncPhase.
*/
struct SyncPhase
{

  constexpr static const char* methodName = "SyncPhase";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief synchronisation phase difference between master and slave.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(NumericRange<std::int16_t, -180, 180, 180> SyncPhase)
        : _SyncPhase(std::move(SyncPhase))
      {}

      NumericRange<std::int16_t, -180, 180, 180> _SyncPhase;
    };

  }; // struct Post

}; // struct SyncPhase

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
