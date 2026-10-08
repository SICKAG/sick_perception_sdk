/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EncoderDataEnable.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan150::v2_2_1::api::rest {

/**
 * @brief Payloads for endpoint /EncoderDataEnable.
*/
struct EncoderDataEnable
{

  constexpr static const char* variableName = "EncoderDataEnable";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Enables/disables the encoder data streaming. The encoder data itself is sent via a UDP-based SICK-specific format.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool EncoderDataEnable)
        : _EncoderDataEnable(EncoderDataEnable)
      {}

      bool _EncoderDataEnable;
    };

  }; // struct Get

  /**
   * @brief Enables/disables the encoder data streaming. The encoder data itself is sent via a UDP-based SICK-specific format.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool EncoderDataEnable)
        : _EncoderDataEnable(EncoderDataEnable)
      {}

      bool _EncoderDataEnable;
    };

  }; // struct Post

}; // struct EncoderDataEnable

} // namespace sick::picoScan150::v2_2_1::api::rest
