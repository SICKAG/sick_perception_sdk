/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file SoftReset.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once


namespace sick::multiScan200::v1_1_0::api::rest {

/**
 * @brief Payloads for endpoint /SoftReset.
*/
struct SoftReset
{

  constexpr static const char* methodName = "SoftReset";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Reboots the device. All non-saved parameters are lost.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(int ProcessorNbr)
        : _ProcessorNbr(ProcessorNbr)
      {}

      int _ProcessorNbr;
    };

  }; // struct Post

}; // struct SoftReset

} // namespace sick::multiScan200::v1_1_0::api::rest
