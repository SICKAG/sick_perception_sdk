/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file CreateParameterBackup.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.4'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <string>

namespace sick::multiScan100::v2_4_4::api::rest {

/**
 * @brief Payloads for endpoint /CreateParameterBackup.
*/
struct CreateParameterBackup
{

  constexpr static const char* methodName = "CreateParameterBackup";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Creates a parameter backup file.

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

} // namespace sick::multiScan100::v2_4_4::api::rest
