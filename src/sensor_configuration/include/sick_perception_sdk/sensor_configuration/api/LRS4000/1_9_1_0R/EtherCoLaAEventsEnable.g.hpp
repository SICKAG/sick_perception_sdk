/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EtherCoLaAEventsEnable.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once


namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /EtherCoLaAEventsEnable.
*/
struct EtherCoLaAEventsEnable
{

  constexpr static const char* methodName = "EtherCoLaAEventsEnable";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief This command enables/ disables the CoLa A event output. If disabled, CoLa A port 2111 still provides access to poll device parameters but event-based streaming output is limited to the ports 2112 (CoLa B) or data protocol Compact.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool EtherCoLaAEventsEnable)
        : _EtherCoLaAEventsEnable(EtherCoLaAEventsEnable)
      {}

      bool _EtherCoLaAEventsEnable;
    };

  }; // struct Post

}; // struct EtherCoLaAEventsEnable

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
