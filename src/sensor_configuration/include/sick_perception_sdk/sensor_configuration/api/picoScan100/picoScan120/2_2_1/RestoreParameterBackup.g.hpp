/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file RestoreParameterBackup.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.2.1'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <string>

namespace sick::picoScan120::v2_2_1::api::rest {

/**
 * @brief Payloads for endpoint /RestoreParameterBackup.
*/
struct RestoreParameterBackup
{

  constexpr static const char* methodName = "RestoreParameterBackup";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Restores the backup file on the device. The restored parameters will then be applied.

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
      Response() = default;

      explicit Response(bool Result)
        : _Result(Result)
      {}

      bool _Result;
    };

  }; // struct Post

}; // struct RestoreParameterBackup

} // namespace sick::picoScan120::v2_2_1::api::rest
