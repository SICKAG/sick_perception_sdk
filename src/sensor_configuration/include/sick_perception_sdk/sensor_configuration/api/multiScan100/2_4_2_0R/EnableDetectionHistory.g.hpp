/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EnableDetectionHistory.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once


namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /EnableDetectionHistory.
*/
struct EnableDetectionHistory
{

  constexpr static const char* methodName = "EnableDetectionHistory";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Returns/sets the detection history.

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

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
