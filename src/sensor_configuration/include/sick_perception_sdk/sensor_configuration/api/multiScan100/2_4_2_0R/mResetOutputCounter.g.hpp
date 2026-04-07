/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file mResetOutputCounter.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once


namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /mResetOutputCounter.
*/
struct mResetOutputCounter
{

  constexpr static const char* methodName = "mResetOutputCounter";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Resets the counter for the outputs.

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

}; // struct mResetOutputCounter

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
