/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EtherCoLaScanMode.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /EtherCoLaScanMode.
*/
struct EtherCoLaScanMode
{

  constexpr static const char* variableName = "EtherCoLaScanMode";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Configures the device search by SICK tools. If disabled, finding the device via device search and changing the IP address via SICK tools is not possible.
   */
  struct Get
  {
    struct Response
    {
      enum class EtherCoLaScanMode
      {
        Enabled = 0,
        IpConfigDisabled = 1,
        Disabled = 2,
        IpConfigTimeLimit = 3,
      };

      Response() = default;

      explicit Response(EtherCoLaScanMode EtherCoLaScanMode)
        : _EtherCoLaScanMode(EtherCoLaScanMode)
      {}

      EtherCoLaScanMode _EtherCoLaScanMode;
    };

  }; // struct Get

  /**
   * @brief Configures the device search by SICK tools. If disabled, finding the device via device search and changing the IP address via SICK tools is not possible.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      enum class EtherCoLaScanMode
      {
        Enabled = 0,
        IpConfigDisabled = 1,
        Disabled = 2,
        IpConfigTimeLimit = 3,
      };

      Request() = default;

      explicit Request(EtherCoLaScanMode EtherCoLaScanMode)
        : _EtherCoLaScanMode(EtherCoLaScanMode)
      {}

      EtherCoLaScanMode _EtherCoLaScanMode;
    };

  }; // struct Post

}; // struct EtherCoLaScanMode

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
