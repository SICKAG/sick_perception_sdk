/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file compactTelegramType1Content.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan120::v2_3_3::api::rest {

/**
 * @brief Payloads for endpoint /compactTelegramType1Content.
*/
struct compactTelegramType1Content
{

  constexpr static const char* variableName = "compactTelegramType1Content";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the content of the Compact telegram type 1 (e.g. whether to include the RSSI values).
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool includeRssi, bool includeProperties)
        : _includeRssi(includeRssi), _includeProperties(includeProperties)
      {}

      bool _includeRssi;
      bool _includeProperties;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the content of the Compact telegram type 1 (e.g. whether to include the RSSI values).

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool includeRssi, bool includeProperties)
        : _includeRssi(includeRssi), _includeProperties(includeProperties)
      {}

      bool _includeRssi;
      bool _includeProperties;
    };

  }; // struct Post

}; // struct compactTelegramType1Content

} // namespace sick::picoScan120::v2_3_3::api::rest
