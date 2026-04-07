/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EtherAddressingMode.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /EtherAddressingMode.
*/
struct EtherAddressingMode
{

  constexpr static const char* variableName = "EtherAddressingMode";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the mode for the IP address assignment (static or DHCP).
   */
  struct Get
  {
    struct Response
    {
      enum class EtherAddressingMode
      {
        TxIpStatic = 0,
        TxIpDhcp = 1,
      };

      Response() = default;

      explicit Response(EtherAddressingMode EtherAddressingMode)
        : _EtherAddressingMode(EtherAddressingMode)
      {}

      EtherAddressingMode _EtherAddressingMode;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the mode for the IP address assignment (static or DHCP).

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      enum class EtherAddressingMode
      {
        TxIpStatic = 0,
        TxIpDhcp = 1,
      };

      Request() = default;

      explicit Request(EtherAddressingMode EtherAddressingMode)
        : _EtherAddressingMode(EtherAddressingMode)
      {}

      EtherAddressingMode _EtherAddressingMode;
    };

  }; // struct Post

}; // struct EtherAddressingMode

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
