/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LEDEnable.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan150::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /LEDEnable.
*/
struct LEDEnable
{

  constexpr static const char* variableName = "LEDEnable";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the LED mode (on/off).
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool LEDEnable)
        : _LEDEnable(LEDEnable)
      {}

      bool _LEDEnable;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the LED mode (on/off).

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool LEDEnable)
        : _LEDEnable(LEDEnable)
      {}

      bool _LEDEnable;
    };

  }; // struct Post

}; // struct LEDEnable

} // namespace sick::picoScan150::v2_2_1_0R::api::rest
