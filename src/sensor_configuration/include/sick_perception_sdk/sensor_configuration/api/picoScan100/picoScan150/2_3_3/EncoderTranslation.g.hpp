/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EncoderTranslation.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan150::v2_3_3::api::rest {

/**
 * @brief Payloads for endpoint /EncoderTranslation.
*/
struct EncoderTranslation
{

  constexpr static const char* variableName = "EncoderTranslation";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the translation of the encoder in mm.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(float x, float y, float z)
        : _x(x), _y(y), _z(z)
      {}

      float _x;
      float _y;
      float _z;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the translation of the encoder in mm.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(float x, float y, float z)
        : _x(x), _y(y), _z(z)
      {}

      float _x;
      float _y;
      float _z;
    };

  }; // struct Post

}; // struct EncoderTranslation

} // namespace sick::picoScan150::v2_3_3::api::rest
