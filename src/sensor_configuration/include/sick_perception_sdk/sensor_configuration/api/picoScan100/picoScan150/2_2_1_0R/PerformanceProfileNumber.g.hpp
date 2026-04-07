/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file PerformanceProfileNumber.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan150::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /PerformanceProfileNumber.
*/
struct PerformanceProfileNumber
{

  constexpr static const char* variableName = "PerformanceProfileNumber";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the scan configuration (scanning frequency and angular resolution).
   */
  struct Get
  {
    struct Response
    {
      enum class PerformanceProfileNumber
      {
        Mode1 = 1,
        Mode2 = 2,
        Mode3 = 3,
        Mode4 = 4,
        Mode5 = 5,
        Mode6 = 6,
        Mode7 = 7,
        Mode8 = 8,
        Mode9 = 9,
        Mode10 = 10,
        Mode11 = 11,
      };

      Response() = default;

      explicit Response(PerformanceProfileNumber PerformanceProfileNumber)
        : _PerformanceProfileNumber(PerformanceProfileNumber)
      {}

      PerformanceProfileNumber _PerformanceProfileNumber;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the scan configuration (scanning frequency and angular resolution).

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      enum class PerformanceProfileNumber
      {
        Mode1 = 1,
        Mode2 = 2,
        Mode3 = 3,
        Mode4 = 4,
        Mode5 = 5,
        Mode6 = 6,
        Mode7 = 7,
        Mode8 = 8,
        Mode9 = 9,
        Mode10 = 10,
        Mode11 = 11,
      };

      Request() = default;

      explicit Request(PerformanceProfileNumber PerformanceProfileNumber)
        : _PerformanceProfileNumber(PerformanceProfileNumber)
      {}

      PerformanceProfileNumber _PerformanceProfileNumber;
    };

  }; // struct Post

}; // struct PerformanceProfileNumber

} // namespace sick::picoScan150::v2_2_1_0R::api::rest
