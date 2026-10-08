/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LocationName.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <string>

namespace sick::multiScan200::v1_1_0::api::rest {

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

 This function requires at least user level: Authorized Client.
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

} // namespace sick::multiScan200::v1_1_0::api::rest
