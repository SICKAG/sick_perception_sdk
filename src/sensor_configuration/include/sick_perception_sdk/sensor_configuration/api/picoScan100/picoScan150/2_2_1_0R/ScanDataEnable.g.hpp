/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ScanDataEnable.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan150::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /ScanDataEnable.
*/
struct ScanDataEnable
{

  constexpr static const char* variableName = "ScanDataEnable";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Enables/disables the measurement data streaming. The measurement data itself is sent via a UDP-based SICK-specific format. A Python example can be found at https://github.com/SICKAG/ScanSegmentAPI.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool ScanDataEnable)
        : _ScanDataEnable(ScanDataEnable)
      {}

      bool _ScanDataEnable;
    };

  }; // struct Get

  /**
   * @brief Enables/disables the measurement data streaming. The measurement data itself is sent via a UDP-based SICK-specific format. A Python example can be found at https://github.com/SICKAG/ScanSegmentAPI.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool ScanDataEnable)
        : _ScanDataEnable(ScanDataEnable)
      {}

      bool _ScanDataEnable;
    };

  }; // struct Post

}; // struct ScanDataEnable

} // namespace sick::picoScan150::v2_2_1_0R::api::rest
