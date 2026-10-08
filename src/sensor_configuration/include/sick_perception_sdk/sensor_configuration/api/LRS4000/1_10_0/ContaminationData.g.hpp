/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ContaminationData.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'LRS4000' version '1.10.0'.
 * Do not edit manually!
 */
#pragma once

#include <array>
#include <cstdint>

namespace sick::LRS4000::v1_10_0::api::rest {

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

      explicit Response(std::array<std::uint8_t, 12> ContaminationData)
        : _ContaminationData(ContaminationData)
      {}

      std::array<std::uint8_t, 12> _ContaminationData;
    };

  }; // struct Get

}; // struct ContaminationData

} // namespace sick::LRS4000::v1_10_0::api::rest
