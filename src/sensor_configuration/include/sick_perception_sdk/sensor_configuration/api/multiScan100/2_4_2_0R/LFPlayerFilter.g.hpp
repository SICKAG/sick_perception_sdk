/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LFPlayerFilter.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /LFPlayerFilter.
*/
struct LFPlayerFilter
{

  constexpr static const char* variableName = "LFPlayerFilter";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Filter complete layers in the output data.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool bEnable, std::vector<bool> aLayers)
        : _bEnable(bEnable), _aLayers(aLayers)
      {}

      bool _bEnable;
      std::vector<bool> _aLayers;
    };

  }; // struct Get

  /**
   * @brief Filter complete layers in the output data.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool bEnable, std::vector<bool> aLayers)
        : _bEnable(bEnable), _aLayers(aLayers)
      {}

      bool _bEnable;
      std::vector<bool> _aLayers;
    };

  }; // struct Post

}; // struct LFPlayerFilter

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
