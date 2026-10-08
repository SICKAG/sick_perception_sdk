/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file FirmwareVersion.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once

#include <string>

namespace sick::picoScan150::v2_2_1::api::rest {

/**
 * @brief Payloads for endpoint /FirmwareVersion.
*/
struct FirmwareVersion
{

  constexpr static const char* variableName = "FirmwareVersion";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the current firmware version.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::string FirmwareVersion)
        : _FirmwareVersion(std::move(FirmwareVersion))
      {}

      std::string _FirmwareVersion;
    };

  }; // struct Get

}; // struct FirmwareVersion

} // namespace sick::picoScan150::v2_2_1::api::rest
