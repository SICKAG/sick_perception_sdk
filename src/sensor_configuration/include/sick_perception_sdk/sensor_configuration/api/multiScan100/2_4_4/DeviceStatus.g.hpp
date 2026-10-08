/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file DeviceStatus.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.4'.
 * Do not edit manually!
 */
#pragma once


namespace sick::multiScan100::v2_4_4::api::rest {

/**
 * @brief Payloads for endpoint /DeviceStatus.
*/
struct DeviceStatus
{

  constexpr static const char* variableName = "DeviceStatus";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the device state.
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

} // namespace sick::multiScan100::v2_4_4::api::rest
