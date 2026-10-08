/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EtherSessionTimeout.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>

namespace sick::picoScan120::v2_3_3::api::rest {

/**
 * @brief Payloads for endpoint /EtherSessionTimeout.
*/
struct EtherSessionTimeout
{

  constexpr static const char* variableName = "EtherSessionTimeout";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the session timeout for the LMDscandata output. Be careful with low values as they might cause unexpected disconnections.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::uint32_t EtherSessionTimeout)
        : _EtherSessionTimeout(EtherSessionTimeout)
      {}

      std::uint32_t _EtherSessionTimeout;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the session timeout for the LMDscandata output. Be careful with low values as they might cause unexpected disconnections.

 This function requires at least user level: Service.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(std::uint32_t EtherSessionTimeout)
        : _EtherSessionTimeout(EtherSessionTimeout)
      {}

      std::uint32_t _EtherSessionTimeout;
    };

  }; // struct Post

}; // struct EtherSessionTimeout

} // namespace sick::picoScan120::v2_3_3::api::rest
