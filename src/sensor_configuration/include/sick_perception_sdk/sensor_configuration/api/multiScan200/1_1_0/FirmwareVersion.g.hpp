/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file FirmwareVersion.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <string>

namespace sick::multiScan200::v1_1_0::api::rest {

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

} // namespace sick::multiScan200::v1_1_0::api::rest
