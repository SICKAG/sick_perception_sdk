/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ContaminationData.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'picoScan150' version '2.3.3'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>
#include <vector>

namespace sick::picoScan150::v2_3_3::api::rest {

/**
 * @brief Payloads for endpoint /ContaminationData.
*/
struct ContaminationData
{

  constexpr static const char* variableName = "ContaminationData";
  constexpr static const bool isSopasMethod = false;

  /**
   * @brief Returns the contamination state of all contamination sectors.
   */
  struct Get
  {
    struct Response
    {
      Response() = default;

      explicit Response(std::vector<std::uint8_t> ContaminationData)
        : _ContaminationData(ContaminationData)
      {}

      std::vector<std::uint8_t> _ContaminationData;
    };

  }; // struct Get

}; // struct ContaminationData

} // namespace sick::picoScan150::v2_3_3::api::rest
