/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file SetWebserverEnabled.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once


namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /SetWebserverEnabled.
*/
struct SetWebserverEnabled
{

  constexpr static const char* methodName = "SetWebserverEnabled";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Sets availability of the webserver (reboot required). If disabled, the webserver-based GUI and the REST interface can not be used anymore.

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

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
