/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file certificateBundleInfo.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once

#include <string>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /certificateBundleInfo.
*/
struct certificateBundleInfo
{

  constexpr static const char* variableName = "certificateBundleInfo";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns information about the uploaded certificate bundle.
   */
  struct Get
  {
    struct Response
    {
      struct certificatesItem
      {
        struct namesItem
        {
          namesItem() = default;

          explicit namesItem(std::string entry)
            : _entry(std::move(entry))
          {}

          std::string _entry;
        };

        certificatesItem() = default;

        explicit certificatesItem(std::vector<namesItem> names, std::string issuer, std::string subject, std::string serialNumber, std::string fingerprint, std::string validNotBefore, std::string validNotAfter)
          : _names(names), _issuer(std::move(issuer)), _subject(std::move(subject)), _serialNumber(std::move(serialNumber)), _fingerprint(std::move(fingerprint)), _validNotBefore(std::move(validNotBefore)), _validNotAfter(std::move(validNotAfter))
        {}

        std::vector<namesItem> _names;
        std::string _issuer;
        std::string _subject;
        std::string _serialNumber;
        std::string _fingerprint;
        std::string _validNotBefore;
        std::string _validNotAfter;
      };

      struct errorCode
      {
        errorCode() = default;

        explicit errorCode(std::string error)
          : _error(std::move(error))
        {}

        std::string _error;
      };

      Response() = default;

      explicit Response(std::string uuidBundle, std::vector<certificatesItem> certificates, errorCode errorCode)
        : _uuidBundle(std::move(uuidBundle)), _certificates(certificates), _errorCode(errorCode)
      {}

      std::string _uuidBundle;
      std::vector<certificatesItem> _certificates;
      errorCode _errorCode;
    };

  }; // struct Get

}; // struct certificateBundleInfo

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
