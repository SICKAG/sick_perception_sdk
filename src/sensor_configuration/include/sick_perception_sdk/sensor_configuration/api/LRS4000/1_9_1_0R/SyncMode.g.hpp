/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file SyncMode.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once


namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /SyncMode.
*/
struct SyncMode
{

  constexpr static const char* methodName = "SyncMode";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief synchronisation mode e.g. no synchronisation, hardware synchronisation, CAN synchronisation or CLOCK synchronisation (LRS4000 only supports Clock-Sync and wire sync).
   */
  struct Post
  {
    struct Request
    {
      enum class SyncMode
      {
        NoSync = 0,
        SyncByWire = 1,
        SyncByClock = 3,
      };

      Request() = default;

      explicit Request(SyncMode SyncMode)
        : _SyncMode(SyncMode)
      {}

      SyncMode _SyncMode;
    };

  }; // struct Post

}; // struct SyncMode

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
