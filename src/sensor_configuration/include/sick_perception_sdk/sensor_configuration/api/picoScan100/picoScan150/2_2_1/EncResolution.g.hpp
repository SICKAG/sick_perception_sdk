/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EncResolution.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan150::v2_2_1::api::rest {

/**
 * @brief Payloads for endpoint /EncResolution.
*/
struct EncResolution
{

  constexpr static const char* variableName = "EncResolution";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Enables/disables the use of the 2nd reference signal (Port4).
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(float EncResolution)
        : _EncResolution(EncResolution)
      {}

      float _EncResolution;
    };

  }; // struct Get

  /**
   * @brief Enables/disables the use of the 2nd reference signal (Port4).

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(float EncResolution)
        : _EncResolution(EncResolution)
      {}

      float _EncResolution;
    };

  }; // struct Post

}; // struct EncResolution

} // namespace sick::picoScan150::v2_2_1::api::rest
