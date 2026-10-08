/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file FREchoFilter.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan150::v2_2_1::api::rest {

/**
 * @brief Payloads for endpoint /FREchoFilter.
*/
struct FREchoFilter
{

  constexpr static const char* variableName = "FREchoFilter";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the multi-echo filter settings. Depending on the environment the sensor receives several measurement points on the same angular step (multi-echo). The filter can filter out the first echo, the last echo or all echoes.
   */
  struct Get
  {
    struct Response
    {
      enum class FREchoFilter
      {
        FirstEcho = 0,
        AllEchos = 1,
        LastEcho = 2,
      };

      Response() = default;

      explicit Response(FREchoFilter FREchoFilter)
        : _FREchoFilter(FREchoFilter)
      {}

      FREchoFilter _FREchoFilter;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the multi-echo filter settings. Depending on the environment the sensor receives several measurement points on the same angular step (multi-echo). The filter can filter out the first echo, the last echo or all echoes.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      enum class FREchoFilter
      {
        FirstEcho = 0,
        AllEchos = 1,
        LastEcho = 2,
      };

      Request() = default;

      explicit Request(FREchoFilter FREchoFilter)
        : _FREchoFilter(FREchoFilter)
      {}

      FREchoFilter _FREchoFilter;
    };

  }; // struct Post

}; // struct FREchoFilter

} // namespace sick::picoScan150::v2_2_1::api::rest
