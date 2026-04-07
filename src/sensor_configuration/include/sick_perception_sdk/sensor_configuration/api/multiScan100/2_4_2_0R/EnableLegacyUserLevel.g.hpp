/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EnableLegacyUserLevel.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once

#include <cstdint>
#include <sick_perception_sdk/sensor_configuration/api/NumericRange.hpp>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /EnableLegacyUserLevel.
*/
struct EnableLegacyUserLevel
{

  constexpr static const char* methodName = "EnableLegacyUserLevel";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Activates / deactivates a specific user level for the CoLa A/B interface.

 This function requires at least user level: Service.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(NumericRange<std::uint8_t, 0, 7, 0> userLevel, bool isEnabled)
        : _userLevel(std::move(userLevel)), _isEnabled(isEnabled)
      {}

      NumericRange<std::uint8_t, 0, 7, 0> _userLevel;
      bool _isEnabled;
    };

    struct Response
    {
      Response() = default;

      explicit Response(bool result)
        : _result(result)
      {}

      bool _result;
    };

  }; // struct Post

}; // struct EnableLegacyUserLevel

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
