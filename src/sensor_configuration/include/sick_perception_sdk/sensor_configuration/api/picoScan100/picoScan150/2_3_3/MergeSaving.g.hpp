/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file MergeSaving.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan150::v2_3_3::api::rest {

/**
 * @brief Payloads for endpoint /MergeSaving.
*/
struct MergeSaving
{

  constexpr static const char* variableName = "MergeSaving";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the status for saving the merged scans. As soon as a scan merge is completed, the point cloud is available for download on port 80 (<ip>192.168.0.1/cloud.pcd). Curl: http://<ip>/cloud.pcd -o cloud.pcd. Only the most recently created point cloud is available for download. The point cloud is ready for download when MergeSaving changes from 1 (Saving in progress) to 0 (Saving not active).
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool MergeSaving)
        : _MergeSaving(MergeSaving)
      {}

      bool _MergeSaving;
    };

  }; // struct Get

}; // struct MergeSaving

} // namespace sick::picoScan150::v2_3_3::api::rest
