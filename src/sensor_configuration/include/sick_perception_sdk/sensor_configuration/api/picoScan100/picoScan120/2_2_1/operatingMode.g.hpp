/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file operatingMode.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan120::v2_2_1::api::rest {

/**
 * @brief Payloads for endpoint /operatingMode.
*/
struct operatingMode
{

  constexpr static const char* variableName = "operatingMode";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the operating mode of the receiver unit.
   */
  struct Get
  {
    struct Response
    {
      enum class operatingMode
      {
        Standard = 0,
        ReflectorOptimizationMode = 1,
      };

      Response() = default;

      explicit Response(operatingMode operatingMode)
        : _operatingMode(operatingMode)
      {}

      operatingMode _operatingMode;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the operating mode of the receiver unit.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      enum class operatingMode
      {
        Standard = 0,
        ReflectorOptimizationMode = 1,
      };

      Request() = default;

      explicit Request(operatingMode operatingMode)
        : _operatingMode(operatingMode)
      {}

      operatingMode _operatingMode;
    };

  }; // struct Post

}; // struct operatingMode

} // namespace sick::picoScan120::v2_2_1::api::rest
