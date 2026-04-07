/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file DeviceTime.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /DeviceTime.
*/
struct DeviceTime
{

  constexpr static const char* variableName = "DeviceTime";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the current time of the internal clock (ms). The timer is 32 bit counter with a resolution of 1 ms.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::uint32_t DeviceTime)
        : _DeviceTime(DeviceTime)
      {}

      std::uint32_t _DeviceTime;
    };

  }; // struct Get

}; // struct DeviceTime

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
