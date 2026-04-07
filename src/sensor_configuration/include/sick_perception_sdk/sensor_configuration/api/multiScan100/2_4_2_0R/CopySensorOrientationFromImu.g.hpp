/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file CopySensorOrientationFromImu.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once


namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /CopySensorOrientationFromImu.
*/
struct CopySensorOrientationFromImu
{

  constexpr static const char* methodName = "CopySensorOrientationFromImu";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Copy roll and pitch angles from IMU data to sensor orientation.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
  }; // struct Post

}; // struct CopySensorOrientationFromImu

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
