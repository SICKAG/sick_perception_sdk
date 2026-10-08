/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file RebootDevice.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once


namespace sick::multiScan200::v1_1_0::api::rest {

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

} // namespace sick::multiScan200::v1_1_0::api::rest
