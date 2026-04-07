/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file DeviceStatus.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /DeviceStatus.
*/
struct DeviceStatus
{

  constexpr static const char* variableName = "DeviceStatus";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the device state (9 possible states).
   */
  struct Get
  {
    struct Response
    {
      enum class DeviceStatus
      {
        DsUnknownstate = 0,
        DsStartup = 1,
        DsServicemode = 2,
        DsNormaloperation = 3,
        DsSuspendedoperation = 4,
        DsServicerecommended = 5,
        DsServicerequired = 6,
        DsRecoverableerror = 7,
        DsFatalerror = 8,
      };

      Response() = default;

      explicit Response(DeviceStatus DeviceStatus)
        : _DeviceStatus(DeviceStatus)
      {}

      DeviceStatus _DeviceStatus;
    };

  }; // struct Get

}; // struct DeviceStatus

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
