/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ScanDataFormat.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /ScanDataFormat.
*/
struct ScanDataFormat
{

  constexpr static const char* variableName = "ScanDataFormat";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the scan data format (e.g. Compact format) or disable scan data transmission.
   */
  struct Get
  {
    struct Response
    {
      enum class ScanDataFormat
      {
        Deactivated = 0,
        Compact = 2,
        Lmdscandata = 3,
      };

      Response() = default;

      explicit Response(ScanDataFormat ScanDataFormat)
        : _ScanDataFormat(ScanDataFormat)
      {}

      ScanDataFormat _ScanDataFormat;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the scan data format (e.g. Compact format) or disable scan data transmission.
   */
  struct Post
  {
    struct Request
    {
      enum class ScanDataFormat
      {
        Deactivated = 0,
        Compact = 2,
        Lmdscandata = 3,
      };

      Request() = default;

      explicit Request(ScanDataFormat ScanDataFormat)
        : _ScanDataFormat(ScanDataFormat)
      {}

      ScanDataFormat _ScanDataFormat;
    };

  }; // struct Post

}; // struct ScanDataFormat

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
