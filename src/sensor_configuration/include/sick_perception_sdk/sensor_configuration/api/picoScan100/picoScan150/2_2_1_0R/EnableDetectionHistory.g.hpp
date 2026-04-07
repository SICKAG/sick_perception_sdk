/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EnableDetectionHistory.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan150::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /EnableDetectionHistory.
*/
struct EnableDetectionHistory
{

  constexpr static const char* variableName = "EnableDetectionHistory";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Enables/disables the detection history.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool EnableDetectionHistory)
        : _EnableDetectionHistory(EnableDetectionHistory)
      {}

      bool _EnableDetectionHistory;
    };

  }; // struct Get

  /**
   * @brief Enables/disables the detection history.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool EnableDetectionHistory)
        : _EnableDetectionHistory(EnableDetectionHistory)
      {}

      bool _EnableDetectionHistory;
    };

  }; // struct Post

}; // struct EnableDetectionHistory

} // namespace sick::picoScan150::v2_2_1_0R::api::rest
