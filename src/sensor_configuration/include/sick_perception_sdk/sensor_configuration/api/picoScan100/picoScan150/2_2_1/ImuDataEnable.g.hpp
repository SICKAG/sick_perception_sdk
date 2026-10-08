/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ImuDataEnable.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan150::v2_2_1::api::rest {

/**
 * @brief Payloads for endpoint /ImuDataEnable.
*/
struct ImuDataEnable
{

  constexpr static const char* variableName = "ImuDataEnable";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Enables/Disables IMU data streaming.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool ImuDataEnable)
        : _ImuDataEnable(ImuDataEnable)
      {}

      bool _ImuDataEnable;
    };

  }; // struct Get

  /**
   * @brief Enables/Disables IMU data streaming.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool ImuDataEnable)
        : _ImuDataEnable(ImuDataEnable)
      {}

      bool _ImuDataEnable;
    };

  }; // struct Post

}; // struct ImuDataEnable

} // namespace sick::picoScan150::v2_2_1::api::rest
