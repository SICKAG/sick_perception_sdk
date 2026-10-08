/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ContaminationActiveSectors.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.4'.
 * Do not edit manually!
 */
#pragma once

#include <vector>

namespace sick::multiScan100::v2_4_4::api::rest {

/**
 * @brief Payloads for endpoint /ContaminationActiveSectors.
*/
struct ContaminationActiveSectors
{

  constexpr static const char* variableName = "ContaminationActiveSectors";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Element i is true, if the sector result i is included in the computation of the contamination results and false otherwise.
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

} // namespace sick::multiScan100::v2_4_4::api::rest
