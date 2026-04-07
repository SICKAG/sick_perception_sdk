/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EtherDHCPFallback.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /EtherDHCPFallback.
*/
struct EtherDHCPFallback
{

  constexpr static const char* variableName = "EtherDHCPFallback";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the more for the DHCP fallback (retry or static).
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
   * @brief Returns/sets the more for the DHCP fallback (retry or static).
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

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
