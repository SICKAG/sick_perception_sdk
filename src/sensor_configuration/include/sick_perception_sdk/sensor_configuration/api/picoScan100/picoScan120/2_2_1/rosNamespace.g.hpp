/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file rosNamespace.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once

#include <string>

namespace sick::picoScan120::v2_2_1::api::rest {

/**
 * @brief Payloads for endpoint /rosNamespace.
*/
struct rosNamespace
{

  constexpr static const char* variableName = "rosNamespace";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the namespace of the published topics.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::string rosNamespace)
        : _rosNamespace(std::move(rosNamespace))
      {}

      std::string _rosNamespace;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the namespace of the published topics.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(std::string rosNamespace)
        : _rosNamespace(std::move(rosNamespace))
      {}

      std::string _rosNamespace;
    };

  }; // struct Post

}; // struct rosNamespace

} // namespace sick::picoScan120::v2_2_1::api::rest
