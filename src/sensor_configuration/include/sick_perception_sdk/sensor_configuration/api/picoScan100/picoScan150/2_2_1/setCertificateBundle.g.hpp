/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file setCertificateBundle.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <string>

namespace sick::picoScan150::v2_2_1::api::rest {

/**
 * @brief Payloads for endpoint /setCertificateBundle.
*/
struct setCertificateBundle
{

  constexpr static const char* methodName = "setCertificateBundle";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Uploads a certificate bundle in the PEM format via JSON.

 This function requires at least user level: Service.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(std::string contentCertificateBundle, std::string contentPrivateKey)
        : _contentCertificateBundle(std::move(contentCertificateBundle)), _contentPrivateKey(std::move(contentPrivateKey))
      {}

      std::string _contentCertificateBundle;
      std::string _contentPrivateKey;
    };

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

}; // struct setCertificateBundle

} // namespace sick::picoScan150::v2_2_1::api::rest
