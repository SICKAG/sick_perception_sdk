/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ContaminationData.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan200' version '1.1.0'.
 * Do not edit manually!
 */
#pragma once

#include <vector>

namespace sick::multiScan200::v1_1_0::api::rest {

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

      explicit Response(std::vector<int> ContaminationData)
        : _ContaminationData(ContaminationData)
      {}

      std::vector<int> _ContaminationData;
    };

  }; // struct Get

}; // struct ContaminationData

} // namespace sick::multiScan200::v1_1_0::api::rest
