/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EtherAuxEnabled.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /EtherAuxEnabled.
*/
struct EtherAuxEnabled
{

  constexpr static const char* variableName = "EtherAuxEnabled";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Enables/disables the legacy interface CoLa A/B. If enabled CoLa A uses port 2111 and CoLa B uses 2112.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool EtherAuxEnabled)
        : _EtherAuxEnabled(EtherAuxEnabled)
      {}

      bool _EtherAuxEnabled;
    };

  }; // struct Get

  /**
   * @brief Enables/disables the legacy interface CoLa A/B. If enabled CoLa A uses port 2111 and CoLa B uses 2112.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool EtherAuxEnabled)
        : _EtherAuxEnabled(EtherAuxEnabled)
      {}

      bool _EtherAuxEnabled;
    };

  }; // struct Post

}; // struct EtherAuxEnabled

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
