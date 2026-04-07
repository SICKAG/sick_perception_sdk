/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file FindMe.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.2.1.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <cstdint>

namespace sick::picoScan120::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /FindMe.
*/
struct FindMe
{

  constexpr static const char* methodName = "FindMe";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Sets the device LEDs into blinking mode for better identification.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(std::uint16_t uiDuration)
        : _uiDuration(uiDuration)
      {}

      std::uint16_t _uiDuration;
    };

  }; // struct Post

}; // struct FindMe

} // namespace sick::picoScan120::v2_2_1_0R::api::rest
