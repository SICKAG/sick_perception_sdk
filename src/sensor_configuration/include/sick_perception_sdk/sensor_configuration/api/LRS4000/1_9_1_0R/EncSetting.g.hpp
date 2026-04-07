/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file EncSetting.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.9.1.0R'.
 * Do not edit manually!
 *
 * @note This class represents the payload of a SOPAS method. Do not use in `write_variable()`!
 */
#pragma once


namespace sick::LRS4000::v1_9_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /EncSetting.
*/
struct EncSetting
{

  constexpr static const char* methodName = "EncSetting";
  constexpr static const bool isSopasMethod = true;

  /**
   * @brief Select the encoder type.
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
      };

      Request() = default;

      explicit Request(EncSetting EncSetting)
        : _EncSetting(EncSetting)
      {}

      EncSetting _EncSetting;
    };

  }; // struct Post

}; // struct EncSetting

} // namespace sick::LRS4000::v1_9_1_0R::api::rest
