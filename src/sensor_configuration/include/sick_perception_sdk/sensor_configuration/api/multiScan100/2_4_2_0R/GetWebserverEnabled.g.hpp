/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file GetWebserverEnabled.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once


namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /GetWebserverEnabled.
*/
struct GetWebserverEnabled
{

  constexpr static const char* methodName = "GetWebserverEnabled";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Returns the availability of the web server.
   */
  struct Post
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool IsEnabled)
        : _IsEnabled(IsEnabled)
      {}

      bool _IsEnabled;
    };

  }; // struct Post

}; // struct GetWebserverEnabled

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
