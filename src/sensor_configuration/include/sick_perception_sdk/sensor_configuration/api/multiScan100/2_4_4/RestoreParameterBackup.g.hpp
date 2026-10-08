/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file RestoreParameterBackup.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.4'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <string>
#include <vector>

namespace sick::multiScan100::v2_4_4::api::rest {

/**
 * @brief Payloads for endpoint /RestoreParameterBackup.
*/
struct RestoreParameterBackup
{

  constexpr static const char* methodName = "RestoreParameterBackup";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Starts the backup file upload.

 This function requires at least user level: Service.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(std::string Passphrase)
        : _Passphrase(std::move(Passphrase))
      {}

      std::string _Passphrase;
    };

    struct Response
    {
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

      explicit Response(RestoreResult RestoreResult, std::vector<std::string> ParametersFailedToRestore)
        : _RestoreResult(RestoreResult), _ParametersFailedToRestore(ParametersFailedToRestore)
      {}

      RestoreResult _RestoreResult;
      std::vector<std::string> _ParametersFailedToRestore;
    };

  }; // struct Post

}; // struct RestoreParameterBackup

} // namespace sick::multiScan100::v2_4_4::api::rest
