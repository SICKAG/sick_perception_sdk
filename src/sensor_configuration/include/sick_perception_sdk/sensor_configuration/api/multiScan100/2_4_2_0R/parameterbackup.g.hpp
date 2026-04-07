/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file parameterbackup.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /parameterbackup.
*/
struct parameterbackup
{

  constexpr static const char* variableName = "parameterbackup";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Reads/transfers the backup file (.json) from/to the device.
   */
  struct Get
  {
  }; // struct Get

}; // struct parameterbackup

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
