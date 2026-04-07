/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file SoftReset.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <cstdint>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /SoftReset.
*/
struct SoftReset
{

  constexpr static const char* methodName = "SoftReset";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Reboots the device. All non-saved parameters are lost. This function requires the user level: Service.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(std::uint16_t ProcessorNbr)
        : _ProcessorNbr(ProcessorNbr)
      {}

      std::uint16_t _ProcessorNbr;
    };

  }; // struct Post

}; // struct SoftReset

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
