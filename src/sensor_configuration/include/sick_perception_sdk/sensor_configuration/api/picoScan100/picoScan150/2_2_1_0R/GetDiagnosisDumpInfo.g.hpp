/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file GetDiagnosisDumpInfo.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <cstdint>

namespace sick::picoScan150::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /GetDiagnosisDumpInfo.
*/
struct GetDiagnosisDumpInfo
{

  constexpr static const char* methodName = "GetDiagnosisDumpInfo";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Returns additional meta-information about the diagnostic file.
   */
  struct Post
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool DiagDumpExists, std::uint32_t DiagDumpTimestamp)
        : _DiagDumpExists(DiagDumpExists), _DiagDumpTimestamp(DiagDumpTimestamp)
      {}

      bool _DiagDumpExists;
      std::uint32_t _DiagDumpTimestamp;
    };

  }; // struct Post

}; // struct GetDiagnosisDumpInfo

} // namespace sick::picoScan150::v2_2_1_0R::api::rest
