/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file DeviceIdent.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once

#include <string>

namespace sick::picoScan120::v2_2_1::api::rest {

/**
 * @brief Payloads for endpoint /DeviceIdent.
*/
struct DeviceIdent
{

  constexpr static const char* variableName = "DeviceIdent";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the device name and the firmware version.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::string Name, std::string Version)
        : _Name(std::move(Name)), _Version(std::move(Version))
      {}

      std::string _Name;
      std::string _Version;
    };

  }; // struct Get

}; // struct DeviceIdent

} // namespace sick::picoScan120::v2_2_1::api::rest
