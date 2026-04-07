/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ScanDataScaleFactor.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /ScanDataScaleFactor.
*/
struct ScanDataScaleFactor
{

  constexpr static const char* variableName = "ScanDataScaleFactor";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Configure the scaling factor for distance measurements when LMDscandata or Compact is selected as the data output format.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(float ScanDataScaleFactor)
        : _ScanDataScaleFactor(ScanDataScaleFactor)
      {}

      float _ScanDataScaleFactor;
    };

  }; // struct Get

  /**
   * @brief Configure the scaling factor for distance measurements when LMDscandata or Compact is selected as the data output format.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(float ScanDataScaleFactor)
        : _ScanDataScaleFactor(ScanDataScaleFactor)
      {}

      float _ScanDataScaleFactor;
    };

  }; // struct Post

}; // struct ScanDataScaleFactor

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
