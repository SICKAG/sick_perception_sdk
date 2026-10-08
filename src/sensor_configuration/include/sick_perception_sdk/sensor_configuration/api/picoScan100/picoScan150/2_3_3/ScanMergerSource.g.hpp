/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ScanMergerSource.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan150::v2_3_3::api::rest {

/**
 * @brief Payloads for endpoint /ScanMergerSource.
*/
struct ScanMergerSource
{

  constexpr static const char* variableName = "ScanMergerSource";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the data source for angle information used during scan merging (IMU or ENCODER).
   */
  struct Get
  {
    struct Response
    {
      enum class ScanMergerSource
      {
        Imu = 0,
        Encoder = 1,
      };

      Response() = default;

      explicit Response(ScanMergerSource ScanMergerSource)
        : _ScanMergerSource(ScanMergerSource)
      {}

      ScanMergerSource _ScanMergerSource;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the data source for angle information used during scan merging (IMU or ENCODER).

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      enum class ScanMergerSource
      {
        Imu = 0,
        Encoder = 1,
      };

      Request() = default;

      explicit Request(ScanMergerSource ScanMergerSource)
        : _ScanMergerSource(ScanMergerSource)
      {}

      ScanMergerSource _ScanMergerSource;
    };

  }; // struct Post

}; // struct ScanMergerSource

} // namespace sick::picoScan150::v2_3_3::api::rest
