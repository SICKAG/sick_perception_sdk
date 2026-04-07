/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EnableLongRangeMode.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan150::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /EnableLongRangeMode.
*/
struct EnableLongRangeMode
{

  constexpr static const char* variableName = "EnableLongRangeMode";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Enables/disables the maximum scanning range depending on the scan configuration.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool EnableLongRangeMode)
        : _EnableLongRangeMode(EnableLongRangeMode)
      {}

      bool _EnableLongRangeMode;
    };

  }; // struct Get

  /**
   * @brief Enables/disables the maximum scanning range depending on the scan configuration.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool EnableLongRangeMode)
        : _EnableLongRangeMode(EnableLongRangeMode)
      {}

      bool _EnableLongRangeMode;
    };

  }; // struct Post

}; // struct EnableLongRangeMode

} // namespace sick::picoScan150::v2_2_1_0R::api::rest
