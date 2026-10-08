/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file FREchoFilter.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once


namespace sick::multiScan200::v1_1_0::api::rest {

/**
 * @brief Payloads for endpoint /FREchoFilter.
*/
struct FREchoFilter
{

  constexpr static const char* variableName = "FREchoFilter";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the multi-echo filter settings. Depending on the environment the sensor receives several measurement points on the same angular step (multi-echo).
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
        StrongestEcho = 3,
        AllEchosStrongestFirst = 4,
      };

      Response() = default;

      explicit Response(FREchoFilter FREchoFilter)
        : _FREchoFilter(FREchoFilter)
      {}

      FREchoFilter _FREchoFilter;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the multi-echo filter settings. Depending on the environment the sensor receives several measurement points on the same angular step (multi-echo).

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
        StrongestEcho = 3,
        AllEchosStrongestFirst = 4,
      };

      Request() = default;

      explicit Request(FREchoFilter FREchoFilter)
        : _FREchoFilter(FREchoFilter)
      {}

      FREchoFilter _FREchoFilter;
    };

  }; // struct Post

}; // struct FREchoFilter

} // namespace sick::multiScan200::v1_1_0::api::rest
