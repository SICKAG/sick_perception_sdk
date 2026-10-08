/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file TSCTCSrvAddr.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <vector>

namespace sick::multiScan200::v1_1_0::api::rest {

/**
 * @brief Payloads for endpoint /TSCTCSrvAddr.
*/
struct TSCTCSrvAddr
{

  constexpr static const char* variableName = "TSCTCSrvAddr";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the IP address of the time server.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::vector<int> TSCTCSrvAddr)
        : _TSCTCSrvAddr(TSCTCSrvAddr)
      {}

      std::vector<int> _TSCTCSrvAddr;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the IP address of the time server.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(std::vector<int> TSCTCSrvAddr)
        : _TSCTCSrvAddr(TSCTCSrvAddr)
      {}

      std::vector<int> _TSCTCSrvAddr;
    };

  }; // struct Post

}; // struct TSCTCSrvAddr

} // namespace sick::multiScan200::v1_1_0::api::rest
