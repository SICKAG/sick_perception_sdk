/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file AutoStartMeasure.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once


namespace sick::multiScan200::v1_1_0::api::rest {

/**
 * @brief Payloads for endpoint /AutoStartMeasure.
*/
struct AutoStartMeasure
{

  constexpr static const char* variableName = "AutoStartMeasure";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns/sets the mode for automatic start of measurement after boot-up.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(bool AutoStartMeasure)
        : _AutoStartMeasure(AutoStartMeasure)
      {}

      bool _AutoStartMeasure;
    };

  }; // struct Get

  /**
   * @brief Returns/sets the mode for automatic start of measurement after boot-up.

 This function requires at least user level: Authorized Client.
   */
  struct Post
  {
    struct Request
    {
      Request() = default;

      explicit Request(bool AutoStartMeasure)
        : _AutoStartMeasure(AutoStartMeasure)
      {}

      bool _AutoStartMeasure;
    };

  }; // struct Post

}; // struct AutoStartMeasure

} // namespace sick::multiScan200::v1_1_0::api::rest
