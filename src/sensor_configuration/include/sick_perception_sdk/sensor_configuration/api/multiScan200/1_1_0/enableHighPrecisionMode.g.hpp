/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file enableHighPrecisionMode.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once


namespace sick::multiScan200::v1_1_0::api::rest {

/**
 * @brief Payloads for endpoint /enableHighPrecisionMode.
*/
struct enableHighPrecisionMode
{

  constexpr static const char* variableName = "enableHighPrecisionMode";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the high precision mode (temporal moving averaging).
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool enableHighPrecisionMode)
        : _enableHighPrecisionMode(enableHighPrecisionMode)
      {}

      bool _enableHighPrecisionMode;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the high precision mode (temporal moving averaging).

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool enableHighPrecisionMode)
        : _enableHighPrecisionMode(enableHighPrecisionMode)
      {}

      bool _enableHighPrecisionMode;
    };

  }; // struct Post

}; // struct enableHighPrecisionMode

} // namespace sick::multiScan200::v1_1_0::api::rest
