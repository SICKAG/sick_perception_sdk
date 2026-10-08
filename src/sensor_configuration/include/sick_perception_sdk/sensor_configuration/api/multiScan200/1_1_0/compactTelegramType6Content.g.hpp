/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file compactTelegramType6Content.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once


namespace sick::multiScan200::v1_1_0::api::rest {

/**
 * @brief Payloads for endpoint /compactTelegramType6Content.
*/
struct compactTelegramType6Content
{

  constexpr static const char* variableName = "compactTelegramType6Content";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Return/sets the optional channels in the scan data compact telegram type 6 (muls270 specific compact format.).
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool includeRssi, bool includeProperties, bool includeAmbientLight, bool reserved)
        : _includeRssi(includeRssi), _includeProperties(includeProperties), _includeAmbientLight(includeAmbientLight), _reserved(reserved)
      {}

      bool _includeRssi;
      bool _includeProperties;
      bool _includeAmbientLight;
      bool _reserved;
    };

  }; // struct Get

  /**
   * @brief Return/sets the optional channels in the scan data compact telegram type 6 (muls270 specific compact format.).

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool includeRssi, bool includeProperties, bool includeAmbientLight, bool reserved)
        : _includeRssi(includeRssi), _includeProperties(includeProperties), _includeAmbientLight(includeAmbientLight), _reserved(reserved)
      {}

      bool _includeRssi;
      bool _includeProperties;
      bool _includeAmbientLight;
      bool _reserved;
    };

  }; // struct Post

}; // struct compactTelegramType6Content

} // namespace sick::multiScan200::v1_1_0::api::rest
