/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file RebootDevice.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once


namespace sick::picoScan150::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /RebootDevice.
*/
struct RebootDevice
{

  constexpr static const char* methodName = "RebootDevice";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Reboots the device. All parameters are saved.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
  }; // struct Post

}; // struct RebootDevice

} // namespace sick::picoScan150::v2_2_1_0R::api::rest
