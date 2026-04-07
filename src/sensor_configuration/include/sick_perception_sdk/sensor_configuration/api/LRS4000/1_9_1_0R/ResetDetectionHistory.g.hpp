/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ResetDetectionHistory.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once


namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /ResetDetectionHistory.
*/
struct ResetDetectionHistory
{

  constexpr static const char* methodName = "ResetDetectionHistory";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Resets the detection history logs.
   */
  struct Post
  {
  }; // struct Post

}; // struct ResetDetectionHistory

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
