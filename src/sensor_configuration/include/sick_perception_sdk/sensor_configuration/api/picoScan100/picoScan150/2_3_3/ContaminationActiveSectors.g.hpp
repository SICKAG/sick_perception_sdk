/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ContaminationActiveSectors.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once

#include <vector>

namespace sick::picoScan150::v2_3_3::api::rest {

/**
 * @brief Payloads for endpoint /ContaminationActiveSectors.
*/
struct ContaminationActiveSectors
{

  constexpr static const char* variableName = "ContaminationActiveSectors";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the active contamination sectors. Starts by the first sector at -138 degree and continues counterclockwise.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::vector<bool> ContaminationActiveSectors)
        : _ContaminationActiveSectors(ContaminationActiveSectors)
      {}

      std::vector<bool> _ContaminationActiveSectors;
    };

  }; // struct Get

}; // struct ContaminationActiveSectors

} // namespace sick::picoScan150::v2_3_3::api::rest
