/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LocationName.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <string>

namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /LocationName.
*/
struct LocationName
{

  constexpr static const char* variableName = "LocationName";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the device name.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::string LocationName)
        : _LocationName(std::move(LocationName))
      {}

      std::string _LocationName;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the device name.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(std::string LocationName)
        : _LocationName(std::move(LocationName))
      {}

      std::string _LocationName;
    };

  }; // struct Post

}; // struct LocationName

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
