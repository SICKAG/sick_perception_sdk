/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file CreateParameterBackup.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <string>

namespace sick::picoScan150::v2_2_1::api::rest {

/**
 * @brief Payloads for endpoint /CreateParameterBackup.
*/
struct CreateParameterBackup
{

  constexpr static const char* methodName = "CreateParameterBackup";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Creates a parameter backup file on the device.

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

}; // struct CreateParameterBackup

} // namespace sick::picoScan150::v2_2_1::api::rest
