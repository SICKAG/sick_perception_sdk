/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file RestoreParameterBackup.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <string>

namespace sick::multiScan200::v1_1_0::api::rest {

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

      explicit Request(std::string Passphrase, int Filter)
        : _Passphrase(std::move(Passphrase)), _Filter(Filter)
      {}

      std::string _Passphrase;
      int _Filter;
    };

    struct Response
    {
      Response() = default;

      explicit Response(bool Result)
        : _Result(Result)
      {}

      bool _Result;
    };

  }; // struct Post

}; // struct RestoreParameterBackup

} // namespace sick::multiScan200::v1_1_0::api::rest
