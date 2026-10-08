/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file CreateParameterBackupResult.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once


namespace sick::multiScan200::v1_1_0::api::rest {

/**
 * @brief Payloads for endpoint /CreateParameterBackupResult.
*/
struct CreateParameterBackupResult
{

  constexpr static const char* variableName = "CreateParameterBackupResult";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the current status of the parameter backup process.
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

} // namespace sick::multiScan200::v1_1_0::api::rest
