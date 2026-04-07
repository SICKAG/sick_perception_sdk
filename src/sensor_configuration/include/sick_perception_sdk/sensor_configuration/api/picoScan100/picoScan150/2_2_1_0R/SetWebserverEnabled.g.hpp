/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file SetWebserverEnabled.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once


namespace sick::picoScan150::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /SetWebserverEnabled.
*/
struct SetWebserverEnabled
{

  constexpr static const char* methodName = "SetWebserverEnabled";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Sets availability of the webserver (reboot required). If disabled, the webserver-based GUI and the REST interface cannot be used anymore.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool Enable)
        : _Enable(Enable)
      {}

      bool _Enable;
    };

  }; // struct Post

}; // struct SetWebserverEnabled

} // namespace sick::picoScan150::v2_2_1_0R::api::rest
