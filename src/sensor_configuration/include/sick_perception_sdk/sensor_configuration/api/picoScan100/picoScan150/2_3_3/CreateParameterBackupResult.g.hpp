/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file CreateParameterBackupResult.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan150::v2_3_3::api::rest {

/**
 * @brief Payloads for endpoint /CreateParameterBackupResult.
*/
struct CreateParameterBackupResult
{

  constexpr static const char* variableName = "CreateParameterBackupResult";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Result of the last CreateParameterBackup call (either normal or developer version).
   */
  struct Get
  {
    struct Response
    {
      enum class Status
      {
        Pending = 0,
        Finished = 1,
      };

      Response() = default;

      explicit Response(Status Status, bool Result)
        : _Status(Status), _Result(Result)
      {}

      Status _Status;
      bool _Result;
    };

  }; // struct Get

}; // struct CreateParameterBackupResult

} // namespace sick::picoScan150::v2_3_3::api::rest
