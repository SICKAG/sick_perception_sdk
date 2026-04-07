/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file WriteEeprom.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once


namespace sick::picoScan150::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /WriteEeprom.
*/
struct WriteEeprom
{

  constexpr static const char* methodName = "WriteEeprom";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Saves all parameters permanently.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool Success)
        : _Success(Success)
      {}

      bool _Success;
    };

  }; // struct Post

}; // struct WriteEeprom

} // namespace sick::picoScan150::v2_2_1_0R::api::rest
