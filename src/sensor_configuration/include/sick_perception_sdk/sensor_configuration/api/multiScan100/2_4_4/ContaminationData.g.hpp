/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ContaminationData.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.4'.
 * Do not edit manually!
 */
#pragma once

#include <cstdint>
#include <vector>

namespace sick::multiScan100::v2_4_4::api::rest {

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

} // namespace sick::multiScan100::v2_4_4::api::rest
