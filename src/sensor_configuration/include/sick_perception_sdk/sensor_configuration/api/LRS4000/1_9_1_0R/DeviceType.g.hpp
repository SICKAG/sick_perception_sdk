/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file DeviceType.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <string>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

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

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
