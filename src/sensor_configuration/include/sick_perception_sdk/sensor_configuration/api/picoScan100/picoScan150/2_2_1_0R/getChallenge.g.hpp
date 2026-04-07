/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file getChallenge.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <string>

namespace sick::picoScan150::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /getChallenge.
*/
struct getChallenge
{

  constexpr static const char* methodName = "getChallenge";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Returns a challenge for the challenge and response authentication method. For more details see https://github.com/SICKAG/sick_scan_rest_client
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(std::string user)
        : _user(std::move(user))
      {}

      std::string _user;
    };

  }; // struct Post

}; // struct getChallenge

} // namespace sick::picoScan150::v2_2_1_0R::api::rest
