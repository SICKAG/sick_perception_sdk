/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EncoderRotation.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan150::v2_3_3::api::rest {

/**
 * @brief Payloads for endpoint /EncoderRotation.
*/
struct EncoderRotation
{

  constexpr static const char* variableName = "EncoderRotation";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the rotation center of the encoder in mm.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(float yaw, float pitch, float roll)
        : _yaw(yaw), _pitch(pitch), _roll(roll)
      {}

      float _yaw;
      float _pitch;
      float _roll;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the rotation center of the encoder in mm.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(float yaw, float pitch, float roll)
        : _yaw(yaw), _pitch(pitch), _roll(roll)
      {}

      float _yaw;
      float _pitch;
      float _roll;
    };

  }; // struct Post

}; // struct EncoderRotation

} // namespace sick::picoScan150::v2_3_3::api::rest
