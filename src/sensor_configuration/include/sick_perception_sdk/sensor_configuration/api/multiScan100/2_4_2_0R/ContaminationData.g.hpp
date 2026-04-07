/*
Copyright (c) 2026 SICK AG
SPDX-License-Identifier: MIT
*/

/**
 * @file ContaminationData.g.hpp Sensor REST API payload definitions.
 * @warning This file was generated for device 'multiScan100' version '2.4.2.0R'.
 * Do not edit manually!
 */
#pragma once


namespace sick::multiScan100::v2_4_2_0R::api::rest {

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

} // namespace sick::multiScan100::v2_4_2_0R::api::rest
