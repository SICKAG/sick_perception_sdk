/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file PowerOnCnt.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once


namespace sick::multiScan200::v1_1_0::api::rest {

/**
 * @brief Payloads for endpoint /PowerOnCnt.
*/
struct PowerOnCnt
{

  constexpr static const char* variableName = "PowerOnCnt";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the number of power on cycles.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(int PowerOnCnt)
        : _PowerOnCnt(PowerOnCnt)
      {}

      int _PowerOnCnt;
    };

  }; // struct Get

}; // struct PowerOnCnt

} // namespace sick::multiScan200::v1_1_0::api::rest
