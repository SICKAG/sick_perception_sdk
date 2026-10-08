/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file httpsStatus.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.10.0'.
 * Do not edit manually!
 */
#pragma once

#include <string>

namespace sick::LRS4000::v1_10_0::api::rest {

/**
 * @brief Payloads for endpoint /httpsStatus.
*/
struct httpsStatus
{

  constexpr static const char* variableName = "httpsStatus";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the status of the HTTPS interface.
   */
  struct Get
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

      explicit Response(bool enabled, errorCode errorCode)
        : _enabled(enabled), _errorCode(errorCode)
      {}

      bool _enabled;
      errorCode _errorCode;
    };

  }; // struct Get

}; // struct httpsStatus

} // namespace sick::LRS4000::v1_10_0::api::rest
