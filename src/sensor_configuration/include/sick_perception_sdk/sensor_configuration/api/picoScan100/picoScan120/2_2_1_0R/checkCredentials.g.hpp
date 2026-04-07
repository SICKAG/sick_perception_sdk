/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file checkCredentials.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.2.1.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once


namespace sick::picoScan120::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /checkCredentials.
*/
struct checkCredentials
{

  constexpr static const char* methodName = "checkCredentials";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Returns authentication success. For more details see https://github.com/SICKAG/sick_scan_rest_client.
   */
  struct Post
  {
  }; // struct Post

}; // struct checkCredentials

} // namespace sick::picoScan120::v2_2_1_0R::api::rest
