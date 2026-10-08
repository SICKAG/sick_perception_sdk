/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file CreateSessionToken.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.3.3'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <cstdint>
#include <string>

namespace sick::picoScan150::v2_3_3::api::rest {

/**
 * @brief Payloads for endpoint /CreateSessionToken.
*/
struct CreateSessionToken
{

  constexpr static const char* methodName = "CreateSessionToken";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief A short-lived session token to pass to a HTTP request header.
   */
  struct Post
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::string token, std::uint16_t timeToLive)
        : _token(std::move(token)), _timeToLive(timeToLive)
      {}

      std::string _token;
      std::uint16_t _timeToLive;
    };

  }; // struct Post

}; // struct CreateSessionToken

} // namespace sick::picoScan150::v2_3_3::api::rest
