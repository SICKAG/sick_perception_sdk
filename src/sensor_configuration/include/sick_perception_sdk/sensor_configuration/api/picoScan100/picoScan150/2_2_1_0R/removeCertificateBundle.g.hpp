/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file removeCertificateBundle.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <string>

namespace sick::picoScan150::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /removeCertificateBundle.
*/
struct removeCertificateBundle
{

  constexpr static const char* methodName = "removeCertificateBundle";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Removes the uploaded certificate bundle.

 This function requires at least user level: Service.
   */
  struct Post
  {
    struct Response
    {
      struct errorCode
      {
        errorCode() = default;

        explicit errorCode(std::string error)
          : _error(std::move(error))
        {}

        std::string _error;
      };

      Response() = default;

      explicit Response(bool success, errorCode errorCode)
        : _success(success), _errorCode(errorCode)
      {}

      bool _success;
      errorCode _errorCode;
    };

  }; // struct Post

}; // struct removeCertificateBundle

} // namespace sick::picoScan150::v2_2_1_0R::api::rest
