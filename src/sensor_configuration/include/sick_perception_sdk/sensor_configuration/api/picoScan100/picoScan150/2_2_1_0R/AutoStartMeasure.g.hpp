/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file AutoStartMeasure.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::picoScan150::v2_2_1_0R::api::rest {

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

} // namespace sick::picoScan150::v2_2_1_0R::api::rest
