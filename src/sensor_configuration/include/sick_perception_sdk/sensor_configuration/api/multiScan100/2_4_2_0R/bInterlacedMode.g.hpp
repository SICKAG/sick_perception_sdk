/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file bInterlacedMode.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /bInterlacedMode.
*/
struct bInterlacedMode
{

  constexpr static const char* variableName = "bInterlacedMode";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Enables the interlaced mode.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool bInterlacedMode)
        : _bInterlacedMode(bInterlacedMode)
      {}

      bool _bInterlacedMode;
    };

  }; // struct Get

  /**
   * @brief Enables the interlaced mode.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool bInterlacedMode)
        : _bInterlacedMode(bInterlacedMode)
      {}

      bool _bInterlacedMode;
    };

  }; // struct Post

}; // struct bInterlacedMode

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
