/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file SetOutput.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <cstdint>

namespace sick::picoScan150::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /SetOutput.
*/
struct SetOutput
{

  constexpr static const char* methodName = "SetOutput";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Sets the output state for an individual output. Precondition is to set the output source to "SOPAS command".
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(std::uint8_t Output, std::uint8_t Value)
        : _Output(Output), _Value(Value)
      {}

      std::uint8_t _Output;
      std::uint8_t _Value;
    };

    struct Response
    {
      Response() = default;

      explicit Response(bool Success)
        : _Success(Success)
      {}

      bool _Success;
    };

  }; // struct Post

}; // struct SetOutput

} // namespace sick::picoScan150::v2_2_1_0R::api::rest
