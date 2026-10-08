/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file TSCTCSrvAddr.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.10.0'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>
#include <vector>

namespace sick::LRS4000::v1_10_0::api::rest {

/**
 * @brief Payloads for endpoint /TSCTCSrvAddr.
*/
struct TSCTCSrvAddr
{

  constexpr static const char* variableName = "TSCTCSrvAddr";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the NTP time server"s IP address.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::vector<std::uint8_t> TSCTCSrvAddr)
        : _TSCTCSrvAddr(TSCTCSrvAddr)
      {}

      std::vector<std::uint8_t> _TSCTCSrvAddr;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the NTP time server"s IP address.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(std::vector<std::uint8_t> TSCTCSrvAddr)
        : _TSCTCSrvAddr(TSCTCSrvAddr)
      {}

      std::vector<std::uint8_t> _TSCTCSrvAddr;
    };

  }; // struct Post

}; // struct TSCTCSrvAddr

} // namespace sick::LRS4000::v1_10_0::api::rest
