/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file SetOutput.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once


namespace sick::multiScan200::v1_1_0::api::rest {

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

      explicit Request(int Output, int Value)
        : _Output(Output), _Value(Value)
      {}

      int _Output;
      int _Value;
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

} // namespace sick::multiScan200::v1_1_0::api::rest
