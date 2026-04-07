/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LoadApplicationDefaults.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once


namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /LoadApplicationDefaults.
*/
struct LoadApplicationDefaults
{

  constexpr static const char* methodName = "LoadApplicationDefaults";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Resets only the user parametrization of the fields, evaluation cases, and parameters under the section Application. Other parameters like interface settings, echo filter, etc. remain unchanged.This function requires the user level: Service.
   */
  struct Post
  {
  }; // struct Post

}; // struct LoadApplicationDefaults

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
