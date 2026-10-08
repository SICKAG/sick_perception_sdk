/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EncSetting.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan150::v2_2_1::api::rest {

/**
 * @brief Payloads for endpoint /EncSetting.
*/
struct EncSetting
{

  constexpr static const char* variableName = "EncSetting";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the encoder mode (e.g. phase mode).
   */
  struct Get
  {
    struct Response
    {
      enum class EncSetting
      {
        TxOff = 0,
        TxIncrement1 = 1,
        TxDirPhase12 = 2,
        TxDirLevel12 = 3,
        TxFixVelocity = 4,
      };

      Response() = default;

      explicit Response(EncSetting EncSetting)
        : _EncSetting(EncSetting)
      {}

      EncSetting _EncSetting;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the encoder mode (e.g. phase mode).

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      enum class EncSetting
      {
        TxOff = 0,
        TxIncrement1 = 1,
        TxDirPhase12 = 2,
        TxDirLevel12 = 3,
        TxFixVelocity = 4,
      };

      Request() = default;

      explicit Request(EncSetting EncSetting)
        : _EncSetting(EncSetting)
      {}

      EncSetting _EncSetting;
    };

  }; // struct Post

}; // struct EncSetting

} // namespace sick::picoScan150::v2_2_1::api::rest
