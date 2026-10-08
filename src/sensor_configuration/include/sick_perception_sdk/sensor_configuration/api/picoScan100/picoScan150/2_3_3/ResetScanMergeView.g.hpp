/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ResetScanMergeView.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.3.3'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once


namespace sick::picoScan150::v2_3_3::api::rest {

/**
 * @brief Payloads for endpoint /ResetScanMergeView.
*/
struct ResetScanMergeView
{

  constexpr static const char* methodName = "ResetScanMergeView";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Deletes the currently displayed point clouds.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
  }; // struct Post

}; // struct ResetScanMergeView

} // namespace sick::picoScan150::v2_3_3::api::rest
