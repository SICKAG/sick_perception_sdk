/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file changePassword.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <string>
#include <vector>

namespace sick::multiScan200::v1_1_0::api::rest {

/**
 * @brief Payloads for endpoint /changePassword.
*/
struct changePassword
{

  constexpr static const char* methodName = "changePassword";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Sets the password for the REST interface. For more details see https://github.com/SICKAG/sick_scan_rest_client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(std::vector<int> encryptedMessage, std::string userLevel)
        : _encryptedMessage(encryptedMessage), _userLevel(std::move(userLevel))
      {}

      std::vector<int> _encryptedMessage;
      std::string _userLevel;
    };

    struct Response
    {
      enum class result
      {
        Success = 0,
        NotAccepted = 2,
        PwdNotChangable = 4,
        TimelockActive = 5,
      };

      Response() = default;

      explicit Response(result result)
        : _result(result)
      {}

      result _result;
    };

  }; // struct Post

}; // struct changePassword

} // namespace sick::multiScan200::v1_1_0::api::rest
