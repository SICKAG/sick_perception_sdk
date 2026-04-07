/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file SetPassword.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <cstdint>

namespace sick::picoScan150::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /SetPassword.
*/
struct SetPassword
{

  constexpr static const char* methodName = "SetPassword";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Sets the password for the CoLa A/B interface only. In this example the password for user level: Service (4) is set to - test - (integer value of the password hash - test -). For more details see  https://github.com/SICKAG/sick_scan_rest_client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(std::int8_t siUserLevel, std::uint32_t udiNewPassword)
        : _siUserLevel(siUserLevel), _udiNewPassword(udiNewPassword)
      {}

      std::int8_t _siUserLevel;
      std::uint32_t _udiNewPassword;
    };

    struct Response
    {
      Response() = default;

      explicit Response(bool bSuccess)
        : _bSuccess(bSuccess)
      {}

      bool _bSuccess;
    };

  }; // struct Post

}; // struct SetPassword

} // namespace sick::picoScan150::v2_2_1_0R::api::rest
