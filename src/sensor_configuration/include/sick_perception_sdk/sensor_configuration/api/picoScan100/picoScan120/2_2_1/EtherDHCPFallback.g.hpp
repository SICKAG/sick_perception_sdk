/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EtherDHCPFallback.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan120::v2_2_1::api::rest {

/**
 * @brief Payloads for endpoint /EtherDHCPFallback.
*/
struct EtherDHCPFallback
{

  constexpr static const char* variableName = "EtherDHCPFallback";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the mode for the DHCP fallback (retry or static).
   */
  struct Get
  {
    struct Response
    {
      enum class EtherDHCPFallback
      {
        TxUseStaticIp = 0,
        TxRetryDhcp = 1,
      };

      Response() = default;

      explicit Response(EtherDHCPFallback EtherDHCPFallback)
        : _EtherDHCPFallback(EtherDHCPFallback)
      {}

      EtherDHCPFallback _EtherDHCPFallback;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the mode for the DHCP fallback (retry or static).

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      enum class EtherDHCPFallback
      {
        TxUseStaticIp = 0,
        TxRetryDhcp = 1,
      };

      Request() = default;

      explicit Request(EtherDHCPFallback EtherDHCPFallback)
        : _EtherDHCPFallback(EtherDHCPFallback)
      {}

      EtherDHCPFallback _EtherDHCPFallback;
    };

  }; // struct Post

}; // struct EtherDHCPFallback

} // namespace sick::picoScan120::v2_2_1::api::rest
