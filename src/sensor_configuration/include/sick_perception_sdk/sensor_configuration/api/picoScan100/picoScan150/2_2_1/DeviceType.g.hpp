/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file DeviceType.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once

#include <string>

namespace sick::picoScan150::v2_2_1::api::rest {

/**
 * @brief Payloads for endpoint /DeviceType.
*/
struct DeviceType
{

  constexpr static const char* variableName = "DeviceType";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the device type.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::string DeviceType)
        : _DeviceType(std::move(DeviceType))
      {}

      std::string _DeviceType;
    };

  }; // struct Get

}; // struct DeviceType

} // namespace sick::picoScan150::v2_2_1::api::rest
