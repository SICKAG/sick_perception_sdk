/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file DeviceIdent.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <string>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /DeviceIdent.
*/
struct DeviceIdent
{

  constexpr static const char* variableName = "DeviceIdent";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the device name and firmware version.
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

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
