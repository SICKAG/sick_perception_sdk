/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file groundFilterEnable.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /groundFilterEnable.
*/
struct groundFilterEnable
{

  constexpr static const char* variableName = "groundFilterEnable";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/set the ground filter enable.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool groundFilterEnable)
        : _groundFilterEnable(groundFilterEnable)
      {}

      bool _groundFilterEnable;
    };

  }; // struct Get

  /**
   * @brief Returns/set the ground filter enable.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool groundFilterEnable)
        : _groundFilterEnable(groundFilterEnable)
      {}

      bool _groundFilterEnable;
    };

  }; // struct Post

}; // struct groundFilterEnable

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
