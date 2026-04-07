/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file RunFirmwareUpdate.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.2.1.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once


namespace sick::picoScan120::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /RunFirmwareUpdate.
*/
struct RunFirmwareUpdate
{

  constexpr static const char* methodName = "RunFirmwareUpdate";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Starts the firmware update process.

 This function requires at least user level: Service.
   */
  struct Post
  {
  }; // struct Post

}; // struct RunFirmwareUpdate

} // namespace sick::picoScan120::v2_2_1_0R::api::rest
