/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file rosDomainId.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>

namespace sick::picoScan120::v2_3_3::api::rest {

/**
 * @brief Payloads for endpoint /rosDomainId.
*/
struct rosDomainId
{

  constexpr static const char* variableName = "rosDomainId";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the ROS domain ID used for the ROS 2 communication.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::uint8_t rosDomainId)
        : _rosDomainId(rosDomainId)
      {}

      std::uint8_t _rosDomainId;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the ROS domain ID used for the ROS 2 communication.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(std::uint8_t rosDomainId)
        : _rosDomainId(rosDomainId)
      {}

      std::uint8_t _rosDomainId;
    };

  }; // struct Post

}; // struct rosDomainId

} // namespace sick::picoScan120::v2_3_3::api::rest
