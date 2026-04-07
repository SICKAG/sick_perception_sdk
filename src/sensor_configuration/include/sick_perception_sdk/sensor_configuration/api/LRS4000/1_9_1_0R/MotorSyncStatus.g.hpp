/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file MotorSyncStatus.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /MotorSyncStatus.
*/
struct MotorSyncStatus
{

  constexpr static const char* variableName = "MotorSyncStatus";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Check if PTP master and slave are synced.
   */
  struct Get
  {
    struct Response
    {
      enum class MotorSyncStatus
      {
        NoClockAndRotSync = 0,
        OnlyTimeSynced = 1,
        Synced = 2,
      };

      Response() = default;

      explicit Response(MotorSyncStatus MotorSyncStatus)
        : _MotorSyncStatus(MotorSyncStatus)
      {}

      MotorSyncStatus _MotorSyncStatus;
    };

  }; // struct Get

}; // struct MotorSyncStatus

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
