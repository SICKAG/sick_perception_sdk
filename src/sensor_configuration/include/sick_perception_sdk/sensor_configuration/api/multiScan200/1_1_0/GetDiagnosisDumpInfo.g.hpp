/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file GetDiagnosisDumpInfo.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once


namespace sick::multiScan200::v1_1_0::api::rest {

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

      explicit Response(bool DiagDumpExists, int DiagDumpTimestamp)
        : _DiagDumpExists(DiagDumpExists), _DiagDumpTimestamp(DiagDumpTimestamp)
      {}

      bool _DiagDumpExists;
      int _DiagDumpTimestamp;
    };

  }; // struct Post

}; // struct GetDiagnosisDumpInfo

} // namespace sick::multiScan200::v1_1_0::api::rest
