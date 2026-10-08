/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file RestoreParameterBackupResult.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once

#include <string>
#include <vector>

namespace sick::picoScan120::v2_3_3::api::rest {

/**
 * @brief Payloads for endpoint /RestoreParameterBackupResult.
*/
struct RestoreParameterBackupResult
{

  constexpr static const char* variableName = "RestoreParameterBackupResult";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Result of the last RestoreParameterBackup call (either normal or developer version).
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

      enum class RestoreResult
      {
        Ok = 0,
        Checksumerror = 1,
        Parseerror = 2,
        Deviceidentificationerror = 3,
        Updaterepositoryerror = 4,
        Updatesourceerror = 5,
        Decryptionerror = 6,
        Decryptionheadererror = 7,
        Decryptionlengtherror = 8,
        Ioerror = 9,
        Versionconversionerror = 10,
        Componentregistryerror = 50,
      };

      Response() = default;

      explicit Response(Status Status, RestoreResult RestoreResult, std::vector<std::string> ParametersFailedToRestore)
        : _Status(Status), _RestoreResult(RestoreResult), _ParametersFailedToRestore(ParametersFailedToRestore)
      {}

      Status _Status;
      RestoreResult _RestoreResult;
      std::vector<std::string> _ParametersFailedToRestore;
    };

  }; // struct Get

}; // struct RestoreParameterBackupResult

} // namespace sick::picoScan120::v2_3_3::api::rest
