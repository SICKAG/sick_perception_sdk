/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file TSCRole.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /TSCRole.
*/
struct TSCRole
{

  constexpr static const char* variableName = "TSCRole";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the time synchronization role (none = 0 , NTP = 1 or PTP = 3).
   */
  struct Get
  {
    struct Response
    {
      enum class TSCRole
      {
        TxNone = 0,
        TxClient = 1,
        TxPtpSlave = 3,
        TxPtpMaster = 4,
      };

      Response() = default;

      explicit Response(TSCRole TSCRole)
        : _TSCRole(TSCRole)
      {}

      TSCRole _TSCRole;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the time synchronization role (none = 0 , NTP = 1 or PTP = 3).
   */
  struct Post
  {
    struct Request
    {
      enum class TSCRole
      {
        TxNone = 0,
        TxClient = 1,
        TxPtpSlave = 3,
        TxPtpMaster = 4,
      };

      Request() = default;

      explicit Request(TSCRole TSCRole)
        : _TSCRole(TSCRole)
      {}

      TSCRole _TSCRole;
    };

  }; // struct Post

}; // struct TSCRole

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
