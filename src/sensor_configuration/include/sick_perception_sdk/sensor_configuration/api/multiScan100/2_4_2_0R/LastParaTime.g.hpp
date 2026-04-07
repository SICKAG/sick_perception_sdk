/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LastParaTime.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once

#include <string>

namespace sick::multiScan100::v2_4_2_0R::api::rest {

/**
 * @brief Payloads for endpoint /LastParaTime.
*/
struct LastParaTime
{

  constexpr static const char* variableName = "LastParaTime";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the last time (e.g. 13:24) when a permanent parameter save was executed.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::string LastParaTime)
        : _LastParaTime(std::move(LastParaTime))
      {}

      std::string _LastParaTime;
    };

  }; // struct Get

}; // struct LastParaTime

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
