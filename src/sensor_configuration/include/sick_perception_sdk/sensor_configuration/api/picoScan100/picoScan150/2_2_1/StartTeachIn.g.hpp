/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file StartTeachIn.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once


namespace sick::picoScan150::v2_2_1::api::rest {

/**
 * @brief Payloads for endpoint /StartTeachIn.
*/
struct StartTeachIn
{

  constexpr static const char* methodName = "StartTeachIn";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Starts the teach in process.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
  }; // struct Post

}; // struct StartTeachIn

} // namespace sick::picoScan150::v2_2_1::api::rest
