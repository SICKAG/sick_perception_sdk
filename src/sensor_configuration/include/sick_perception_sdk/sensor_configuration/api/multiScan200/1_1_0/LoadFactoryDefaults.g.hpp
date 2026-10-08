/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LoadFactoryDefaults.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once


namespace sick::multiScan200::v1_1_0::api::rest {

/**
 * @brief Payloads for endpoint /LoadFactoryDefaults.
*/
struct LoadFactoryDefaults
{

  constexpr static const char* methodName = "LoadFactoryDefaults";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Resets all parameters to default.

 This function requires at least user level: Service.
   */
  struct Post
  {
  }; // struct Post

}; // struct LoadFactoryDefaults

} // namespace sick::multiScan200::v1_1_0::api::rest
