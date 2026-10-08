/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file StopScanMerge.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.10.0'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once


namespace sick::LRS4000::v1_10_0::api::rest {

/**
 * @brief Payloads for endpoint /StopScanMerge.
*/
struct StopScanMerge
{

  constexpr static const char* methodName = "StopScanMerge";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Stop the recording of a running scan merge.
   */
  struct Post
  {
  }; // struct Post

}; // struct StopScanMerge

} // namespace sick::LRS4000::v1_10_0::api::rest
