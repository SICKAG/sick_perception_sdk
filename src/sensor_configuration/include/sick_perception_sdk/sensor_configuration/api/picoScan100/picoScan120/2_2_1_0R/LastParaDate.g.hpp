/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file LastParaDate.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan120' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <string>

namespace sick::picoScan120::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /LastParaDate.
*/
struct LastParaDate
{

  constexpr static const char* variableName = "LastParaDate";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the last date (e.g., 12.11.2024) when a permanent parameter save was executed.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::string LastParaDate)
        : _LastParaDate(std::move(LastParaDate))
      {}

      std::string _LastParaDate;
    };

  }; // struct Get

}; // struct LastParaDate

} // namespace sick::picoScan120::v2_2_1_0R::api::rest
