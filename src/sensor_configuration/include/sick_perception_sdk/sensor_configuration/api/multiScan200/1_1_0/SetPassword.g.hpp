/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file SetPassword.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once


namespace sick::multiScan200::v1_1_0::api::rest {

/**
 * @brief Payloads for endpoint /SetPassword.
*/
struct SetPassword
{

  constexpr static const char* methodName = "SetPassword";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Sets the password for the CoLa A/B interface only. For more details see https://github.com/SICKAG/sick_scan_rest_client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(int siUserLevel, int udiNewPassword)
        : _siUserLevel(siUserLevel), _udiNewPassword(udiNewPassword)
      {}

      int _siUserLevel;
      int _udiNewPassword;
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

} // namespace sick::multiScan200::v1_1_0::api::rest
