/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file OrderNumber.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.2.1.0R'.
 * Do not edit manually!
 */
#pragma once

#include <string>

namespace sick::picoScan150::v2_2_1_0R::api::rest {

/**
 * @brief Payloads for endpoint /OrderNumber.
*/
struct OrderNumber
{

  constexpr static const char* variableName = "OrderNumber";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the order number (SICK part number).
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::string OrderNumber)
        : _OrderNumber(std::move(OrderNumber))
      {}

      std::string _OrderNumber;
    };

  }; // struct Get

}; // struct OrderNumber

} // namespace sick::picoScan150::v2_2_1_0R::api::rest
