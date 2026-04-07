/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EthernetUpdate.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once


namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /EthernetUpdate.
*/
struct EthernetUpdate
{

  constexpr static const char* methodName = "EthernetUpdate";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Applies the ethernet settings. This needs to be executed to actually change the ethernet settings.
   */
  struct Post
  {
  }; // struct Post

}; // struct EthernetUpdate

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
