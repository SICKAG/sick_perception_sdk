/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file mStartMeasure.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once


namespace sick::multiScan200::v1_1_0::api::rest {

/**
 * @brief Payloads for endpoint /mStartMeasure.
*/
struct mStartMeasure
{

  constexpr static const char* methodName = "mStartMeasure";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Starts motor and measurement.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Response
    {
      enum class ErrorCode
      {
        SopasErrNoErr = 0,
        SopasErrStateChangeNotPermitted = 1,
      };

      Response() = default;

      explicit Response(ErrorCode ErrorCode)
        : _ErrorCode(ErrorCode)
      {}

      ErrorCode _ErrorCode;
    };

  }; // struct Post

}; // struct mStartMeasure

} // namespace sick::multiScan200::v1_1_0::api::rest
