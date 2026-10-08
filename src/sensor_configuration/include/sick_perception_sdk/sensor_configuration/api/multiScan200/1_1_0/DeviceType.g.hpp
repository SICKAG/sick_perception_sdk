/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file DeviceType.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <string>

namespace sick::multiScan200::v1_1_0::api::rest {

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

} // namespace sick::multiScan200::v1_1_0::api::rest
