/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file CreateSessionToken.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <string>

namespace sick::multiScan200::v1_1_0::api::rest {

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

      explicit Response(std::string token, int timeToLive)
        : _token(std::move(token)), _timeToLive(timeToLive)
      {}

      std::string _token;
      int _timeToLive;
    };

  }; // struct Post

}; // struct CreateSessionToken

} // namespace sick::multiScan200::v1_1_0::api::rest
