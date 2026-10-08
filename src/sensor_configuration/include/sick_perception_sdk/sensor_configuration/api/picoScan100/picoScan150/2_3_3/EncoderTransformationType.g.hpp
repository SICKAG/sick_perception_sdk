/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EncoderTransformationType.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan150::v2_3_3::api::rest {

/**
 * @brief Payloads for endpoint /EncoderTransformationType.
*/
struct EncoderTransformationType
{

  constexpr static const char* variableName = "EncoderTransformationType";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the encoder transformation type (ROTATION or DISPLACEMENT).
   */
  struct Get
  {
    struct Response
    {
      enum class EncoderTransformationType
      {
        Rotation = 0,
        Translation = 1,
      };

      Response() = default;

      explicit Response(EncoderTransformationType EncoderTransformationType)
        : _EncoderTransformationType(EncoderTransformationType)
      {}

      EncoderTransformationType _EncoderTransformationType;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the encoder transformation type (ROTATION or DISPLACEMENT).

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      enum class EncoderTransformationType
      {
        Rotation = 0,
        Translation = 1,
      };

      Request() = default;

      explicit Request(EncoderTransformationType EncoderTransformationType)
        : _EncoderTransformationType(EncoderTransformationType)
      {}

      EncoderTransformationType _EncoderTransformationType;
    };

  }; // struct Post

}; // struct EncoderTransformationType

} // namespace sick::picoScan150::v2_3_3::api::rest
