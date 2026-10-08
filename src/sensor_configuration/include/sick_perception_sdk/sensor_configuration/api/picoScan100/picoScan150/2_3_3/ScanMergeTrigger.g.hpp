/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ScanMergeTrigger.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan150::v2_3_3::api::rest {

/**
 * @brief Payloads for endpoint /ScanMergeTrigger.
*/
struct ScanMergeTrigger
{

  constexpr static const char* variableName = "ScanMergeTrigger";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets how the scan merge is triggered (e.g. via method call).
   */
  struct Get
  {
    struct Response
    {
      enum class ScanMergeTrigger
      {
        Method = 0,
      };

      Response() = default;

      explicit Response(ScanMergeTrigger ScanMergeTrigger)
        : _ScanMergeTrigger(ScanMergeTrigger)
      {}

      ScanMergeTrigger _ScanMergeTrigger;
    };

  }; // struct Get

  /**
   * @brief Returns/sets how the scan merge is triggered (e.g. via method call).

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      enum class ScanMergeTrigger
      {
        Method = 0,
      };

      Request() = default;

      explicit Request(ScanMergeTrigger ScanMergeTrigger)
        : _ScanMergeTrigger(ScanMergeTrigger)
      {}

      ScanMergeTrigger _ScanMergeTrigger;
    };

  }; // struct Post

}; // struct ScanMergeTrigger

} // namespace sick::picoScan150::v2_3_3::api::rest
