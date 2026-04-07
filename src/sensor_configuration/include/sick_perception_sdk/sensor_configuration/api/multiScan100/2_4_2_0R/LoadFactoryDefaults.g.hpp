/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LoadFactoryDefaults.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once


namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /LoadFactoryDefaults.
*/
struct LoadFactoryDefaults
{

  constexpr static const char* methodName = "LoadFactoryDefaults";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Resets all parameters to default. This function requires the user level: Service.

 This function requires at least user level: Service.
   */
  struct Post
  {
  }; // struct Post

}; // struct LoadFactoryDefaults

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
